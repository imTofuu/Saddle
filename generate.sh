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
libs=""

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
        # -Wno | Disables warnings
        name=$(basename $i)
        extension=${i##*.}
        if [ $extension = "c" ] ; then
            clang -c -obin/$PLATFORM-$VERSION/${name%.*}.o -g $defines $includes -fPIC $3$i
        else
            clang++ -c -obin/$PLATFORM-$VERSION/${name%.*}.o -g $defines $includes -fPIC $3$i
        fi
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
    libs=$libs" $1.a"
    cd ../..
}

compileSaddle() {
    echo "Compiling project..."
    cd Saddle

    createBinaryDirectories

    for i in $(find . -name \*.cpp) ; do
        name=$(basename $i)
        clang++ -c -fPIC -obin/$PLATFORM-$VERSION/${name%.*}.o -DSDL_PLATFORM_LINUX -DSDL_BUILD_DLL -DSDL_DEBUG -I../dependencies/GLFW/include -I../dependencies/imgui -I../dependencies/imgui/backends -I../dependencies/glad/include $i
    done

    clang++ -o../bin/$PLATFORM-$VERSION/Saddle.so -Wl, ../bin/$PLATFORM-$VERSION/GLFW.a -Wl, ../bin/$PLATFORM-$VERSION/imgui.a -Wl, ../bin/$PLATFORM-$VERSION/glad.a -Wl, -shared $(find bin/$PLATFORM-$VERSION -name \*.o)
}

addProject

addLibrary imgui
addLibrary GLFW
addLibrary glad

GLFWFILES=(
    "x11_init.c"
    "x11_monitor.c"
    "x11_window.c"
    "xkb_unicode.c"
    "posix_module.c"
    "posix_time.c"
    "posix_thread.c"
    "glx_context.c"
    "egl_context.c"
    "osmesa_context.c"
    "linux_joystick.c"
)

GLFWDEFINES=(_GLFW_X11)
GLFWINCLUDES=()

compileLibrary GLFW GLFWFILES src/ GLFWINCLUDES GLFWDEFINES 1

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

compileSaddle
echo "Saddle compiled"
cd ..
clang++ -obin/$PLATFORM-$VERSION/run $(find Run/src -name \*.cpp) -Wl, bin/$PLATFORM-$VERSION/Saddle.so -ISaddle/src -DSDL_PLATFORM_LINUX -Idependencies/GLFW/include -Idependencies/GLFW -Ldependencies/GLFW
#clang++ -obin/$PLATFORM-$VERSION/run bin/$PLATFORM-$VERSION/Saddle.so bin/$PLATFORM-$VERSION/Run.o