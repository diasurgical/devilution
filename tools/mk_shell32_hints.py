"""Stand-in until the real library turns up: copy of the DDK Oct 2000 free-build shell32.lib (LIB 5.12.9049) with the
hints of the three imports Diablo 1.09b uses set to the values in its import table. Local use only.
usage: mk_shell32_hints.py IN.lib OUT.lib"""
import struct, sys
HINTS = {"ShellExecuteA": 140, "SHGetSpecialFolderLocation": 102, "SHGetPathFromIDListA": 99}
d = bytearray(open(sys.argv[1], "rb").read()); o = 8; done = set()
while o + 60 <= len(d):
    size = int(d[o + 48:o + 58]); b = o + 60
    if d[b:b + 4] == b"\0\0\xff\xff":
        e = d.index(b"\0", b + 20); name = d[b + 20:e].decode("latin1").lstrip("_").split("@")[0]
        if name in HINTS:
            struct.pack_into("<H", d, b + 16, HINTS[name]); done.add(name)
    o += 60 + size; o += o & 1
assert done == set(HINTS), done
open(sys.argv[2], "wb").write(d); print(sys.argv[2], "hints set:", sorted(done))
