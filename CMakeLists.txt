cmake_minimum_required(VERSION 3.7)

include(CMake/out_of_tree.cmake)

project(devilutionX
  VERSION 0.0.1
  LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

option(ASAN "Enable address sanitizer" ON)
option(DEBUG "Enable debug mode in engine" ON)

list(APPEND CMAKE_MODULE_PATH "${devilutionX_SOURCE_DIR}/CMake")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if(NOT CMAKE_SIZEOF_VOID_P EQUAL 4)
  message(WARNING "sizeof(void*) == ${CMAKE_SIZEOF_VOID_P}.")
  message(WARNING [[Not 32-bit, highly experimental!]])
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(sodium REQUIRED)

set(SOURCES
  Source/appfat.cpp
  Source/automap.cpp
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
  Source/effects.cpp
  Source/encrypt.cpp
  Source/engine.cpp
  Source/error.cpp
  Source/gamemenu.cpp
  Source/gendung.cpp
  Source/gmenu.cpp
  Source/help.cpp
  Source/interfac.cpp
  Source/inv.cpp
  Source/items.cpp
  Source/lighting.cpp
  Source/loadsave.cpp
  Source/mainmenu.cpp
  Source/minitext.cpp
  Source/missiles.cpp
  Source/monster.cpp
  Source/mpqapi.cpp
  Source/msgcmd.cpp
  Source/msg.cpp
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
  Source/render.cpp
  Source/scrollrt.cpp
  Source/setmaps.cpp
  Source/sha.cpp
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

  3rdParty/PKWare/explode.cpp
  3rdParty/PKWare/implode.cpp)

# Stubbed out sources, for reference
set(ORIGINAL_SOURCES
  Source/capture.cpp
  Source/dx.cpp
  Source/fault.cpp
  Source/init.cpp
  Source/logging.cpp
  Source/movie.cpp
  Source/restrict.cpp
  Source/sound.cpp)

set(STUB_SOURCES
  Stub/capture.cpp
  Stub/dx.cpp
  Stub/fault.cpp
  Stub/init.cpp
  Stub/miniwin.cpp
  Stub/miniwin_io.cpp
  Stub/miniwin_msg_sdl.cpp
  Stub/miniwin_rand.cpp
  Stub/miniwin_thread.cpp
  Stub/movie.cpp
  Stub/restrict.cpp
  Stub/sound.cpp
  Stub/storm.cpp
  Stub/storm_net.cpp

  Stub/dvlnet/loopback.cpp
  Stub/dvlnet/packet.cpp
  Stub/dvlnet/base.cpp
  Stub/dvlnet/frame_queue.cpp
  Stub/dvlnet/tcp_client.cpp
  Stub/dvlnet/tcp_server.cpp
  Stub/dvlnet/udp_p2p.cpp

  Stub/DiabloUI/credits.cpp
  Stub/DiabloUI/diabloui.cpp
  Stub/DiabloUI/dialogs.cpp
  Stub/DiabloUI/mainmenu.cpp
  Stub/DiabloUI/progress.cpp
  Stub/DiabloUI/selconn.cpp
  Stub/DiabloUI/selgame.cpp
  Stub/DiabloUI/selhero.cpp
  Stub/DiabloUI/title.cpp

  Stub/main.cpp

  3rdParty/libsmacker/smk_bitstream.c
  3rdParty/libsmacker/smk_hufftree.c
  3rdParty/libsmacker/smacker.c

  3rdParty/Radon/Radon/source/File.cpp
  3rdParty/Radon/Radon/source/Key.cpp
  3rdParty/Radon/Radon/source/Named.cpp
  3rdParty/Radon/Radon/source/Section.cpp

  3rdParty/StormLib/src/FileStream.cpp
  3rdParty/StormLib/src/SBaseCommon.cpp
  3rdParty/StormLib/src/SBaseFileTable.cpp
  3rdParty/StormLib/src/SBaseSubTypes.cpp
  3rdParty/StormLib/src/SCompression.cpp
  3rdParty/StormLib/src/SFileExtractFile.cpp
  3rdParty/StormLib/src/SFileFindFile.cpp
  3rdParty/StormLib/src/SFileGetFileInfo.cpp
  3rdParty/StormLib/src/SFileOpenArchive.cpp
  3rdParty/StormLib/src/SFileOpenFileEx.cpp
  3rdParty/StormLib/src/SFileReadFile.cpp)

add_executable(devilution ${SOURCES} ${STUB_SOURCES})
target_link_libraries(devilution PRIVATE SDL2::SDL2main SDL2::SDL2_ttf SDL2::SDL2_mixer sodium)
target_include_directories(devilution PRIVATE . Stub 3rdParty/asio/include)
target_compile_definitions(devilution PRIVATE
  ASIO_STANDALONE
  MINIWIN
  "$<$<BOOL:${DEBUG}>:_DEBUG>"
  # Skip fades and other fluff
  FASTER)

# Enable ASAN in Debug mode
if(ASAN)
  target_compile_options(devilution PRIVATE "$<$<CONFIG:Debug>:-fsanitize=address;-fsanitize-recover=address>")
  target_link_libraries(devilution PRIVATE "$<$<CONFIG:Debug>:-fsanitize=address;-fsanitize-recover=address>")
endif()

# Note: In Debug mode, GCC generates spurious memory references that upset Valgrind,
# these options fix that.
target_compile_options(devilution PRIVATE $<$<CONFIG:Debug>:-fno-omit-frame-pointer>)

# Ignore serious warnings due to "quality" of decompiled code
target_compile_options(devilution PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-fpermissive> -Wno-write-strings -Wno-multichar)
# Disable optimizations that can break non-standards-conforming code
target_compile_options(devilution PRIVATE -fno-aggressive-loop-optimizations -fno-strict-aliasing)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # Style issues
  target_compile_options(devilution PRIVATE -Wno-parentheses -Wno-logical-op-parentheses -Wno-bitwise-op-parentheses)
  # Silence warnings about __int64 alignment hack not always being applicable
  target_compile_options(devilution PRIVATE -Wno-ignored-attributes)
  # Fix: error: cast from pointer to smaller type 'unsigned char' loses information
  target_compile_options(devilution PRIVATE -fms-extensions)
endif()
