#!/bin/bash

# if build directory exists, remove it
if [ -d "build" ]; then
    rm -rf build
fi

mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DWXT_GENERATE_MSIX:BOOL=OFF -G "Ninja" ../../../
cmake --build . --target all
cmake --build . --target wxTools-appimage