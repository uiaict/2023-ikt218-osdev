#!/bin/bash

echo "\nConfiguring\n"

/usr/bin/cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++ -S group_27 -B build_group_27 -G "Unix Makefiles"

echo "\nBuilding\n"

/usr/bin/cmake --build build_group_27 --config Debug --target uia-os-kernel -j 10 --

yes Ignore | /usr/bin/cmake --build build_group_27 --config Debug --target uia-os-create-image -j 10 --
