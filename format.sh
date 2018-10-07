#!/bin/bash

ROOT=`pwd`

CPP_DONE="doom.cpp movie.cpp pfile.cpp player.cpp plrmsg.cpp sound.cpp spells.cpp tmsg.cpp"

cd ${ROOT}/Source
for f in $CPP_DONE; do
	echo "Formatting $f"
	clang-format -style=file -i $f
done

H_DONE="enums.h structs.h"

cd ${ROOT}
for f in $H_DONE; do
	echo "Formatting $f"
	clang-format -style=file -i $f
done
