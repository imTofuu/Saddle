#!/bin/bash

RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
WHITE="\033[0m"

PLATFORM="Linux-x64"
VERSION="1.0"
BINPATH=$PLATFORM-$VERSION

#-----------------------------------------------------------------------------\
# [ Formatting functions ]                                                    |
#-----------------------------------------------------------------------------/

printDone() {
    echo -e "[${GREEN}DONE${WHITE}] $1"
}

# 1 Value
# 2 Fail value
# 3 Success message
# 4 Failed message
printSuccess() {
    if [ $1 != $2 ] ; then
        echo -e "[${GREEN}DONE${WHITE}] $3"
    else
        echo -e "[${RED}FAILED${WHITE}] $4"
        exit 1
    fi
}

printSection() {
    echo -e "[${YELLOW}SECTION${WHITE}] $1"
}

#-----------------------------------------------------------------------------\
# [ Generate binary directories ]                                             |
#-----------------------------------------------------------------------------/

printSection "Creating new library directories..."

Scripts/generateBinFolders.sh dependencies/imgui $BINPATH # - imgui ----------|
Scripts/generateBinFolders.sh Saddle $BINPATH # ------------- Saddle ---------|
Scripts/generateBinFolders.sh Run $BINPATH # ---------------- Run ------------|
Scripts/generateBinFolders.sh . $BINPATH # ------------------ Main -----------|

printDone "Created new library directories"

#-----------------------------------------------------------------------------\
#  [ Generate individual libraries ]                                          |
#-----------------------------------------------------------------------------/

printSection "Generating libraries..."

# - glad ---------------------------------------------------------------------|

cd dependencies/glad # / dependencies/glad \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\|


newChecksum=""
cachedChecksum="0"
if [ -d cache ] ; then
    tar cvf cache/cache.tar src

    for i in $(md5deep cache/cache.tar) ; do
        newChecksum=$i
        break
    done
    for i in $(basename $(find cache -name \*.cache)) ; do
        cachedChecksum=${i%.*}
        break
    done
    rm -rf cache/cache.tar
fi
echo $newChecksum
echo $cachedChecksum


if [ $newChecksum == $cachedChecksum ] ; then
    printSuccess 1 0 "Using cached version of glad"
else
    echo "Generating glad library..."

    ../../Scripts/generateBinFolders.sh . $BINPATH

    gcc -fPIC -c -obin/$BINPATH/glad.o src/glad.c -Iinclude
    ar -rc ../../bin/$BINPATH/libglad.a bin/$BINPATH/glad.o
    ranlib ../../bin/$BINPATH/libglad.a

    symbols=$(nm --demangle --defined-only --extern-only ../../bin/$BINPATH/libglad.a | wc -l)
    printSuccess $symbols 2 "Generated glad library" "Failed to generate glad library"

    tar cWf cache/cache.tar .
    rm -rf cWf cache/cache.tar
    touch cache/$(md5deep cache/cache.tar)
fi

cd ../.. # / Main \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|

# - GLFW ---------------------------------------------------------------------|

echo "Generating GLFW library..."

rm -rf dependencies/bin/GLFW
mkdir dependencies/bin/GLFW

cd dependencies/GLFW # / dependencies/GLFW \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\|

cmake -S . -B ../bin/GLFW
success=$?

cd ../bin/GLFW # / dependencies/bin/GLFW \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\|

cmake --build .
success=$(($success & $?))

cp src/libglfw3.a ../../../bin/$BINPATH/libglfw3.a

printSuccess $success 1 "Generated GLFW library" "Failed to generate GLFW library"

cd ../../.. # / Main \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\|

# - imgui --------------------------------------------------------------------|

echo "Generating imgui library..."

cd dependencies/imgui # / dependencies/imgui \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\|

FILES=(
    $(find . -maxdepth 1 -name \*.cpp)
    "backends/imgui_impl_opengl3.h"
    "backends/imgui_impl_opengl3.cpp"
    "backends/imgui_impl_glfw.h"
    "backends/imgui_impl_glfw.cpp"
)

for i in ${FILES[@]} ; do
    name=$(basename $i)
    g++ -fPIC -c -obin/$BINPATH/${name%.*}.o $i -I../GLFW/include
done
ar -rc ../../bin/$BINPATH/libimgui.a $(find bin/$BINPATH -name \*.o)
ranlib ../../bin/$BINPATH/libimgui.a

symbols=$(nm --demangle --defined-only --extern-only ../../bin/$BINPATH/libimgui.a | wc -l)
printSuccess $symbols 14 "Generated imgui library" "Failed to generate imgui library"

cd ../.. # / Main \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|

#-----------------------------------------------------------------------------\
# [ Generate core library and binary ]                                        |
#-----------------------------------------------------------------------------/

printSection "Generate core library and binary..."

# - Saddle -------------------------------------------------------------------|

echo "Generating Saddle..."

for i in $(find Saddle/src -name \*.cpp) ; do
    name=$(basename $i)
    g++ -fPIC -c -oSaddle/bin/$BINPATH/${name%.*}.o $i -Idependencies/GLFW/include -Idependencies/glad/include -Idependencies/imgui -Idependencies/imgui/backends -DSDL_PLATFORM_LINUX -DSDL_DEBUG
done

echo "Linking into single shared object..."

g++ -shared -Lbin/$BINPATH -o bin/$BINPATH/libSaddle.so $(find Saddle/bin/$BINPATH -name \*.o) -Wl,--whole-archive -lglad -lglfw3 -limgui -Wl,--no-whole-archive

printSuccess 1 0 "Generated Saddle library and linked into shared object"

# - Run ----------------------------------------------------------------------|

echo "Generating exectuable..."

g++ -o bin/$BINPATH/run $(find Run/src -name \*.cpp) -Lbin/$BINPATH -L. -lSaddle -ISaddle/src -Idependencies/GLFW/include -DSDL_PLATFORM_LINUX -DSDL_DEBUG

printSuccess 1 0 "Successfully generated executable"

./run