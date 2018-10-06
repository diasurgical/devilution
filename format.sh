#!/bin/bash

CPP_DONE="Source/doom.cpp Source/movie.cpp Source/pfile.cpp Source/player.cpp Source/plrmsg.cpp Source/sound.cpp Source/spells.cpp Source/tmsg.cpp"

for f in $CPP_DONE; do
	echo "Formatting $f"
	clang-format -style=file -i $f
done

H_DONE="enums.h structs.h"

for f in $H_DONE; do
	echo "Formatting $f"
	clang-format -style="{BasedOnStyle: webkit, AlignTrailingComments: true, AllowShortBlocksOnASingleLine: true, AllowShortFunctionsOnASingleLine: None, PointerAlignment: Right, AlignConsecutiveAssignments: true}" -i $f
done
