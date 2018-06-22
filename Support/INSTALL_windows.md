# Installation

## Dependencies

* Install [MSYS2](https://www.msys2.org/)

```bash
# Start the *MSYS2 MinGW 32-bit* terminal.
pacman -Sy git make mingw-w64-i686-gcc mingw-w64-i686-binutils
ln -s /mingw32/i686-w64-mingw32/bin/dlltool.exe /usr/bin/i686-w64-mingw32-dlltool.exe
ln -s /mingw32/i686-w64-mingw32/bin/as.exe /usr/bin/i686-w64-mingw32-as.exe
```

## Building

```bash
git clone https://github.com/galaxyhaxz/devilution
cd devilution
cp /path/to/diablo_game_dir/diabloui.dll .
cp /path/to/diablo_game_dir/storm.dll .
make
```

## Install

```bash
cp devilution.exe /path/to/diablo_game_dir/
```
