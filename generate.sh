#!/bin/bash

VERSION=1.0
PLATFORM="Linux-x64"

VERBOSE=0

for i in $* ; do
    term="-v"
    term1="--verbose"
    if [ $i == $term -o $i == $term1 ] ; then
        VERBOSE=1
        break
    fi
done

logVerbose() {
    if [ $VERBOSE == 1 ] ; then
        echo $1
    fi
}

createBinaryDirectory() {
    if [ ! -d ./$1 ]; then
        mkdir $1
        logVerbose "Created $1"
    fi
}

createBinaryDirectories() {
    startdir=$(pwd)
    rm -rf bin
    createBinaryDirectory "bin"
    cd bin
    createBinaryDirectory "$PLATFORM-$VERSION"
    cd $startdir
}

#1 depname
addLibrary() {
    cd dependencies/$1
    createBinaryDirectories
    echo "Validated binary directories for $1"
    cd ../..
}

addProject() {
    createBinaryDirectories
    echo "Validated binary directories for project"
}

#1 depname
#2 files to compile (array)
#3 source files location
#4 include directories rel to dependency location
#5 defines
compileLibrary() {
    echo "Compiling library $1..."
    cd dependencies/$1

    includesdirs=$4"[@]"
    includes=""
    for i in ${!includesdirs} ; do
        includes=$includes" -I$i"
    done

    definesarr=$5"[@]"
    defines=""
    for i in ${!definesarr} ; do
        defines=$defines" -D$i"
    done

    files=$2"[@]"
    for i in ${!files} ; do
        #  -c  | Does not compile into an executable
        #  -o  | Sets output of binary
        #  -g  | Enables debugging features
        name=$(basename $i)
        extension=${i##*.}
        g++ -c -obin/$PLATFORM-$VERSION/${name%.*}.o -g $defines $includes -fPIC $3$i
    done
    if [ $? != 0 ] ; then
        echo "Failed to generate, exiting"
        return
    fi
    echo "Creating library archive for library $1..."
    ar -rcs bin/$PLATFORM-$VERSION/$1.a bin/$PLATFORM-$VERSION/*.o
    ranlib bin/$PLATFORM-$VERSION/$1.a
    echo "Copying library to main so..."
    cp bin/$PLATFORM-$VERSION/$1.a ../../bin/$PLATFORM-$VERSION/$1.a
    cd ../..
}

compileLibraryc() {
    echo "Compiling library $1..."
    cd dependencies/$1

    includesdirs=$4"[@]"
    includes=""
    for i in ${!includesdirs} ; do
        includes=$includes" -I$i"
    done

    definesarr=$5"[@]"
    defines=""
    for i in ${!definesarr} ; do
        defines=$defines" -D$i"
    done

    files=$2"[@]"
    for i in ${!files} ; do
        #  -c  | Does not compile into an executable
        #  -o  | Sets output of binary
        #  -g  | Enables debugging features
        name=$(basename $i)
        extension=${i##*.}
        gcc -c -obin/$PLATFORM-$VERSION/${name%.*}.o -g $defines $includes -fPIC $3$i
    done
    if [ $? != 0 ] ; then
        echo "Failed to generate, exiting"
        return
    fi
    echo "Creating library archive for library $1..."
    ar -rcs bin/$PLATFORM-$VERSION/$1.a bin/$PLATFORM-$VERSION/*.o
    ranlib bin/$PLATFORM-$VERSION/$1.a
    echo "Copying library to main so..."
    cp bin/$PLATFORM-$VERSION/$1.a ../../bin/$PLATFORM-$VERSION/$1.a
    cd ../..
}

compileSaddle() {
    echo "Compiling project..."

    g++ -fPIC -shared -Wl,-soname,Saddle.so -o bin/$PLATFORM-$VERSION/Saddle.so -Wl,--push-state,--whole-archive bin/$PLATFORM-$VERSION/Saddlelibs.a -Wl,--pop-state
}

addProject

addLibrary imgui
addLibrary GLFW
addLibrary glad
cd dependencies/GLFW
GLFWFILES=(
    "src/x11_init.c"
	"src/x11_monitor.c"
	"src/x11_window.c"
	"src/xkb_unicode.c"
	"src/posix_module.c"
	"src/posix_time.c"
	"src/posix_thread.c"
	"src/glx_context.c"
	"src/egl_context.c"
	"src/osmesa_context.c"
	"src/linux_joystick.c"
)
cd ../..

GLFWDEFINES=(_GLFW_X11)
GLFWINCLUDES=(include/GLFW)

#compileLibraryc GLFW GLFWFILES "" GLFWINCLUDES GLFWDEFINES 1

cd

IMGUIFILES=(
        "*.cpp"
        "backends/imgui_impl_opengl3.h"
        "backends/imgui_impl_opengl3.cpp"
        "backends/imgui_impl_glfw.h"
        "backends/imgui_impl_glfw.cpp"
)

IMGUIDEFINES=()
IMGUIINCLUDES=("../GLFW/include")

compileLibrary imgui IMGUIFILES "" IMGUIINCLUDES IMGUIDEFINES 1

GLADFILES=(
        "glad.c"
)

GLADDEFINES=()
GLADINCLUDES=("include")

compileLibrary glad GLADFILES "src/" GLADINCLUDES GLADDEFINES 1

#compiling saddle
cd Saddle
for i in $(find src -name \*.cpp) ; do
    name=${i##*.}
    g++ -c -fPIC -obin/$PLATFORM-$VERSION/${name%.*}.o -g -DSDL_PLATFORM_LINUX -DSDL_BUILD_DLL -DSDL_DEBUG $i -I../dependencies/imgui -I../dependencies/imgui/backends -I../dependencies/GLFW/include -I../dependencies/glad/include
done
ar -rcs bin/$PLATFORM-$VERSION/Saddle.a bin/$PLATFORM-$VERSION/*.o
ranlib bin/$PLATFORM-$VERSION/Saddle.a
cp  bin/$PLATFORM-$VERSION/Saddle.a  ../bin/$PLATFORM-$VERSION/Saddle.a

cd ..

#optimise later
mkdir bin/$PLATFORM-$VERSION/tmp
cd bin/$PLATFORM-$VERSION/tmp
ar -x ../glad.a
ar -x ../GLFW.a
ar -x ../imgui.a
ar -x ../Saddle.a
cd ../
ar -qc Saddlelibs.a $(find tmp -name \*.o)
ranlib Saddlelibs.a
cd ../..
echo "Compiled libs into one lib"

compileSaddle
echo "Saddle compiled"
cd Run
createBinaryDirectories
for i in $(find src -name \*.cpp) ; do
    name=$(basename $i)
    g++ -c -obin/$PLATFORM-$VERSION/${name%.*}.o $i -DSDL_PLATFORM_LINUX -DSDL_DEBUG -I../Saddle/src -I../dependencies/GLFW/include -L. -L../dependencies/GLFW
done
echo "Compiled Run"
#clang++ -obin/$PLATFORM-$VERSION/run bin/$PLATFORM-$VERSION/Saddle.so bin/$PLATFORM-$VERSION/Run.o
cd ..
g++ -obin/$PLATFORM-$VERSION/run $(find Run/bin/$PLATFORM-$VERSION -name \*.o) bin/$PLATFORM-$VERSION/Saddle.so