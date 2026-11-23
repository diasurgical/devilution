#!/bin/sh
# Build Diablo 1.09b byte for byte from this source and check the result against the retail hash.
#
#   tools/build_109b.sh [--keep] DDK_LIB_DIR MSVCRT_DIR IMPLODE_LIB
#
#   DDK_LIB_DIR  kernel32/user32/gdi32/advapi32/shell32/version.lib from the Windows DDK, October 2000,
#                x86 free build (cab X86DLIBF; LIB 5.12.9049)
#   MSVCRT_DIR   a directory holding Microsoft's MSVCRT.DLL from Visual C++ 5.0 (VC/REDIST): the linker
#                sorts its import thunks with it, Wine's own qsort gives another order
#   IMPLODE_LIB  PKWARE's Data Compression Library (IMPLODE.LIB), which 1.09b links
#
# None of these files may be distributed; they stay on the machine that builds. The script needs docker,
# rsync and python3, and uses the Riivaaja image (diasurgical/riivaaja:stable).
#
# Until the original shell32.lib turns up, the build uses a copy of the DDK one with the three hints Diablo
# uses set to 1.09b's values (tools/mk_shell32_hints.py); this changes nothing else in the output.
#
# The build runs in a copy of the tree (default build-109b/ next to it; set BUILD_DIR to change it), so the
# working tree stays clean. --keep reuses that copy without "make clean".
# Exit status: 0 = identical to retail 1.09b, 1 = built but different, 2 = could not build.
set -e

EXPECTED_MD5=da62d5cd8bd71a0b66e6d4ef7a111233   # retail Diablo.exe 1.09b
IMAGE=diasurgical/riivaaja:stable

KEEP=
[ "$1" = "--keep" ] && { KEEP=1; shift; }
if [ $# -ne 3 ]; then
	sed -n '2,10p' "$0" | sed 's/^# \{0,1\}//'
	exit 2
fi
DDK=$(realpath "$1"); MSVCRT=$(realpath "$2"); IMPLODE=$(realpath "$3")
SRC=$(cd "$(dirname "$0")/.." && pwd)
WORK=${BUILD_DIR:-$(dirname "$SRC")/build-109b}

fail() { echo "build_109b: $*" >&2; exit 2; }
md5() { md5sum "$1" | cut -d' ' -f1; }

# --- inputs ----------------------------------------------------------------------------------------------
# known good copies; a different file is reported, not refused (another print of the same library may do)
check() { # file expected-md5 description
	[ -f "$1" ] || fail "missing $1 ($3)"
	[ "$(md5 "$1")" = "$2" ] || echo "build_109b: warning: $1 is not the known $3 (md5 $(md5 "$1"))" >&2
}
for l in kernel32 user32 gdi32 advapi32 shell32 version; do
	f=$(find "$DDK" -maxdepth 1 -iname "$l.lib" | head -1)
	[ -n "$f" ] || fail "missing $l.lib in $DDK"
done
check "$(find "$DDK" -maxdepth 1 -iname kernel32.lib)" f7f75585293e590a710ad9869af8e8df "DDK Oct 2000 free kernel32.lib"
check "$(find "$DDK" -maxdepth 1 -iname user32.lib)" 763b198a091d9b2a342adf1971b72ed7 "DDK Oct 2000 free user32.lib"
check "$(find "$DDK" -maxdepth 1 -iname gdi32.lib)" 680eed309e815e0391db1a26a8113801 "DDK Oct 2000 free gdi32.lib"
check "$(find "$DDK" -maxdepth 1 -iname advapi32.lib)" 8a84764a9694e74d04d9bfa3fff65b76 "DDK Oct 2000 free advapi32.lib"
check "$(find "$DDK" -maxdepth 1 -iname version.lib)" f05052fd9e7df3fc6856c25f17632f5a "DDK Oct 2000 free version.lib"
M=$(find "$MSVCRT" -maxdepth 1 -iname msvcrt.dll | head -1)
[ -n "$M" ] || fail "missing MSVCRT.DLL in $MSVCRT"
check "$M" 2ed73c4f9be8e3866693ec6aff06f26a "VC5 redistributable MSVCRT.DLL"
check "$IMPLODE" 020f66163bbb02638cebd106e7160e55 "PKWARE IMPLODE.LIB"

# --- work copy ---------------------------------------------------------------------------------------------
mkdir -p "$WORK"
rsync -a --delete --exclude .git --exclude 'build-109b' --exclude '*.obj' --exclude '*.exe' --exclude '/diablo.res' \
	--exclude '*.pch' --exclude '*.idb' --exclude '*.pdb' --exclude 'vc5link' --exclude '_inputs' \
	$( [ -n "$KEEP" ] && echo --exclude '*.lib' ) "$SRC"/ "$WORK"/
mkdir -p "$WORK/_inputs/ddk" "$WORK/_inputs/msvcrt"
for l in kernel32 user32 gdi32 advapi32 version; do cp "$(find "$DDK" -maxdepth 1 -iname "$l.lib")" "$WORK/_inputs/ddk/$l.lib"; done
SH=$(find "$DDK" -maxdepth 1 -iname shell32.lib)
case "$(md5 "$SH")" in
	9d8164851fad77b36799f2d958ad8222) python3 "$SRC/tools/mk_shell32_hints.py" "$SH" "$WORK/_inputs/ddk/shell32.lib" >/dev/null ;;
	*) cp "$SH" "$WORK/_inputs/ddk/shell32.lib" ;;   # already prepared, or the original library
esac
cp "$M" "$WORK/_inputs/msvcrt/MSVCRT.DLL"
cp "$IMPLODE" "$WORK/_inputs/implode.lib"

# --- build -------------------------------------------------------------------------------------------------
UIDGID="$(id -u):$(id -g)"
docker run --rm -v "$WORK":/root/devilution -w /root/devilution "$IMAGE" sh -c "
	$( [ -z "$KEEP" ] && echo 'make -f MakefileVC clean >/dev/null 2>&1;' )
	make -f MakefileVC DDK_LIB_DIR=_inputs/ddk MSVCRT_DIR=_inputs/msvcrt PKWARE_LIB=_inputs/implode.lib PE_TIMESTAMP=1 \
		> build-109b.log 2>&1; rc=\$?; chown -R $UIDGID /root/devilution; exit \$rc" \
	|| { tail -20 "$WORK/build-109b.log" >&2; fail "build failed, log: $WORK/build-109b.log"; }

# --- verify ------------------------------------------------------------------------------------------------
GOT=$(md5 "$WORK/Diablo.exe")
echo "built    $WORK/Diablo.exe"
echo "md5      $GOT"
echo "expected $EXPECTED_MD5 (retail 1.09b)"
if [ "$GOT" = "$EXPECTED_MD5" ]; then echo "IDENTICAL"; exit 0; fi
echo "DIFFERENT"; exit 1
