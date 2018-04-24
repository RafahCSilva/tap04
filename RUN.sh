#!/usr/bin/env bash

## Compile
#g++ src/uri1362.cpp -o src/uri1362.exe -std=c++11
#./src/uri1362.exe < test/uri1362_in.txt

#./cmake-build-debug/uri1362 < test/uri1362_in.txt


g++ src/uri1362.cpp -o src/uri1362.exe -std=c++11 -O2 -lm
./src/uri1362.exe < test/uri1362_in.txt
