// ref: 0x1000523E
signed int __stdcall UiGetDefaultStats(int a1, _WORD *a2) { return 0; }
/* {
	if ( !a2 )
		return 0;
	*a2 = word_10022958[4 * a1];
	a2[1] = word_1002295A[4 * a1];
	a2[2] = word_1002295C[4 * a1];
	a2[3] = word_1002295E[4 * a1];
	return 1;
} */
// 10022958: using guessed type short word_10022958[];
// 1002295A: using guessed type short word_1002295A[];
// 1002295C: using guessed type short word_1002295C[];

// ref: 0x10005287
signed int CreaStat_10005287() { return 0; }
/* {
	signed int result; // eax

	result = 2139095040;
	dword_100296E0 = 2139095040;
	return result;
} */
// 100296E0: using guessed type int dword_100296E0;
