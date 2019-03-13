; Listing generated by Microsoft (R) Optimizing Compiler Version 12.00.9044.0 

	TITLE	Source/movie.cpp
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
;	COMDAT ??_C@_0BD@JNPG@Sfx?2Misc?2blank?4wav?$AA@
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
CRT$XCU	SEGMENT DWORD USE32 PUBLIC ''
CRT$XCU	ENDS
;	COMDAT @play_movie@8
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT _MovieWndProc@16
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
FLAT	GROUP _DATA, CONST, _BSS, CRT$XCU
	ASSUME	CS: FLAT, DS: FLAT, SS: FLAT
endif

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

_DATA	SEGMENT
COMM	_movie_playing:BYTE
COMM	_loop_movie:DWORD
_DATA	ENDS
PUBLIC	@play_movie@8
PUBLIC	_MovieWndProc@16
PUBLIC	??_C@_0BD@JNPG@Sfx?2Misc?2blank?4wav?$AA@	; `string'
EXTRN	_ghMainWnd:DWORD
EXTRN	_sfx_stop:NEAR
EXTRN	_SVidPlayBegin@28:NEAR
EXTRN	_SVidPlayEnd@4:NEAR
EXTRN	_gbActive:DWORD
EXTRN	_effects_play_sound@4:NEAR
EXTRN	@SetWindowProc@4:NEAR
EXTRN	_SVidPlayContinue:NEAR
EXTRN	__imp__UpdateWindow@4:NEAR
EXTRN	__imp__InvalidateRect@12:NEAR
EXTRN	@sound_disable_music@4:NEAR
EXTRN	__imp__TranslateMessage@4:NEAR
EXTRN	__imp__DispatchMessageA@4:NEAR
EXTRN	__imp__PeekMessageA@20:NEAR
;	COMDAT ??_C@_0BD@JNPG@Sfx?2Misc?2blank?4wav?$AA@
; File Source/movie.cpp
_DATA	SEGMENT
??_C@_0BD@JNPG@Sfx?2Misc?2blank?4wav?$AA@ DB 'Sfx\Misc\blank.wav', 00H ; `string'
; Function compile flags: /Ogsy
_DATA	ENDS
;	COMDAT @play_movie@8
_TEXT	SEGMENT
_user_can_close$ = -8
_video_stream$ = -4
_Msg$84992 = -36
@play_movie@8 PROC NEAR					; COMDAT
; _pszMovie$ = ecx
; _user_can_close$ = edx
; Line 9
	push	ebp
	mov	ebp, esp
	sub	esp, 36					; 00000024H
	push	ebx
; Line 13
	xor	ebx, ebx
	cmp	DWORD PTR _gbActive, ebx
	push	esi
	mov	DWORD PTR _user_can_close$[ebp], edx
	mov	esi, ecx
	je	$L84986
	push	edi
; Line 17
	mov	ecx, OFFSET FLAT:_MovieWndProc@16
	call	@SetWindowProc@4
	mov	edi, eax
; Line 18
	push	ebx
	push	ebx
	push	DWORD PTR _ghMainWnd
	call	DWORD PTR __imp__InvalidateRect@12
; Line 19
	push	DWORD PTR _ghMainWnd
	call	DWORD PTR __imp__UpdateWindow@4
; Line 21
	xor	ecx, ecx
	mov	BYTE PTR _movie_playing, 1
	inc	ecx
	call	@sound_disable_music@4
; Line 22
	call	_sfx_stop
; Line 23
	push	OFFSET FLAT:??_C@_0BD@JNPG@Sfx?2Misc?2blank?4wav?$AA@ ; `string'
	call	_effects_play_sound@4
; Line 25
	lea	eax, DWORD PTR _video_stream$[ebp]
	push	eax
	mov	eax, DWORD PTR _loop_movie
	neg	eax
	sbb	eax, eax
	and	eax, -1835008				; ffe40000H
	add	eax, 271058952				; 10280808H
	push	eax
	push	ebx
	push	ebx
	push	ebx
	push	ebx
	push	esi
	call	_SVidPlayBegin@28
; Line 26
	cmp	DWORD PTR _video_stream$[ebp], ebx
	je	SHORT $L85004
	mov	esi, DWORD PTR __imp__PeekMessageA@20
$L84994:
; Line 29
	cmp	DWORD PTR _gbActive, ebx
	je	SHORT $L85036
	cmp	DWORD PTR _user_can_close$[ebp], ebx
	je	SHORT $L85002
	cmp	BYTE PTR _movie_playing, bl
	je	SHORT $L85036
; Line 31
	jmp	SHORT $L85002
$L85000:
; Line 32
	cmp	DWORD PTR _Msg$84992[ebp+4], 18		; 00000012H
	je	SHORT $L85002
; Line 33
	lea	eax, DWORD PTR _Msg$84992[ebp]
	push	eax
	call	DWORD PTR __imp__TranslateMessage@4
; Line 34
	lea	eax, DWORD PTR _Msg$84992[ebp]
	push	eax
	call	DWORD PTR __imp__DispatchMessageA@4
$L85002:
	push	1
	push	ebx
	push	ebx
	lea	eax, DWORD PTR _Msg$84992[ebp]
	push	ebx
	push	eax
	call	esi
	test	eax, eax
	jne	SHORT $L85000
; Line 37
	call	_SVidPlayContinue
	test	eax, eax
	je	SHORT $L85036
; Line 28
	cmp	DWORD PTR _video_stream$[ebp], ebx
	jne	SHORT $L84994
$L85036:
; Line 40
	cmp	DWORD PTR _video_stream$[ebp], ebx
	je	SHORT $L85004
; Line 41
	push	DWORD PTR _video_stream$[ebp]
	call	_SVidPlayEnd@4
$L85004:
; Line 43
	mov	ecx, edi
	call	@SetWindowProc@4
; Line 44
	xor	ecx, ecx
	call	@sound_disable_music@4
	pop	edi
$L84986:
	pop	esi
	pop	ebx
; Line 45
	leave
	ret	0
@play_movie@8 ENDP
_TEXT	ENDS
EXTRN	_MainWndProc@16:NEAR
; Function compile flags: /Ogsy
;	COMDAT _MovieWndProc@16
_TEXT	SEGMENT
_hWnd$ = 8
_Msg$ = 12
_wParam$ = 16
_lParam$ = 20
_MovieWndProc@16 PROC NEAR				; COMDAT
; Line 49
	push	ebp
	mov	ebp, esp
; Line 50
	mov	eax, DWORD PTR _Msg$[ebp]
	sub	eax, 256				; 00000100H
	je	SHORT $L85018
	dec	eax
	dec	eax
	je	SHORT $L85018
	sub	eax, 16					; 00000010H
	je	SHORT $L85019
	sub	eax, 239				; 000000efH
	je	SHORT $L85018
	sub	eax, 3
	jne	SHORT $L85015
$L85018:
; Line 55
	and	BYTE PTR _movie_playing, 0
$L85015:
; Line 65
	push	DWORD PTR _lParam$[ebp]
	push	DWORD PTR _wParam$[ebp]
	push	DWORD PTR _Msg$[ebp]
	push	DWORD PTR _hWnd$[ebp]
	call	_MainWndProc@16
$L85013:
; Line 66
	pop	ebp
	ret	16					; 00000010H
$L85019:
; Line 58
	cmp	DWORD PTR _wParam$[ebp], 61536		; 0000f060H
	jne	SHORT $L85015
; Line 59
	and	BYTE PTR _movie_playing, 0
; Line 60
	xor	eax, eax
	jmp	SHORT $L85013
_MovieWndProc@16 ENDP
_TEXT	ENDS
END
