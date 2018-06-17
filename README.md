# Devilution
Diablo devolved - magic behind the 1996 computer game

Reverse engineered by GalaXyHaXz in 2018

# Introduction
Diablo was everything but loved by Blizzard. The last update to the game was in 2001, and Blizzard stopped supporting/selling it altogether a few years ago. I took up a mission to fix this problem. Diablo was a game I played extensively as a teenager; but as time passed, it became difficult to run the game on newer hardware. The lack of new content also took away from the re-playability. The ideal solution would be to modernize the source, but reversing the whole game initially sounded impossible.

Thankfully, there was a little oversight in 1998. Blizzard gave Diablo's source code to two developers: Synergestic Software (to create an expansion), and Climax Studios (to create a Playstation port). Now Sony of Japan has long been known for letting things slide in their QA department. Anything from prototypes to full source code leaks (Beatmania), and Diablo was no exception. A symbolic file was accidentally left on the Japanese port, which contained a layout of everything in the game. This includes functions, data, types, and more! A beta version of the port also leaked, which contained yet another one of these files.

To top it all off, a debug build of the PC version is contained right there on your Diablo disc! Hidden in `DIABDAT.MPQ -> D1221A.MPQ -> DIABLO.EXE`. This build contains debug tools not found in the retail game, and many assert strings giving away code information. Combining these aspects not only makes reversing the game much easier, but it makes it far more accurate. File names, function names, and even line numbers will be fairly close to the real deal.

After four months of hard work, I present to you Devilution! Instead of seeing how Diablo evolved, we'll see it devolved!

# Purpose
Having the source code makes things much easier to maintain. For years mod-makers had to rely on tedious code editing and memory injection. A few even went even further and reversed a good chunk of the game (such as Belzebub/The Hell). The problem is that they never released their sources. Usually being a one-man job, they move on with their lives inevitably due to the amount of time/work required or lack of interest. This leaves people with a half-finished mod; one which had countless hours put into it, but left full of bugs and unfinished potential. So we're back to square one. Devilution aims to fix this, by making the source code of Diablo freely available to all.

The goal of Devilution itself is to recreate the original source code as accurately as possible, in order to ensure that everything is preserved. This goes as far as bugs and badly written code in the original game. However, it becomes a solid base for developers to work with; making it much easier than before to update, fix, and port the game to other platforms.

As a side goal, Devilution helps document the unused and cut content from the final game. Development of Diablo was rushed near the end--many ideas were scrapped and Multiplayer was quickly hacked in. By examining the source, we can see various quirks of planned development.

# Compiling
Development of Diablo began around the time Windows 95 released, for which is was optimized. The compiler used was Microsoft Visual C++ 4.20, which was upgraded to 5.10 in later patches ([ref: spreadsheet](Surgery/sdk.xls)). Compatibility with these tools is retained to help ensure the reversal is as accurate as possible. There are also Makefiles provided to compile with modern tools as well.

Building with Visual C++ 5.10
- Make sure Service Pack 3 is installed in order to update the linker from 5.00 -> 5.10! Newer versions of Visual Studio work as well, but will upgrade the project.
- Open the project workspace "Diablo.dsw" and select "Build Diablo.exe". This will build all dependencies and only takes a few seconds.

Building with MinGW(32/64)
- Ensure that the MinGW binary paths have been added to the command line.
- For MinGW32, navigate to the project root and execute "mingw32-make -f Makefile32". The process will take longer than Visual Studio.
- For MinGW64, refer to the respective documentation: [Linux](INSTALL_linux.md) | [Windows](INSTALL_windows.md). Note that only x86 systems may be targeted for the time being.

Compiling Definitions
- `COPYPROT` (default: on) will define whether or not to use the CD drive for DIABDAT.MPQ
- `DEBUGGER` (default: off) will define whether to skip reloading for direct execution through debuggers
- `SLEEP` (default: off) will define whether to sleep the program to prevent 100% CPU usage
- `_DEBUG` (default: off) will define whether to include debug features (refer to 'Debugging' section)

# Debugging
There are debug features available through both in-game and through the command-line. These have been ported from the 12-21-96 debug build. Note that not all of them are available yet.

Command-line parameters
- `-^` : enable god mode and debug tools
- `-$` : enable god mode with less stuff (further documenting needed) [NOT YET IMPLEMENTED]
- `-b` : enables item drop log [NOT YET IMPLEMENTED]
- `-d` : disable startup video + increased item drops [PARTIALLY IMPLEMENTED]
- `-f` : display frames per second
- `-i` : disable network timeout
- `-n` : disable startup video
- `-s` : unused
- `-v` : draw yellow debug tiles
- `-w` : enable cheats
- `-x` : disable exclusive DirectDraw access [NOT YET IMPLEMENTED]
- `-j <##>` : init trigger at level [NOT YET IMPLEMENTED]
- `-l <#> <##>` : start in level as type
- `-m <###>` : add debug monster, up to 10 allowed
- `-q <#>` : force a certain quest
- `-r <##########>` : set map seed to
- `-t <##>` : sets current quest level

In-game hotkeys
- `?` -> start quest text mode (`-`/`_`, `+`/`=`, and `Enter` to use) [NOT YET IMPLEMENTED]
- `Esc` -> stop quest text mode [NOT YET IMPLEMENTED]
- `0`/`)` -> cycle through active item flags [NOT YET IMPLEMENTED]
- `8`/`*` -> level up character
- `~` -> refresh vendor items (Griswold premium and Adria)
- `]` -> all spells level 10
- `:` -> all spells preset level
- `[` -> delete all gold in inventory
- `|` -> fill inventory with gold (5000 piece piles)
- `.` -> display dungeon Y/sum [NOT YET IMPLEMENTED]
- `a` -> increase level of the last spell casted
- `A` -> display "Mid" monster related
- `d` -> print debug player info
- `D` -> switch current debug player
- `e` -> display "EFlag"
- `l`/`L` -> toggle lighting in dungeon [NOT YET IMPLEMENTED]
- `m` -> print debug monster info
- `M` -> switch current debug monster
- `r`/`R` -> display game seeds
- `t`/`T` -> display player and cursor coordinates

# Contributing
Currently there are a few issues with the decompiled code. The focus should be on fixing these issues for now instead of cleaning up the code. Currently only Diablo.exe has been reversed, the other files are:
- `Battle.snp`: code for battle.net, outdated protocol and not worth the time.
- `DiabloUI.dll`: code for the main menu, this is entirely Windows specific and poorly written. However, it needs to be reversed to complete the source code.
- `SmackW32.dll`: code for the Smacker video library, not worth the time.
- `Standard.snp`: code for local multiplayer, again outdated. Starcraft uses the same format and TCP/IP was added in a later patch. Reversing the UDP portion is desired.
- `Storm.dll`: we want Diablo to be independent of this library, the main file functions have been reversed as part of StormLib.
- `VidSize.exe`: changes one byte in registry, ignore.

If you are experienced with reversing, help is needed to reverse the user interface (DiabloUI) to help make Diablo cross-platform.

# Modding
Here are some screenshots of a few things I tinkered around with, to demonstrate the relative ease of improving the game:

![Screenshot 1: Monster lifebar+items](https://s33.postimg.cc/6xnnhhlmn/diabuimon.png "Monster lifebar+items")

![Screenshot 2: New trade screen](https://s22.postimg.cc/z8fhuutk1/diabstore.png "New trade screen")

# Credits
- [sanctuary](https://github.com/sanctuary) - documenting the Windows-specific Diablo code (engine, mpq, directx)
- [BWAPI Team](https://github.com/bwapi) - providing library API to work with Storm
- [Ladislav Zezula](https://github.com/ladislav-zezula) - decompiling PKWARE library, decompiling Storm (StormLib)
- [fearedbliss](https://github.com/fearedbliss) - being awe-inspiring
- Climax Studios & Sony - secretly helping with their undercover QA :P
- Blizzard North - wait, this was a typo!
- Depression - reason to waste four months of my life doing this ;)

# Legal
This work is being released to the Public Domain. No assets of Diablo are being provided. You must own a copy of Diablo and have access to the assets beforehand in order to use this software.

Battle.net(R) - Copyright (C) 1996 Blizzard Entertainment, Inc. All rights reserved. Battle.net and Blizzard Entertainment are trademarks or registered trademarks of Blizzard Entertainment, Inc. in the U.S. and/or other countries.

Diablo(R) - Copyright (C) 1996 Blizzard Entertainment, Inc. All rights reserved. Diablo and Blizzard Entertainment are trademarks or registered trademarks of Blizzard Entertainment, Inc. in the U.S. and/or other countries.

This software is in no way associated with or endorsed by Blizzard Entertainment(R).
