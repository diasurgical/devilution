# Devilution
Diablo devolved - magic behind the 1996 computer game

Reverse engineered by GalaXyHaXz in 2018

[Rough Draft] This readme will be updated and enhanced in the future

# Introduction
Diablo was everything but loved by Blizzard. The last update to the game was in 2001, and Blizzard stopped supporting/selling it altogether a few years ago. I took up a mission to fix this problem. Diablo was a game I played extensively as a teenager; but as time passed, it became harder to run the game on newer hardware. The lack of new content also took away from the re-playability. Modding has too many limitations and reversing the game initially sounded like far too much work.

Thankfully, there was a little oversight in 1998. Blizzard gave Diablo's source code to two developers: Synergestic Software (to create an expansion), and Climax Studios (to create a Playstation port). Now Sony of Japan has long been known for letting things slide in their QA department. Anything from prototypes to full source code (Beatmania) leaks, and Diablo was no exception. The Japanese port of Diablo was left with both a symbolic+map file, which contained a layout of everything in the game. This includes functions, data, structures, and more! Several beta versions of the port also leaked, which contain more revisions of these files.

To top it all off, a debug build of the PC version is contained right there on your Diablo disc! Hidden in DIABDAT.MPQ->D1221A.MPQ>DIABLO.EXE. This build contains the missing debug functions, as well as many assert strings giving away code information (and most of all file names). Combining these aspects not only makes reversing the game much easier, but it makes it far more accurate. File names, function names, and even line numbers will be fairly close to the real deal.

After four months of hard work, I present to you Devilution! Instead of seeing how Diablo evolved, we'll see it devolved!

# Purpose
Having the source code makes things much easier to maintain. For years mod-makers had to rely on tedious code editing and memory injection. A few even went even further and reversed a good chunk of the game (such as Belzebub/The Hell). The problem is that they never released their sources. Usually being a one-man job, they move on with their lives inevitably due to the amount of time/work required or lack of interest. This leaves people with a half-finished mod; one which had countless hours put into it, but left full of bugs and unfinished designs. So we're back to square one. I want something that can and *will* be preserved, one that can be passed from one developer to the next, without the mercy of any one person.

Even though the goal of Devilution is to recreate Diablo's source code, it can be forked to update, improve, and mod the all-time classic. As an example, I've uploaded a small mod which makes the UI much more like Diablo 2 in only a few hundred lines of code.

On top of all that, it allows us to understand and unlock secrets hidden within the game. When you began seeing holes in certain functions or enums, beta elements begin coming together. We can understand better various aspects removed or changed during development, such as cool spells/items removed from the Battle.net Beta and the Demo.

# Compiling
Development of Diablo began in 1995 on a DOS-based system, so it was likely compiled under Microsoft Visual C++ 2 or 4. The project is currently setup to compile with VC6, which is compatible with newer systems. Simply open up the project workspace and select compile, it takes a few seconds. Place the Diablo.exe in the directory where Diablo was installed. The source is based on patch 1.09b, so the installation will need to be upgraded to that version. If compiling with copy protection, the Diablo CD will need to be present; else, the DIABDAT.MPQ file found on the CD will need to be copied into the installation directory.

There are two configurations: Debug and Release. The Debug version will compile with functions I ported from the 12-21-96 debug release. Most of these are command-line options or in-game hotkeys (such as cheats and testing features).

There are currently three options defined in types.h. You can compile without copy protection, compile with debugger support, and compile with CPU throttling. The last option will sleep the main program loop to keep Diablo from using 100% CPU on modern computers.

# Contributing
Currently there are a few issues with the decompiled code. Most of them are outlined in the TODO file. If you wish to contribute, small changes to help fix as many issues possible until everything is perfect and identical to the original game. Currently only Diablo.exe has been reversed, I have not yet started on the other files. Those are:
- Battle.snp: code for battle.net, outdated protocol and not worth the time.
- DiabloUI.dll: code for the main menu, this is entirely Windows specific and poorly written. However, it needs to be reversed to complete the source code.
- SmackW32.dll: code for the Smacker video library, not worth the time.
- Standard.snp: code for local multiplayer, again outdated. Starcraft uses the same format and TCP/IP was added in a later patch. Reversing the UDP portion is desired.
- Storm.dll: we want Diablo to be independent of this library, the main file functions have been reversed as part of StormLib.
- VidSize.exe: changes one byte in registry, ignore.

If you are experienced with reversing, help is needed to document and decompile the user interface (DiabloUI) to help make Diablo cross-platform.

# Modding
Here are some screenshots of a few things I tinkered around with, to demonstrate what can be achieved.

Screenshot 1: Monster life https://postimg.cc/image/xgmizy2h9/

Screenshot 2: New trade screen https://postimg.cc/image/nw2wd2kv1/

# Credits
- mewmew - documenting the Windows-specific Diablo code (engine, mpq, directx)
- Ladislav Zezula - decompiling PKWARE library
- fearedbliss - being awe-inspiring
- Climax Studios - basically giving out an intermediate source code
- Blizzard North - wait, this was a typo!
- Depression - reason to waste four months of my life doing this ;)

# Legal
This work is being released to the Public Domain. No assets of Diablo are being provided. You must own a copy of Diablo and have access to the assets beforehand in order to use this software.

Copyright (c) 1996 BLIZZARD ENTERTAINMENT, All rights reserved

Diablo and Battle.net are trademarks and Blizzard Entertainment is a trademark of Davidson and Associates, Inc.
