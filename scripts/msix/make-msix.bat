mkdir build
cd build
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
cmake -DCMAKE_BUILD_TYPE=Release -DWXT_PORTABLE_EDITION:BOOL=OFF -G "NMake Makefiles" ../../../
cmake clean
cmake --build . --target all
cmake --build . --target %1_msix
