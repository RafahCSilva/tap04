#!/usr/bin/env bash

## Compile
echo " :: URI1362 :: "
g++ src/uri1362.cpp -o src/uri1362.exe -std=c++11 -O2 -lm
./src/uri1362.exe < test/uri1362_in.txt
echo "==================="
cat test/uri1362_out.txt

echo
echo
echo " :: URI1330 :: "
g++ src/uri1330.cpp -o src/uri1330.exe -std=c++11 -O2 -lm
./src/uri1330.exe < test/uri1330_in.txt
echo "==================="
cat test/uri1330_out.txt

echo
echo
echo " :: URI1056 :: "
g++ src/uri1056.cpp -o src/uri1056.exe -std=c++11 -O2 -lm
./src/uri1056.exe < test/uri1056_in.txt
echo "==================="
cat test/uri1056_out.txt

echo
echo
echo " :: URI1331 :: "
g++ src/uri1331.cpp -o src/uri1331.exe -std=c++11 -O2 -lm
./src/uri1331.exe < test/uri1331_in.txt
echo "==================="
cat test/uri1331_out.txt
