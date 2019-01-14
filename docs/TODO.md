### Comments
- `BUGFIX` known bugs in original (vanilla) code
- `/* */` block comments are things to be fixed/checked
- `FIX_ME` bad data

Code issues (incorrect code that still works)
- Critical sections should be constructors using `CCritSect`
- Some code uses macros such as `__ROL2__`
- Some functions/structures have incorrect signing (signed/unsigned BYTE)
