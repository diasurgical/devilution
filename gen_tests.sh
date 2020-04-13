#!/bin/bash

echo "Building testgen.exe"
make -f MakefileVC testgen

echo "Writing test cases to testdata/"
mkdir -p testdata
wine testgen.exe
