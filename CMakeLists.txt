cmake_minimum_required(VERSION 3.5)

# Turn on modern `try_compile()` policies.
if(POLICY CMP0066)
    cmake_policy(SET CMP0066 NEW)
endif()
if(POLICY CMP0067)
    cmake_policy(SET CMP0067 NEW)
endif()

include(CMake/out_of_tree.cmake)

# This *must* be included before calling `project()`, due to setting early compiler flags.
if($ENV{FORCE32})
    include(CMake/32bit.cmake)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(devilutionX
    VERSION 0.0.1
    LANGUAGES C CXX
)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${devilutionX_SOURCE_DIR}/CMake")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

if($ENV{FORCE32})
    if(NOT CMAKE_SIZEOF_VOID_P EQUAL 4)
        message(WARNING "sizeof(void*) == ${CMAKE_SIZEOF_VOID_P}.")
        message(FATAL_ERROR [[32-bit mode was requested but pointer size is not 32 bits.]])
    endif()
endif()

# Note: In Debug mode, GCC generates spurious memory references that upset Valgrind,
# these options fix that.
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fno-omit-frame-pointer")
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address -fsanitize-recover=address")

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)

set(SOURCES
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
    3rdParty/PKWare/implode.cpp
)

# Stubbed out sources, for reference
set(ORIGINAL_SOURCES
    Source/capture.cpp
    Source/appfat.cpp
    Source/dthread.cpp
    Source/dx.cpp
    Source/fault.cpp
    Source/init.cpp
    Source/logging.cpp
    Source/movie.cpp
    Source/nthread.cpp
    Source/restrict.cpp
    Source/sound.cpp
)

set(STUB_SOURCES
    Stub/miniwin.cpp
    Stub/miniwin_rand.cpp
    Stub/appfat.cpp
    Stub/capture.cpp
    Stub/dthread.cpp
    Stub/dx.cpp
    Stub/fault.cpp
    Stub/init.cpp
    Stub/movie.cpp
    Stub/nthread.cpp
    Stub/restrict.cpp
    Stub/sound.cpp
    Stub/storm.cpp
    Stub/diabloui.cpp
    Stub/miniwin_io.cpp
    Stub/miniwin_msg_sdl.cpp
    Stub/storm_net.cpp
#   Stub/validate.cpp
    Stub/sdlrender.cpp

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
    3rdParty/StormLib/src/SFileReadFile.cpp
)

include(CMake/SDL2_fixed.cmake)

include_directories(${SDL2_INCLUDE_DIRS}
                    ${SDL2_MIXER_INCLUDE_DIR})

include_directories(. Stub)

# FUTURE: use add_compile_definitions()
add_definitions(
    -D_DEBUG
    -DMINIWIN
    # Skip fades and other fluff
    -DFASTER
)

# Ignore serious warnings due to "quality" of decompiled code
add_compile_options(-fpermissive -Wno-write-strings -Wno-multichar)
# Disable optimizations that can break non-standards-conforming code
add_compile_options(-fno-aggressive-loop-optimizations -fno-strict-aliasing)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # Style issues
    add_compile_options(-Wno-parentheses -Wno-logical-op-parentheses -Wno-bitwise-op-parentheses)
    # Silence warnings about __int64 alignment hack not always being applicable
    add_compile_options(-Wno-ignored-attributes)
    # Fix: error: cast from pointer to smaller type 'unsigned char' loses information
    add_compile_options(-fms-extensions)
endif()

add_executable(devilution
    ${SOURCES}
    ${STUB_SOURCES}
    Stub/main.cpp
)

target_link_libraries(devilution PUBLIC
    m
    ${SDL2_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
)

# xxhash fast hashing library
add_library(xxhash STATIC 3rdParty/xxhash/xxhash.c)
set_source_files_properties(3rdParty/xxhash/xxhash.c PROPERTIES LANGUAGE CXX)
target_include_directories(xxhash PUBLIC 3rdParty/xxhash)
target_compile_options(xxhash PRIVATE -O3 -fno-pie -fno-pic)
