# Installation

## Dependencies

Arch Linux:
```bash
pacman -Sy mingw-w64-gcc mingw-w64-binutils
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

## Run

```bash
wine devilution.exe
```
