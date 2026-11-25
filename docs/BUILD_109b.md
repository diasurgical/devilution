# Building Diablo 1.09b byte for byte

The `match-109b` branch builds a `Diablo.exe` that is identical to Blizzard's retail Diablo 1.09b
(May 2001):

| | md5 |
|---|---|
| retail `Diablo.exe` 1.09b | `da62d5cd8bd71a0b66e6d4ef7a111233` |
| built from this branch | `da62d5cd8bd71a0b66e6d4ef7a111233` |

All 1883 functions are byte-identical, addresses included; `.text`, `.data`, `.rdata`, `.rsrc` and the header
(Rich header included) match. Three bytes, the import hints of SHELL32's three functions, match only because a
local copy of `shell32.lib` has those hints set by hand; see [Open items](#open-items).

This document records how to build it, what we learned about the toolchain, which parts of the source are
educated stand-ins, and what is still open.

## Build

```
tools/build_109b.sh DDK_LIB_DIR MSVCRT_DIR IMPLODE_LIB
```

The script checks the inputs, prepares the `shell32.lib` stand-in, copies the tree to `../build-109b`, runs a
clean `make -f MakefileVC` in the Riivaaja image (`diasurgical/riivaaja:stable`, Wine) and compares the result with
the retail hash. It needs docker, rsync and python3 and takes about ten seconds. Exit status: 0 identical,
1 different, 2 build failed.

### Inputs that cannot be distributed

They stay on the machine that builds; never commit them.

| Input | Source | md5 |
|---|---|---|
| `kernel32.lib` `user32.lib` `gdi32.lib` `advapi32.lib` `shell32.lib` `version.lib` | Windows DDK, October 2000, x86 **free** build libraries (cab `X86DLIBF`), LIB 5.12.9049. The checked build has other USER32 hints. | kernel32 `f7f75585293e590a710ad9869af8e8df`, user32 `763b198a091d9b2a342adf1971b72ed7`, gdi32 `680eed309e815e0391db1a26a8113801`, advapi32 `8a84764a9694e74d04d9bfa3fff65b76`, version `f05052fd9e7df3fc6856c25f17632f5a`, shell32 `9d8164851fad77b36799f2d958ad8222` |
| `MSVCRT.DLL` | Visual C++ 5.0 redistributable (`VC/REDIST` on the Visual Studio 97 discs) | `2ed73c4f9be8e3866693ec6aff06f26a` |
| `IMPLODE.LIB` | PKWARE Data Compression Library, as linked by 1.09b | `020f66163bbb02638cebd106e7160e55` |

`MakefileVC` takes them as `DDK_LIB_DIR`, `MSVCRT_DIR` and `PKWARE_LIB`; `PE_TIMESTAMP=1` writes 1.09b's link time
into the header. Without these options the build still works, but uses Devilution's PKWARE code, Wine's own
`qsort` and the current time, and differs from retail.

## Toolchain

Every entry of the retail Rich header is reproduced with the same tool build and object count.

| Stage | Tool | Notes |
|---|---|---|
| C++ front end | C1XX.DLL 11.00.7303 (VC 5.0 SP3) | loaded by VC6 `cl.exe` with `/Bx` |
| Back end | c2.dll 13.00.9044 (VC6 Processor Pack) | Rich `0x30 b9044 ×72` |
| Linker | LINK 5.10.7303 (VC 5.0) | run next to Microsoft's `MSVCRT.DLL` (copied into `vc5link/` by the makefile) |
| Import libraries | LIB 5.12.9049 | Rich `0x13 b9049 ×12`: six DLLs, two descriptor objects each |
| C runtime | VC 5.0 `libcmt.lib` | linked before `kernel32.lib` |
| Renderer | MASM, from `render.cpp` via `tools/render_asm.py` | 1.09b's was TASM (`scroll.asm`); the OMF object is converted by the linker (Rich `0x03 b7303 ×1`) |
| Resources | RC + CVTRES | Rich `0x06 b1668` |
| Storm, DiabloUI | import libraries only | the DLLs are Blizzard's |

## What made it match

These are the rules VC5 and LINK 5.10 follow, worked out from the retail binary, small test programs and the
linker's `/verbose` output.

### Compiler

- **C1. Uninitialised globals are ordered by name hash.** In each object's `.bss`, uninitialised globals come first,
  in VC5's name-hash order (a shared bucket keeps declaration order). Globals with an initialiser (`= 0`) or a dynamic
  initialiser follow in definition order; a function static with an initialiser joins them at the function's
  position. Used for `sgdwOwnerWait`, `save_prev_tc = 0`, `sgdwMsgCmdTimer = 0`, `msg_err_timer = 0`, `sgbTrackMode`,
  the player frame-size globals and storm.h's per-file `sginfinity`.
- **C2. Structures of 64 bytes or more are 8-aligned, integer tables are not.** This also raises the section's
  alignment. `Qtalklist` and `ChrBtnPos` became plain `int` arrays.
- **C3. Externals and string literals come out in reverse order of use** within a function; functions follow file
  order, and a `static` function is compiled right after its first caller. Used for the `"Steel Tome"` case and the
  `"AS"/"ST"`, `"AW"/"WL"` pairs in `InitPlrGFXMem`.
- **C4. Sums are regrouped but keep a trace of the source order.** The first `int` term gets its own register, the
  others are added in reverse source order. Term order was restored in `MonsterMHit`, `Plr2PlrMHit`,
  `DrawSpellBook`, `BreakObject`, the armor sums, `AddTown`, the L1 doors, `ResyncQuests` and `NextItemRecord`;
  the meaning is unchanged.
- **C5. Switch case bodies are laid out in source order.** Fixed in `ProcessMonsters`, `STextEnter`,
  `CreateThemeRooms` and `ProcessTowners`.
- **C6. A register tie depends on the declarations seen.** `SpawnHealer` matches only with a narrower include list in
  `items.cpp` (Blizzard's list, in `all.h` order), not with `all.h`.
- **C7. Template members defined in the class are emitted breadth-first, in class order.** `list.h` defines its
  members in the class with `Insert` before `UnlinkAll`, and `EXTERNMESSAGE::Delete` comes from a template base, so
  `msgcmd`'s list functions appear in 1.09b's order.
- **C8. TASM encodings.** TASM wrote `cmp ax, imm` as `66 3D iw`; `render_asm.py` emits those 78 compares as raw
  bytes. Render data is packed and byte-aligned as in `scroll.asm`.

### Linker

- **L1. Import order comes from an unstable sort in MSVCRT.** LINK 5.10 sorts import thunks with `qsort` from
  `MSVCRT.DLL`. Wine's `qsort` is a different algorithm and gives another order; Microsoft's DLL reproduces 1.09b.
  Wine takes a native DLL only from the program's folder, hence `vc5link/`.
- **L2. Dropped functions still count.** With `/O1` each function is a COMDAT and `/OPT:REF` drops unused ones, but
  their references still decide the order in which libraries load members. 1.09b's `diablo.cpp` had an unused
  `FlushMsgs` (present in Hellfire); an unused helper in `logging.cpp` puts `_vsnprintf` before `_snprintf`.
- **L3. Identical-code folding depends on every function, dropped ones included.** Which copy `/OPT:ICF` keeps changes
  when any function is added. 1.09b keeps the C runtime's `initcoll`, `aw_cmp`, `explode` and `initnum` copies;
  14 unused placeholder functions at the end of `wave.cpp` reproduce that (count found by search).
- **L4. Load order.** Library members load by the first object referencing them, then by that object's symbol order.
  `libcmt.lib` comes before `kernel32.lib`.
- **L5. Header.** The Rich header lists tools in object order, so `diablo.res` goes before `render.obj`. The time
  stamp is 0x3B05AC00 (2001-05-18 23:10:56 UTC).

### Data

- **D1.** Most `.data`/`.rdata` work restored 1.09b's declarations: `const`-ness, named `static char` arrays for all
  250 texts in `textdat.cpp`, constants kept in `.rdata` (`extern const`), and Blizzard's names (from Hellfire) where
  they decide the hash order.

## Placeholders to review

They reproduce the layout without evidence for their real form; each is commented in the source.

| What | File | Why | Evidence |
|---|---|---|---|
| `zzdummy0` … `zzdummy13` | wave.cpp | identical-code folding (L3); count tuned by search | none |
| `log_vprintf_unused` | logging.cpp | references `_vsnprintf` early (L2) | none |
| `FlushMsgs` | diablo.cpp | USER32 import order (L2) | Hellfire source |
| `sgnLFrame`, `sgnWFrame`, `sgnGfxFlag` | player.cpp | names chosen to hash into place (C1) | names invented |
| `sgnTurnCnt`, `hfArchive`, `gbMomParent`, `gbSaveActive` | multi.cpp, init.cpp | names chosen to hash into place | names invented |
| `sgdwUnused1`–`5`, `help_unused[0x46C]`, `multi_unused` | diablo.cpp, help.cpp, multi.cpp | space the original reserves | size only |
| `TDeletable`, in-class `list.h` | msgcmd.cpp, list.h | template emission order (C7) | structure guessed |
| `items.cpp` include list | items.cpp | `SpawnHealer` register tie (C6) | Hellfire include list |
| `shell32.lib` hints | local library | three hints set by `tools/mk_shell32_hints.py` | stand-in |

The placeholder functions are the most fragile part: adding or removing any function can change which copies the
linker keeps. If the C runtime stops matching after a change, search for a new placeholder count before suspecting
the change itself.

## Behaviour changes against Devilution

| Change | File | 1.09b | Devilution before |
|---|---|---|---|
| Diablo's armor class | monstdat.cpp | 70 | 90 |
| Scroll used up by `RemoveScroll` | inv.cpp | matches `_pSpell` | matched `_pRSpell` |
| `level_seeds` size | debug.cpp | `NUMLEVELS` (BUGFIX comment kept) | `NUMLEVELS + 1` |
| Save error text | pfile.cpp | "Unable to write to save file archive" | "… write so save …" |

## Open items

1. **The real `shell32.lib`.** Needed: LIB 5.12.9049, with `ShellExecuteA` hint 140, `SHGetSpecialFolderLocation` 102,
   `SHGetPathFromIDListA` 99. Ruled out: Windows DDK October 2000 (135/97/94, free and checked), Windows 2000 Beta 3
   DDK, Windows XP DDK 2600 (152, made by LIB 7.0), Visual Studio 6 (114). Likely a Windows Me DDK or a 2000–2001
   Platform SDK.
2. **Storm, DiabloUI and the network providers are not built from source.** `Storm.dll` 1.09b is whole in the 1.09b
   patch; `DiabloUI.dll`, `standard.snp` and `battle.snp` are only deltas there.
3. **Not yet played.** Under Wine the exe starts, loads Storm and DiabloUI and shows 1.09b's "insert the Diablo CD"
   dialog; Wine did not present a CD-ROM in our tests. Since the bytes are identical, behaviour should equal retail;
   confirm on Windows, in a VM, or with the CD image mounted as a real CD.
4. **The identical-code folding rule is not modelled.** Modelling the linker's sort could replace the tuned
   placeholders with something principled.
5. **Other configurations untested.** Only retail 1.09b was built after these changes; Hellfire, Spawn, debug and the
   GCC/CMake builds were not.
6. **Analysis tools** (`devcmp`, `datamap`, call-order and operand comparisons, the folding search) are not in this
   repository yet.
