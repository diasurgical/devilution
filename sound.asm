; Listing generated by Microsoft (R) Optimizing Compiler Version 12.00.9044.0 

	TITLE	Source/sound.cpp
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
;	COMDAT ??_C@_0BB@GLLI@Music?2DTowne?4wav?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0BA@FAOG@Music?2DLvlA?4wav?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0BA@LAIJ@Music?2DLvlB?4wav?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0BA@BAKM@Music?2DLvlC?4wav?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0BA@HAFG@Music?2DLvlD?4wav?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0BB@EGF@Music?2Dintro?4wav?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0BP@LEGP@C?3?2Src?2Diablo?2Source?2SOUND?4CPP?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0CA@LJJC@Invalid?5sound?5format?5on?5file?5?$CFs?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0N@DCLE@Sound?5Volume?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0N@FBBG@Music?5Volume?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_06EMML@Diablo?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0L@PLHI@dsound?4dll?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ??_C@_0BC@OJFH@DirectSoundCreate?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
CRT$XCU	SEGMENT DWORD USE32 PUBLIC ''
CRT$XCU	ENDS
;	COMDAT @snd_update@4
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT @snd_stop_snd@4
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT @snd_playing@4
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT @snd_play_snd@12
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT @sound_dup_channel@4
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT @sound_file_reload@8
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT @sound_file_load@4
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT @sound_CreateSoundBuffer@4
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT @sound_file_cleanup@4
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT @snd_init@4
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT @sound_load_volume@8
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT @sound_create_primary_buffer@4
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT @sound_DirectSoundCreate@12
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT _sound_cleanup
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT @sound_store_volume@8
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT _music_stop
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT @music_start@4
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT @sound_disable_music@4
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT @sound_get_or_set_music_volume@4
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT @sound_get_or_set_sound_volume@4
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
FLAT	GROUP _DATA, CONST, _BSS, CRT$XCU
	ASSUME	CS: FLAT, DS: FLAT, SS: FLAT
endif

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	_sgnMusicTrack
PUBLIC	_sgszMusicTracks
PUBLIC	??_C@_0BB@GLLI@Music?2DTowne?4wav?$AA@		; `string'
PUBLIC	??_C@_0BA@FAOG@Music?2DLvlA?4wav?$AA@		; `string'
PUBLIC	??_C@_0BA@LAIJ@Music?2DLvlB?4wav?$AA@		; `string'
PUBLIC	??_C@_0BA@BAKM@Music?2DLvlC?4wav?$AA@		; `string'
PUBLIC	??_C@_0BA@HAFG@Music?2DLvlD?4wav?$AA@		; `string'
PUBLIC	??_C@_0BB@EGF@Music?2Dintro?4wav?$AA@		; `string'
PUBLIC	_gbMusicOn
PUBLIC	_gbSoundOn
PUBLIC	_gbDupSounds
PUBLIC	_unk_volume
_DATA	SEGMENT
COMM	_sglpDS:DWORD
COMM	_sglMusicVolume:DWORD
COMM	_sglSoundVolume:DWORD
COMM	_sgpMusicTrack:DWORD
COMM	_sglpDSB:DWORD
COMM	_DSBs:DWORD:08H
COMM	_gbSndInited:BYTE
COMM	_hDsound_dll:DWORD
_gbMusicOn DB	01H
_gbSoundOn DB	01H
_gbDupSounds DB	01H
	ORG $+1
_sgnMusicTrack DD 06H
_DATA	ENDS
;	COMDAT ??_C@_0BB@GLLI@Music?2DTowne?4wav?$AA@
_DATA	SEGMENT
??_C@_0BB@GLLI@Music?2DTowne?4wav?$AA@ DB 'Music\DTowne.wav', 00H ; `string'
_DATA	ENDS
;	COMDAT ??_C@_0BA@FAOG@Music?2DLvlA?4wav?$AA@
_DATA	SEGMENT
??_C@_0BA@FAOG@Music?2DLvlA?4wav?$AA@ DB 'Music\DLvlA.wav', 00H ; `string'
_DATA	ENDS
;	COMDAT ??_C@_0BA@LAIJ@Music?2DLvlB?4wav?$AA@
_DATA	SEGMENT
??_C@_0BA@LAIJ@Music?2DLvlB?4wav?$AA@ DB 'Music\DLvlB.wav', 00H ; `string'
_DATA	ENDS
;	COMDAT ??_C@_0BA@BAKM@Music?2DLvlC?4wav?$AA@
_DATA	SEGMENT
??_C@_0BA@BAKM@Music?2DLvlC?4wav?$AA@ DB 'Music\DLvlC.wav', 00H ; `string'
_DATA	ENDS
;	COMDAT ??_C@_0BA@HAFG@Music?2DLvlD?4wav?$AA@
_DATA	SEGMENT
??_C@_0BA@HAFG@Music?2DLvlD?4wav?$AA@ DB 'Music\DLvlD.wav', 00H ; `string'
_DATA	ENDS
;	COMDAT ??_C@_0BB@EGF@Music?2Dintro?4wav?$AA@
_DATA	SEGMENT
??_C@_0BB@EGF@Music?2Dintro?4wav?$AA@ DB 'Music\Dintro.wav', 00H ; `string'
_DATA	ENDS
_DATA	SEGMENT
_sgszMusicTracks DD FLAT:??_C@_0BB@GLLI@Music?2DTowne?4wav?$AA@
	DD	FLAT:??_C@_0BA@FAOG@Music?2DLvlA?4wav?$AA@
	DD	FLAT:??_C@_0BA@LAIJ@Music?2DLvlB?4wav?$AA@
	DD	FLAT:??_C@_0BA@BAKM@Music?2DLvlC?4wav?$AA@
	DD	FLAT:??_C@_0BA@HAFG@Music?2DLvlD?4wav?$AA@
	DD	FLAT:??_C@_0BB@EGF@Music?2Dintro?4wav?$AA@
_unk_volume DB	0fH
	DB	0f0H
	DB	0fH
	DB	0f0H
	DB	01eH
	DB	0e1H
	DB	01eH
	DB	0e1H
_DATA	ENDS
PUBLIC	@snd_update@4
; Function compile flags: /Ogsy
;	COMDAT @snd_update@4
_TEXT	SEGMENT
_error_code$ = -4
@snd_update@4 PROC NEAR					; COMDAT
; _bStopAll$ = ecx
; File Source/sound.cpp
; Line 36
	push	ebp
	mov	ebp, esp
	push	ecx
	push	esi
	push	edi
	mov	edi, ecx
; Line 39
	xor	esi, esi
$L85000:
; Line 40
	mov	eax, DWORD PTR _DSBs[esi]
	test	eax, eax
	je	SHORT $L85001
; Line 50
	test	edi, edi
	jne	SHORT $L85004
	mov	ecx, DWORD PTR [eax]
	lea	edx, DWORD PTR _error_code$[ebp]
	push	edx
	push	eax
	call	DWORD PTR [ecx+36]
	test	eax, eax
	jne	SHORT $L85004
	cmp	DWORD PTR _error_code$[ebp], 1
	je	SHORT $L85001
$L85004:
; Line 53
	mov	eax, DWORD PTR _DSBs[esi]
	push	eax
	mov	ecx, DWORD PTR [eax]
	call	DWORD PTR [ecx+72]
; Line 54
	mov	eax, DWORD PTR _DSBs[esi]
	push	eax
	mov	ecx, DWORD PTR [eax]
	call	DWORD PTR [ecx+8]
; Line 57
	and	DWORD PTR _DSBs[esi], 0
$L85001:
	add	esi, 4
	cmp	esi, 32					; 00000020H
	jb	SHORT $L85000
	pop	edi
	pop	esi
; Line 59
	leave
	ret	0
@snd_update@4 ENDP
_TEXT	ENDS
PUBLIC	@snd_stop_snd@4
; Function compile flags: /Ogsy
;	COMDAT @snd_stop_snd@4
_TEXT	SEGMENT
@snd_stop_snd@4 PROC NEAR				; COMDAT
; _pSnd$ = ecx
; Line 63
	test	ecx, ecx
	je	SHORT $L85009
	mov	eax, DWORD PTR [ecx+32]
	test	eax, eax
	je	SHORT $L85009
; Line 67
	mov	ecx, DWORD PTR [eax]
	push	eax
	call	DWORD PTR [ecx+72]
$L85009:
; Line 69
	ret	0
@snd_stop_snd@4 ENDP
_TEXT	ENDS
PUBLIC	@snd_playing@4
; Function compile flags: /Ogsy
;	COMDAT @snd_playing@4
_TEXT	SEGMENT
_error_code$ = -4
@snd_playing@4 PROC NEAR				; COMDAT
; _pSnd$ = ecx
; Line 72
	push	ebp
	mov	ebp, esp
	push	ecx
; Line 75
	test	ecx, ecx
; Line 76
	je	SHORT $L85262
; Line 78
	mov	eax, DWORD PTR [ecx+32]
	test	eax, eax
; Line 79
	je	SHORT $L85262
; Line 84
	mov	ecx, DWORD PTR [eax]
	lea	edx, DWORD PTR _error_code$[ebp]
	push	edx
	push	eax
	call	DWORD PTR [ecx+36]
	test	eax, eax
	je	SHORT $L85017
$L85262:
; Line 86
	xor	eax, eax
; Line 89
	leave
	ret	0
$L85017:
; Line 88
	xor	eax, eax
	cmp	DWORD PTR _error_code$[ebp], 1
	sete	al
; Line 89
	leave
	ret	0
@snd_playing@4 ENDP
_TEXT	ENDS
PUBLIC	??_C@_0BP@LEGP@C?3?2Src?2Diablo?2Source?2SOUND?4CPP?$AA@ ; `string'
PUBLIC	@snd_play_snd@12
PUBLIC	@sound_dup_channel@4
PUBLIC	@sound_file_reload@8
EXTRN	@DSErrMsg@12:NEAR
EXTRN	__imp__GetTickCount@0:NEAR
;	COMDAT ??_C@_0BP@LEGP@C?3?2Src?2Diablo?2Source?2SOUND?4CPP?$AA@
_DATA	SEGMENT
??_C@_0BP@LEGP@C?3?2Src?2Diablo?2Source?2SOUND?4CPP?$AA@ DB 'C:\Src\Diabl'
	DB	'o\Source\SOUND.CPP', 00H			; `string'
; Function compile flags: /Ogsy
_DATA	ENDS
;	COMDAT @snd_play_snd@12
_TEXT	SEGMENT
_lPan$ = 8
_tc$ = -4
@snd_play_snd@12 PROC NEAR				; COMDAT
; _pSnd$ = ecx
; _lVolume$ = edx
; Line 92
	push	ecx
	push	ebx
	push	ebp
	push	esi
	push	edi
	mov	edi, ecx
	mov	ebp, edx
; Line 97
	test	edi, edi
	je	$L85029
	cmp	BYTE PTR _gbSoundOn, 0
	je	$L85029
; Line 101
	mov	esi, DWORD PTR [edi+32]
; Line 102
	test	esi, esi
	je	$L85029
; Line 106
	mov	ebx, DWORD PTR __imp__GetTickCount@0
	call	ebx
	mov	DWORD PTR _tc$[esp+20], eax
; Line 107
	sub	eax, DWORD PTR [edi+36]
	cmp	eax, 80					; 00000050H
	jae	SHORT $L85031
; Line 108
	call	ebx
; Line 109
	jmp	$L85266
$L85031:
; Line 112
	mov	ecx, edi
	call	@snd_playing@4
	test	eax, eax
	je	SHORT $L85265
; Line 113
	mov	ecx, DWORD PTR [edi+32]
	call	@sound_dup_channel@4
	mov	esi, eax
; Line 114
	xor	ebx, ebx
	cmp	esi, ebx
	je	SHORT $L85029
	jmp	SHORT $L85034
$L85265:
	xor	ebx, ebx
$L85034:
; Line 119
	add	ebp, DWORD PTR _sglSoundVolume
; Line 120
	mov	eax, -1600				; fffff9c0H
	cmp	ebp, eax
	jge	SHORT $L85035
; Line 121
	mov	ebp, eax
; Line 122
	jmp	SHORT $L85037
$L85035:
	cmp	ebp, ebx
	jle	SHORT $L85037
; Line 123
	xor	ebp, ebp
$L85037:
; Line 131
	mov	eax, DWORD PTR [esi]
	push	ebp
	push	esi
	call	DWORD PTR [eax+60]
; Line 132
	mov	eax, DWORD PTR [esi]
	push	DWORD PTR _lPan$[esp+16]
	push	esi
	call	DWORD PTR [eax+64]
; Line 134
	mov	eax, DWORD PTR [esi]
	push	ebx
	push	ebx
	push	ebx
	push	esi
	call	DWORD PTR [eax+48]
; Line 137
	cmp	eax, -2005401450			; 88780096H
	je	SHORT $L85042
; Line 138
	cmp	eax, ebx
	je	SHORT $L85046
; Line 139
	push	OFFSET FLAT:??_C@_0BP@LEGP@C?3?2Src?2Diablo?2Source?2SOUND?4CPP?$AA@ ; `string'
	mov	edx, 261				; 00000105H
	mov	ecx, eax
	call	@DSErrMsg@12
; Line 141
	jmp	SHORT $L85046
$L85042:
	mov	edx, esi
	mov	ecx, edi
	call	@sound_file_reload@8
	test	eax, eax
	je	SHORT $L85046
; Line 145
	mov	eax, DWORD PTR [esi]
	push	ebx
	push	ebx
	push	ebx
	push	esi
	call	DWORD PTR [eax+48]
$L85046:
; Line 149
	mov	eax, DWORD PTR _tc$[esp+20]
$L85266:
	mov	DWORD PTR [edi+36], eax
$L85029:
	pop	edi
	pop	esi
	pop	ebp
	pop	ebx
; Line 150
	pop	ecx
	ret	4
@snd_play_snd@12 ENDP
; Function compile flags: /Ogsy
_TEXT	ENDS
;	COMDAT @sound_dup_channel@4
_TEXT	SEGMENT
@sound_dup_channel@4 PROC NEAR				; COMDAT
; _DSB$ = ecx
; Line 157
	xor	eax, eax
	push	esi
	cmp	BYTE PTR _gbDupSounds, al
	je	SHORT $L85049
$L85053:
; Line 161
	cmp	DWORD PTR _DSBs[eax*4], 0
	je	SHORT $L85271
	inc	eax
	cmp	eax, 8
	jb	SHORT $L85053
$L85055:
; Line 174
	xor	eax, eax
$L85049:
	pop	esi
; Line 175
	ret	0
$L85271:
; Line 165
	lea	esi, DWORD PTR _DSBs[eax*4]
	mov	eax, DWORD PTR _sglpDS
	push	esi
	push	ecx
	mov	edx, DWORD PTR [eax]
	push	eax
	call	DWORD PTR [edx+20]
	test	eax, eax
; Line 167
	jne	SHORT $L85055
; Line 170
	mov	eax, DWORD PTR [esi]
	pop	esi
; Line 175
	ret	0
@sound_dup_channel@4 ENDP
_TEXT	ENDS
EXTRN	@WCloseFile@4:NEAR
EXTRN	@WOpenFile@12:NEAR
EXTRN	@WReadFile@12:NEAR
EXTRN	@WSetFilePointer@16:NEAR
; Function compile flags: /Ogsy
;	COMDAT @sound_file_reload@8
_TEXT	SEGMENT
_file$ = -4
_buf1$ = -12
_buf2$ = -24
_size1$ = -8
_size2$ = -20
_rv$ = -16
@sound_file_reload@8 PROC NEAR				; COMDAT
; _sound_file$ = ecx
; _DSB$ = edx
; Line 178
	push	ebp
	mov	ebp, esp
	sub	esp, 24					; 00000018H
	push	esi
	push	edi
	mov	edi, edx
	mov	esi, ecx
; Line 187
	push	edi
	mov	eax, DWORD PTR [edi]
	call	DWORD PTR [eax+80]
	test	eax, eax
	je	SHORT $L85071
; Line 189
	xor	eax, eax
	jmp	SHORT $L85064
$L85071:
; Line 193
	mov	ecx, DWORD PTR [esi+28]
	push	ebx
	xor	ebx, ebx
	lea	edx, DWORD PTR _file$[ebp]
	push	ebx
	mov	DWORD PTR _rv$[ebp], ebx
	call	@WOpenFile@12
; Line 194
	mov	edx, DWORD PTR [esi+24]
	mov	ecx, DWORD PTR _file$[ebp]
	push	ebx
	push	ebx
	call	@WSetFilePointer@16
; Line 203
	lea	ecx, DWORD PTR _size2$[ebp]
	mov	eax, DWORD PTR [edi]
	push	ebx
	push	ecx
	lea	ecx, DWORD PTR _buf2$[ebp]
	push	ecx
	lea	ecx, DWORD PTR _size1$[ebp]
	push	ecx
	lea	ecx, DWORD PTR _buf1$[ebp]
	push	ecx
	push	DWORD PTR [esi+20]
	push	ebx
	push	edi
	call	DWORD PTR [eax+44]
	test	eax, eax
	pop	ebx
	jne	SHORT $L85074
; Line 204
	push	DWORD PTR _size1$[ebp]
	mov	edx, DWORD PTR _buf1$[ebp]
	mov	ecx, DWORD PTR _file$[ebp]
	call	@WReadFile@12
; Line 205
	mov	eax, DWORD PTR [edi]
	push	DWORD PTR _size2$[ebp]
	push	DWORD PTR _buf2$[ebp]
	push	DWORD PTR _size1$[ebp]
	push	DWORD PTR _buf1$[ebp]
	push	edi
	call	DWORD PTR [eax+76]
	test	eax, eax
	jne	SHORT $L85074
; Line 206
	mov	DWORD PTR _rv$[ebp], 1
$L85074:
; Line 210
	mov	ecx, DWORD PTR _file$[ebp]
	call	@WCloseFile@4
; Line 212
	mov	eax, DWORD PTR _rv$[ebp]
$L85064:
	pop	edi
	pop	esi
; Line 213
	leave
	ret	0
@sound_file_reload@8 ENDP
_TEXT	ENDS
PUBLIC	@sound_file_load@4
PUBLIC	@sound_CreateSoundBuffer@4
PUBLIC	??_C@_0CA@LJJC@Invalid?5sound?5format?5on?5file?5?$CFs?$AA@ ; `string'
EXTRN	@LoadWaveFile@12:NEAR
EXTRN	@DiabloAllocPtr@4:NEAR
EXTRN	@mem_free_dbg@4:NEAR
EXTRN	_TermMsg:NEAR
EXTRN	_memcpy:NEAR
EXTRN	_memset:NEAR
;	COMDAT ??_C@_0CA@LJJC@Invalid?5sound?5format?5on?5file?5?$CFs?$AA@
_DATA	SEGMENT
??_C@_0CA@LJJC@Invalid?5sound?5format?5on?5file?5?$CFs?$AA@ DB 'Invalid s'
	DB	'ound format on file %s', 00H		; `string'
; Function compile flags: /Ogsy
_DATA	ENDS
;	COMDAT @sound_file_load@4
_TEXT	SEGMENT
_file$ = -16
_wave_file$ = -12
_buf1$ = -8
_buf2$ = -24
_size1$ = -4
_size2$ = -20
@sound_file_load@4 PROC NEAR				; COMDAT
; _path$ = ecx
; Line 216
	push	ebp
	mov	ebp, esp
	sub	esp, 24					; 00000018H
	push	ebx
; Line 224
	xor	ebx, ebx
	cmp	DWORD PTR _sglpDS, ebx
	push	edi
	mov	edi, ecx
	jne	SHORT $L85086
; Line 225
	xor	eax, eax
	jmp	$L85077
$L85086:
	push	esi
; Line 227
	push	ebx
	lea	edx, DWORD PTR _file$[ebp]
	mov	ecx, edi
	call	@WOpenFile@12
; Line 228
	push	40					; 00000028H
	pop	ecx
	call	@DiabloAllocPtr@4
	mov	esi, eax
; Line 229
	push	40					; 00000028H
	push	ebx
	push	esi
	call	_memset
	add	esp, 12					; 0000000cH
; Line 230
	mov	DWORD PTR [esi+28], edi
; Line 231
	call	DWORD PTR __imp__GetTickCount@0
	sub	eax, 81					; 00000051H
; Line 233
	lea	edi, DWORD PTR [esi+20]
	mov	DWORD PTR [esi+36], eax
	mov	ecx, DWORD PTR _file$[ebp]
	push	edi
	mov	edx, esi
	call	@LoadWaveFile@12
; Line 234
	cmp	eax, ebx
	mov	DWORD PTR _wave_file$[ebp], eax
	jne	SHORT $L85091
; Line 235
	push	DWORD PTR [esi+28]
	push	OFFSET FLAT:??_C@_0CA@LJJC@Invalid?5sound?5format?5on?5file?5?$CFs?$AA@ ; `string'
	call	_TermMsg
	pop	ecx
	pop	ecx
$L85091:
; Line 237
	mov	ecx, esi
	call	@sound_CreateSoundBuffer@4
; Line 242
	lea	edx, DWORD PTR _size2$[ebp]
	mov	eax, DWORD PTR [esi+32]
	push	ebx
	push	edx
	lea	edx, DWORD PTR _buf2$[ebp]
	mov	ecx, DWORD PTR [eax]
	push	edx
	lea	edx, DWORD PTR _size1$[ebp]
	push	edx
	lea	edx, DWORD PTR _buf1$[ebp]
	push	edx
	push	DWORD PTR [edi]
	push	ebx
	push	eax
	call	DWORD PTR [ecx+44]
; Line 244
	cmp	eax, ebx
	mov	edi, OFFSET FLAT:??_C@_0BP@LEGP@C?3?2Src?2Diablo?2Source?2SOUND?4CPP?$AA@ ; `string'
	je	SHORT $L85093
; Line 245
	push	edi
	mov	edx, 318				; 0000013eH
	mov	ecx, eax
	call	@DSErrMsg@12
$L85093:
; Line 247
	mov	eax, DWORD PTR [esi+24]
	push	DWORD PTR _size1$[ebp]
	add	eax, DWORD PTR _wave_file$[ebp]
	push	eax
	push	DWORD PTR _buf1$[ebp]
	call	_memcpy
	add	esp, 12					; 0000000cH
; Line 252
	mov	eax, DWORD PTR [esi+32]
	push	DWORD PTR _size2$[ebp]
	mov	ecx, DWORD PTR [eax]
	push	DWORD PTR _buf2$[ebp]
	push	DWORD PTR _size1$[ebp]
	push	DWORD PTR _buf1$[ebp]
	push	eax
	call	DWORD PTR [ecx+76]
; Line 254
	cmp	eax, ebx
	je	SHORT $L85094
; Line 255
	push	edi
	mov	edx, 325				; 00000145H
	mov	ecx, eax
	call	@DSErrMsg@12
$L85094:
; Line 257
	mov	ecx, DWORD PTR _wave_file$[ebp]
	call	@mem_free_dbg@4
; Line 258
	mov	ecx, DWORD PTR _file$[ebp]
	call	@WCloseFile@4
; Line 260
	mov	eax, esi
	pop	esi
$L85077:
	pop	edi
	pop	ebx
; Line 261
	leave
	ret	0
@sound_file_load@4 ENDP
; Function compile flags: /Ogsy
_TEXT	ENDS
;	COMDAT @sound_CreateSoundBuffer@4
_TEXT	SEGMENT
_DSB$ = -20
@sound_CreateSoundBuffer@4 PROC NEAR			; COMDAT
; _sound_file$ = ecx
; Line 265
	push	ebp
	mov	ebp, esp
	sub	esp, 20					; 00000014H
	push	esi
; Line 268
	push	20					; 00000014H
	lea	eax, DWORD PTR _DSB$[ebp]
	push	0
	push	eax
	mov	esi, ecx
	call	_memset
; Line 270
	mov	eax, DWORD PTR [esi+20]
	add	esp, 12					; 0000000cH
	mov	DWORD PTR _DSB$[ebp+8], eax
; Line 278
	mov	eax, DWORD PTR _sglpDS
	mov	DWORD PTR _DSB$[ebp+16], esi
	add	esi, 32					; 00000020H
	push	0
	lea	edx, DWORD PTR _DSB$[ebp]
	mov	DWORD PTR _DSB$[ebp], 20		; 00000014H
	mov	DWORD PTR _DSB$[ebp+4], 194		; 000000c2H
	mov	ecx, DWORD PTR [eax]
	push	esi
	push	edx
	push	eax
	call	DWORD PTR [ecx+12]
; Line 280
	test	eax, eax
	pop	esi
	je	SHORT $L85104
; Line 281
	push	OFFSET FLAT:??_C@_0BP@LEGP@C?3?2Src?2Diablo?2Source?2SOUND?4CPP?$AA@ ; `string'
	mov	edx, 282				; 0000011aH
	mov	ecx, eax
	call	@DSErrMsg@12
$L85104:
; Line 282
	leave
	ret	0
@sound_CreateSoundBuffer@4 ENDP
_TEXT	ENDS
PUBLIC	@sound_file_cleanup@4
; Function compile flags: /Ogsy
;	COMDAT @sound_file_cleanup@4
_TEXT	SEGMENT
@sound_file_cleanup@4 PROC NEAR				; COMDAT
; _sound_file$ = ecx
; Line 285
	push	esi
	mov	esi, ecx
; Line 286
	test	esi, esi
	je	SHORT $L85108
; Line 287
	mov	eax, DWORD PTR [esi+32]
	test	eax, eax
	je	SHORT $L85109
; Line 292
	mov	ecx, DWORD PTR [eax]
	push	eax
	call	DWORD PTR [ecx+72]
; Line 293
	mov	eax, DWORD PTR [esi+32]
	push	eax
	mov	ecx, DWORD PTR [eax]
	call	DWORD PTR [ecx+8]
; Line 295
	and	DWORD PTR [esi+32], 0
$L85109:
; Line 298
	mov	ecx, esi
	pop	esi
	jmp	@mem_free_dbg@4
$L85108:
	pop	esi
; Line 300
	ret	0
@sound_file_cleanup@4 ENDP
_TEXT	ENDS
PUBLIC	@snd_init@4
PUBLIC	@sound_load_volume@8
PUBLIC	@sound_create_primary_buffer@4
PUBLIC	@sound_DirectSoundCreate@12
PUBLIC	??_C@_0N@DCLE@Sound?5Volume?$AA@		; `string'
PUBLIC	??_C@_0N@FBBG@Music?5Volume?$AA@		; `string'
EXTRN	_SVidInitialize@4:NEAR
EXTRN	_SFileDdaInitialize@4:NEAR
;	COMDAT ??_C@_0N@DCLE@Sound?5Volume?$AA@
_DATA	SEGMENT
??_C@_0N@DCLE@Sound?5Volume?$AA@ DB 'Sound Volume', 00H	; `string'
_DATA	ENDS
;	COMDAT ??_C@_0N@FBBG@Music?5Volume?$AA@
_DATA	SEGMENT
??_C@_0N@FBBG@Music?5Volume?$AA@ DB 'Music Volume', 00H	; `string'
; Function compile flags: /Ogsy
_DATA	ENDS
;	COMDAT @snd_init@4
_TEXT	SEGMENT
@snd_init@4 PROC NEAR					; COMDAT
; _hWnd$ = ecx
; Line 303
	push	esi
	push	edi
	mov	edi, ecx
; Line 304
	mov	edx, OFFSET FLAT:_sglSoundVolume
	mov	ecx, OFFSET FLAT:??_C@_0N@DCLE@Sound?5Volume?$AA@ ; `string'
	call	@sound_load_volume@8
; Line 305
	mov	esi, -1600				; fffff9c0H
; Line 307
	mov	edx, OFFSET FLAT:_sglMusicVolume
	cmp	DWORD PTR _sglSoundVolume, esi
	mov	ecx, OFFSET FLAT:??_C@_0N@FBBG@Music?5Volume?$AA@ ; `string'
	setg	al
	mov	BYTE PTR _gbSoundOn, al
	call	@sound_load_volume@8
; Line 308
	cmp	DWORD PTR _sglMusicVolume, esi
; Line 310
	mov	edx, OFFSET FLAT:_sglpDS
	setg	al
	xor	esi, esi
	xor	ecx, ecx
	push	esi
	mov	BYTE PTR _gbMusicOn, al
	call	@sound_DirectSoundCreate@12
	test	eax, eax
	je	SHORT $L85118
; Line 311
	mov	DWORD PTR _sglpDS, esi
$L85118:
; Line 316
	mov	eax, DWORD PTR _sglpDS
	cmp	eax, esi
	je	SHORT $L85120
	mov	ecx, DWORD PTR [eax]
	push	3
	push	edi
	push	eax
	call	DWORD PTR [ecx+24]
	test	eax, eax
	jne	SHORT $L85120
; Line 318
	xor	ecx, ecx
	call	@sound_create_primary_buffer@4
$L85120:
; Line 320
	push	DWORD PTR _sglpDS
	call	_SVidInitialize@4
; Line 321
	push	DWORD PTR _sglpDS
	call	_SFileDdaInitialize@4
; Line 323
	cmp	DWORD PTR _sglpDS, esi
	pop	edi
	pop	esi
	setne	al
	mov	BYTE PTR _gbSndInited, al
; Line 324
	ret	0
@snd_init@4 ENDP
_TEXT	ENDS
PUBLIC	??_C@_06EMML@Diablo?$AA@			; `string'
EXTRN	_SRegLoadValue@16:NEAR
;	COMDAT ??_C@_06EMML@Diablo?$AA@
_DATA	SEGMENT
??_C@_06EMML@Diablo?$AA@ DB 'Diablo', 00H		; `string'
; Function compile flags: /Ogsy
_DATA	ENDS
;	COMDAT @sound_load_volume@8
_TEXT	SEGMENT
_v$ = -4
@sound_load_volume@8 PROC NEAR				; COMDAT
; _value_name$ = ecx
; _value$ = edx
; Line 327
	push	ebp
	mov	ebp, esp
	push	ecx
	push	esi
	mov	esi, edx
	push	edi
; Line 328
	mov	eax, DWORD PTR [esi]
	mov	DWORD PTR _v$[ebp], eax
; Line 329
	lea	eax, DWORD PTR _v$[ebp]
	push	eax
	push	0
	push	ecx
	push	OFFSET FLAT:??_C@_06EMML@Diablo?$AA@	; `string'
	call	_SRegLoadValue@16
	test	eax, eax
	jne	SHORT $L85292
; Line 330
	xor	ecx, ecx
	jmp	SHORT $L85129
$L85292:
	mov	ecx, DWORD PTR _v$[ebp]
$L85129:
; Line 334
	mov	eax, -1600				; fffff9c0H
	mov	DWORD PTR [esi], ecx
	cmp	ecx, eax
	jge	SHORT $L85131
; Line 335
	mov	DWORD PTR [esi], eax
; Line 336
	jmp	SHORT $L85133
$L85131:
	test	ecx, ecx
	jle	SHORT $L85133
; Line 337
	and	DWORD PTR [esi], 0
$L85133:
; Line 339
	mov	ecx, DWORD PTR [esi]
	push	100					; 00000064H
	mov	eax, ecx
	pop	edi
	cdq
	idiv	edi
	pop	edi
	sub	ecx, edx
	mov	DWORD PTR [esi], ecx
	pop	esi
; Line 340
	leave
	ret	0
@sound_load_volume@8 ENDP
_TEXT	ENDS
EXTRN	@LoadWaveFormat@8:NEAR
; Function compile flags: /Ogsy
;	COMDAT @sound_create_primary_buffer@4
_TEXT	SEGMENT
_music_track$ = -24
_dsbuf$ = -44
_format$ = -20
_dsbcaps$85146 = -140
@sound_create_primary_buffer@4 PROC NEAR		; COMDAT
; _music_track$ = ecx
; Line 343
	push	ebp
	mov	ebp, esp
	sub	esp, 140				; 0000008cH
	push	edi
; Line 348
	xor	edi, edi
	cmp	ecx, edi
	mov	DWORD PTR _music_track$[ebp], ecx
	jne	SHORT $L85144
; Line 349
	push	20					; 00000014H
	lea	eax, DWORD PTR _dsbuf$[ebp]
	push	edi
	push	eax
	call	_memset
; Line 356
	mov	eax, DWORD PTR _sglpDS
	add	esp, 12					; 0000000cH
	lea	edx, DWORD PTR _dsbuf$[ebp]
	mov	DWORD PTR _dsbuf$[ebp], 20		; 00000014H
	push	edi
	mov	DWORD PTR _dsbuf$[ebp+4], 1
	mov	ecx, DWORD PTR [eax]
	push	OFFSET FLAT:_sglpDSB
	push	edx
	push	eax
	call	DWORD PTR [ecx+12]
; Line 358
	cmp	eax, edi
	je	SHORT $L85144
; Line 359
	push	OFFSET FLAT:??_C@_0BP@LEGP@C?3?2Src?2Diablo?2Source?2SOUND?4CPP?$AA@ ; `string'
	mov	edx, 375				; 00000177H
	mov	ecx, eax
	call	@DSErrMsg@12
$L85144:
; Line 362
	cmp	DWORD PTR _sglpDSB, edi
	je	$L85145
; Line 369
	mov	eax, DWORD PTR _sglpDS
	lea	edx, DWORD PTR _dsbcaps$85146[ebp]
	mov	DWORD PTR _dsbcaps$85146[ebp], 96	; 00000060H
	push	edx
	mov	ecx, DWORD PTR [eax]
	push	eax
	call	DWORD PTR [ecx+16]
; Line 371
	cmp	eax, edi
	je	SHORT $L85148
; Line 372
	push	OFFSET FLAT:??_C@_0BP@LEGP@C?3?2Src?2Diablo?2Source?2SOUND?4CPP?$AA@ ; `string'
	mov	edx, 383				; 0000017fH
	mov	ecx, eax
	call	@DSErrMsg@12
$L85148:
; Line 374
	mov	ecx, DWORD PTR _music_track$[ebp]
	cmp	ecx, edi
	je	SHORT $L85150
	lea	edx, DWORD PTR _format$[ebp]
	call	@LoadWaveFormat@8
	test	eax, eax
	jne	SHORT $L85149
$L85150:
; Line 375
	push	18					; 00000012H
	lea	eax, DWORD PTR _format$[ebp]
	push	edi
	push	eax
	call	_memset
	add	esp, 12					; 0000000cH
; Line 376
	mov	WORD PTR _format$[ebp], 1
; Line 377
	mov	DWORD PTR _format$[ebp+4], 22050	; 00005622H
; Line 378
	mov	WORD PTR _format$[ebp+14], 16		; 00000010H
; Line 379
	mov	WORD PTR _format$[ebp+16], di
$L85149:
; Line 383
	movzx	eax, WORD PTR _format$[ebp+14]
	add	eax, eax
	push	8
	cdq
	pop	ecx
	mov	WORD PTR _format$[ebp+2], 2
	idiv	ecx
; Line 389
	lea	edx, DWORD PTR _format$[ebp]
	push	edx
	mov	WORD PTR _format$[ebp+12], ax
	movzx	eax, ax
	imul	eax, DWORD PTR _format$[ebp+4]
	mov	DWORD PTR _format$[ebp+8], eax
	mov	eax, DWORD PTR _sglpDSB
	push	eax
	mov	ecx, DWORD PTR [eax]
	call	DWORD PTR [ecx+56]
$L85145:
	pop	edi
; Line 392
	leave
	ret	0
@sound_create_primary_buffer@4 ENDP
_TEXT	ENDS
PUBLIC	??_C@_0L@PLHI@dsound?4dll?$AA@			; `string'
PUBLIC	??_C@_0BC@OJFH@DirectSoundCreate?$AA@		; `string'
EXTRN	__imp__GetLastError@0:NEAR
EXTRN	__imp__LoadLibraryA@4:NEAR
EXTRN	@ErrDlg@16:NEAR
EXTRN	__imp__GetProcAddress@8:NEAR
;	COMDAT ??_C@_0L@PLHI@dsound?4dll?$AA@
_DATA	SEGMENT
??_C@_0L@PLHI@dsound?4dll?$AA@ DB 'dsound.dll', 00H	; `string'
_DATA	ENDS
;	COMDAT ??_C@_0BC@OJFH@DirectSoundCreate?$AA@
_DATA	SEGMENT
??_C@_0BC@OJFH@DirectSoundCreate?$AA@ DB 'DirectSoundCreate', 00H ; `string'
; Function compile flags: /Ogsy
_DATA	ENDS
;	COMDAT @sound_DirectSoundCreate@12
_TEXT	SEGMENT
_lpGuid$ = -4
_pUnkOuter$ = 8
@sound_DirectSoundCreate@12 PROC NEAR			; COMDAT
; _lpGuid$ = ecx
; _ppDS$ = edx
; Line 396
	push	ecx
; Line 400
	cmp	DWORD PTR _hDsound_dll, 0
	push	ebx
	push	ebp
	push	esi
	mov	esi, DWORD PTR __imp__GetLastError@0
	push	edi
	mov	ebp, edx
	mov	DWORD PTR _lpGuid$[esp+20], ecx
	mov	edi, OFFSET FLAT:??_C@_0BP@LEGP@C?3?2Src?2Diablo?2Source?2SOUND?4CPP?$AA@ ; `string'
	jne	SHORT $L85170
; Line 401
	push	OFFSET FLAT:??_C@_0L@PLHI@dsound?4dll?$AA@ ; `string'
	call	DWORD PTR __imp__LoadLibraryA@4
; Line 402
	test	eax, eax
	mov	DWORD PTR _hDsound_dll, eax
	jne	SHORT $L85170
; Line 403
	push	422					; 000001a6H
	push	edi
	call	esi
	mov	edx, eax
	push	108					; 0000006cH
	pop	ecx
	call	@ErrDlg@16
$L85170:
; Line 407
	push	OFFSET FLAT:??_C@_0BC@OJFH@DirectSoundCreate?$AA@ ; `string'
	push	DWORD PTR _hDsound_dll
	call	DWORD PTR __imp__GetProcAddress@8
	mov	ebx, eax
; Line 408
	test	ebx, ebx
	jne	SHORT $L85177
; Line 409
	push	427					; 000001abH
	push	edi
	call	esi
	mov	edx, eax
	push	108					; 0000006cH
	pop	ecx
	call	@ErrDlg@16
$L85177:
; Line 411
	push	DWORD PTR _pUnkOuter$[esp+16]
	push	ebp
	push	DWORD PTR _lpGuid$[esp+28]
	call	ebx
	pop	edi
	pop	esi
	pop	ebp
	pop	ebx
; Line 412
	pop	ecx
	ret	4
@sound_DirectSoundCreate@12 ENDP
_TEXT	ENDS
PUBLIC	_sound_cleanup
PUBLIC	@sound_store_volume@8
EXTRN	_SVidDestroy@0:NEAR
EXTRN	_SFileDdaDestroy@0:NEAR
; Function compile flags: /Ogsy
;	COMDAT _sound_cleanup
_TEXT	SEGMENT
_sound_cleanup PROC NEAR				; COMDAT
; Line 416
	xor	ecx, ecx
	inc	ecx
	call	@snd_update@4
; Line 417
	call	_SVidDestroy@0
; Line 418
	call	_SFileDdaDestroy@0
; Line 420
	mov	eax, DWORD PTR _sglpDS
	test	eax, eax
	je	SHORT $L85179
; Line 424
	mov	ecx, DWORD PTR [eax]
	push	eax
	call	DWORD PTR [ecx+8]
; Line 426
	and	DWORD PTR _sglpDS, 0
$L85179:
; Line 429
	cmp	BYTE PTR _gbSndInited, 0
	je	SHORT $L85181
; Line 431
	mov	edx, DWORD PTR _sglSoundVolume
	and	BYTE PTR _gbSndInited, 0
	mov	ecx, OFFSET FLAT:??_C@_0N@DCLE@Sound?5Volume?$AA@ ; `string'
	call	@sound_store_volume@8
; Line 432
	mov	edx, DWORD PTR _sglMusicVolume
	mov	ecx, OFFSET FLAT:??_C@_0N@FBBG@Music?5Volume?$AA@ ; `string'
	jmp	@sound_store_volume@8
$L85181:
; Line 434
	ret	0
_sound_cleanup ENDP
_TEXT	ENDS
EXTRN	_SRegSaveValue@16:NEAR
; Function compile flags: /Ogsy
;	COMDAT @sound_store_volume@8
_TEXT	SEGMENT
@sound_store_volume@8 PROC NEAR				; COMDAT
; _key$ = ecx
; _value$ = edx
; Line 438
	push	edx
	push	0
	push	ecx
	push	OFFSET FLAT:??_C@_06EMML@Diablo?$AA@	; `string'
	call	_SRegSaveValue@16
; Line 439
	ret	0
@sound_store_volume@8 ENDP
_TEXT	ENDS
PUBLIC	_music_stop
EXTRN	_SFileCloseFile@4:NEAR
EXTRN	_SFileDdaEnd@4:NEAR
; Function compile flags: /Ogsy
;	COMDAT _music_stop
_TEXT	SEGMENT
_music_stop PROC NEAR					; COMDAT
; Line 443
	mov	eax, DWORD PTR _sgpMusicTrack
	test	eax, eax
	je	SHORT $L85188
; Line 444
	push	eax
	call	_SFileDdaEnd@4
; Line 445
	push	DWORD PTR _sgpMusicTrack
	call	_SFileCloseFile@4
; Line 446
	and	DWORD PTR _sgpMusicTrack, 0
; Line 447
	mov	DWORD PTR _sgnMusicTrack, 6
$L85188:
; Line 449
	ret	0
_music_stop ENDP
_TEXT	ENDS
PUBLIC	@music_start@4
EXTRN	_SFileDdaBeginEx@28:NEAR
EXTRN	_SFileOpenFile@8:NEAR
; Function compile flags: /Ogsy
;	COMDAT @music_start@4
_TEXT	SEGMENT
@music_start@4 PROC NEAR				; COMDAT
; _nTrack$ = ecx
; Line 452
	push	ebx
	push	esi
	mov	esi, ecx
; Line 456
	call	_music_stop
; Line 457
	xor	ebx, ebx
	cmp	DWORD PTR _sglpDS, ebx
	je	SHORT $L85197
	cmp	BYTE PTR _gbMusicOn, bl
	je	SHORT $L85197
	push	edi
; Line 461
	push	OFFSET FLAT:_sgpMusicTrack
	push	DWORD PTR _sgszMusicTracks[esi*4]
	call	_SFileOpenFile@8
; Line 465
	mov	ecx, DWORD PTR _sgpMusicTrack
	mov	edi, eax
	call	@sound_create_primary_buffer@4
; Line 466
	cmp	edi, ebx
	pop	edi
	jne	SHORT $L85195
; Line 467
	mov	DWORD PTR _sgpMusicTrack, ebx
; Line 468
	jmp	SHORT $L85197
$L85195:
; Line 469
	push	ebx
	push	ebx
	push	DWORD PTR _sglMusicVolume
	mov	eax, 262144				; 00040000H
	push	ebx
	push	eax
	push	eax
	push	DWORD PTR _sgpMusicTrack
	call	_SFileDdaBeginEx@28
; Line 470
	mov	DWORD PTR _sgnMusicTrack, esi
$L85197:
	pop	esi
	pop	ebx
; Line 473
	ret	0
@music_start@4 ENDP
_TEXT	ENDS
PUBLIC	@sound_disable_music@4
; Function compile flags: /Ogsy
;	COMDAT @sound_disable_music@4
_TEXT	SEGMENT
@sound_disable_music@4 PROC NEAR			; COMDAT
; _disable$ = ecx
; Line 477
	test	ecx, ecx
	je	SHORT $L85201
; Line 478
	jmp	_music_stop
$L85201:
; Line 479
	mov	ecx, DWORD PTR _sgnMusicTrack
	cmp	ecx, 6
	je	SHORT $L85203
; Line 480
	jmp	@music_start@4
$L85203:
; Line 482
	ret	0
@sound_disable_music@4 ENDP
_TEXT	ENDS
PUBLIC	@sound_get_or_set_music_volume@4
EXTRN	_SFileDdaSetVolume@12:NEAR
; Function compile flags: /Ogsy
;	COMDAT @sound_get_or_set_music_volume@4
_TEXT	SEGMENT
@sound_get_or_set_music_volume@4 PROC NEAR		; COMDAT
; _volume$ = ecx
; Line 486
	cmp	ecx, 1
; Line 487
	je	SHORT $L85208
; Line 491
	mov	eax, DWORD PTR _sgpMusicTrack
	mov	DWORD PTR _sglMusicVolume, ecx
	test	eax, eax
	je	SHORT $L85208
; Line 492
	push	0
	push	ecx
	push	eax
	call	_SFileDdaSetVolume@12
$L85208:
; Line 494
	mov	eax, DWORD PTR _sglMusicVolume
; Line 495
	ret	0
@sound_get_or_set_music_volume@4 ENDP
_TEXT	ENDS
PUBLIC	@sound_get_or_set_sound_volume@4
; Function compile flags: /Ogsy
;	COMDAT @sound_get_or_set_sound_volume@4
_TEXT	SEGMENT
@sound_get_or_set_sound_volume@4 PROC NEAR		; COMDAT
; _volume$ = ecx
; Line 498
	mov	eax, ecx
; Line 499
	cmp	eax, 1
	jne	SHORT $L85212
; Line 500
	mov	eax, DWORD PTR _sglSoundVolume
; Line 505
	ret	0
$L85212:
; Line 502
	mov	DWORD PTR _sglSoundVolume, eax
; Line 505
	ret	0
@sound_get_or_set_sound_volume@4 ENDP
_TEXT	ENDS
END
