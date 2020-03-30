# Implode Library make file for Win32

CFLAGS = /nologo /W3 /O2 /D "_X86_" /D "NDEBUG" /ML

BCCFLAGS = -vi -WC -c

all: implode.lib implodei.lib

CRC32.OBJ: crc32.C
	cl $(CFLAGS) /c CRC32.C
	cl $(CFLAGS) /c crc32.c /Gr /Focrcfast.obj
	cl $(CFLAGS) /c crc32.c /Gz /Focrcstd.obj
	Bcc32 $(BCCFLAGS) -ocrcborl.obj crc32.c

EXPLODE.OBJ: EXPLODE.C tables.inc implode.h
	cl $(CFLAGS) /c EXPLODE.C
	cl $(CFLAGS) /c explode.c /Gr /Foexpfast.obj
	cl $(CFLAGS) /c explode.c /Gz /Foexpstd.obj
	Bcc32 $(BCCFLAGS) -oexpborl.obj explode.c

IMPLODE.OBJ:IMPLODE.C tables.inc implode.h
	cl $(CFLAGS) /c IMPLODE.C
	cl $(CFLAGS) /c implode.c /Gr /Foimpfast.obj
	cl $(CFLAGS) /c implode.c /Gz /Foimpstd.obj
	Bcc32 $(BCCFLAGS) -oimpborl.obj implode.c

implode.LIB: CRC32.OBJ EXPLODE.OBJ IMPLODE.OBJ
        link -lib implode.obj impfast.obj impstd.obj crc32.obj crcfast.obj crcstd.obj explode.obj expfast.obj expstd.obj
	tlib impborl.lib -+crcborl.obj -+expborl.obj -+impborl.obj

implodei.lib: implode.obj explode.obj crc32.obj
        link -dll -implib:implodei.lib -DEF:implode.def -OUT:implode.dll implode.obj explode.obj crc32.obj
	tlink32 -Tpd crcborl.obj expborl.obj impborl.obj, impborl.dll,,,impborl.def
	implib impborli.lib impborl.dll

