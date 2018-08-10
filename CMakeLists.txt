cmake_minimum_required(VERSION 3.10)

project(devilution VERSION 1.09 LANGUAGES C CXX)

SET(DEVILUTION_SRC
Source/appfat.cpp
Source/automap.cpp
Source/capture.cpp
Source/codec.cpp
Source/control.cpp
Source/cursor.cpp
Source/dead.cpp
Source/debug.cpp
Source/diablo.cpp
Source/doom.cpp
Source/drlg_l1.cpp
Source/drlg_l2.cpp
Source/drlg_l3.cpp
Source/drlg_l4.cpp
Source/dthread.cpp
Source/dx.cpp
Source/effects.cpp
Source/encrypt.cpp
Source/engine.cpp
Source/error.cpp
Source/fault.cpp
Source/gamemenu.cpp
Source/gendung.cpp
Source/gmenu.cpp
Source/help.cpp
Source/init.cpp
Source/interfac.cpp
Source/inv.cpp
Source/items.cpp
Source/lighting.cpp
Source/loadsave.cpp
Source/logging.cpp
Source/mainmenu.cpp
Source/minitext.cpp
Source/missiles.cpp
Source/monster.cpp
Source/movie.cpp
Source/mpqapi.cpp
Source/msg.cpp
Source/msgcmd.cpp
Source/multi.cpp
Source/nthread.cpp
Source/objects.cpp
Source/pack.cpp
Source/palette.cpp
Source/path.cpp
Source/pfile.cpp
Source/player.cpp
Source/plrmsg.cpp
Source/portal.cpp
Source/quests.cpp
Source/restrict.cpp
Source/scrollrt.cpp
Source/setmaps.cpp
Source/sha.cpp
Source/sound.cpp
Source/spells.cpp
Source/stores.cpp
Source/sync.cpp
Source/textdat.cpp
Source/themes.cpp
Source/tmsg.cpp
Source/town.cpp
Source/towners.cpp
Source/track.cpp
Source/trigs.cpp
Source/wave.cpp
Source/world.cpp

3rdParty/PKWare/explode.cpp
3rdParty/PKWare/implode.cpp
)

add_subdirectory(3rdParty/Storm)
add_subdirectory(DiabloUI)

add_executable(devilution WIN32  ${DEVILUTION_SRC})
target_compile_definitions(devilution PRIVATE _CRT_SECURE_NO_WARNINGS)
target_link_libraries(devilution diabloui Storm version)
