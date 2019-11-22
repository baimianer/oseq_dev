#!/bin/bash

rm -rf include lib

cd htslib
make clean
cd -

rm -f sam_read_example
