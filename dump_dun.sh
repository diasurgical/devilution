#!/bin/bash

TILES_BIN_NAME=dlvl=1,quest_id=255,seed=7281,setlvl=0_tiles.bin
TILES_BIN_PATH=testdata/${TILES_BIN_NAME}
DUN_NAME=${TILES_BIN_NAME/.bin/.bin.dun}
DUN_FROM=testdata/${DUN_NAME}
DUN_TO=testdata/levels/l1data/${DUN_NAME}

./cmd/viewdun/viewdun ${TILES_BIN_PATH}
mkdir -p testdata/levels/l1data
mv ${DUN_FROM} ${DUN_TO}
dun_dump ${DUN_TO}
