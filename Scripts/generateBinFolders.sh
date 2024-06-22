#!/bin/bash

startdir=$(pwd)
cd $1

rm -rf cache
rm -rf bin
mkdir cache
mkdir bin
cd bin
mkdir $2
cd $startdir