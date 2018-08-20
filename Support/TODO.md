### Comments
- `BUG_FIX` known bugs in original (vanilla) code
- `/* */` block comments are things to be fixed/checked
- `FIX_ME` bad data

### Known Bugs
Serious bugs (crash/fault)
- TBA

Minor bugs (noticeable but can be avoided)
- Lighting of objects/items in dungeon is slightly lighter than it should be
- Some tiles are drawn fully lit when they should be transparent `world.cpp`
- Timed messages are broken and have been disabled `tmsg.cpp`
- Server commands are broken and have been disabled `msgcmd.cpp`

Code issues (incorrect code that still works)
- Critical sections should be constructors using `CCritSect`
- Function `DRLG_L4TransFix`, decompile and check (Test: seed `2349839` level 13)
- Some code uses macros such as `__PAIR__` or `__ROL4__`, or `__int64`
- Some functions/structures have incorrect signing (signed/unsigned BYTE)
- Function `GetLevelMTypes`, decompile and check `monster.cpp`
- Function `SetAutomapView`, decompile and check `automap.cpp`
- Function `engine_draw_automap_pixels`, decompile and check `engine.cpp`
- Double check `UseMana` references
- Double check `LOBYTE` of function `random(int, int)`
