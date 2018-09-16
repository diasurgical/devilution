// ref: 0x10010306
void UNKCALL TitleSnd_10010306(void *arg) { return; }
/* {
	dword_1002A594 = (int (__stdcall *)(_DWORD))arg;
} */
// 1002A594: using guessed type int (__stdcall *dword_1002A594)(_DWORD);

// ref: 0x1001030D
void TitleSnd_1001030D() { return; }
/* {
	dword_1002A594 = 0;
} */
// 1002A594: using guessed type int (__stdcall *dword_1002A594)(_DWORD);

// ref: 0x10010315
int (__stdcall *TitleSnd_10010315())(_DWORD) { return 0; }
/* {
	int (__stdcall *result)(_DWORD); // eax

	result = dword_1002A594;
	if ( dword_1002A594 )
		result = (int (__stdcall *)(_DWORD))dword_1002A594("sfx\\items\\titlemov.wav");
	return result;
} */
// 1002A594: invalid function type has been ignored
// 1002A594: using guessed type int (__stdcall *dword_1002A594)(_DWORD);

// ref: 0x1001031F
int (__stdcall *TitleSnd_1001031F())(_DWORD) { return 0; }
/* {
	int (__stdcall *result)(_DWORD); // eax

	result = dword_1002A594;
	if ( dword_1002A594 )
		result = (int (__stdcall *)(_DWORD))dword_1002A594("sfx\\items\\titlslct.wav");
	return result;
} */
// 1002A594: using guessed type int (__stdcall *dword_1002A594)(_DWORD);

// ref: 0x1001032E
signed int TitleSnd_1001032E() { return 0; }
/* {
	signed int result; // eax

	result = 2139095040;
	dword_1002A590 = 2139095040;
	return result;
} */
// 1002A590: using guessed type int dword_1002A590;
