[![Build Status](https://travis-ci.org/galaxyhaxz/devilution.svg?branch=master)](https://travis-ci.org/galaxyhaxz/devilution)

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
Development of Diablo began around the time Windows 95 released, for which it was optimized. The compiler used was Microsoft Visual C++ 4.20, which was upgraded to 5.10 in later patches ([ref: spreadsheet](Support/linker.xls)). Compatibility with these tools is retained to help ensure the reversal is as accurate as possible. There are also Makefiles provided to compile with modern tools as well.

Building with Visual C++ 5.10
- Make sure Service Pack 3 is installed in order to update the linker from 5.00 -> 5.10! Newer versions of Visual Studio work as well, but will upgrade the project.
- Open the project workspace `Diablo.dsw` and select `Build Diablo.exe`. This will build all dependencies and only takes a few seconds.

Building with MinGW(32/64)
- Ensure that the MinGW binary paths have been added to the command line. On Windows, you would usually type: `set PATH=C:\mingw\bin;C:\mingw\msys\1.0\bin`
- For MinGW32, navigate to the project root and execute `make MINGW32=1`. The process will take longer than Visual Studio.
- For MinGW64, refer to the respective documentation: [Linux](Support/INSTALL_linux.md) | [Windows](Support/INSTALL_windows.md) | [Mac](Support/INSTALL_mac.md). Note that only x86 systems may be targeted for the time being.

Compiling Definitions
- `COPYPROT` (default: on) will define whether or not to use the CD drive for DIABDAT.MPQ
- `DEBUGGER` (default: off) will define whether to skip reloading for direct execution through debuggers
- `SLEEP` (default: off) will define whether to sleep the program to prevent 100% CPU usage
- `_DEBUG` (default: off) will define whether to include debug features (refer to [Debugging Document](Support/debug.md))

# Installing
Once compiled, the Devilution binary will serve as a replacement for `Diablo.exe`. A clean installation of Diablo patched to 1.09(b) is needed to run the game. Either copy Devilution into Diablo's installation folder, or make sure the following files are present:
- `DIABDAT.MPQ` : if `COPYPROT` was defined, then the Diablo CD will be required
- `DiabloUI.dll` : provides module for the title screen interface
- `SmackW32.dll` : provides library for playing Smacker video files
- `Standard.snp` : provides local multiplayer code (Modem/IPX/Serial, Starcraft version adds TCP/IP)
- `Storm.dll` : provides various "standard" functions

To run the game in windowed mode, a DirectDraw wrapper will be needed. Strange Bytes' [DirectDraw patch](http://www.strangebytes.com/index.php/projects/1-diablo-1-windows-7-vista-patch) is recommended. To install, place the `ddraw.dll` into the same location as the Devilution binary.

# Troubleshooting
While Devilution should produce a binary close to the original (compatible with Windows 95/NT), it may cause issues on newer systems. It has been reported to frequently crash on some setups, although for many it appears to be running flawless otherwise. Windows 7, Linux-WINE, and Windows 10 have all reported success.

Note that newer compilers may need to be tweaked to properly produce an executable. Currently this is being worked on to provide multiple Makefiles for a variety of systems. To ensure the best results, either MinGW or Visual Studio 2003/older should be used for the time being.

# F.A.Q.
> Wow, does this mean I can download and play Diablo for free now?

No, you'll need access to the data from the original game. Blizzard has discontinued Diablo, but there's plenty of used copies floating around. (I'm still using an original 1996-disc in 2018 without problems)
> Cool, so I fired your mod up, but there's no 1080p or new features?

Devilution aims to keep the original code unaltered, for documentation purposes.
> So will you ever add cross-platform support or new features in the future?

Yes! However, this will be a **_side project_** based on Devilution. I have yet to announce the project.
> When and what can I expect from the upcoming project?

Honestly I have no idea. More than 1,200 hours went into creating Devilution, and I have other things going on right now. Maybe in 6-12 months? The goal is to create a native Linux port, convert to OpenGL, modernize the UI, etc. you get the drill. There has to be some surprises. ;)
> Ok, so I'm playing Devilution now and all the sudden it crashed. NOW WHAT??

Try to remember as many details about the crash as possible. Inside the Diablo folder should be a log file containing crash information. Open an issue, upload the log, and provide as much information as possible (OS version, etc.).
> I thought I'd fix the crash myself, but after looking at the code its a disaster. Do you speak v2-34-v8?

That is the result of decompiled code. Whenever a program is compiled, much of the source is optimized and stripped away, so it's nearly impossible to decompile it back. Have patience. Everything will be cleaned up eventually. :)
> Will you be reverse engineering Diablo II next? Ooooh please!

Absolutely not. Diablo II is still supported, sold, and maintained by Blizzard. Setting the legal implications aside, there's about 8x as much code, and a chance Blizzard will remaster the game soon anyway. (as of 2018)
> Are you interested in working for me? I have this game I want you to reverse...

Sorry, but no. Money takes the passion out of it. Forgoing that, Diablo was an exception given that symbolic information was readily available. Even then it took countless hours to pick apart such a tiny game.
> I think that's about all, but is Devilution even legal?

That's a tricky question. Under the DMCA, reverse-engineering has exceptions for the purpose of documentation and interoperability. Devilution provides the necessary documentation needed to achieve the latter. However, it falls into an entirely grey area. The real question is whether or not Blizzard deems it necessary to take action.

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
