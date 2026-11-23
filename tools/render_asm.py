"""Generate Source/render.asm from Source/render.cpp's compiler listings.

Diablo 1.09b's render object was assembled with MASM in OMF format (Rich header: one Cvtomf510 object, 72 compiled
objects). render.cpp is still the readable source; this script turns cl's listings of it into an .asm file that
MASM 6.15 assembles into the same bytes:
  - jumps written as "$+N" get the encoding size the compiler used (taken from the /FAc listing),
  - [r1+r2] operands are swapped (MASM uses the second register as the SIB base, cl the first),
  - the listing's explicit-segment branch is used and _TEXT is BYTE aligned (flat-model MASM forces DWORD;
    the original render code starts at an odd address),
  - "include listing.inc" is dropped.

Make the listings with the same flags as MakefileVC, e.g.
    cl <CFLAGS> /FA  /Fa render.asm Source/render.cpp
    cl <CFLAGS> /FAc /Fa render.cod Source/render.cpp
then run:  python tools/render_asm.py render.asm render.cod Source/render.asm
"""
import re, sys
asm, cod, out = sys.argv[1:4]
enc = []
_prev = ""
for _l in open(cod, newline="").read().replace("\r", "").split("\n"):
    _m = re.match(r"^\s+[0-9a-f]{5}\t((?:[0-9a-f]{2} ?)+)", _l)
    if re.search(r"\t\s*j\w+\t\s*(?:SHORT )?\$[+-]\d+", _l):
        enc.append(_m.group(1) if _m else _prev)   # continuation line: opcode bytes are on the line before
    _prev = _m.group(1) if _m else _prev
res = []; k = 0
for line in open(asm, newline="").read().split("\n"):
    m = re.match(r"^(\s+)(j\w+)\s+(?:SHORT\s+)?(\$[+-]\d+)(.*)$", line)
    if m:
        op = enc[k].split()[0]; k += 1
        size = "SHORT" if op in ("eb",) or re.match(r"^7[0-9a-f]$", op) else "NEAR PTR"
        line = f"{m.group(1)}{m.group(2)}\t{size} {m.group(3)}{m.group(4)}"
    if line.strip().lower() == "include listing.inc": continue
    # MASM takes the second register of [r1+r2] as the base, cl the first: swap so the SIB byte comes out the same
    if not line.lstrip().startswith(";"):
        line = re.sub(r"\[(e[a-ds][xpi]|e[sd]i|ebp)\+(e[a-ds][xpi]|e[sd]i|ebp)(?=[\]+-])", lambda m: m.group(0) if "esp" in m.group(0) else f"[{m.group(2)}+{m.group(1)}", line)
    # flat-model MASM forces _TEXT to DWORD alignment; the original render code is byte aligned
    # flat-model MASM forces _TEXT to DWORD alignment, but the original render code is byte aligned: take the
    # listing's explicit-segment branch (FLAT group + ASSUME) and declare _TEXT BYTE
    if line.strip() == "if @Version gt 510": line = "if 0"
    if re.match(r"^FLAT\tGROUP\b", line): continue   # FLAT is predefined (reserved) in MASM 6
    line = line.replace("_TEXT\tSEGMENT PARA USE32 PUBLIC 'CODE'", "_TEXT\tSEGMENT BYTE USE32 PUBLIC 'CODE'")
    res.append(line)
assert k == len(enc), (k, len(enc))
# 1.09b's render data came from TASM (scroll.asm .DATA): the variables are packed, byte aligned, in the data
# segment ahead of the masks, with an unused byte after the 2nd one and four unused dwords after the 4th
txt = "\n".join(res)
bss = re.search(r"\n_BSS\tSEGMENT\r?\n((?:_\w+\s+DD\s+01H DUP \(\?\)[^\n]*\n)+)_BSS\tENDS\r?\n", txt)
if bss:
    names = re.findall(r"^(_\w+)\s+DD", bss.group(1), re.M)
    assert names == ["_WorldBoolFlag", "_gdwCurrentMask", "_gpCelFrame", "_gpDrawMask"], names
    packed = ("\n_DATA\tSEGMENT\r\n_WorldBoolFlag DD 00H\r\n_gdwCurrentMask DD 00H\r\n\tDB\t00H\t\t\t\t\t; unused\r\n"
              "_gpCelFrame DD 00H\r\n_gpDrawMask DD 00H\r\n\tDD\t04H DUP (00H)\t\t\t; unused\r\n_DATA\tENDS\r\n")
    txt = txt[:bss.start()] + packed + txt[bss.end():]
    txt = txt.replace("_DATA\tSEGMENT DWORD USE32 PUBLIC 'DATA'", "_DATA\tSEGMENT BYTE USE32 PUBLIC 'DATA'", 1)
res = txt.split("\n")
res.insert(0, "; Generated from Source/render.cpp by tools/render_asm.py - edit render.cpp and regenerate\r")
open(out, "w", newline="").write("\n".join(res))
print(f"{out}: {k} relative jumps fixed")
