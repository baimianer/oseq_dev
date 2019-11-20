#!/bin/bash

mkdir -p include
mkdir -p lib

cd htslib
make clean
make
cp htslib/* ../include
cp libhts.a ../lib
cd -

gcc main.c -I include/ -L lib/ -lhts -llzma -lbz2 -lz -lpthread -o sam_read_example
