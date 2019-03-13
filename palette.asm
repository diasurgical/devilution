; Listing generated by Microsoft (R) Optimizing Compiler Version 12.00.9044.0 

	TITLE	Source/palette.cpp
	.386P
include listing.inc
if @Version gt 510
.model FLAT
else
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
_BSS	SEGMENT DWORD USE32 PUBLIC 'BSS'
_BSS	ENDS
$$SYMBOLS	SEGMENT BYTE USE32 'DEBSYM'
$$SYMBOLS	ENDS
$$TYPES	SEGMENT BYTE USE32 'DEBTYP'
$$TYPES	ENDS
_TLS	SEGMENT DWORD USE32 PUBLIC 'TLS'
_TLS	ENDS
;	COMDAT ??_C@_0BB@IDPP@Gamma?5Correction?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_06EMML@Diablo?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0O@HEEN@Color?5Cycling?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0CB@DMHD@C?3?2Src?2Diablo?2Source?2PALETTE?4CPP@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0BK@EDBJ@Levels?2L?$CFiData?2L?$CFi_?$CFi?4PAL?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0BJ@CLDP@Levels?2TownData?2Town?4pal?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
CRT$XCU	SEGMENT DWORD USE32 PUBLIC ''
CRT$XCU	ENDS
;	COMDAT _SaveGamma
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT _palette_init
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT _LoadGamma
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT _LoadSysPal
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT @LoadPalette@4
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT @LoadRndLvlPal@4
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT _ResetPal
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT _IncreaseGamma
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT _palette_update
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT @ApplyGamma@12
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT _DecreaseGamma
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT @UpdateGamma@4
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT _BlackPalette
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT @SetFadeLevel@4
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT @PaletteFadeIn@4
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT @PaletteFadeOut@4
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT _palette_update_caves
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT @palette_update_quest_palette@4
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT _palette_get_colour_cycling
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT @palette_set_color_cycling@4
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
FLAT	GROUP _DATA, CONST, _BSS, CRT$XCU
	ASSUME	CS: FLAT, DS: FLAT, SS: FLAT
endif

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	_gamma_correction
PUBLIC	_color_cycling_enabled
PUBLIC	_sgbFadedIn
_DATA	SEGMENT
COMM	_logical_palette:DWORD:0100H
COMM	_system_palette:DWORD:0100H
COMM	_orig_palette:DWORD:0100H
COMM	_gdwPalEntries:DWORD
_gamma_correction DD 064H
_color_cycling_enabled DD 01H
_sgbFadedIn DB	01H
_DATA	ENDS
PUBLIC	_SaveGamma
PUBLIC	??_C@_0BB@IDPP@Gamma?5Correction?$AA@		; `string'
PUBLIC	??_C@_06EMML@Diablo?$AA@			; `string'
PUBLIC	??_C@_0O@HEEN@Color?5Cycling?$AA@		; `string'
EXTRN	_SRegSaveValue@16:NEAR
;	COMDAT ??_C@_06EMML@Diablo?$AA@
; File Source/palette.cpp
_DATA	SEGMENT
??_C@_06EMML@Diablo?$AA@ DB 'Diablo', 00H		; `string'
_DATA	ENDS
;	COMDAT ??_C@_0BB@IDPP@Gamma?5Correction?$AA@
_DATA	SEGMENT
??_C@_0BB@IDPP@Gamma?5Correction?$AA@ DB 'Gamma Correction', 00H ; `string'
_DATA	ENDS
;	COMDAT ??_C@_0O@HEEN@Color?5Cycling?$AA@
_DATA	SEGMENT
??_C@_0O@HEEN@Color?5Cycling?$AA@ DB 'Color Cycling', 00H ; `string'
; Function compile flags: /Ogsy
_DATA	ENDS
;	COMDAT _SaveGamma
_TEXT	SEGMENT
_SaveGamma PROC NEAR					; COMDAT
; Line 17
	push	esi
; Line 18
	mov	esi, OFFSET FLAT:??_C@_06EMML@Diablo?$AA@ ; `string'
	push	DWORD PTR _gamma_correction
	push	0
	push	OFFSET FLAT:??_C@_0BB@IDPP@Gamma?5Correction?$AA@ ; `string'
	push	esi
	call	_SRegSaveValue@16
; Line 19
	push	DWORD PTR _color_cycling_enabled
	push	0
	push	OFFSET FLAT:??_C@_0O@HEEN@Color?5Cycling?$AA@ ; `string'
	push	esi
	call	_SRegSaveValue@16
	pop	esi
; Line 20
	ret	0
_SaveGamma ENDP
_TEXT	ENDS
PUBLIC	_palette_init
PUBLIC	_LoadGamma
PUBLIC	_LoadSysPal
PUBLIC	??_C@_0CB@DMHD@C?3?2Src?2Diablo?2Source?2PALETTE?4CPP@ ; `string'
EXTRN	_lpDDInterface:DWORD
EXTRN	_lpDDPalette:DWORD
EXTRN	_lpDDSPrimary:DWORD
EXTRN	@ErrDlg@16:NEAR
EXTRN	_memcpy:NEAR
;	COMDAT ??_C@_0CB@DMHD@C?3?2Src?2Diablo?2Source?2PALETTE?4CPP@
_DATA	SEGMENT
??_C@_0CB@DMHD@C?3?2Src?2Diablo?2Source?2PALETTE?4CPP@ DB 'C:\Src\Diablo\'
	DB	'Source\PALETTE.CPP', 00H			; `string'
; Function compile flags: /Ogsy
_DATA	ENDS
;	COMDAT _palette_init
_TEXT	SEGMENT
_palette_init PROC NEAR					; COMDAT
; Line 23
	push	esi
; Line 27
	call	_LoadGamma
; Line 28
	push	1024					; 00000400H
	mov	esi, OFFSET FLAT:_system_palette
	push	OFFSET FLAT:_orig_palette
	push	esi
	call	_memcpy
	add	esp, 12					; 0000000cH
; Line 29
	call	_LoadSysPal
; Line 33
	mov	eax, DWORD PTR _lpDDInterface
	push	0
	push	OFFSET FLAT:_lpDDPalette
	push	esi
	mov	ecx, DWORD PTR [eax]
	push	68					; 00000044H
	push	eax
	call	DWORD PTR [ecx+20]
; Line 35
	test	eax, eax
	mov	esi, OFFSET FLAT:??_C@_0CB@DMHD@C?3?2Src?2Diablo?2Source?2PALETTE?4CPP@ ; `string'
	je	SHORT $L84991
; Line 36
	push	143					; 0000008fH
	push	esi
	push	111					; 0000006fH
	mov	edx, eax
	pop	ecx
	call	@ErrDlg@16
$L84991:
; Line 40
	mov	eax, DWORD PTR _lpDDSPrimary
	push	DWORD PTR _lpDDPalette
	mov	ecx, DWORD PTR [eax]
	push	eax
	call	DWORD PTR [ecx+124]
; Line 42
	test	eax, eax
	je	SHORT $L84993
; Line 43
	push	146					; 00000092H
	push	esi
	push	111					; 0000006fH
	mov	edx, eax
	pop	ecx
	call	@ErrDlg@16
$L84993:
	pop	esi
; Line 44
	ret	0
_palette_init ENDP
_TEXT	ENDS
EXTRN	_SRegLoadValue@16:NEAR
; Function compile flags: /Ogsy
;	COMDAT _LoadGamma
_TEXT	SEGMENT
_value$ = -4
_LoadGamma PROC NEAR					; COMDAT
; Line 47
	push	ebp
	mov	ebp, esp
	push	ecx
; Line 51
	mov	eax, DWORD PTR _gamma_correction
	push	esi
	mov	DWORD PTR _value$[ebp], eax
; Line 52
	lea	eax, DWORD PTR _value$[ebp]
	push	edi
	push	eax
	push	0
	mov	esi, OFFSET FLAT:??_C@_06EMML@Diablo?$AA@ ; `string'
	push	OFFSET FLAT:??_C@_0BB@IDPP@Gamma?5Correction?$AA@ ; `string'
	push	esi
	call	_SRegLoadValue@16
	test	eax, eax
	jne	SHORT $L85163
; Line 53
	push	100					; 00000064H
	pop	ecx
	mov	DWORD PTR _value$[ebp], ecx
	jmp	SHORT $L84997
$L85163:
	mov	ecx, DWORD PTR _value$[ebp]
$L84997:
; Line 54
	cmp	ecx, 30					; 0000001eH
	jl	SHORT $L84998
; Line 55
	cmp	ecx, 100				; 00000064H
	jle	SHORT $L85000
; Line 56
	push	100					; 00000064H
; Line 57
	jmp	SHORT $L85164
$L84998:
; Line 58
	push	30					; 0000001eH
$L85164:
	pop	ecx
	mov	DWORD PTR _value$[ebp], ecx
$L85000:
; Line 60
	mov	eax, ecx
	push	5
	cdq
	pop	edi
	idiv	edi
; Line 61
	lea	eax, DWORD PTR _value$[ebp]
	push	eax
	push	0
	push	OFFSET FLAT:??_C@_0O@HEEN@Color?5Cycling?$AA@ ; `string'
	push	esi
	sub	ecx, edx
	mov	DWORD PTR _gamma_correction, ecx
	call	_SRegLoadValue@16
	pop	edi
	pop	esi
	test	eax, eax
	je	SHORT $L85001
; Line 62
	mov	eax, DWORD PTR _value$[ebp]
; Line 63
	jmp	SHORT $L85002
$L85001:
; Line 64
	xor	eax, eax
	inc	eax
$L85002:
; Line 65
	mov	DWORD PTR _color_cycling_enabled, eax
; Line 66
	leave
	ret	0
_LoadGamma ENDP
_TEXT	ENDS
EXTRN	__imp__GetDeviceCaps@8:NEAR
EXTRN	_fullscreen:DWORD
EXTRN	__imp__GetSystemPaletteEntries@16:NEAR
EXTRN	__imp__GetDC@4:NEAR
EXTRN	__imp__ReleaseDC@8:NEAR
; Function compile flags: /Ogsy
;	COMDAT _LoadSysPal
_TEXT	SEGMENT
_LoadSysPal PROC NEAR					; COMDAT
; Line 74
	mov	eax, OFFSET FLAT:_system_palette+3
$L85007:
; Line 75
	mov	BYTE PTR [eax], 5
	add	eax, 4
	cmp	eax, OFFSET FLAT:_system_palette+1027
	jl	SHORT $L85007
	push	esi
; Line 77
	xor	esi, esi
	cmp	DWORD PTR _fullscreen, esi
	jne	$L85010
	push	ebx
	push	ebp
	push	edi
; Line 78
	push	esi
	call	DWORD PTR __imp__GetDC@4
	mov	ebx, eax
; Line 79
	push	106					; 0000006aH
	push	ebx
	call	DWORD PTR __imp__GetDeviceCaps@8
	cdq
; Line 80
	mov	ebp, DWORD PTR __imp__GetSystemPaletteEntries@16
	sub	eax, edx
	sar	eax, 1
	push	OFFSET FLAT:_system_palette
	push	eax
	push	esi
	push	ebx
	mov	DWORD PTR _gdwPalEntries, eax
	call	ebp
; Line 81
	mov	eax, DWORD PTR _gdwPalEntries
	xor	ecx, ecx
	cmp	eax, esi
	jbe	SHORT $L85014
$L85012:
; Line 82
	and	BYTE PTR _system_palette[ecx*4+3], 0
	inc	ecx
	cmp	ecx, eax
	jb	SHORT $L85012
$L85014:
; Line 83
	mov	esi, 256				; 00000100H
	sub	esi, eax
; Line 84
	mov	edi, esi
	shl	edi, 2
	lea	ecx, DWORD PTR _system_palette[edi]
	push	ecx
	push	eax
	push	esi
	push	ebx
	call	ebp
; Line 85
	cmp	esi, 256				; 00000100H
	jge	SHORT $L85018
; Line 86
	lea	eax, DWORD PTR _system_palette[edi+3]
$L85016:
; Line 87
	and	BYTE PTR [eax], 0
	add	eax, 4
	cmp	eax, OFFSET FLAT:_system_palette+1027
	jl	SHORT $L85016
$L85018:
; Line 89
	push	ebx
	push	0
	call	DWORD PTR __imp__ReleaseDC@8
	pop	edi
	pop	ebp
	pop	ebx
$L85010:
	pop	esi
; Line 91
	ret	0
_LoadSysPal ENDP
_TEXT	ENDS
PUBLIC	@LoadPalette@4
EXTRN	@WCloseFile@4:NEAR
EXTRN	@WOpenFile@12:NEAR
EXTRN	@WReadFile@12:NEAR
; Function compile flags: /Ogsy
;	COMDAT @LoadPalette@4
_TEXT	SEGMENT
_PalData$ = -772
_pBuf$ = -4
@LoadPalette@4 PROC NEAR				; COMDAT
; _pszFileName$ = ecx
; Line 94
	push	ebp
	mov	ebp, esp
	sub	esp, 772				; 00000304H
; Line 99
	push	0
	lea	edx, DWORD PTR _pBuf$[ebp]
	call	@WOpenFile@12
; Line 100
	mov	ecx, DWORD PTR _pBuf$[ebp]
	lea	edx, DWORD PTR _PalData$[ebp]
	push	768					; 00000300H
	call	@WReadFile@12
; Line 101
	mov	ecx, DWORD PTR _pBuf$[ebp]
	call	@WCloseFile@4
	lea	ecx, DWORD PTR _PalData$[ebp+1]
	mov	eax, OFFSET FLAT:_orig_palette
$L85027:
; Line 105
	mov	dl, BYTE PTR [ecx-1]
	and	BYTE PTR [eax+3], 0
	mov	BYTE PTR [eax], dl
; Line 106
	mov	dl, BYTE PTR [ecx]
	mov	BYTE PTR [eax+1], dl
; Line 107
	mov	dl, BYTE PTR [ecx+1]
	mov	BYTE PTR [eax+2], dl
	add	eax, 4
	add	ecx, 3
	cmp	eax, OFFSET FLAT:_orig_palette+1024
	jl	SHORT $L85027
; Line 109
	leave
	ret	0
@LoadPalette@4 ENDP
_TEXT	ENDS
PUBLIC	@LoadRndLvlPal@4
PUBLIC	??_C@_0BK@EDBJ@Levels?2L?$CFiData?2L?$CFi_?$CFi?4PAL?$AA@ ; `string'
PUBLIC	??_C@_0BJ@CLDP@Levels?2TownData?2Town?4pal?$AA@	; `string'
EXTRN	_sprintf:NEAR
EXTRN	@random@8:NEAR
;	COMDAT ??_C@_0BK@EDBJ@Levels?2L?$CFiData?2L?$CFi_?$CFi?4PAL?$AA@
_DATA	SEGMENT
??_C@_0BK@EDBJ@Levels?2L?$CFiData?2L?$CFi_?$CFi?4PAL?$AA@ DB 'Levels\L%iD'
	DB	'ata\L%i_%i.PAL', 00H			; `string'
_DATA	ENDS
;	COMDAT ??_C@_0BJ@CLDP@Levels?2TownData?2Town?4pal?$AA@
_DATA	SEGMENT
??_C@_0BJ@CLDP@Levels?2TownData?2Town?4pal?$AA@ DB 'Levels\TownData\Town.'
	DB	'pal', 00H					; `string'
; Function compile flags: /Ogsy
_DATA	ENDS
;	COMDAT @LoadRndLvlPal@4
_TEXT	SEGMENT
_szTemp$ = -260
@LoadRndLvlPal@4 PROC NEAR				; COMDAT
; _l$ = ecx
; Line 112
	push	ebp
	mov	ebp, esp
	sub	esp, 260				; 00000104H
	push	esi
	mov	esi, ecx
; Line 116
	test	esi, esi
	je	SHORT $L85035
; Line 117
	push	4
	xor	cl, cl
	pop	edx
	call	@random@8
	inc	eax
	push	eax
	push	esi
	push	esi
	lea	eax, DWORD PTR _szTemp$[ebp]
	push	OFFSET FLAT:??_C@_0BK@EDBJ@Levels?2L?$CFiData?2L?$CFi_?$CFi?4PAL?$AA@ ; `string'
	push	eax
	call	_sprintf
	add	esp, 20					; 00000014H
; Line 118
	lea	ecx, DWORD PTR _szTemp$[ebp]
; Line 119
	jmp	SHORT $L85037
$L85035:
; Line 120
	mov	ecx, OFFSET FLAT:??_C@_0BJ@CLDP@Levels?2TownData?2Town?4pal?$AA@ ; `string'
$L85037:
; Line 122
	call	@LoadPalette@4
	pop	esi
; Line 123
	leave
	ret	0
@LoadRndLvlPal@4 ENDP
_TEXT	ENDS
PUBLIC	_ResetPal
EXTRN	_SDrawRealizePalette:NEAR
; Function compile flags: /Ogsy
;	COMDAT _ResetPal
_TEXT	SEGMENT
_ResetPal PROC NEAR					; COMDAT
; Line 133
	mov	eax, DWORD PTR _lpDDSPrimary
	test	eax, eax
	je	SHORT $L85045
	mov	ecx, DWORD PTR [eax]
	push	eax
	call	DWORD PTR [ecx+96]
	cmp	eax, -2005532222			; 887601c2H
	jne	SHORT $L85045
	mov	eax, DWORD PTR _lpDDSPrimary
	push	eax
	mov	ecx, DWORD PTR [eax]
	call	DWORD PTR [ecx+108]
	test	eax, eax
	jne	SHORT $L85044
$L85045:
; Line 135
	jmp	_SDrawRealizePalette
$L85044:
; Line 137
	ret	0
_ResetPal ENDP
_TEXT	ENDS
PUBLIC	_IncreaseGamma
PUBLIC	_palette_update
PUBLIC	@ApplyGamma@12
; Function compile flags: /Ogsy
;	COMDAT _IncreaseGamma
_TEXT	SEGMENT
_IncreaseGamma PROC NEAR				; COMDAT
; Line 141
	push	100					; 00000064H
	pop	eax
	cmp	DWORD PTR _gamma_correction, eax
	jge	SHORT $L85047
; Line 142
	add	DWORD PTR _gamma_correction, 5
; Line 143
	cmp	DWORD PTR _gamma_correction, eax
	jle	SHORT $L85048
; Line 144
	mov	DWORD PTR _gamma_correction, eax
$L85048:
; Line 145
	push	256					; 00000100H
	mov	edx, OFFSET FLAT:_logical_palette
	mov	ecx, OFFSET FLAT:_system_palette
	call	@ApplyGamma@12
; Line 146
	jmp	_palette_update
$L85047:
; Line 148
	ret	0
_IncreaseGamma ENDP
_TEXT	ENDS
EXTRN	_SDrawUpdatePalette@16:NEAR
; Function compile flags: /Ogsy
;	COMDAT _palette_update
_TEXT	SEGMENT
_palette_update PROC NEAR				; COMDAT
; Line 155
	xor	edx, edx
	cmp	DWORD PTR _lpDDPalette, edx
	je	SHORT $L85052
; Line 156
	xor	ecx, ecx
; Line 158
	cmp	DWORD PTR _fullscreen, edx
	mov	eax, 256				; 00000100H
	jne	SHORT $L85053
; Line 159
	mov	ecx, DWORD PTR _gdwPalEntries
; Line 160
	add	eax, -128				; ffffff80H
	sub	eax, ecx
	add	eax, eax
$L85053:
; Line 162
	push	edx
	lea	edx, DWORD PTR _system_palette[ecx*4]
	push	edx
	push	eax
	push	ecx
	call	_SDrawUpdatePalette@16
$L85052:
; Line 164
	ret	0
_palette_update ENDP
_TEXT	ENDS
PUBLIC	__real@3f847ae147ae147b
PUBLIC	__real@3f70000000000000
PUBLIC	__real@4070000000000000
EXTRN	_pow:NEAR
EXTRN	__ftol:NEAR
EXTRN	__fltused:NEAR
;	COMDAT __real@3f847ae147ae147b
CONST	SEGMENT
__real@3f847ae147ae147b DQ 03f847ae147ae147br	; 0.01
CONST	ENDS
;	COMDAT __real@3f70000000000000
CONST	SEGMENT
__real@3f70000000000000 DQ 03f70000000000000r	; 0.00390625
CONST	ENDS
;	COMDAT __real@4070000000000000
CONST	SEGMENT
__real@4070000000000000 DQ 04070000000000000r	; 256
; Function compile flags: /Ogsy
CONST	ENDS
;	COMDAT @ApplyGamma@12
_TEXT	SEGMENT
_n$ = 8
_v5$ = -16
@ApplyGamma@12 PROC NEAR				; COMDAT
; _dst$ = ecx
; _src$ = edx
; Line 167
	push	ebp
	mov	ebp, esp
	sub	esp, 16					; 00000010H
; Line 174
	fild	DWORD PTR _gamma_correction
; Line 175
	cmp	DWORD PTR _n$[ebp], 0
	push	edi
	mov	edi, edx
	fmul	QWORD PTR __real@3f847ae147ae147b
	fstp	QWORD PTR _v5$[ebp]
	jle	$L85068
; Line 183
	mov	DWORD PTR -4+[ebp], edx
	push	esi
	sub	DWORD PTR -4+[ebp], ecx
	lea	esi, DWORD PTR [ecx+2]
$L85066:
	movzx	eax, BYTE PTR [edi]
	fld	QWORD PTR _v5$[ebp]
	sub	esp, 16					; 00000010H
	mov	DWORD PTR -8+[ebp], eax
	fstp	QWORD PTR [esp+8]
	fild	DWORD PTR -8+[ebp]
	fmul	QWORD PTR __real@3f70000000000000
	fstp	QWORD PTR [esp]
	call	_pow
	fmul	QWORD PTR __real@4070000000000000
	call	__ftol
	fld	QWORD PTR _v5$[ebp]
	mov	BYTE PTR [esi-2], al
	movzx	eax, BYTE PTR [edi+1]
	fstp	QWORD PTR [esp+8]
	mov	DWORD PTR -8+[ebp], eax
	fild	DWORD PTR -8+[ebp]
	fmul	QWORD PTR __real@3f70000000000000
	fstp	QWORD PTR [esp]
	call	_pow
	fmul	QWORD PTR __real@4070000000000000
	call	__ftol
	fld	QWORD PTR _v5$[ebp]
	mov	BYTE PTR [esi-1], al
	mov	eax, DWORD PTR -4+[ebp]
	fstp	QWORD PTR [esp+8]
	movzx	eax, BYTE PTR [eax+esi]
	mov	DWORD PTR -8+[ebp], eax
	fild	DWORD PTR -8+[ebp]
	fmul	QWORD PTR __real@3f70000000000000
	fstp	QWORD PTR [esp]
	call	_pow
	fmul	QWORD PTR __real@4070000000000000
	add	esp, 16					; 00000010H
	call	__ftol
	mov	BYTE PTR [esi], al
	add	edi, 4
	add	esi, 4
	dec	DWORD PTR _n$[ebp]
	jne	$L85066
	pop	esi
$L85068:
	pop	edi
; Line 185
	leave
	ret	4
@ApplyGamma@12 ENDP
_TEXT	ENDS
PUBLIC	_DecreaseGamma
; Function compile flags: /Ogsy
;	COMDAT _DecreaseGamma
_TEXT	SEGMENT
_DecreaseGamma PROC NEAR				; COMDAT
; Line 189
	push	30					; 0000001eH
	pop	eax
	cmp	DWORD PTR _gamma_correction, eax
	jle	SHORT $L85070
; Line 190
	sub	DWORD PTR _gamma_correction, 5
; Line 191
	cmp	DWORD PTR _gamma_correction, eax
	jge	SHORT $L85071
; Line 192
	mov	DWORD PTR _gamma_correction, eax
$L85071:
; Line 193
	push	256					; 00000100H
	mov	edx, OFFSET FLAT:_logical_palette
	mov	ecx, OFFSET FLAT:_system_palette
	call	@ApplyGamma@12
; Line 194
	jmp	_palette_update
$L85070:
; Line 196
	ret	0
_DecreaseGamma ENDP
_TEXT	ENDS
PUBLIC	@UpdateGamma@4
; Function compile flags: /Ogsy
;	COMDAT @UpdateGamma@4
_TEXT	SEGMENT
@UpdateGamma@4 PROC NEAR				; COMDAT
; _gamma$ = ecx
; Line 200
	test	ecx, ecx
	je	SHORT $L85075
; Line 201
	mov	eax, 130				; 00000082H
; Line 202
	push	256					; 00000100H
	sub	eax, ecx
	mov	edx, OFFSET FLAT:_logical_palette
	mov	ecx, OFFSET FLAT:_system_palette
	mov	DWORD PTR _gamma_correction, eax
	call	@ApplyGamma@12
; Line 203
	call	_palette_update
$L85075:
; Line 205
	mov	eax, 130				; 00000082H
	sub	eax, DWORD PTR _gamma_correction
; Line 206
	ret	0
@UpdateGamma@4 ENDP
_TEXT	ENDS
PUBLIC	_BlackPalette
PUBLIC	@SetFadeLevel@4
; Function compile flags: /Ogsy
;	COMDAT _BlackPalette
_TEXT	SEGMENT
_BlackPalette PROC NEAR					; COMDAT
; Line 210
	xor	ecx, ecx
	jmp	@SetFadeLevel@4
_BlackPalette ENDP
_TEXT	ENDS
EXTRN	__imp__Sleep@4:NEAR
; Function compile flags: /Ogsy
;	COMDAT @SetFadeLevel@4
_TEXT	SEGMENT
@SetFadeLevel@4 PROC NEAR				; COMDAT
; _fadeval$ = ecx
; Line 217
	cmp	DWORD PTR _lpDDInterface, 0
	je	SHORT $L85081
; Line 218
	xor	eax, eax
$L85082:
; Line 219
	movzx	edx, BYTE PTR _logical_palette[eax]
	imul	edx, ecx
	sar	edx, 8
	mov	BYTE PTR _system_palette[eax], dl
; Line 220
	movzx	edx, BYTE PTR _logical_palette[eax+1]
	imul	edx, ecx
	sar	edx, 8
	mov	BYTE PTR _system_palette[eax+1], dl
; Line 221
	movzx	edx, BYTE PTR _logical_palette[eax+2]
	imul	edx, ecx
	sar	edx, 8
	mov	BYTE PTR _system_palette[eax+2], dl
	add	eax, 4
	cmp	eax, 1020				; 000003fcH
	jl	SHORT $L85082
; Line 223
	push	3
	call	DWORD PTR __imp__Sleep@4
; Line 227
	mov	eax, DWORD PTR _lpDDInterface
	push	0
	push	1
	mov	ecx, DWORD PTR [eax]
	push	eax
	call	DWORD PTR [ecx+88]
; Line 229
	jmp	_palette_update
$L85081:
; Line 231
	ret	0
@SetFadeLevel@4 ENDP
_TEXT	ENDS
PUBLIC	@PaletteFadeIn@4
; Function compile flags: /Ogsy
;	COMDAT @PaletteFadeIn@4
_TEXT	SEGMENT
_fr$ = -4
@PaletteFadeIn@4 PROC NEAR				; COMDAT
; _fr$ = ecx
; Line 234
	push	ecx
	push	ebx
	push	ebp
	push	esi
	push	edi
; Line 237
	mov	esi, 256				; 00000100H
	mov	ebx, OFFSET FLAT:_orig_palette
	mov	edi, OFFSET FLAT:_logical_palette
	mov	DWORD PTR _fr$[esp+20], ecx
	push	esi
	mov	edx, ebx
	mov	ecx, edi
	call	@ApplyGamma@12
; Line 239
	xor	ebp, ebp
$L85090:
; Line 240
	mov	ecx, ebp
	call	@SetFadeLevel@4
	add	ebp, DWORD PTR _fr$[esp+20]
	cmp	ebp, esi
	jl	SHORT $L85090
; Line 242
	mov	ecx, esi
	call	@SetFadeLevel@4
; Line 243
	push	1024					; 00000400H
	push	ebx
	push	edi
	call	_memcpy
	add	esp, 12					; 0000000cH
; Line 244
	mov	BYTE PTR _sgbFadedIn, 1
	pop	edi
	pop	esi
	pop	ebp
	pop	ebx
; Line 245
	pop	ecx
	ret	0
@PaletteFadeIn@4 ENDP
_TEXT	ENDS
PUBLIC	@PaletteFadeOut@4
; Function compile flags: /Ogsy
;	COMDAT @PaletteFadeOut@4
_TEXT	SEGMENT
@PaletteFadeOut@4 PROC NEAR				; COMDAT
; _fr$ = ecx
; Line 251
	cmp	BYTE PTR _sgbFadedIn, 0
	push	edi
	mov	edi, ecx
	je	SHORT $L85097
	push	esi
; Line 252
	mov	esi, 256				; 00000100H
$L85098:
; Line 253
	mov	ecx, esi
	call	@SetFadeLevel@4
	sub	esi, edi
	test	esi, esi
	jg	SHORT $L85098
; Line 255
	xor	ecx, ecx
	call	@SetFadeLevel@4
; Line 256
	and	BYTE PTR _sgbFadedIn, 0
	pop	esi
$L85097:
	pop	edi
; Line 258
	ret	0
@PaletteFadeOut@4 ENDP
_TEXT	ENDS
PUBLIC	_palette_update_caves
; Function compile flags: /Ogsy
;	COMDAT _palette_update_caves
_TEXT	SEGMENT
_v4$ = -2
_v5$ = -1
_palette_update_caves PROC NEAR				; COMDAT
; Line 261
	push	ebp
	mov	ebp, esp
	push	ecx
; Line 269
	mov	al, BYTE PTR _system_palette+5
	mov	dl, BYTE PTR _system_palette+4
	mov	BYTE PTR _v5$[ebp], al
; Line 270
	mov	al, BYTE PTR _system_palette+6
; Line 271
	xor	ecx, ecx
	mov	BYTE PTR _v4$[ebp], al
	inc	ecx
	push	ebx
$L85107:
; Line 277
	mov	eax, ecx
	shl	eax, 2
	inc	ecx
	mov	bl, BYTE PTR _system_palette[eax+4]
	cmp	ecx, 31					; 0000001fH
	mov	BYTE PTR _system_palette[eax], bl
	mov	bl, BYTE PTR _system_palette[eax+5]
	mov	BYTE PTR _system_palette[eax+1], bl
	mov	bl, BYTE PTR _system_palette[eax+6]
	mov	BYTE PTR _system_palette[eax+2], bl
	jl	SHORT $L85107
; Line 278
	mov	eax, ecx
; Line 279
	mov	cl, BYTE PTR _v5$[ebp]
	shl	eax, 2
	mov	BYTE PTR _system_palette[eax+1], cl
; Line 280
	mov	cl, BYTE PTR _v4$[ebp]
	mov	BYTE PTR _system_palette[eax], dl
	mov	BYTE PTR _system_palette[eax+2], cl
; Line 281
	call	_palette_update
	pop	ebx
; Line 282
	leave
	ret	0
_palette_update_caves ENDP
_TEXT	ENDS
PUBLIC	@palette_update_quest_palette@4
; Function compile flags: /Ogsy
;	COMDAT @palette_update_quest_palette@4
_TEXT	SEGMENT
@palette_update_quest_palette@4 PROC NEAR		; COMDAT
; _n$ = ecx
; Line 288
	push	32					; 00000020H
	pop	eax
	sub	eax, ecx
	js	SHORT $L85116
$L85114:
; Line 289
	mov	ecx, DWORD PTR _orig_palette[eax*4]
	mov	DWORD PTR _logical_palette[eax*4], ecx
	dec	eax
	jns	SHORT $L85114
$L85116:
; Line 290
	push	32					; 00000020H
	mov	edx, OFFSET FLAT:_logical_palette
	mov	ecx, OFFSET FLAT:_system_palette
	call	@ApplyGamma@12
; Line 291
	jmp	_palette_update
@palette_update_quest_palette@4 ENDP
_TEXT	ENDS
PUBLIC	_palette_get_colour_cycling
; Function compile flags: /Ogsy
;	COMDAT _palette_get_colour_cycling
_TEXT	SEGMENT
_palette_get_colour_cycling PROC NEAR			; COMDAT
; Line 296
	mov	al, BYTE PTR _color_cycling_enabled
; Line 297
	ret	0
_palette_get_colour_cycling ENDP
_TEXT	ENDS
PUBLIC	@palette_set_color_cycling@4
; Function compile flags: /Ogsy
;	COMDAT @palette_set_color_cycling@4
_TEXT	SEGMENT
@palette_set_color_cycling@4 PROC NEAR			; COMDAT
; _enabled$ = cl
; Line 301
	movzx	eax, cl
	mov	DWORD PTR _color_cycling_enabled, eax
; Line 302
	ret	0
@palette_set_color_cycling@4 ENDP
_TEXT	ENDS
END
