#!/bin/bash

RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
WHITE="\033[0m"

PLATFORM="Linux-x64"
VERSION="1.0"
BINPATH=$PLATFORM-$VERSION

#-----------------------------------------------------------------------------\
# [ Functions ]                                                               |
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

generateBinFolders() {
    startdir=$(pwd)
    cd $1
    rm -rf cache
    rm -rf bin
    mkdir cache
    mkdir bin
    cd bin
    mkdir $BINPATH
    cd $startdir
}

# 1 Library name (for formatting)
# 2 Files to check
needsRebuild() {
    if [ ! -d cache ] ; then # Validate cache folder existence
        echo "Cache folder not found; rebuilding library $1"
        return 0 # Rebuild if cache folder doesn't exist
    fi

    
    files=$2"[@]"
    for file in ${!files} ; do # Loop through all the files to check
        tempChecksum=$(md5deep $file) # Get the checksum of the current file
        currentChecksum=0
        for i in $tempChecksum ; do # Get only the string before the space
            currentChecksum=$i
            break
        done
        # If a cached file with the name of the checksum of the current file exists
        if [ $(find cache -name $currentChecksum.cache | wc -l) -ne 0 ] ; then
            continue # Exit early
        fi

        echo "Cached file not found for file $file; Rebuilding library $1"
        return 0
    done

    return 1
}

# 1 Directory
# 2 Files to cache
cacheFiles() {
    startdir=$(pwd)
    cd $1
    files=$2"[@]"
    for i in ${!files} ; do
        for j in $(md5deep $i) ; do
            touch cache/$j.cache
            break
        done
    done
    cd $startdir
}

clearCache() {
    startdir=$(pwd)
    cd $1
    rm -rf cache
    mkdir cache
    cd $startdir
}

#-----------------------------------------------------------------------------\
# [ Generate binary directories ]                                             |
#-----------------------------------------------------------------------------/

printSection "Creating new library directories..."

useVsync=0

while getopts "cv" flag ; do
    case $flag in
        c) 
            clearCache dependencies/glad
            clearCache dependencies/GLFW
            clearCache dependencies/imgui
            clearCache Saddle
            clearCache Run
            clearCache .
        ;;
	    v)
            useVsync=1
	    ;;
    esac
done

if [ ! -d bin ] && [ ! -d bin/$BINPATH ] ; then
    generateBinFolders .
fi

printDone "Created new library directories"

#-----------------------------------------------------------------------------\
#  [ Generate individual libraries ]                                          |
#-----------------------------------------------------------------------------/

printSection "Generating libraries..."

# - glad ---------------------------------------------------------------------|

cd dependencies/glad # / dependencies/glad \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\|

GLADFILES=($(find src -type f))
needsRebuild glad GLADFILES
rebuild=$?
if [ $rebuild -ne 0 ]; then # If library does not need to be rebuilt
    printSuccess 1 0 "Using cached version of glad"
else
    echo "Generating glad library..."

    generateBinFolders . # Regenerate binary folders

    gcc -fPIC -c -obin/$BINPATH/glad.o src/glad.c -Iinclude # Compile source file
    ar -rc ../../bin/$BINPATH/libglad.a bin/$BINPATH/glad.o # Create static lib
    ranlib ../../bin/$BINPATH/libglad.a # Generate indexes

    # Check number of defined symbols created in static lib
    symbols=$(nm --defined-only --extern-only ../../bin/$BINPATH/libglad.a | wc -l)
    printSuccess $symbols 2 "Generated glad library" "Failed to generate glad library"
fi

cd ../.. # / Main \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|

# - GLFW ---------------------------------------------------------------------|

cd dependencies/GLFW # / dependencies/GLFW \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\|

GLFWFILES=(
    $(find src -type f)
    $(find include -type f)
)
needsRebuild GLFW GLFWFILES
rebuild=$?
if [ $rebuild -ne 0 ] ; then
    printSuccess 1 0 "Using cached version of GLFW"
else

    echo "Generating GLFW library..."

    generateBinFolders .

    rm -rf ../bin/GLFW
    mkdir ../bin/GLFW

    cmake -S . -B ../bin/GLFW
    success=$?

    cd ../bin/GLFW # / dependencies/bin/GLFW \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\|

    cmake --build .
    success=$(($success & $?))

    cp src/libglfw3.a ../../../bin/$BINPATH/libglfw3.a

    cd ../../GLFW # / dependencies/GLFW \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|

    printSuccess $success 1 "Generated GLFW library" "Failed to generate GLFW library"
fi

cd ../.. # / Main \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\|


# - imgui --------------------------------------------------------------------|

cd dependencies/imgui # / dependencies/imgui \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\|

IMGUIFILES=(
    $(find . -maxdepth 1 -name \*.cpp)
    $(find . -maxdepth 1 -name \*.h)
    "backends/imgui_impl_opengl3.cpp"
    "backends/imgui_impl_glfw.cpp"
)

needsRebuild imgui IMGUIFILES
rebuild=$?
if [ $rebuild -ne 0 ]; then
    printSuccess 1 0 "Using cached version of imgui"
else

    echo "Generating imgui library..."

    generateBinFolders .

    for i in ${IMGUIFILES[@]} ; do
        name=$(basename $i)
        extension=${name##*.}
        if [ $extension = "h" ] ; then
            continue
        fi
        g++ -std=c++11 -fPIC -c -obin/$BINPATH/${name%.*}.o $i -I../GLFW/include
    done
    ar -rc ../../bin/$BINPATH/libimgui.a $(find bin/$BINPATH -name \*.o)
    ranlib ../../bin/$BINPATH/libimgui.a

    symbols=$(nm --demangle --defined-only --extern-only ../../bin/$BINPATH/libimgui.a | wc -l)
    printSuccess $symbols 14 "Generated imgui library" "Failed to generate imgui library"
fi

cd ../.. # / Main \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|

#-----------------------------------------------------------------------------\
# [ Generate core library and binary ]                                        |
#-----------------------------------------------------------------------------/

printSection "Generate core library and binary..."

# - Saddle -------------------------------------------------------------------|

cd Saddle # / Saddle \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\|

SADDLEFILES=(
    $(find src -name \*.cpp)
    $(find src -name \*.h)
)
needsRebuild Saddle SADDLEFILES
rebuild=$?
if [ $rebuild -ne 0 ] ; then
    printSuccess 1 0 "Using cached version of Saddle"
else

    echo "Generating Saddle..."

    generateBinFolders .

    for i in $(find src -name \*.cpp) ; do
        name=$(basename $i)
        g++ -std=c++11 -fPIC -c -obin/$BINPATH/${name%.*}.o $i -I../dependencies/GLFW/include -I../dependencies/glad/include -I../dependencies/imgui -I../dependencies/imgui/backends -DSDL_PLATFORM_LINUX -DSDL_DEBUG -DSDL_USE_VSYNC=$useVsync
    done

    echo "Linking into single shared object..."

    g++ -std=c++11 -shared -L../bin/$BINPATH -o ../bin/$BINPATH/libSaddle.so $(find bin/$BINPATH -name \*.o) -Wl,--whole-archive -lglad -lglfw3 -limgui -Wl,--no-whole-archive

    printSuccess 1 0 "Generated Saddle library and linked into shared object"
fi

cd .. # / Main \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\|

# - Run ----------------------------------------------------------------------|

cd Run # / Run \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\|

RUNFILES=(
    $(find src -name \*.cpp)
    $(find src -name \*.h)
)

needsRebuild Run RUNFILES
rebuild=$?
if [ $rebuild -ne 0 ] ; then
    printSuccess 1 0 "Using cached version of Run"
else

    echo "Generating exectuable..."

    generateBinFolders .

    g++ -std=c++11 -o ../bin/$BINPATH/run $(find src -name \*.cpp) -L../bin/$BINPATH -L. -lSaddle -I../Saddle/src -I../dependencies/GLFW/include -DSDL_PLATFORM_LINUX -DSDL_DEBUG

    printSuccess 1 0 "Successfully generated executable"
fi

cd .. # / Main \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\|

cacheFiles dependencies/glad GLADFILES
cacheFiles dependencies/GLFW GLFWFILES
cacheFiles dependencies/imgui IMGUIFILES
cacheFiles Saddle SADDLEFILES
cacheFiles Run RUNFILES

while getopts "n" flag ; do
    case $flag in
        n)
            clearCache dependencies/glad
            clearCache dependencies/GLFW
            clearCache dependencies/imgui
            clearCache Saddle
            clearCache Run
        ;;
    esac
done

export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/home/tofu/Documents/Projects/Saddle/bin/$BINPATH"
bin/$BINPATH/run
