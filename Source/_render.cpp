#pragma warning (disable : 4731) // frame pointer register 'ebp' modified by inline assembly code

void __fastcall drawTopArchesUpperScreen(unsigned char *pbDst)
{
	unsigned char *dst; // edi MAPDST
	unsigned char *tbl; // ebx
	unsigned char *src; // esi MAPDST
	short cel_type_16; // ax MAPDST

	gpCelFrame = (unsigned char *)speed_cel_frame_num_from_light_index_frame_num;
	dst = pbDst;
	if ( !(_BYTE)light_table_index )
	{
		if ( level_cel_block & 0x8000 )
			level_cel_block = *(_DWORD *)&gpCelFrame[64 * (level_cel_block & 0xFFF)]
							+ (unsigned short)(level_cel_block & 0xF000);
		src = (unsigned char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
		cel_type_16 = ((level_cel_block >> 12) & 7) + 8;
		goto LABEL_11;
	}
	if ( (_BYTE)light_table_index != lightmax )
	{
		if ( !(level_cel_block & 0x8000) )
		{
			src = (unsigned char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
			tbl = (unsigned char *)&pLightTbl[256 * light_table_index];
			cel_type_16 = (unsigned char)(level_cel_block >> 12);
			__asm {
				xor		edx, edx
				xor		ecx, ecx
				mov		ebx, tbl
				mov		edi, dst
				mov		esi, src
			}
			switch ( cel_type_16 )
			{
				case 0: // upper (top transparent), with lighting
					__asm {
						push	ebp
						mov		ebp, 10h
					loc_46325B:
						cmp		edi, gpBufEnd
						jb		short loc_4632BF
						mov		ecx, 8
					loc_463268:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, ah
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi+1], dl
						mov		dl, ah
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-1], dl
						jnz		short loc_463268
						sub		edi, 320h
						cmp		edi, gpBufEnd
						jb		short loc_4632BF
						mov		ecx, 8
					loc_463299:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi], dl
						mov		dl, al
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-2], dl
						jnz		short loc_463299
						sub		edi, 320h
						dec		ebp
						jnz		short loc_46325B
					loc_4632BF:
						pop		ebp
					}
					break;
				case 1: // upper (top transparent), with lighting
					__asm {
						push	ebp
						mov		eax, edi
						and		eax, 1
						mov		WorldBoolFlag, eax
						mov		ebp, 20h
					loc_4632D5:
						mov		edx, 20h
					loc_4632DA:
						xor		eax, eax
						mov		al, [esi]
						inc		esi
						test	al, al
						js		loc_4633F8
						sub		edx, eax
						cmp		edi, gpBufEnd
						jb		loc_46341F
						mov		ecx, eax
						mov		eax, edi
						and		eax, 1
						cmp		eax, WorldBoolFlag
						jnz		short loc_463377
						push	edx
						shr		ecx, 1
						jb		short loc_463340
						shr		ecx, 1
						jnb		short loc_46331C
						mov		dl, [esi+1]
						mov		dl, [ebx+edx]
						add		esi, 2
						mov		[edi+1], dl
						add		edi, 2
					loc_46331C:
						test	cl, cl
						jz		short loc_46333E
					loc_463320:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, ah
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi+1], dl
						mov		dl, ah
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-1], dl
						jnz		short loc_463320
					loc_46333E:
						jmp		short loc_463374

					loc_463340:
						inc		esi
						inc		edi
						shr		ecx, 1
						jnb		short loc_463353
						mov		dl, [esi]
						mov		dl, [ebx+edx]
						add		esi, 2
						mov		[edi], dl
						add		edi, 2
					loc_463353:
						test	cl, cl
						jz		short loc_463374
					loc_463357:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi], dl
						mov		dl, al
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-2], dl
						jnz		short loc_463357
					loc_463374:
						pop		edx
						jmp		short loc_4633EF

					loc_463377:
						push	edx
						shr		ecx, 1
						jb		short loc_4633B0
						shr		ecx, 1
						jnb		short loc_46338D
						mov		dl, [esi]
						mov		dl, [ebx+edx]
						add		esi, 2
						mov		[edi], dl
						add		edi, 2
					loc_46338D:
						test	cl, cl
						jz		short loc_4633AE
					loc_463391:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi], dl
						mov		dl, al
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-2], dl
						jnz		short loc_463391
					loc_4633AE:
						jmp		short loc_4633EE

					loc_4633B0:
						mov		dl, [esi]
						mov		dl, [ebx+edx]
						inc		esi
						mov		[edi], dl
						inc		edi
						shr		ecx, 1
						jnb		short loc_4633CC
						mov		dl, [esi+1]
						mov		dl, [ebx+edx]
						add		esi, 2
						mov		[edi+1], dl
						add		edi, 2
					loc_4633CC:
						test	cl, cl
						jz		short loc_4633EE
					loc_4633D0:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, ah
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi+1], dl
						mov		dl, ah
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-1], dl
						jnz		short loc_4633D0
					loc_4633EE:
						pop		edx
					loc_4633EF:
						test	edx, edx
						jz		short loc_463404
						jmp		loc_4632DA

					loc_4633F8:
						neg		al
						add		edi, eax
						sub		edx, eax
						jnz		loc_4632DA
					loc_463404:
						mov		eax, WorldBoolFlag
						inc		eax
						and		eax, 1
						mov		WorldBoolFlag, eax
						sub		edi, 320h
						dec		ebp
						jnz		loc_4632D5
					loc_46341F:
						pop		ebp
					}
					break;
				case 2: // upper (top transparent), with lighting
					__asm {
						push	ebp
						xor		eax, eax
						mov		WorldBoolFlag, eax
						mov		ebp, 1Eh
					loc_463432:
						cmp		edi, gpBufEnd
						jb		loc_463692
						add		edi, ebp
						mov		ecx, 20h
						sub		ecx, ebp
						mov		eax, WorldBoolFlag
						inc		eax
						and		eax, 1
						mov		WorldBoolFlag, eax
						jz		short loc_4634D2
						mov		edx, ecx
						and		edx, 2
						add		esi, edx
						shr		ecx, 1
						jb		short loc_463499
						shr		ecx, 1
						jnb		short loc_463475
						mov		dl, [esi+1]
						mov		dl, [ebx+edx]
						add		esi, 2
						mov		[edi+1], dl
						add		edi, 2
					loc_463475:
						test	cl, cl
						jz		short loc_463497
					loc_463479:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, ah
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi+1], dl
						mov		dl, ah
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-1], dl
						jnz		short loc_463479
					loc_463497:
						jmp		short loc_4634CD

					loc_463499:
						inc		esi
						inc		edi
						shr		ecx, 1
						jnb		short loc_4634AC
						mov		dl, [esi]
						mov		dl, [ebx+edx]
						add		esi, 2
						mov		[edi], dl
						add		edi, 2
					loc_4634AC:
						test	cl, cl
						jz		short loc_4634CD
					loc_4634B0:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi], dl
						mov		dl, al
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-2], dl
						jnz		short loc_4634B0
					loc_4634CD:
						jmp		loc_46354F

					loc_4634D2:
						mov		edx, ecx
						and		edx, 2
						add		esi, edx
						shr		ecx, 1
						jb		short loc_463511
						shr		ecx, 1
						jnb		short loc_4634EE
						mov		dl, [esi]
						mov		dl, [ebx+edx]
						add		esi, 2
						mov		[edi], dl
						add		edi, 2
					loc_4634EE:
						test	cl, cl
						jz		short loc_46350F
					loc_4634F2:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi], dl
						mov		dl, al
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-2], dl
						jnz		short loc_4634F2
					loc_46350F:
						jmp		short loc_46354F

					loc_463511:
						mov		dl, [esi]
						mov		dl, [ebx+edx]
						inc		esi
						mov		[edi], dl
						inc		edi
						shr		ecx, 1
						jnb		short loc_46352D
						mov		dl, [esi+1]
						mov		dl, [ebx+edx]
						add		esi, 2
						mov		[edi+1], dl
						add		edi, 2
					loc_46352D:
						test	cl, cl
						jz		short loc_46354F
					loc_463531:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, ah
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi+1], dl
						mov		dl, ah
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-1], dl
						jnz		short loc_463531
					loc_46354F:
						sub		edi, 320h
						sub		ebp, 2
						jge		loc_463432
						mov		ebp, 2
					loc_463563:
						cmp		edi, gpBufEnd
						jb		loc_463692
						add		edi, ebp
						mov		ecx, 20h
						sub		ecx, ebp
						mov		eax, WorldBoolFlag
						inc		eax
						and		eax, 1
						mov		WorldBoolFlag, eax
						jz		short loc_463603
						mov		edx, ecx
						and		edx, 2
						add		esi, edx
						shr		ecx, 1
						jb		short loc_4635CA
						shr		ecx, 1
						jnb		short loc_4635A6
						mov		dl, [esi+1]
						mov		dl, [ebx+edx]
						add		esi, 2
						mov		[edi+1], dl
						add		edi, 2
					loc_4635A6:
						test	cl, cl
						jz		short loc_4635C8
					loc_4635AA:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, ah
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi+1], dl
						mov		dl, ah
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-1], dl
						jnz		short loc_4635AA
					loc_4635C8:
						jmp		short loc_4635FE

					loc_4635CA:
						inc		esi
						inc		edi
						shr		ecx, 1
						jnb		short loc_4635DD
						mov		dl, [esi]
						mov		dl, [ebx+edx]
						add		esi, 2
						mov		[edi], dl
						add		edi, 2
					loc_4635DD:
						test	cl, cl
						jz		short loc_4635FE
					loc_4635E1:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi], dl
						mov		dl, al
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-2], dl
						jnz		short loc_4635E1
					loc_4635FE:
						jmp		loc_463680

					loc_463603:
						mov		edx, ecx
						and		edx, 2
						add		esi, edx
						shr		ecx, 1
						jb		short loc_463642
						shr		ecx, 1
						jnb		short loc_46361F
						mov		dl, [esi]
						mov		dl, [ebx+edx]
						add		esi, 2
						mov		[edi], dl
						add		edi, 2
					loc_46361F:
						test	cl, cl
						jz		short loc_463640
					loc_463623:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi], dl
						mov		dl, al
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-2], dl
						jnz		short loc_463623
					loc_463640:
						jmp		short loc_463680

					loc_463642:
						mov		dl, [esi]
						mov		dl, [ebx+edx]
						inc		esi
						mov		[edi], dl
						inc		edi
						shr		ecx, 1
						jnb		short loc_46365E
						mov		dl, [esi+1]
						mov		dl, [ebx+edx]
						add		esi, 2
						mov		[edi+1], dl
						add		edi, 2
					loc_46365E:
						test	cl, cl
						jz		short loc_463680
					loc_463662:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, ah
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi+1], dl
						mov		dl, ah
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-1], dl
						jnz		short loc_463662
					loc_463680:
						sub		edi, 320h
						add		ebp, 2
						cmp		ebp, 20h
						jnz		loc_463563
					loc_463692:
						pop		ebp
					}
					break;
				case 3: // upper (top transparent), with lighting
					__asm {
						push	ebp
						xor		eax, eax
						mov		WorldBoolFlag, eax
						mov		ebp, 1Eh
					loc_4636A5:
						cmp		edi, gpBufEnd
						jb		loc_463905
						mov		ecx, 20h
						sub		ecx, ebp
						mov		eax, WorldBoolFlag
						inc		eax
						and		eax, 1
						mov		WorldBoolFlag, eax
						jz		short loc_463743
						shr		ecx, 1
						jb		short loc_463703
						shr		ecx, 1
						jnb		short loc_4636DF
						mov		dl, [esi+1]
						mov		dl, [ebx+edx]
						add		esi, 2
						mov		[edi+1], dl
						add		edi, 2
					loc_4636DF:
						test	cl, cl
						jz		short loc_463701
					loc_4636E3:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, ah
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi+1], dl
						mov		dl, ah
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-1], dl
						jnz		short loc_4636E3
					loc_463701:
						jmp		short loc_463737

					loc_463703:
						inc		esi
						inc		edi
						shr		ecx, 1
						jnb		short loc_463716
						mov		dl, [esi]
						mov		dl, [ebx+edx]
						add		esi, 2
						mov		[edi], dl
						add		edi, 2
					loc_463716:
						test	cl, cl
						jz		short loc_463737
					loc_46371A:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi], dl
						mov		dl, al
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-2], dl
						jnz		short loc_46371A
					loc_463737:
						mov		edx, esi
						and		edx, 2
						add		esi, edx
						jmp		loc_4637C0

					loc_463743:
						shr		ecx, 1
						jb		short loc_46377B
						shr		ecx, 1
						jnb		short loc_463758
						mov		dl, [esi]
						mov		dl, [ebx+edx]
						add		esi, 2
						mov		[edi], dl
						add		edi, 2
					loc_463758:
						test	cl, cl
						jz		short loc_463779
					loc_46375C:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi], dl
						mov		dl, al
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-2], dl
						jnz		short loc_46375C
					loc_463779:
						jmp		short loc_4637B9

					loc_46377B:
						mov		dl, [esi]
						mov		dl, [ebx+edx]
						inc		esi
						mov		[edi], dl
						inc		edi
						shr		ecx, 1
						jnb		short loc_463797
						mov		dl, [esi+1]
						mov		dl, [ebx+edx]
						add		esi, 2
						mov		[edi+1], dl
						add		edi, 2
					loc_463797:
						test	cl, cl
						jz		short loc_4637B9
					loc_46379B:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, ah
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi+1], dl
						mov		dl, ah
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-1], dl
						jnz		short loc_46379B
					loc_4637B9:
						mov		edx, esi
						and		edx, 2
						add		esi, edx
					loc_4637C0:
						sub		edi, 320h
						add		edi, ebp
						sub		ebp, 2
						jge		loc_4636A5
						mov		ebp, 2
					loc_4637D6:
						cmp		edi, gpBufEnd
						jb		loc_463905
						mov		ecx, 20h
						sub		ecx, ebp
						mov		eax, WorldBoolFlag
						inc		eax
						and		eax, 1
						mov		WorldBoolFlag, eax
						jz		short loc_463874
						shr		ecx, 1
						jb		short loc_463834
						shr		ecx, 1
						jnb		short loc_463810
						mov		dl, [esi+1]
						mov		dl, [ebx+edx]
						add		esi, 2
						mov		[edi+1], dl
						add		edi, 2
					loc_463810:
						test	cl, cl
						jz		short loc_463832
					loc_463814:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, ah
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi+1], dl
						mov		dl, ah
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-1], dl
						jnz		short loc_463814
					loc_463832:
						jmp		short loc_463868

					loc_463834:
						inc		esi
						inc		edi
						shr		ecx, 1
						jnb		short loc_463847
						mov		dl, [esi]
						mov		dl, [ebx+edx]
						add		esi, 2
						mov		[edi], dl
						add		edi, 2
					loc_463847:
						test	cl, cl
						jz		short loc_463868
					loc_46384B:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi], dl
						mov		dl, al
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-2], dl
						jnz		short loc_46384B
					loc_463868:
						mov		edx, esi
						and		edx, 2
						add		esi, edx
						jmp		loc_4638F1

					loc_463874:
						shr		ecx, 1
						jb		short loc_4638AC
						shr		ecx, 1
						jnb		short loc_463889
						mov		dl, [esi]
						mov		dl, [ebx+edx]
						add		esi, 2
						mov		[edi], dl
						add		edi, 2
					loc_463889:
						test	cl, cl
						jz		short loc_4638AA
					loc_46388D:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi], dl
						mov		dl, al
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-2], dl
						jnz		short loc_46388D
					loc_4638AA:
						jmp		short loc_4638EA

					loc_4638AC:
						mov		dl, [esi]
						mov		dl, [ebx+edx]
						inc		esi
						mov		[edi], dl
						inc		edi
						shr		ecx, 1
						jnb		short loc_4638C8
						mov		dl, [esi+1]
						mov		dl, [ebx+edx]
						add		esi, 2
						mov		[edi+1], dl
						add		edi, 2
					loc_4638C8:
						test	cl, cl
						jz		short loc_4638EA
					loc_4638CC:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, ah
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi+1], dl
						mov		dl, ah
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-1], dl
						jnz		short loc_4638CC
					loc_4638EA:
						mov		edx, esi
						and		edx, 2
						add		esi, edx
					loc_4638F1:
						sub		edi, 320h
						add		edi, ebp
						add		ebp, 2
						cmp		ebp, 20h
						jnz		loc_4637D6
					loc_463905:
						pop		ebp
					}
					break;
				case 4: // upper (top transparent), with lighting
					__asm {
						push	ebp
						xor		eax, eax
						mov		WorldBoolFlag, eax
						mov		ebp, 1Eh
					loc_463918:
						cmp		edi, gpBufEnd
						jb		loc_463AAD
						add		edi, ebp
						mov		ecx, 20h
						sub		ecx, ebp
						mov		eax, WorldBoolFlag
						inc		eax
						and		eax, 1
						mov		WorldBoolFlag, eax
						jz		short loc_4639B8
						mov		edx, ecx
						and		edx, 2
						add		esi, edx
						shr		ecx, 1
						jb		short loc_46397F
						shr		ecx, 1
						jnb		short loc_46395B
						mov		dl, [esi+1]
						mov		dl, [ebx+edx]
						add		esi, 2
						mov		[edi+1], dl
						add		edi, 2
					loc_46395B:
						test	cl, cl
						jz		short loc_46397D
					loc_46395F:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, ah
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi+1], dl
						mov		dl, ah
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-1], dl
						jnz		short loc_46395F
					loc_46397D:
						jmp		short loc_4639B3

					loc_46397F:
						inc		esi
						inc		edi
						shr		ecx, 1
						jnb		short loc_463992
						mov		dl, [esi]
						mov		dl, [ebx+edx]
						add		esi, 2
						mov		[edi], dl
						add		edi, 2
					loc_463992:
						test	cl, cl
						jz		short loc_4639B3
					loc_463996:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi], dl
						mov		dl, al
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-2], dl
						jnz		short loc_463996
					loc_4639B3:
						jmp		loc_463A35

					loc_4639B8:
						mov		edx, ecx
						and		edx, 2
						add		esi, edx
						shr		ecx, 1
						jb		short loc_4639F7
						shr		ecx, 1
						jnb		short loc_4639D4
						mov		dl, [esi]
						mov		dl, [ebx+edx]
						add		esi, 2
						mov		[edi], dl
						add		edi, 2
					loc_4639D4:
						test	cl, cl
						jz		short loc_4639F5
					loc_4639D8:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi], dl
						mov		dl, al
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-2], dl
						jnz		short loc_4639D8
					loc_4639F5:
						jmp		short loc_463A35

					loc_4639F7:
						mov		dl, [esi]
						mov		dl, [ebx+edx]
						inc		esi
						mov		[edi], dl
						inc		edi
						shr		ecx, 1
						jnb		short loc_463A13
						mov		dl, [esi+1]
						mov		dl, [ebx+edx]
						add		esi, 2
						mov		[edi+1], dl
						add		edi, 2
					loc_463A13:
						test	cl, cl
						jz		short loc_463A35
					loc_463A17:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, ah
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi+1], dl
						mov		dl, ah
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-1], dl
						jnz		short loc_463A17
					loc_463A35:
						sub		edi, 320h
						sub		ebp, 2
						jge		loc_463918
						mov		ebp, 8
					loc_463A49:
						cmp		edi, gpBufEnd
						jb		short loc_463AAD
						mov		ecx, 8
					loc_463A56:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, ah
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi+1], dl
						mov		dl, ah
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-1], dl
						jnz		short loc_463A56
						sub		edi, 320h
						cmp		edi, gpBufEnd
						jb		short loc_463AAD
						mov		ecx, 8
					loc_463A87:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi], dl
						mov		dl, al
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-2], dl
						jnz		short loc_463A87
						sub		edi, 320h
						dec		ebp
						jnz		short loc_463A49
					loc_463AAD:
						pop		ebp
					}
					break;
				default: // upper (top transparent), with lighting
					__asm {
						push	ebp
						xor		eax, eax
						mov		WorldBoolFlag, eax
						mov		ebp, 1Eh
					loc_463AC0:
						cmp		edi, gpBufEnd
						jb		loc_463C55
						mov		ecx, 20h
						sub		ecx, ebp
						mov		eax, WorldBoolFlag
						inc		eax
						and		eax, 1
						mov		WorldBoolFlag, eax
						jz		short loc_463B5E
						shr		ecx, 1
						jb		short loc_463B1E
						shr		ecx, 1
						jnb		short loc_463AFA
						mov		dl, [esi+1]
						mov		dl, [ebx+edx]
						add		esi, 2
						mov		[edi+1], dl
						add		edi, 2
					loc_463AFA:
						test	cl, cl
						jz		short loc_463B1C
					loc_463AFE:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, ah
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi+1], dl
						mov		dl, ah
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-1], dl
						jnz		short loc_463AFE
					loc_463B1C:
						jmp		short loc_463B52

					loc_463B1E:
						inc		esi
						inc		edi
						shr		ecx, 1
						jnb		short loc_463B31
						mov		dl, [esi]
						mov		dl, [ebx+edx]
						add		esi, 2
						mov		[edi], dl
						add		edi, 2
					loc_463B31:
						test	cl, cl
						jz		short loc_463B52
					loc_463B35:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi], dl
						mov		dl, al
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-2], dl
						jnz		short loc_463B35
					loc_463B52:
						mov		edx, esi
						and		edx, 2
						add		esi, edx
						jmp		loc_463BDB

					loc_463B5E:
						shr		ecx, 1
						jb		short loc_463B96
						shr		ecx, 1
						jnb		short loc_463B73
						mov		dl, [esi]
						mov		dl, [ebx+edx]
						add		esi, 2
						mov		[edi], dl
						add		edi, 2
					loc_463B73:
						test	cl, cl
						jz		short loc_463B94
					loc_463B77:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi], dl
						mov		dl, al
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-2], dl
						jnz		short loc_463B77
					loc_463B94:
						jmp		short loc_463BD4

					loc_463B96:
						mov		dl, [esi]
						mov		dl, [ebx+edx]
						inc		esi
						mov		[edi], dl
						inc		edi
						shr		ecx, 1
						jnb		short loc_463BB2
						mov		dl, [esi+1]
						mov		dl, [ebx+edx]
						add		esi, 2
						mov		[edi+1], dl
						add		edi, 2
					loc_463BB2:
						test	cl, cl
						jz		short loc_463BD4
					loc_463BB6:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, ah
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi+1], dl
						mov		dl, ah
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-1], dl
						jnz		short loc_463BB6
					loc_463BD4:
						mov		edx, esi
						and		edx, 2
						add		esi, edx
					loc_463BDB:
						sub		edi, 320h
						add		edi, ebp
						sub		ebp, 2
						jge		loc_463AC0
						mov		ebp, 8
					loc_463BF1:
						cmp		edi, gpBufEnd
						jb		short loc_463C55
						mov		ecx, 8
					loc_463BFE:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, ah
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi+1], dl
						mov		dl, ah
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-1], dl
						jnz		short loc_463BFE
						sub		edi, 320h
						cmp		edi, gpBufEnd
						jb		short loc_463C55
						mov		ecx, 8
					loc_463C2F:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						shr		eax, 10h
						mov		dl, [ebx+edx]
						mov		[edi], dl
						mov		dl, al
						add		edi, 4
						mov		dl, [ebx+edx]
						dec		ecx
						mov		[edi-2], dl
						jnz		short loc_463C2F
						sub		edi, 320h
						dec		ebp
						jnz		short loc_463BF1
					loc_463C55:
						pop		ebp
					}
					break;
			}
			return;
		}
		src = (unsigned char *)pSpeedCels
				   + *(_DWORD *)&gpCelFrame[4 * (light_table_index + 16 * (level_cel_block & 0xFFF))];
		cel_type_16 = (unsigned char)(level_cel_block >> 12);
LABEL_11:
		__asm {
			xor		edx, edx
			xor		ecx, ecx
			mov		edi, dst
			mov		esi, src
		}
		switch ( cel_type_16 )
		{
			case 8: // upper (top transparent), without lighting
				__asm {
					mov		edx, 10h
				loc_463C60:
					cmp		edi, gpBufEnd
					jb		ret_464688_8S
					mov		ecx, 8
				loc_463C71:
					mov		eax, [esi]
					add		esi, 4
					inc		edi
					ror		eax, 8
					mov		[edi], al
					add		edi, 2
					ror		eax, 10h
					mov		[edi], al
					inc		edi
					dec		ecx
					jnz		short loc_463C71
					sub		edi, 320h
					cmp		edi, gpBufEnd
					jb		ret_464688_8S
					mov		ecx, 8
				loc_463C9F:
					mov		eax, [esi]
					add		esi, 4
					mov		[edi], al
					add		edi, 2
					ror		eax, 10h
					mov		[edi], al
					add		edi, 2
					dec		ecx
					jnz		short loc_463C9F
					sub		edi, 320h
					dec		edx
					jnz		short loc_463C60
				ret_464688_8S:
				}
				break;
			case 9: // upper (top transparent), without lighting
				__asm {
					push	ebp
					mov		eax, edi
					and		eax, 1
					mov		WorldBoolFlag, eax
					mov		ebp, 20h
				loc_463CD2:
					mov		edx, 20h
				loc_463CD7:
					xor		eax, eax
					mov		al, [esi]
					inc		esi
					test	al, al
					js		loc_463D76
					sub		edx, eax
					cmp		edi, gpBufEnd
					jb		loc_463D9D
					mov		ecx, eax
					mov		eax, edi
					and		eax, 1
					cmp		eax, WorldBoolFlag
					jnz		short loc_463D36
					shr		ecx, 1
					jnb		short loc_463D0D
					inc		esi
					inc		edi
					test	ecx, ecx
					jz		short loc_463D6D
					jmp		short loc_463D46

				loc_463D0D:
					shr		ecx, 1
					jnb		short loc_463D1D
					inc		esi
					inc		edi
					mov		al, [esi]
					inc		esi
					mov		[edi], al
					inc		edi
					test	ecx, ecx
					jz		short loc_463D6D
				loc_463D1D:
					mov		eax, [esi]
					add		esi, 4
					inc		edi
					ror		eax, 8
					mov		[edi], al
					add		edi, 2
					ror		eax, 10h
					mov		[edi], al
					inc		edi
					dec		ecx
					jnz		short loc_463D1D
					jmp		short loc_463D6D

				loc_463D36:
					shr		ecx, 1
					jnb		short loc_463D46
					mov		al, [esi]
					inc		esi
					mov		[edi], al
					inc		edi
					test	ecx, ecx
					jz		short loc_463D6D
					jmp		short loc_463D0D

				loc_463D46:
					shr		ecx, 1
					jnb		short loc_463D58
					mov		al, [esi]
					add		esi, 2
					mov		[edi], al
					add		edi, 2
					test	ecx, ecx
					jz		short loc_463D6D
				loc_463D58:
					mov		eax, [esi]
					add		esi, 4
					mov		[edi], al
					add		edi, 2
					ror		eax, 10h
					mov		[edi], al
					add		edi, 2
					dec		ecx
					jnz		short loc_463D58
				loc_463D6D:
					test	edx, edx
					jz		short loc_463D82
					jmp		loc_463CD7

				loc_463D76:
					neg		al
					add		edi, eax
					sub		edx, eax
					jnz		loc_463CD7
				loc_463D82:
					mov		eax, WorldBoolFlag
					inc		eax
					and		eax, 1
					mov		WorldBoolFlag, eax
					sub		edi, 320h
					dec		ebp
					jnz		loc_463CD2
				loc_463D9D:
					pop		ebp
				}
				break;
			case 10: // upper (top transparent), without lighting
				__asm {
					xor		eax, eax
					mov		WorldBoolFlag, eax
					mov		edx, 1Eh
				loc_463DAF:
					cmp		edi, gpBufEnd
					jb		ret_464688_10S
					add		edi, edx
					mov		ecx, 20h
					sub		ecx, edx
					mov		eax, WorldBoolFlag
					inc		eax
					and		eax, 1
					mov		WorldBoolFlag, eax
					jz		short loc_463E04
					shr		ecx, 2
					jnb		short loc_463DEB
					mov		ax, [esi+2]
					add		esi, 4
					inc		edi
					ror		eax, 8
					mov		[edi], al
					inc		edi
					test	ecx, ecx
					jz		short loc_463E2E
				loc_463DEB:
					mov		eax, [esi]
					add		esi, 4
					inc		edi
					ror		eax, 8
					mov		[edi], al
					add		edi, 2
					ror		eax, 10h
					mov		[edi], al
					inc		edi
					dec		ecx
					jnz		short loc_463DEB
					jmp		short loc_463E2E

				loc_463E04:
					shr		ecx, 2
					jnb		short loc_463E19
					mov		ax, [esi+2]
					add		esi, 4
					mov		[edi], al
					add		edi, 2
					test	ecx, ecx
					jz		short loc_463E2E
				loc_463E19:
					mov		eax, [esi]
					add		esi, 4
					mov		[edi], al
					add		edi, 2
					ror		eax, 10h
					mov		[edi], al
					add		edi, 2
					dec		ecx
					jnz		short loc_463E19
				loc_463E2E:
					sub		edi, 320h
					sub		edx, 2
					jge		loc_463DAF
					mov		edx, 2
				loc_463E42:
					cmp		edi, gpBufEnd
					jb		ret_464688_10S
					add		edi, edx
					mov		ecx, 20h
					sub		ecx, edx
					mov		eax, WorldBoolFlag
					inc		eax
					and		eax, 1
					mov		WorldBoolFlag, eax
					jz		short loc_463E97
					shr		ecx, 2
					jnb		short loc_463E7E
					mov		ax, [esi+2]
					add		esi, 4
					inc		edi
					ror		eax, 8
					mov		[edi], al
					inc		edi
					test	ecx, ecx
					jz		short loc_463EC1
				loc_463E7E:
					mov		eax, [esi]
					add		esi, 4
					inc		edi
					ror		eax, 8
					mov		[edi], al
					add		edi, 2
					ror		eax, 10h
					mov		[edi], al
					inc		edi
					dec		ecx
					jnz		short loc_463E7E
					jmp		short loc_463EC1

				loc_463E97:
					shr		ecx, 2
					jnb		short loc_463EAC
					mov		ax, [esi+2]
					add		esi, 4
					mov		[edi], al
					add		edi, 2
					test	ecx, ecx
					jz		short loc_463EC1
				loc_463EAC:
					mov		eax, [esi]
					add		esi, 4
					mov		[edi], al
					add		edi, 2
					ror		eax, 10h
					mov		[edi], al
					add		edi, 2
					dec		ecx
					jnz		short loc_463EAC
				loc_463EC1:
					sub		edi, 320h
					add		edx, 2
					cmp		edx, 20h
					jnz		loc_463E42
				ret_464688_10S:
				}
				break;
			case 11: // upper (top transparent), without lighting
				__asm {
					push	ebp
					xor		eax, eax
					mov		WorldBoolFlag, eax
					mov		edx, 1Eh
				loc_463EE5:
					cmp		edi, gpBufEnd
					jb		loc_46400B
					mov		ecx, 20h
					sub		ecx, edx
					mov		eax, WorldBoolFlag
					inc		eax
					and		eax, 1
					mov		ebp, ecx
					mov		WorldBoolFlag, eax
					jz		short loc_463F3A
					shr		ecx, 2
					jz		short loc_463F26
				loc_463F0F:
					mov		eax, [esi]
					add		esi, 4
					inc		edi
					ror		eax, 8
					mov		[edi], al
					add		edi, 2
					ror		eax, 10h
					mov		[edi], al
					inc		edi
					dec		ecx
					jnz		short loc_463F0F
				loc_463F26:
					and		ebp, 2
					jz		short loc_463F64
					mov		ax, [esi]
					add		esi, 4
					inc		edi
					ror		eax, 8
					mov		[edi], al
					inc		edi
					jmp		short loc_463F64

				loc_463F3A:
					shr		ecx, 2
					jz		short loc_463F54
				loc_463F3F:
					mov		eax, [esi]
					add		esi, 4
					mov		[edi], al
					add		edi, 2
					ror		eax, 10h
					mov		[edi], al
					add		edi, 2
					dec		ecx
					jnz		short loc_463F3F
				loc_463F54:
					and		ebp, 2
					jz		short loc_463F64
					mov		ax, [esi]
					add		esi, 4
					mov		[edi], al
					add		edi, 2
				loc_463F64:
					sub		edi, 320h
					add		edi, edx
					sub		edx, 2
					jge		loc_463EE5
					mov		edx, 2
				loc_463F7A:
					cmp		edi, gpBufEnd
					jb		loc_46400B
					mov		ecx, 20h
					sub		ecx, edx
					mov		eax, WorldBoolFlag
					inc		eax
					and		eax, 1
					mov		WorldBoolFlag, eax
					jz		short loc_463FCD
					shr		ecx, 2
					jz		short loc_463FB9
				loc_463FA2:
					mov		eax, [esi]
					add		esi, 4
					inc		edi
					ror		eax, 8
					mov		[edi], al
					add		edi, 2
					ror		eax, 10h
					mov		[edi], al
					inc		edi
					dec		ecx
					jnz		short loc_463FA2
				loc_463FB9:
					and		ebp, 2
					jz		short loc_463FF7
					mov		ax, [esi]
					add		esi, 4
					inc		edi
					ror		eax, 8
					mov		[edi], al
					inc		edi
					jmp		short loc_463FF7

				loc_463FCD:
					shr		ecx, 2
					jz		short loc_463FE7
				loc_463FD2:
					mov		eax, [esi]
					add		esi, 4
					mov		[edi], al
					add		edi, 2
					ror		eax, 10h
					mov		[edi], al
					add		edi, 2
					dec		ecx
					jnz		short loc_463FD2
				loc_463FE7:
					and		ebp, 2
					jz		short loc_463FF7
					mov		ax, [esi]
					add		esi, 4
					mov		[edi], al
					add		edi, 2
				loc_463FF7:
					sub		edi, 320h
					add		edi, edx
					add		edx, 2
					cmp		edx, 20h
					jnz		loc_463F7A
				loc_46400B:
					pop		ebp
				}
				break;
			case 12: // upper (top transparent), without lighting
				__asm {
					xor		eax, eax
					mov		WorldBoolFlag, eax
					mov		edx, 1Eh
				loc_46401D:
					cmp		edi, gpBufEnd
					jb		ret_464688_12S
					add		edi, edx
					mov		ecx, 20h
					sub		ecx, edx
					mov		eax, WorldBoolFlag
					inc		eax
					and		eax, 1
					mov		WorldBoolFlag, eax
					jz		short loc_464072
					shr		ecx, 2
					jnb		short loc_464059
					mov		ax, [esi+2]
					add		esi, 4
					inc		edi
					ror		eax, 8
					mov		[edi], al
					inc		edi
					test	ecx, ecx
					jz		short loc_46409C
				loc_464059:
					mov		eax, [esi]
					add		esi, 4
					inc		edi
					ror		eax, 8
					mov		[edi], al
					add		edi, 2
					ror		eax, 10h
					mov		[edi], al
					inc		edi
					dec		ecx
					jnz		short loc_464059
					jmp		short loc_46409C

				loc_464072:
					shr		ecx, 2
					jnb		short loc_464087
					mov		ax, [esi+2]
					add		esi, 4
					mov		[edi], al
					add		edi, 2
					test	ecx, ecx
					jz		short loc_46409C
				loc_464087:
					mov		eax, [esi]
					add		esi, 4
					mov		[edi], al
					add		edi, 2
					ror		eax, 10h
					mov		[edi], al
					add		edi, 2
					dec		ecx
					jnz		short loc_464087
				loc_46409C:
					sub		edi, 320h
					sub		edx, 2
					jge		loc_46401D
					mov		edx, 8
				loc_4640B0:
					cmp		edi, gpBufEnd
					jb		ret_464688_12S
					mov		ecx, 8
				loc_4640C1:
					mov		eax, [esi]
					add		esi, 4
					inc		edi
					ror		eax, 8
					mov		[edi], al
					add		edi, 2
					ror		eax, 10h
					mov		[edi], al
					inc		edi
					dec		ecx
					jnz		short loc_4640C1
					sub		edi, 320h
					cmp		edi, gpBufEnd
					jb		ret_464688_12S
					mov		ecx, 8
				loc_4640EF:
					mov		eax, [esi]
					add		esi, 4
					mov		[edi], al
					add		edi, 2
					ror		eax, 10h
					mov		[edi], al
					add		edi, 2
					dec		ecx
					jnz		short loc_4640EF
					sub		edi, 320h
					dec		edx
					jnz		short loc_4640B0
				ret_464688_12S:
				}
				break;
			default: // upper (top transparent), without lighting
				__asm {
					push	ebp
					xor		eax, eax
					mov		WorldBoolFlag, eax
					mov		edx, 1Eh
				loc_46411F:
					cmp		edi, gpBufEnd
					jb		loc_464209
					mov		ecx, 20h
					sub		ecx, edx
					mov		eax, WorldBoolFlag
					inc		eax
					and		eax, 1
					mov		ebp, ecx
					mov		WorldBoolFlag, eax
					jz		short loc_464174
					shr		ecx, 2
					jz		short loc_464160
				loc_464149:
					mov		eax, [esi]
					add		esi, 4
					inc		edi
					ror		eax, 8
					mov		[edi], al
					add		edi, 2
					ror		eax, 10h
					mov		[edi], al
					inc		edi
					dec		ecx
					jnz		short loc_464149
				loc_464160:
					and		ebp, 2
					jz		short loc_46419E
					mov		ax, [esi]
					add		esi, 4
					inc		edi
					ror		eax, 8
					mov		[edi], al
					inc		edi
					jmp		short loc_46419E

				loc_464174:
					shr		ecx, 2
					jz		short loc_46418E
				loc_464179:
					mov		eax, [esi]
					add		esi, 4
					mov		[edi], al
					add		edi, 2
					ror		eax, 10h
					mov		[edi], al
					add		edi, 2
					dec		ecx
					jnz		short loc_464179
				loc_46418E:
					and		ebp, 2
					jz		short loc_46419E
					mov		ax, [esi]
					add		esi, 4
					mov		[edi], al
					add		edi, 2
				loc_46419E:
					sub		edi, 320h
					add		edi, edx
					sub		edx, 2
					jge		loc_46411F
					mov		edx, 8
				loc_4641B4:
					cmp		edi, gpBufEnd
					jb		short loc_464209
					mov		ecx, 8
				loc_4641C1:
					mov		eax, [esi]
					add		esi, 4
					inc		edi
					ror		eax, 8
					mov		[edi], al
					add		edi, 2
					ror		eax, 10h
					mov		[edi], al
					inc		edi
					dec		ecx
					jnz		short loc_4641C1
					sub		edi, 320h
					cmp		edi, gpBufEnd
					jb		short loc_464209
					mov		ecx, 8
				loc_4641EB:
					mov		eax, [esi]
					add		esi, 4
					mov		[edi], al
					add		edi, 2
					ror		eax, 10h
					mov		[edi], al
					add		edi, 2
					dec		ecx
					jnz		short loc_4641EB
					sub		edi, 320h
					dec		edx
					jnz		short loc_4641B4
				loc_464209:
					pop		ebp
				}
				break;
		}
		return;
	}
	if ( level_cel_block & 0x8000 )
		level_cel_block = *(_DWORD *)&gpCelFrame[64 * (level_cel_block & 0xFFF)]
						+ (unsigned short)(level_cel_block & 0xF000);
	src = (unsigned char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
	cel_type_16 = (level_cel_block >> 12) & 7;
	__asm {
		xor		edx, edx
		xor		ecx, ecx
		mov		edi, dst
		mov		esi, src
	}
	switch ( cel_type_16 )
	{
		case 0: // upper (top transparent), black
			__asm {
				mov		edx, 10h
				xor		eax, eax
			loc_464216:
				cmp		edi, gpBufEnd
				jb		ret_464688_0B
				mov		ecx, 8
			loc_464227:
				mov		[edi+1], al
				mov		[edi+3], al
				add		edi, 4
				dec		ecx
				jnz		short loc_464227
				sub		edi, 320h
				cmp		edi, gpBufEnd
				jb		ret_464688_0B
				mov		ecx, 8
			loc_46424A:
				mov		[edi], al
				mov		[edi+2], al
				add		edi, 4
				dec		ecx
				jnz		short loc_46424A
				sub		edi, 320h
				dec		edx
				jnz		short loc_464216
			ret_464688_0B:
			}
			break;
		case 1: // upper (top transparent), black
			__asm {
				push	ebp
				mov		eax, edi
				and		eax, 1
				mov		WorldBoolFlag, eax
				mov		ebp, 20h
			loc_464273:
				mov		edx, 20h
			loc_464278:
				xor		eax, eax
				mov		al, [esi]
				inc		esi
				test	al, al
				js		short loc_4642F4
				sub		edx, eax
				cmp		edi, gpBufEnd
				jb		loc_46431B
				mov		ecx, eax
				add		esi, ecx
				mov		eax, edi
				and		eax, 1
				cmp		eax, WorldBoolFlag
				jnz		short loc_4642C7
				xor		eax, eax
				shr		ecx, 1
				jnb		short loc_4642AD
				inc		edi
				test	ecx, ecx
				jz		short loc_4642EE
				jmp		short loc_4642D6

			loc_4642AD:
				shr		ecx, 1
				jnb		short loc_4642B9
				inc		edi
				mov		[edi], al
				inc		edi
				test	ecx, ecx
				jz		short loc_4642EE
			loc_4642B9:
				mov		[edi+1], al
				mov		[edi+3], al
				add		edi, 4
				dec		ecx
				jnz		short loc_4642B9
				jmp		short loc_4642EE

			loc_4642C7:
				xor		eax, eax
				shr		ecx, 1
				jnb		short loc_4642D6
				mov		[edi], al
				inc		edi
				test	ecx, ecx
				jz		short loc_4642EE
				jmp		short loc_4642AD

			loc_4642D6:
				shr		ecx, 1
				jnb		short loc_4642E3
				mov		[edi], al
				add		edi, 2
				test	ecx, ecx
				jz		short loc_4642EE
			loc_4642E3:
				mov		[edi], al
				mov		[edi+2], al
				add		edi, 4
				dec		ecx
				jnz		short loc_4642E3
			loc_4642EE:
				test	edx, edx
				jz		short loc_464300
				jmp		short loc_464278

			loc_4642F4:
				neg		al
				add		edi, eax
				sub		edx, eax
				jnz		loc_464278
			loc_464300:
				mov		eax, WorldBoolFlag
				inc		eax
				and		eax, 1
				mov		WorldBoolFlag, eax
				sub		edi, 320h
				dec		ebp
				jnz		loc_464273
			loc_46431B:
				pop		ebp
			}
			break;
		case 2: // upper (top transparent), black
			__asm {
				xor		eax, eax
				mov		WorldBoolFlag, eax
				mov		edx, 1Eh
			loc_46432D:
				cmp		edi, gpBufEnd
				jb		ret_464688_2B
				add		edi, edx
				mov		ecx, 20h
				sub		ecx, edx
				mov		eax, WorldBoolFlag
				inc		eax
				and		eax, 1
				mov		WorldBoolFlag, eax
				jz		short loc_46436F
				xor		eax, eax
				shr		ecx, 2
				jnb		short loc_464361
				inc		edi
				mov		[edi], al
				inc		edi
				test	ecx, ecx
				jz		short loc_46438A
			loc_464361:
				mov		[edi+1], al
				mov		[edi+3], al
				add		edi, 4
				dec		ecx
				jnz		short loc_464361
				jmp		short loc_46438A

			loc_46436F:
				xor		eax, eax
				shr		ecx, 2
				jnb		short loc_46437F
				mov		[edi], al
				add		edi, 2
				test	ecx, ecx
				jz		short loc_46438A
			loc_46437F:
				mov		[edi], al
				mov		[edi+2], al
				add		edi, 4
				dec		ecx
				jnz		short loc_46437F
			loc_46438A:
				sub		edi, 320h
				test	edx, edx
				jz		short loc_464399
				sub		edx, 2
				jmp		short loc_46432D

			loc_464399:
				mov		edx, 2
			loc_46439E:
				cmp		edi, gpBufEnd
				jb		ret_464688_2B
				add		edi, edx
				mov		ecx, 20h
				sub		ecx, edx
				mov		eax, WorldBoolFlag
				inc		eax
				and		eax, 1
				mov		WorldBoolFlag, eax
				jz		short loc_4643E0
				xor		eax, eax
				shr		ecx, 2
				jnb		short loc_4643D2
				inc		edi
				mov		[edi], al
				inc		edi
				test	ecx, ecx
				jz		short loc_4643FB
			loc_4643D2:
				mov		[edi+1], al
				mov		[edi+3], al
				add		edi, 4
				dec		ecx
				jnz		short loc_4643D2
				jmp		short loc_4643FB

			loc_4643E0:
				xor		eax, eax
				shr		ecx, 2
				jnb		short loc_4643F0
				mov		[edi], al
				add		edi, 2
				test	ecx, ecx
				jz		short loc_4643FB
			loc_4643F0:
				mov		[edi], al
				mov		[edi+2], al
				add		edi, 4
				dec		ecx
				jnz		short loc_4643F0
			loc_4643FB:
				sub		edi, 320h
				add		edx, 2
				cmp		edx, 20h
				jnz		short loc_46439E
			ret_464688_2B:
			}
			break;
		case 3: // upper (top transparent), black
			__asm {
				xor		eax, eax
				mov		WorldBoolFlag, eax
				mov		edx, 1Eh
			loc_46441A:
				cmp		edi, gpBufEnd
				jb		ret_464688_3B
				mov		ecx, 20h
				sub		ecx, edx
				mov		eax, WorldBoolFlag
				inc		eax
				and		eax, 1
				mov		WorldBoolFlag, eax
				jz		short loc_46445A
				xor		eax, eax
				shr		ecx, 2
				jnb		short loc_46444C
				inc		edi
				mov		[edi], al
				inc		edi
				test	ecx, ecx
				jz		short loc_464475
			loc_46444C:
				mov		[edi+1], al
				mov		[edi+3], al
				add		edi, 4
				dec		ecx
				jnz		short loc_46444C
				jmp		short loc_464475

			loc_46445A:
				xor		eax, eax
				shr		ecx, 2
				jnb		short loc_46446A
				mov		[edi], al
				add		edi, 2
				test	ecx, ecx
				jz		short loc_464475
			loc_46446A:
				mov		[edi], al
				mov		[edi+2], al
				add		edi, 4
				dec		ecx
				jnz		short loc_46446A
			loc_464475:
				sub		edi, 320h
				test	edx, edx
				jz		short loc_464486
				add		edi, edx
				sub		edx, 2
				jmp		short loc_46441A

			loc_464486:
				mov		edx, 2
			loc_46448B:
				cmp		edi, gpBufEnd
				jb		ret_464688_3B
				mov		ecx, 20h
				sub		ecx, edx
				mov		eax, WorldBoolFlag
				inc		eax
				and		eax, 1
				mov		WorldBoolFlag, eax
				jz		short loc_4644CB
				xor		eax, eax
				shr		ecx, 2
				jnb		short loc_4644BD
				inc		edi
				mov		[edi], al
				inc		edi
				test	ecx, ecx
				jz		short loc_4644E6
			loc_4644BD:
				mov		[edi+1], al
				mov		[edi+3], al
				add		edi, 4
				dec		ecx
				jnz		short loc_4644BD
				jmp		short loc_4644E6

			loc_4644CB:
				xor		eax, eax
				shr		ecx, 2
				jnb		short loc_4644DB
				mov		[edi], al
				add		edi, 2
				test	ecx, ecx
				jz		short loc_4644E6
			loc_4644DB:
				mov		[edi], al
				mov		[edi+2], al
				add		edi, 4
				dec		ecx
				jnz		short loc_4644DB
			loc_4644E6:
				sub		edi, 320h
				add		edi, edx
				add		edx, 2
				cmp		edx, 20h
				jnz		short loc_46448B
			ret_464688_3B:
			}
			break;
		case 4: // upper (top transparent), black
			__asm {
				xor		eax, eax
				mov		WorldBoolFlag, eax
				mov		edx, 1Eh
			loc_464507:
				cmp		edi, gpBufEnd
				jb		ret_464688_4B
				add		edi, edx
				mov		ecx, 20h
				sub		ecx, edx
				mov		eax, WorldBoolFlag
				inc		eax
				and		eax, 1
				mov		WorldBoolFlag, eax
				jz		short loc_464549
				xor		eax, eax
				shr		ecx, 2
				jnb		short loc_46453B
				inc		edi
				mov		[edi], al
				inc		edi
				test	ecx, ecx
				jz		short loc_464564
			loc_46453B:
				mov		[edi+1], al
				mov		[edi+3], al
				add		edi, 4
				dec		ecx
				jnz		short loc_46453B
				jmp		short loc_464564

			loc_464549:
				xor		eax, eax
				shr		ecx, 2
				jnb		short loc_464559
				mov		[edi], al
				add		edi, 2
				test	ecx, ecx
				jz		short loc_464564
			loc_464559:
				mov		[edi], al
				mov		[edi+2], al
				add		edi, 4
				dec		ecx
				jnz		short loc_464559
			loc_464564:
				sub		edi, 320h
				test	edx, edx
				jz		short loc_464573
				sub		edx, 2
				jmp		short loc_464507

			loc_464573:
				mov		edx, 8
				xor		eax, eax
			loc_46457A:
				cmp		edi, gpBufEnd
				jb		ret_464688_4B
				mov		ecx, 8
			loc_46458B:
				mov		[edi+1], al
				mov		[edi+3], al
				add		edi, 4
				dec		ecx
				jnz		short loc_46458B
				sub		edi, 320h
				cmp		edi, gpBufEnd
				jb		ret_464688_4B
				mov		ecx, 8
			loc_4645AE:
				mov		[edi], al
				mov		[edi+2], al
				add		edi, 4
				dec		ecx
				jnz		short loc_4645AE
				sub		edi, 320h
				dec		edx
				jnz		short loc_46457A
			ret_464688_4B:
			}
			break;
		default: // upper (top transparent), black
			__asm {
				xor		eax, eax
				mov		WorldBoolFlag, eax
				mov		edx, 1Eh
			loc_4645D3:
				cmp		edi, gpBufEnd
				jb		ret_464688_5B
				mov		ecx, 20h
				sub		ecx, edx
				mov		eax, WorldBoolFlag
				inc		eax
				and		eax, 1
				mov		WorldBoolFlag, eax
				jz		short loc_464613
				xor		eax, eax
				shr		ecx, 2
				jnb		short loc_464605
				inc		edi
				mov		[edi], al
				inc		edi
				test	ecx, ecx
				jz		short loc_46462E
			loc_464605:
				mov		[edi+1], al
				mov		[edi+3], al
				add		edi, 4
				dec		ecx
				jnz		short loc_464605
				jmp		short loc_46462E

			loc_464613:
				xor		eax, eax
				shr		ecx, 2
				jnb		short loc_464623
				mov		[edi], al
				add		edi, 2
				test	ecx, ecx
				jz		short loc_46462E
			loc_464623:
				mov		[edi], al
				mov		[edi+2], al
				add		edi, 4
				dec		ecx
				jnz		short loc_464623
			loc_46462E:
				sub		edi, 320h
				test	edx, edx
				jz		short loc_46463F
				add		edi, edx
				sub		edx, 2
				jmp		short loc_4645D3

			loc_46463F:
				mov		edx, 8
				xor		eax, eax
			loc_464646:
				cmp		edi, gpBufEnd
				jb		short ret_464688_5B
				mov		ecx, 8
			loc_464653:
				mov		[edi+1], al
				mov		[edi+3], al
				add		edi, 4
				dec		ecx
				jnz		short loc_464653
				sub		edi, 320h
				cmp		edi, gpBufEnd
				jb		short ret_464688_5B
				mov		ecx, 8
			loc_464672:
				mov		[edi], al
				mov		[edi+2], al
				add		edi, 4
				dec		ecx
				jnz		short loc_464672
				sub		edi, 320h
				dec		edx
				jnz		short loc_464646
			ret_464688_5B:
			}
			break;
	}
}

void __fastcall drawBottomArchesUpperScreen(unsigned char *pbDst, unsigned int *pMask)
{
	unsigned char *dst; // edi MAPDST
	unsigned char *src; // esi MAPDST
	short cel_type_16; // ax MAPDST
	unsigned char *tbl;

	gpCelFrame = (unsigned char *)speed_cel_frame_num_from_light_index_frame_num;
	dst = pbDst;
	gpDrawMask = pMask;
	if ( !(_BYTE)light_table_index )
	{
		if ( level_cel_block & 0x8000 )
			level_cel_block = *(_DWORD *)&gpCelFrame[64 * (level_cel_block & 0xFFF)]
							+ (unsigned short)(level_cel_block & 0xF000);
		src = (unsigned char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
		cel_type_16 = ((level_cel_block >> 12) & 7) + 8;
LABEL_12:
		__asm {
			xor		edx, edx
			xor		ecx, ecx
			mov		edi, dst
			mov		esi, src
		}
		switch ( cel_type_16 )
		{
			case 8: // upper (bottom transparent), without lighting
				__asm {
					mov		edx, 20h
				loc_464C7F:
					cmp		edi, gpBufEnd
					jb		ret_4652C1_8S
					push	edx
					mov		eax, gpDrawMask
					mov		edx, [eax]
					mov		ecx, 20h
				loc_464C98:
					mov		al, [esi]
					inc		esi
					shl		edx, 1
					jnb		short loc_464CA1
					mov		[edi], al
				loc_464CA1:
					inc		edi
					dec		ecx
					jnz		short loc_464C98
					pop		edx
					sub		edi, 320h
					mov		eax, gpDrawMask
					sub		eax, 4
					mov		gpDrawMask, eax
					dec		edx
					jnz		short loc_464C7F
				ret_4652C1_8S:
				}
				break;
			case 9: // upper (bottom transparent), without lighting
				__asm {
					mov		ecx, 20h
				loc_464CC6:
					push	ecx
					mov		eax, gpDrawMask
					mov		eax, [eax]
					mov		gdwCurrentMask, eax
					mov		edx, 20h
				loc_464CD8:
					xor		eax, eax
					mov		al, [esi]
					inc		esi
					test	al, al
					js		short loc_464D12
					sub		edx, eax
					cmp		edi, gpBufEnd
					jb		ret_4652C0_9S
					push	edx
					mov		edx, gdwCurrentMask
					mov		ecx, eax
				loc_464CF8:
					mov		al, [esi]
					inc		esi
					shl		edx, 1
					jnb		short loc_464D01
					mov		[edi], al
				loc_464D01:
					inc		edi
					dec		ecx
					jnz		short loc_464CF8
					mov		gdwCurrentMask, edx
					pop		edx
					test	edx, edx
					jz		short loc_464D2F
					jmp		short loc_464CD8

				loc_464D12:
					neg		al
					add		edi, eax
					mov		ecx, eax
					and		ecx, 1Fh
					jz		short loc_464D2B
					mov		ebx, gdwCurrentMask
					shl		ebx, cl
					mov		gdwCurrentMask, ebx
				loc_464D2B:
					sub		edx, eax
					jnz		short loc_464CD8
				loc_464D2F:
					pop		ecx
					sub		edi, 320h
					mov		eax, gpDrawMask
					sub		eax, 4
					mov		gpDrawMask, eax
					dec		ecx
					jnz		short loc_464CC6
				ret_4652C0_9S:
					pop		eax
				}
				break;
			case 10: // upper (bottom transparent), without lighting
				__asm {
					mov		edx, 1Eh
				loc_464D50:
					cmp		edi, gpBufEnd
					jb		ret_4652C1_10S
					add		edi, edx
					mov		ecx, 20h
					sub		ecx, edx
					shr		ecx, 2
					jnb		short loc_464D7B
					mov		ax, [esi+2]
					add		esi, 4
					mov		[edi], ax
					add		edi, 2
					test	ecx, ecx
					jz		short loc_464D88
				loc_464D7B:
					mov		eax, [esi]
					add		esi, 4
					mov		[edi], eax
					dec		ecx
					lea		edi, [edi+4]
					jnz		short loc_464D7B
				loc_464D88:
					sub		edi, 320h
					sub		edx, 2
					jge		short loc_464D50
					mov		edx, 2
				loc_464D98:
					cmp		edi, gpBufEnd
					jb		ret_4652C1_10S
					add		edi, edx
					mov		ecx, 20h
					sub		ecx, edx
					shr		ecx, 2
					jnb		short loc_464DC3
					mov		ax, [esi+2]
					add		esi, 4
					mov		[edi], ax
					test	ecx, ecx
					lea		edi, [edi+2]
					jz		short loc_464DD0
				loc_464DC3:
					mov		eax, [esi]
					add		esi, 4
					mov		[edi], eax
					add		edi, 4
					dec		ecx
					jnz		short loc_464DC3
				loc_464DD0:
					sub		edi, 320h
					add		edx, 2
					cmp		edx, 20h
					jnz		short loc_464D98
				ret_4652C1_10S:
				}
				break;
			case 11: // upper (bottom transparent), without lighting
				__asm {
					push	ebp
					mov		edx, 1Eh
				loc_464DE9:
					cmp		edi, gpBufEnd
					jb		loc_464E77
					mov		ecx, 20h
					sub		ecx, edx
					mov		ebp, ecx
					shr		ecx, 2
					jz		short loc_464E10
				loc_464E03:
					mov		eax, [esi]
					add		esi, 4
					mov		[edi], eax
					add		edi, 4
					dec		ecx
					jnz		short loc_464E03
				loc_464E10:
					and		ebp, 2
					jz		short loc_464E21
					mov		ax, [esi]
					add		esi, 4
					mov		[edi], ax
					add		edi, 2
				loc_464E21:
					sub		edi, 320h
					add		edi, edx
					sub		edx, 2
					jge		short loc_464DE9
					mov		edx, 2
				loc_464E33:
					cmp		edi, gpBufEnd
					jb		short loc_464E77
					mov		ecx, 20h
					sub		ecx, edx
					mov		ebp, ecx
					shr		ecx, 2
					jz		short loc_464E56
				loc_464E49:
					mov		eax, [esi]
					add		esi, 4
					mov		[edi], eax
					add		edi, 4
					dec		ecx
					jnz		short loc_464E49
				loc_464E56:
					and		ebp, 2
					jz		short loc_464E67
					mov		ax, [esi]
					add		esi, 4
					mov		[edi], ax
					add		edi, 2
				loc_464E67:
					sub		edi, 320h
					add		edi, edx
					add		edx, 2
					cmp		edx, 20h
					jnz		short loc_464E33
				loc_464E77:
					pop		ebp
				}
				break;
			case 12: // upper (bottom transparent), without lighting
				__asm {
					mov		edx, 1Eh
				loc_464E82:
					cmp		edi, gpBufEnd
					jb		ret_4652C1_12S
					add		edi, edx
					mov		ecx, 20h
					sub		ecx, edx
					shr		ecx, 2
					jnb		short loc_464EAD
					mov		ax, [esi+2]
					add		esi, 4
					mov		[edi], ax
					add		edi, 2
					test	ecx, ecx
					jz		short loc_464EBA
				loc_464EAD:
					mov		eax, [esi]
					add		esi, 4
					mov		[edi], eax
					add		edi, 4
					dec		ecx
					jnz		short loc_464EAD
				loc_464EBA:
					sub		edi, 320h
					sub		edx, 2
					jge		short loc_464E82
					mov		eax, gpDrawMask
					sub		eax, 40h
					mov		gpDrawMask, eax
					mov		edx, 10h
				loc_464ED7:
					cmp		edi, gpBufEnd
					jb		ret_4652C1_12S
					push	edx
					mov		eax, gpDrawMask
					mov		edx, [eax]
					mov		ecx, 20h
				loc_464EF0:
					mov		al, [esi]
					inc		esi
					shl		edx, 1
					jnb		short loc_464EF9
					mov		[edi], al
				loc_464EF9:
					inc		edi
					dec		ecx
					jnz		short loc_464EF0
					pop		edx
					sub		edi, 320h
					mov		eax, gpDrawMask
					sub		eax, 4
					mov		gpDrawMask, eax
					dec		edx
					jnz		short loc_464ED7
				ret_4652C1_12S:
				}
				break;
			default: // upper (bottom transparent), without lighting
				__asm {
					push	ebp
					mov		edx, 1Eh
				loc_464F1F:
					cmp		edi, gpBufEnd
					jb		loc_464FB6
					mov		ecx, 20h
					sub		ecx, edx
					mov		ebp, ecx
					shr		ecx, 2
					jz		short loc_464F46
				loc_464F39:
					mov		eax, [esi]
					add		esi, 4
					mov		[edi], eax
					add		edi, 4
					dec		ecx
					jnz		short loc_464F39
				loc_464F46:
					and		ebp, 2
					jz		short loc_464F57
					mov		ax, [esi]
					add		esi, 4
					mov		[edi], ax
					add		edi, 2
				loc_464F57:
					sub		edi, 320h
					add		edi, edx
					sub		edx, 2
					jge		short loc_464F1F
					mov		eax, gpDrawMask
					sub		eax, 40h
					mov		gpDrawMask, eax
					mov		edx, 10h
				loc_464F76:
					cmp		edi, gpBufEnd
					jb		short loc_464FB6
					push	edx
					mov		eax, gpDrawMask
					mov		edx, [eax]
					mov		ecx, 20h
				loc_464F8B:
					mov		al, [esi]
					inc		esi
					shl		edx, 1
					jnb		short loc_464F94
					mov		[edi], al
				loc_464F94:
					inc		edi
					dec		ecx
					jnz		short loc_464F8B
					mov		ebp, esi
					and		ebp, 2
					add		esi, ebp
					pop		edx
					sub		edi, 320h
					mov		eax, gpDrawMask
					sub		eax, 4
					mov		gpDrawMask, eax
					dec		edx
					jnz		short loc_464F76
				loc_464FB6:
					pop		ebp
				}
				break;
		}
		return;
	}
	if ( (_BYTE)light_table_index != lightmax )
	{
		if ( !(level_cel_block & 0x8000) )
		{
			src = (unsigned char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
			tbl = (unsigned char *)&pLightTbl[256 * light_table_index];
			cel_type_16 = (unsigned char)(level_cel_block >> 12);
			__asm {
				xor		edx, edx
				xor		ecx, ecx
				mov		ebx, tbl
				mov		edi, dst
				mov		esi, src
			}
			switch ( cel_type_16 )
			{
				case 0: // upper (bottom transparent), with lighting
					__asm {
						mov		edx, 20h
					loc_464892:
						cmp		edi, gpBufEnd
						jb		ret_4652C1_0L
						push	edx
						mov		eax, gpDrawMask
						mov		edx, [eax]
						mov		ecx, 20h
					loc_4648AB:
						mov		al, [esi]
						inc		esi
						shl		edx, 1
						jnb		short loc_4648B5
						xlat
						mov		[edi], al
					loc_4648B5:
						inc		edi
						dec		ecx
						jnz		short loc_4648AB
						pop		edx
						sub		edi, 320h
						mov		eax, gpDrawMask
						sub		eax, 4
						mov		gpDrawMask, eax
						dec		edx
						jnz		short loc_464892
					ret_4652C1_0L:
					}
					break;
				case 1: // upper (bottom transparent), with lighting
					__asm {
						mov		ecx, 20h
					loc_4648DA:
						push	ecx
						mov		eax, gpDrawMask
						mov		eax, [eax]
						mov		gdwCurrentMask, eax
						mov		edx, 20h
					loc_4648EC:
						xor		eax, eax
						mov		al, [esi]
						inc		esi
						test	al, al
						js		short loc_464927
						sub		edx, eax
						cmp		edi, gpBufEnd
						jb		ret_4652C0_1L
						mov		ecx, eax
						push	edx
						mov		edx, gdwCurrentMask
					loc_46490C:
						mov		al, [esi]
						inc		esi
						shl		edx, 1
						jnb		short loc_464916
						xlat
						mov		[edi], al
					loc_464916:
						inc		edi
						dec		ecx
						jnz		short loc_46490C
						mov		gdwCurrentMask, edx
						pop		edx
						test	edx, edx
						jz		short loc_464944
						jmp		short loc_4648EC

					loc_464927:
						neg		al
						add		edi, eax
						mov		ecx, eax
						and		ecx, 1Fh
						jz		short loc_464940
						push	eax
						mov		eax, gdwCurrentMask
						shl		eax, cl
						mov		gdwCurrentMask, eax
						pop		eax
					loc_464940:
						sub		edx, eax
						jnz		short loc_4648EC
					loc_464944:
						pop		ecx
						sub		edi, 320h
						mov		eax, gpDrawMask
						sub		eax, 4
						mov		gpDrawMask, eax
						dec		ecx
						jnz		loc_4648DA
					ret_4652C0_1L:
						pop		eax
					}
					break;
				case 2: // upper (bottom transparent), with lighting
					__asm {
						mov		edx, 1Eh
					loc_464969:
						cmp		edi, gpBufEnd
						jb		ret_4652C1_2L
						add		edi, edx
						mov		ecx, 20h
						sub		ecx, edx
						shr		ecx, 2
						jnb		short loc_46499E
						mov		ax, [esi+2]
						add		esi, 4
						xlat
						ror		ax, 8
						xlat
						ror		ax, 8
						mov		[edi], ax
						add		edi, 2
						test	ecx, ecx
						jz		short loc_4649BB
					loc_46499E:
						mov		eax, [esi]
						add		esi, 4
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						mov		[edi], eax
						add		edi, 4
						dec		ecx
						jnz		short loc_46499E
					loc_4649BB:
						sub		edi, 320h
						sub		edx, 2
						jge		short loc_464969
						mov		edx, 2
					loc_4649CB:
						cmp		edi, gpBufEnd
						jb		ret_4652C1_2L
						add		edi, edx
						mov		ecx, 20h
						sub		ecx, edx
						shr		ecx, 2
						jnb		short loc_464A00
						mov		ax, [esi+2]
						add		esi, 4
						xlat
						ror		ax, 8
						xlat
						ror		ax, 8
						mov		[edi], ax
						add		edi, 2
						test	ecx, ecx
						jz		short loc_464A1D
					loc_464A00:
						mov		eax, [esi]
						add		esi, 4
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						mov		[edi], eax
						add		edi, 4
						dec		ecx
						jnz		short loc_464A00
					loc_464A1D:
						sub		edi, 320h
						add		edx, 2
						cmp		edx, 20h
						jnz		short loc_4649CB
					ret_4652C1_2L:
					}
					break;
				case 3: // upper (bottom transparent), with lighting
					__asm {
						push	ebp
						mov		edx, 1Eh
					loc_464A36:
						cmp		edi, gpBufEnd
						jb		loc_464AF8
						mov		ecx, 20h
						sub		ecx, edx
						mov		ebp, ecx
						shr		ecx, 2
						jz		short loc_464A6D
					loc_464A50:
						mov		eax, [esi]
						add		esi, 4
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						mov		[edi], eax
						add		edi, 4
						dec		ecx
						jnz		short loc_464A50
					loc_464A6D:
						and		ebp, 2
						jz		short loc_464A88
						mov		ax, [esi]
						add		esi, 4
						xlat
						ror		ax, 8
						xlat
						ror		ax, 8
						mov		[edi], ax
						add		edi, 2
					loc_464A88:
						sub		edi, 320h
						add		edi, edx
						sub		edx, 2
						jge		short loc_464A36
						mov		edx, 2
					loc_464A9A:
						cmp		edi, gpBufEnd
						jb		short loc_464AF8
						mov		ecx, 20h
						sub		ecx, edx
						mov		ebp, ecx
						shr		ecx, 2
						jz		short loc_464ACD
					loc_464AB0:
						mov		eax, [esi]
						add		esi, 4
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						mov		[edi], eax
						add		edi, 4
						dec		ecx
						jnz		short loc_464AB0
					loc_464ACD:
						and		ebp, 2
						jz		short loc_464AE8
						mov		ax, [esi]
						add		esi, 4
						xlat
						ror		ax, 8
						xlat
						ror		ax, 8
						mov		[edi], ax
						add		edi, 2
					loc_464AE8:
						sub		edi, 320h
						add		edi, edx
						add		edx, 2
						cmp		edx, 20h
						jnz		short loc_464A9A
					loc_464AF8:
						pop		ebp
					}
					break;
				case 4: // upper (bottom transparent), with lighting
					__asm {
						mov		edx, 1Eh
					loc_464B03:
						cmp		edi, gpBufEnd
						jb		ret_4652C1_4L
						add		edi, edx
						mov		ecx, 20h
						sub		ecx, edx
						shr		ecx, 2
						jnb		short loc_464B38
						mov		ax, [esi+2]
						add		esi, 4
						xlat
						ror		ax, 8
						xlat
						ror		ax, 8
						mov		[edi], ax
						add		edi, 2
						test	ecx, ecx
						jz		short loc_464B55
					loc_464B38:
						mov		eax, [esi]
						add		esi, 4
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						mov		[edi], eax
						add		edi, 4
						dec		ecx
						jnz		short loc_464B38
					loc_464B55:
						sub		edi, 320h
						sub		edx, 2
						jge		short loc_464B03
						mov		eax, gpDrawMask
						sub		eax, 40h
						mov		gpDrawMask, eax
						mov		edx, 10h
					loc_464B72:
						cmp		edi, gpBufEnd
						jb		ret_4652C1_4L
						push	edx
						mov		eax, gpDrawMask
						mov		edx, [eax]
						mov		ecx, 20h
						mov		eax, esi
						and		eax, 2
						add		esi, eax
					loc_464B92:
						mov		al, [esi]
						inc		esi
						shl		edx, 1
						jnb		short loc_464B9C
						xlat
						mov		[edi], al
					loc_464B9C:
						inc		edi
						dec		ecx
						jnz		short loc_464B92
						pop		edx
						sub		edi, 320h
						mov		eax, gpDrawMask
						sub		eax, 4
						mov		gpDrawMask, eax
						dec		edx
						jnz		short loc_464B72
					ret_4652C1_4L:
					}
					break;
				default: // upper (bottom transparent), with lighting
					__asm {
						push	ebp
						mov		edx, 1Eh
					loc_464BC2:
						cmp		edi, gpBufEnd
						jb		loc_464C74
						mov		ecx, 20h
						sub		ecx, edx
						mov		ebp, ecx
						shr		ecx, 2
						jz		short loc_464BF9
					loc_464BDC:
						mov		eax, [esi]
						add		esi, 4
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						mov		[edi], eax
						add		edi, 4
						dec		ecx
						jnz		short loc_464BDC
					loc_464BF9:
						and		ebp, 2
						jz		short loc_464C14
						mov		ax, [esi]
						add		esi, 4
						xlat
						ror		ax, 8
						xlat
						ror		ax, 8
						mov		[edi], ax
						add		edi, 2
					loc_464C14:
						sub		edi, 320h
						add		edi, edx
						sub		edx, 2
						jge		short loc_464BC2
						mov		eax, gpDrawMask
						sub		eax, 40h
						mov		gpDrawMask, eax
						mov		edx, 10h
					loc_464C33:
						cmp		edi, gpBufEnd
						jb		short loc_464C74
						push	edx
						mov		eax, gpDrawMask
						mov		edx, [eax]
						mov		ecx, 20h
					loc_464C48:
						mov		al, [esi]
						inc		esi
						shl		edx, 1
						jnb		short loc_464C52
						xlat
						mov		[edi], al
					loc_464C52:
						inc		edi
						dec		ecx
						jnz		short loc_464C48
						mov		ebp, esi
						and		ebp, 2
						add		esi, ebp
						pop		edx
						sub		edi, 320h
						mov		eax, gpDrawMask
						sub		eax, 4
						mov		gpDrawMask, eax
						dec		edx
						jnz		short loc_464C33
					loc_464C74:
						pop		ebp
					}
					break;
			}
			return;
		}
		src = (unsigned char *)pSpeedCels
				   + *(_DWORD *)&gpCelFrame[4 * (light_table_index + 16 * (level_cel_block & 0xFFF))];
		cel_type_16 = (unsigned char)(level_cel_block >> 12);
		goto LABEL_12;
	}
	if ( level_cel_block & 0x8000 )
		level_cel_block = *(_DWORD *)&gpCelFrame[64 * (level_cel_block & 0xFFF)]
						+ (unsigned short)(level_cel_block & 0xF000);
	src = (unsigned char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
	cel_type_16 = (level_cel_block >> 12) & 7;
	__asm {
		xor		edx, edx
		xor		ecx, ecx
		mov		edi, dst
		mov		esi, src
	}
	switch ( cel_type_16 )
	{
		case 0: // upper (bottom transparent), black
			__asm {
				mov		edx, 20h
			loc_464FC1:
				cmp		edi, gpBufEnd
				jb		ret_4652C1_0B
				push	edx
				mov		eax, gpDrawMask
				mov		edx, [eax]
				xor		eax, eax
				mov		ecx, 20h
			loc_464FDC:
				shl		edx, 1
				jnb		short loc_464FE2
				mov		[edi], al
			loc_464FE2:
				inc		edi
				dec		ecx
				jnz		short loc_464FDC
				pop		edx
				sub		edi, 320h
				mov		eax, gpDrawMask
				sub		eax, 4
				mov		gpDrawMask, eax
				dec		edx
				jnz		short loc_464FC1
			ret_4652C1_0B:
			}
			break;
		case 1: // upper (bottom transparent), black
			__asm {
				mov		ecx, 20h
			loc_465007:
				push	ecx
				mov		eax, gpDrawMask
				mov		eax, [eax]
				mov		gdwCurrentMask, eax
				mov		edx, 20h
			loc_465019:
				xor		eax, eax
				mov		al, [esi]
				inc		esi
				test	al, al
				js		short loc_465054
				sub		edx, eax
				cmp		edi, gpBufEnd
				jb		ret_4652C0_1B
				push	edx
				mov		edx, gdwCurrentMask
				mov		ecx, eax
				add		esi, ecx
				xor		eax, eax
			loc_46503D:
				shl		edx, 1
				jnb		short loc_465043
				mov		[edi], al
			loc_465043:
				inc		edi
				dec		ecx
				jnz		short loc_46503D
				mov		gdwCurrentMask, edx
				pop		edx
				test	edx, edx
				jz		short loc_465071
				jmp		short loc_465019

			loc_465054:
				neg		al
				add		edi, eax
				mov		ecx, eax
				and		ecx, 1Fh
				jz		short loc_46506D
				mov		ebx, gdwCurrentMask
				shl		ebx, cl
				mov		gdwCurrentMask, ebx
			loc_46506D:
				sub		edx, eax
				jnz		short loc_465019
			loc_465071:
				pop		ecx
				sub		edi, 320h
				mov		eax, gpDrawMask
				sub		eax, 4
				mov		gpDrawMask, eax
				dec		ecx
				jnz		loc_465007
			ret_4652C0_1B:
				pop		eax
			}
			break;
		case 2: // upper (bottom transparent), black
			__asm {
				mov		edx, 1Eh
				xor		eax, eax
			loc_465098:
				cmp		edi, gpBufEnd
				jb		ret_4652C1_2B
				add		edi, edx
				mov		ecx, 20h
				sub		ecx, edx
				shr		ecx, 2
				jnb		short loc_4650BC
				mov		[edi], ax
				add		edi, 2
				test	ecx, ecx
				jz		short loc_4650C4
			loc_4650BC:
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_4650BC
			loc_4650C4:
				sub		edi, 320h
				test	edx, edx
				jz		short loc_4650D3
				sub		edx, 2
				jmp		short loc_465098

			loc_4650D3:
				mov		edx, 2
			loc_4650D8:
				cmp		edi, gpBufEnd
				jb		ret_4652C1_2B
				add		edi, edx
				mov		ecx, 20h
				sub		ecx, edx
				shr		ecx, 2
				jnb		short loc_4650FC
				mov		[edi], ax
				add		edi, 2
				test	ecx, ecx
				jz		short loc_465104
			loc_4650FC:
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_4650FC
			loc_465104:
				sub		edi, 320h
				add		edx, 2
				cmp		edx, 20h
				jnz		short loc_4650D8
			ret_4652C1_2B:
			}
			break;
		case 3: // upper (bottom transparent), black
			__asm {
				mov		edx, 1Eh
				xor		eax, eax
			loc_46511E:
				cmp		edi, gpBufEnd
				jb		ret_4652C1_3B
				mov		ecx, 20h
				sub		ecx, edx
				shr		ecx, 2
				jnb		short loc_465140
				mov		[edi], ax
				add		edi, 2
				test	ecx, ecx
				jz		short loc_465148
			loc_465140:
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_465140
			loc_465148:
				sub		edi, 320h
				test	edx, edx
				jz		short loc_465159
				add		edi, edx
				sub		edx, 2
				jmp		short loc_46511E

			loc_465159:
				mov		edx, 2
			loc_46515E:
				cmp		edi, gpBufEnd
				jb		ret_4652C1_3B
				mov		ecx, 20h
				sub		ecx, edx
				shr		ecx, 2
				jnb		short loc_465180
				mov		[edi], ax
				add		edi, 2
				test	ecx, ecx
				jz		short loc_465188
			loc_465180:
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_465180
			loc_465188:
				sub		edi, 320h
				add		edi, edx
				add		edx, 2
				cmp		edx, 20h
				jnz		short loc_46515E
			ret_4652C1_3B:
			}
			break;
		case 4: // upper (bottom transparent), black
			__asm {
				mov		edx, 1Eh
				xor		eax, eax
			loc_4651A4:
				cmp		edi, gpBufEnd
				jb		ret_4652C1_4B
				add		edi, edx
				mov		ecx, 20h
				sub		ecx, edx
				shr		ecx, 2
				jnb		short loc_4651C8
				mov		[edi], ax
				add		edi, 2
				test	ecx, ecx
				jz		short loc_4651D0
			loc_4651C8:
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_4651C8
			loc_4651D0:
				sub		edi, 320h
				test	edx, edx
				jz		short loc_4651DF
				sub		edx, 2
				jmp		short loc_4651A4

			loc_4651DF:
				mov		eax, gpDrawMask
				sub		eax, 40h
				mov		gpDrawMask, eax
				mov		edx, 10h
			loc_4651F1:
				cmp		edi, gpBufEnd
				jb		ret_4652C1_4B
				push	edx
				mov		eax, gpDrawMask
				mov		edx, [eax]
				xor		eax, eax
				mov		ecx, 20h
			loc_46520C:
				shl		edx, 1
				jnb		short loc_465212
				mov		[edi], al
			loc_465212:
				inc		edi
				dec		ecx
				jnz		short loc_46520C
				pop		edx
				sub		edi, 320h
				mov		eax, gpDrawMask
				sub		eax, 4
				mov		gpDrawMask, eax
				dec		edx
				jnz		short loc_4651F1
			ret_4652C1_4B:
			}
			break;
		default: // upper (bottom transparent), black
			__asm {
				mov		edx, 1Eh
				xor		eax, eax
			loc_465239:
				cmp		edi, gpBufEnd
				jb		ret_4652C1_5B
				mov		ecx, 20h
				sub		ecx, edx
				shr		ecx, 2
				jnb		short loc_46525B
				mov		[edi], ax
				add		edi, 2
				test	ecx, ecx
				jz		short loc_465263
			loc_46525B:
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_46525B
			loc_465263:
				sub		edi, 320h
				test	edx, edx
				jz		short loc_465274
				add		edi, edx
				sub		edx, 2
				jmp		short loc_465239

			loc_465274:
				mov		eax, gpDrawMask
				sub		eax, 40h
				mov		gpDrawMask, eax
				mov		edx, 10h
			loc_465286:
				cmp		edi, gpBufEnd
				jb		short ret_4652C1_5B
				push	edx
				mov		eax, gpDrawMask
				mov		edx, [eax]
				xor		eax, eax
				mov		ecx, 20h
			loc_46529D:
				shl		edx, 1
				jnb		short loc_4652A3
				mov		[edi], al
			loc_4652A3:
				inc		edi
				dec		ecx
				jnz		short loc_46529D
				pop		edx
				sub		edi, 320h
				mov		eax, gpDrawMask
				sub		eax, 4
				mov		gpDrawMask, eax
				dec		edx
				jnz		short loc_465286
			ret_4652C1_5B:
			}
			break;
	}
}

void __fastcall drawUpperScreen(unsigned char *pbDst)
{
	unsigned char *dst; // edi MAPDST
	unsigned char *tbl; // ebx
	unsigned char *src; // esi MAPDST
	short cel_type_16; // ax MAPDST

	if ( cel_transparency_active )
	{
		if ( !arch_draw_type )
		{
			drawTopArchesUpperScreen(pbDst);
			return;
		}
		if ( arch_draw_type == 1 )
		{
			if ( block_lvid[level_piece_id] == 1 || block_lvid[level_piece_id] == 3 )
			{
				drawBottomArchesUpperScreen(pbDst, &LeftMask[31]);
				return;
			}
		}
		if ( arch_draw_type == 2 )
		{
			if ( block_lvid[level_piece_id] == 2 || block_lvid[level_piece_id] == 3 )
			{
				drawBottomArchesUpperScreen(pbDst, &RightMask[31]);
				return;
			}
		}
	}
	gpCelFrame = (unsigned char *)speed_cel_frame_num_from_light_index_frame_num;
	dst = pbDst;
	if ( !(_BYTE)light_table_index )
	{
		if ( level_cel_block & 0x8000 )
			level_cel_block = *(_DWORD *)&gpCelFrame[64 * (level_cel_block & 0xFFF)]
							+ (unsigned short)(level_cel_block & 0xF000);
		src = (unsigned char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
		cel_type_16 = ((level_cel_block >> 12) & 7) + 8;
LABEL_22:
		__asm {
			xor		edx, edx
			xor		ecx, ecx
			mov		edi, dst
			mov		esi, src
		}
		switch ( cel_type_16 )
		{
			case 8: // upper (solid), without lighting
				__asm {
					mov		edx, 20h
				loc_465A10:
					cmp		edi, gpBufEnd
					jb		ret_465F33_8S
					mov		ecx, 8
				loc_465A21:
					mov		eax, [esi]
					add		esi, 4
					mov		[edi], eax
					add		edi, 4
					dec		ecx
					jnz		short loc_465A21
					sub		edi, 320h
					dec		edx
					jnz		short loc_465A10
				ret_465F33_8S:
				}
				break;
			case 9: // upper (solid), without lighting
				__asm {
					push	ebp
					mov		ebp, 20h
				loc_465A42:
					mov		edx, 20h
				loc_465A47:
					xor		eax, eax
					mov		al, [esi]
					inc		esi
					test	al, al
					js		short loc_465A91
					sub		edx, eax
					cmp		edi, gpBufEnd
					jb		short loc_465AA2
					mov		ecx, eax
					shr		ecx, 1
					jnb		short loc_465A6A
					mov		al, [esi]
					inc		esi
					mov		[edi], al
					inc		edi
					test	ecx, ecx
					jz		short loc_465A8B
				loc_465A6A:
					shr		ecx, 1
					jnb		short loc_465A7E
					mov		ax, [esi]
					add		esi, 2
					mov		[edi], ax
					add		edi, 2
					test	ecx, ecx
					jz		short loc_465A8B
				loc_465A7E:
					mov		eax, [esi]
					add		esi, 4
					mov		[edi], eax
					add		edi, 4
					dec		ecx
					jnz		short loc_465A7E
				loc_465A8B:
					test	edx, edx
					jz		short loc_465A99
					jmp		short loc_465A47

				loc_465A91:
					neg		al
					add		edi, eax
					sub		edx, eax
					jnz		short loc_465A47
				loc_465A99:
					sub		edi, 320h
					dec		ebp
					jnz		short loc_465A42
				loc_465AA2:
					pop		ebp
				}
				break;
			case 10: // upper (solid), without lighting
				__asm {
					mov		edx, 1Eh
				loc_465AAD:
					cmp		edi, gpBufEnd
					jb		ret_465F33_10S
					add		edi, edx
					mov		ecx, 20h
					sub		ecx, edx
					shr		ecx, 2
					jnb		short loc_465AD8
					mov		ax, [esi+2]
					add		esi, 4
					mov		[edi], ax
					add		edi, 2
					test	ecx, ecx
					jz		short loc_465AE5
				loc_465AD8:
					mov		eax, [esi]
					add		esi, 4
					mov		[edi], eax
					add		edi, 4
					dec		ecx
					jnz		short loc_465AD8
				loc_465AE5:
					sub		edi, 320h
					sub		edx, 2
					jge		short loc_465AAD
					mov		edx, 2
				loc_465AF5:
					cmp		edi, gpBufEnd
					jb		ret_465F33_10S
					add		edi, edx
					mov		ecx, 20h
					sub		ecx, edx
					shr		ecx, 2
					jnb		short loc_465B20
					mov		ax, [esi+2]
					add		esi, 4
					mov		[edi], ax
					add		edi, 2
					test	ecx, ecx
					jz		short loc_465B2D
				loc_465B20:
					mov		eax, [esi]
					add		esi, 4
					mov		[edi], eax
					add		edi, 4
					dec		ecx
					jnz		short loc_465B20
				loc_465B2D:
					sub		edi, 320h
					add		edx, 2
					cmp		edx, 20h
					jnz		short loc_465AF5
				ret_465F33_10S:
				}
				break;
			case 11: // upper (solid), without lighting
				__asm {
					push	ebp
					mov		edx, 1Eh
				loc_465B46:
					cmp		edi, gpBufEnd
					jb		loc_465BD4
					mov		ecx, 20h
					sub		ecx, edx
					mov		ebp, ecx
					shr		ecx, 2
					jz		short loc_465B6D
				loc_465B60:
					mov		eax, [esi]
					add		esi, 4
					mov		[edi], eax
					add		edi, 4
					dec		ecx
					jnz		short loc_465B60
				loc_465B6D:
					and		ebp, 2
					jz		short loc_465B7E
					mov		ax, [esi]
					add		esi, 4
					mov		[edi], ax
					add		edi, 2
				loc_465B7E:
					sub		edi, 320h
					add		edi, edx
					sub		edx, 2
					jge		short loc_465B46
					mov		edx, 2
				loc_465B90:
					cmp		edi, gpBufEnd
					jb		short loc_465BD4
					mov		ecx, 20h
					sub		ecx, edx
					mov		ebp, ecx
					shr		ecx, 2
					jz		short loc_465BB3
				loc_465BA6:
					mov		eax, [esi]
					add		esi, 4
					mov		[edi], eax
					add		edi, 4
					dec		ecx
					jnz		short loc_465BA6
				loc_465BB3:
					and		ebp, 2
					jz		short loc_465BC4
					mov		ax, [esi]
					add		esi, 4
					mov		[edi], ax
					add		edi, 2
				loc_465BC4:
					sub		edi, 320h
					add		edi, edx
					add		edx, 2
					cmp		edx, 20h
					jnz		short loc_465B90
				loc_465BD4:
					pop		ebp
				}
				break;
			case 12: // upper (solid), without lighting
				__asm {
					mov		edx, 1Eh
				loc_465BDF:
					cmp		edi, gpBufEnd
					jb		ret_465F33_12S
					add		edi, edx
					mov		ecx, 20h
					sub		ecx, edx
					shr		ecx, 2
					jnb		short loc_465C0A
					mov		ax, [esi+2]
					add		esi, 4
					mov		[edi], ax
					add		edi, 2
					test	ecx, ecx
					jz		short loc_465C17
				loc_465C0A:
					mov		eax, [esi]
					add		esi, 4
					mov		[edi], eax
					add		edi, 4
					dec		ecx
					jnz		short loc_465C0A
				loc_465C17:
					sub		edi, 320h
					sub		edx, 2
					jge		short loc_465BDF
					mov		edx, 10h
				loc_465C27:
					cmp		edi, gpBufEnd
					jb		ret_465F33_12S
					mov		ecx, 8
				loc_465C38:
					mov		eax, [esi]
					add		esi, 4
					mov		[edi], eax
					add		edi, 4
					dec		ecx
					jnz		short loc_465C38
					sub		edi, 320h
					dec		edx
					jnz		short loc_465C27
				ret_465F33_12S:
				}
				break;
			default: // upper (solid), without lighting
				__asm {
					push	ebp
					mov		edx, 1Eh
				loc_465C59:
					cmp		edi, gpBufEnd
					jb		short loc_465CC2
					mov		ecx, 20h
					sub		ecx, edx
					mov		ebp, ecx
					shr		ecx, 2
					jz		short loc_465C7C
				loc_465C6F:
					mov		eax, [esi]
					add		esi, 4
					mov		[edi], eax
					add		edi, 4
					dec		ecx
					jnz		short loc_465C6F
				loc_465C7C:
					and		ebp, 2
					jz		short loc_465C8D
					mov		ax, [esi]
					add		esi, 4
					mov		[edi], ax
					add		edi, 2
				loc_465C8D:
					sub		edi, 320h
					add		edi, edx
					sub		edx, 2
					jge		short loc_465C59
					mov		edx, 10h
				loc_465C9F:
					cmp		edi, gpBufEnd
					jb		short loc_465CC2
					mov		ecx, 8
				loc_465CAC:
					mov		eax, [esi]
					add		esi, 4
					mov		[edi], eax
					add		edi, 4
					dec		ecx
					jnz		short loc_465CAC
					sub		edi, 320h
					dec		edx
					jnz		short loc_465C9F
				loc_465CC2:
					pop		ebp
				}
				break;
		}
		return;
	}
	if ( (_BYTE)light_table_index != lightmax )
	{
		if ( !(level_cel_block & 0x8000) )
		{
			src = (unsigned char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
			tbl = (unsigned char *)&pLightTbl[256 * light_table_index];
			cel_type_16 = (unsigned short)level_cel_block >> 12;
			__asm {
				xor		edx, edx
				xor		ecx, ecx
				mov		ebx, tbl
				mov		edi, dst
				mov		esi, src
			}
			switch ( cel_type_16 )
			{
				case 0: // upper (solid), with lighting
					__asm {
						mov		edx, 20h
					loc_465562:
						cmp		edi, gpBufEnd
						jb		ret_465F33_0L
						mov		ecx, 20h
						push	edx
					loc_465574:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						mov		ch, [ebx+edx]
						mov		dl, ah
						ror		eax, 10h
						mov		[edi], ch
						mov		ch, [ebx+edx]
						mov		dl, al
						mov		[edi+1], ch
						mov		ch, [ebx+edx]
						mov		dl, ah
						mov		[edi+2], ch
						mov		ch, [ebx+edx]
						mov		[edi+3], ch
						add		edi, 4
						sub		cl, 4
						cmp		cl, 4
						jge		short loc_465574
						pop		edx
						sub		edi, 320h
						dec		edx
						jnz		short loc_465562
					ret_465F33_0L:
					}
					break;
				case 1: // upper (solid), with lighting
					__asm {
						push	ebp
						mov		ebp, 20h
					loc_4655BB:
						mov		edx, 20h
					loc_4655C0:
						xor		eax, eax
						mov		al, [esi]
						inc		esi
						test	al, al
						js		short loc_465644
						sub		edx, eax
						cmp		edi, gpBufEnd
						jb		loc_46565D
						mov		ecx, eax
						push	edx
						cmp		cl, 4
						jl		short loc_465611
					loc_4655DF:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						mov		ch, [ebx+edx]
						mov		dl, ah
						ror		eax, 10h
						mov		[edi], ch
						mov		ch, [ebx+edx]
						mov		dl, al
						mov		[edi+1], ch
						mov		ch, [ebx+edx]
						mov		dl, ah
						mov		[edi+2], ch
						mov		ch, [ebx+edx]
						mov		[edi+3], ch
						add		edi, 4
						sub		cl, 4
						cmp		cl, 4
						jge		short loc_4655DF
					loc_465611:
						cmp		cl, 2
						jl		short loc_46562C
						mov		dl, [esi]
						mov		ch, [ebx+edx]
						mov		[edi], ch
						mov		dl, [esi+1]
						mov		ch, [ebx+edx]
						mov		[edi+1], ch
						add		esi, 2
						add		edi, 2
					loc_46562C:
						and		cl, 1
						jz		short loc_46563A
						mov		dl, [esi]
						inc		esi
						mov		dl, [ebx+edx]
						mov		[edi], dl
						inc		edi
					loc_46563A:
						pop		edx
						test	edx, edx
						jz		short loc_465650
						jmp		loc_4655C0

					loc_465644:
						neg		al
						add		edi, eax
						sub		edx, eax
						jnz		loc_4655C0
					loc_465650:
						sub		edi, 320h
						dec		ebp
						jnz		loc_4655BB
					loc_46565D:
						pop		ebp
					}
					break;
				case 2: // upper (solid), with lighting
					__asm {
						push	ebp
						mov		ebp, 1Eh
					loc_465669:
						cmp		edi, gpBufEnd
						jb		loc_46575F
						add		edi, ebp
						mov		ecx, 20h
						sub		ecx, ebp
						mov		edx, ecx
						and		edx, 2
						add		esi, edx
						cmp		cl, 4
						jl		short loc_4656BC
					loc_46568A:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						mov		ch, [ebx+edx]
						mov		dl, ah
						ror		eax, 10h
						mov		[edi], ch
						mov		ch, [ebx+edx]
						mov		dl, al
						mov		[edi+1], ch
						mov		ch, [ebx+edx]
						mov		dl, ah
						mov		[edi+2], ch
						mov		ch, [ebx+edx]
						mov		[edi+3], ch
						add		edi, 4
						sub		cl, 4
						cmp		cl, 4
						jge		short loc_46568A
					loc_4656BC:
						cmp		cl, 2
						jl		short loc_4656D7
						mov		dl, [esi]
						mov		ch, [ebx+edx]
						mov		[edi], ch
						mov		dl, [esi+1]
						mov		ch, [ebx+edx]
						mov		[edi+1], ch
						add		esi, 2
						add		edi, 2
					loc_4656D7:
						sub		edi, 320h
						sub		ebp, 2
						jge		short loc_465669
						mov		ebp, 2
					loc_4656E7:
						cmp		edi, gpBufEnd
						jb		short loc_46575F
						add		edi, ebp
						mov		ecx, 20h
						sub		ecx, ebp
						mov		edx, ecx
						and		edx, 2
						add		esi, edx
						cmp		cl, 4
						jl		short loc_465736
					loc_465704:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						mov		ch, [ebx+edx]
						mov		dl, ah
						ror		eax, 10h
						mov		[edi], ch
						mov		ch, [ebx+edx]
						mov		dl, al
						mov		[edi+1], ch
						mov		ch, [ebx+edx]
						mov		dl, ah
						mov		[edi+2], ch
						mov		ch, [ebx+edx]
						mov		[edi+3], ch
						add		edi, 4
						sub		cl, 4
						cmp		cl, 4
						jge		short loc_465704
					loc_465736:
						cmp		cl, 2
						jl		short loc_465751
						mov		dl, [esi]
						mov		ch, [ebx+edx]
						mov		[edi], ch
						mov		dl, [esi+1]
						mov		ch, [ebx+edx]
						mov		[edi+1], ch
						add		esi, 2
						add		edi, 2
					loc_465751:
						sub		edi, 320h
						add		ebp, 2
						cmp		ebp, 20h
						jnz		short loc_4656E7
					loc_46575F:
						pop		ebp
					}
					break;
				case 3: // upper (solid), with lighting
					__asm {
						push	ebp
						mov		ebp, 1Eh
					loc_46576B:
						cmp		edi, gpBufEnd
						jb		loc_465861
						mov		ecx, 20h
						sub		ecx, ebp
						cmp		cl, 4
						jl		short loc_4657B5
					loc_465783:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						mov		ch, [ebx+edx]
						mov		dl, ah
						ror		eax, 10h
						mov		[edi], ch
						mov		ch, [ebx+edx]
						mov		dl, al
						mov		[edi+1], ch
						mov		ch, [ebx+edx]
						mov		dl, ah
						mov		[edi+2], ch
						mov		ch, [ebx+edx]
						mov		[edi+3], ch
						add		edi, 4
						sub		cl, 4
						cmp		cl, 4
						jge		short loc_465783
					loc_4657B5:
						cmp		cl, 2
						jl		short loc_4657D0
						mov		dl, [esi]
						mov		ch, [ebx+edx]
						mov		[edi], ch
						mov		dl, [esi+1]
						mov		ch, [ebx+edx]
						mov		[edi+1], ch
						add		esi, 2
						add		edi, 2
					loc_4657D0:
						mov		edx, esi
						and		edx, 2
						add		esi, edx
						sub		edi, 320h
						add		edi, ebp
						sub		ebp, 2
						jge		short loc_46576B
						mov		ebp, 2
					loc_4657E9:
						cmp		edi, gpBufEnd
						jb		short loc_465861
						mov		ecx, 20h
						sub		ecx, ebp
						cmp		cl, 4
						jl		short loc_46582F
					loc_4657FD:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						mov		ch, [ebx+edx]
						mov		dl, ah
						ror		eax, 10h
						mov		[edi], ch
						mov		ch, [ebx+edx]
						mov		dl, al
						mov		[edi+1], ch
						mov		ch, [ebx+edx]
						mov		dl, ah
						mov		[edi+2], ch
						mov		ch, [ebx+edx]
						mov		[edi+3], ch
						add		edi, 4
						sub		cl, 4
						cmp		cl, 4
						jge		short loc_4657FD
					loc_46582F:
						cmp		cl, 2
						jl		short loc_46584A
						mov		dl, [esi]
						mov		ch, [ebx+edx]
						mov		[edi], ch
						mov		dl, [esi+1]
						mov		ch, [ebx+edx]
						mov		[edi+1], ch
						add		esi, 2
						add		edi, 2
					loc_46584A:
						mov		edx, esi
						and		edx, 2
						add		esi, edx
						sub		edi, 320h
						add		edi, ebp
						add		ebp, 2
						cmp		ebp, 20h
						jnz		short loc_4657E9
					loc_465861:
						pop		ebp
					}
					break;
				case 4: // upper (solid), with lighting
					__asm {
						push	ebp
						mov		ebp, 1Eh
					loc_46586D:
						cmp		edi, gpBufEnd
						jb		loc_465933
						add		edi, ebp
						mov		ecx, 20h
						sub		ecx, ebp
						mov		edx, ecx
						and		edx, 2
						add		esi, edx
						cmp		cl, 4
						jl		short loc_4658C0
					loc_46588E:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						mov		ch, [ebx+edx]
						mov		dl, ah
						ror		eax, 10h
						mov		[edi], ch
						mov		ch, [ebx+edx]
						mov		dl, al
						mov		[edi+1], ch
						mov		ch, [ebx+edx]
						mov		dl, ah
						mov		[edi+2], ch
						mov		ch, [ebx+edx]
						mov		[edi+3], ch
						add		edi, 4
						sub		cl, 4
						cmp		cl, 4
						jge		short loc_46588E
					loc_4658C0:
						cmp		cl, 2
						jl		short loc_4658DB
						mov		dl, [esi]
						mov		ch, [ebx+edx]
						mov		[edi], ch
						mov		dl, [esi+1]
						mov		ch, [ebx+edx]
						mov		[edi+1], ch
						add		esi, 2
						add		edi, 2
					loc_4658DB:
						sub		edi, 320h
						sub		ebp, 2
						jge		short loc_46586D
						mov		ebp, 10h
					loc_4658EB:
						cmp		edi, gpBufEnd
						jb		short loc_465933
						mov		ecx, 20h
					loc_4658F8:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						mov		ch, [ebx+edx]
						mov		dl, ah
						ror		eax, 10h
						mov		[edi], ch
						mov		ch, [ebx+edx]
						mov		dl, al
						mov		[edi+1], ch
						mov		ch, [ebx+edx]
						mov		dl, ah
						mov		[edi+2], ch
						mov		ch, [ebx+edx]
						mov		[edi+3], ch
						add		edi, 4
						sub		cl, 4
						cmp		cl, 4
						jge		short loc_4658F8
						sub		edi, 320h
						dec		ebp
						jnz		short loc_4658EB
					loc_465933:
						pop		ebp
					}
					break;
				default: // upper (solid), with lighting
					__asm {
						push	ebp
						mov		ebp, 1Eh
					loc_46593F:
						cmp		edi, gpBufEnd
						jb		loc_465A05
						mov		ecx, 20h
						sub		ecx, ebp
						cmp		cl, 4
						jl		short loc_465989
					loc_465957:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						mov		ch, [ebx+edx]
						mov		dl, ah
						ror		eax, 10h
						mov		[edi], ch
						mov		ch, [ebx+edx]
						mov		dl, al
						mov		[edi+1], ch
						mov		ch, [ebx+edx]
						mov		dl, ah
						mov		[edi+2], ch
						mov		ch, [ebx+edx]
						mov		[edi+3], ch
						add		edi, 4
						sub		cl, 4
						cmp		cl, 4
						jge		short loc_465957
					loc_465989:
						cmp		cl, 2
						jl		short loc_4659A4
						mov		dl, [esi]
						mov		ch, [ebx+edx]
						mov		[edi], ch
						mov		dl, [esi+1]
						mov		ch, [ebx+edx]
						mov		[edi+1], ch
						add		esi, 2
						add		edi, 2
					loc_4659A4:
						mov		edx, esi
						and		edx, 2
						add		esi, edx
						sub		edi, 320h
						add		edi, ebp
						sub		ebp, 2
						jge		short loc_46593F
						mov		ebp, 10h
					loc_4659BD:
						cmp		edi, gpBufEnd
						jb		short loc_465A05
						mov		ecx, 20h
					loc_4659CA:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						mov		ch, [ebx+edx]
						mov		dl, ah
						ror		eax, 10h
						mov		[edi], ch
						mov		ch, [ebx+edx]
						mov		dl, al
						mov		[edi+1], ch
						mov		ch, [ebx+edx]
						mov		dl, ah
						mov		[edi+2], ch
						mov		ch, [ebx+edx]
						mov		[edi+3], ch
						add		edi, 4
						sub		cl, 4
						cmp		cl, 4
						jge		short loc_4659CA
						sub		edi, 320h
						dec		ebp
						jnz		short loc_4659BD
					loc_465A05:
						pop		ebp
					}
					break;
			}
			return;
		}
		src = (unsigned char *)pSpeedCels
				   + *(_DWORD *)&gpCelFrame[4 * (light_table_index + 16 * (level_cel_block & 0xFFF))];
		cel_type_16 = (unsigned short)level_cel_block >> 12;
		goto LABEL_22;
	}
	if ( level_cel_block & 0x8000 )
		level_cel_block = *(_DWORD *)&gpCelFrame[64 * (level_cel_block & 0xFFF)]
						+ (unsigned short)(level_cel_block & 0xF000);
	src = (unsigned char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
	cel_type_16 = ((unsigned int)level_cel_block >> 12) & 7;
	__asm {
		xor		edx, edx
		xor		ecx, ecx
		mov		edi, dst
		mov		esi, src
	}
	switch ( cel_type_16 )
	{
		case 0: // upper (solid), black
			__asm {
				mov		edx, 20h
				xor		eax, eax
			loc_465CCF:
				cmp		edi, gpBufEnd
				jb		ret_465F33_0B
				mov		ecx, 8
			loc_465CE0:
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_465CE0
				sub		edi, 320h
				dec		edx
				jnz		short loc_465CCF
			ret_465F33_0B:
			}
			break;
		case 1: // upper (solid), black
			__asm {
				push	ebp
				mov		ebp, 20h
			loc_465CFC:
				mov		edx, 20h
			loc_465D01:
				xor		eax, eax
				mov		al, [esi]
				inc		esi
				test	al, al
				js		short loc_465D41
				sub		edx, eax
				cmp		edi, gpBufEnd
				jb		short loc_465D52
				mov		ecx, eax
				add		esi, ecx
				xor		eax, eax
				shr		ecx, 1
				jnb		short loc_465D25
				mov		[edi], al
				inc		edi
				test	ecx, ecx
				jz		short loc_465D3B
			loc_465D25:
				shr		ecx, 1
				jnb		short loc_465D33
				mov		[edi], ax
				add		edi, 2
				test	ecx, ecx
				jz		short loc_465D3B
			loc_465D33:
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_465D33
			loc_465D3B:
				test	edx, edx
				jz		short loc_465D49
				jmp		short loc_465D01

			loc_465D41:
				neg		al
				add		edi, eax
				sub		edx, eax
				jnz		short loc_465D01
			loc_465D49:
				sub		edi, 320h
				dec		ebp
				jnz		short loc_465CFC
			loc_465D52:
				pop		ebp
			}
			break;
		case 2: // upper (solid), black
			__asm {
				mov		edx, 1Eh
				xor		eax, eax
			loc_465D5F:
				cmp		edi, gpBufEnd
				jb		ret_465F33_2B
				add		edi, edx
				mov		ecx, 20h
				sub		ecx, edx
				shr		ecx, 2
				jnb		short loc_465D83
				mov		[edi], ax
				add		edi, 2
				test	ecx, ecx
				jz		short loc_465D8B
			loc_465D83:
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_465D83
			loc_465D8B:
				sub		edi, 320h
				test	edx, edx
				jz		short loc_465D9A
				sub		edx, 2
				jmp		short loc_465D5F

			loc_465D9A:
				mov		edx, 2
			loc_465D9F:
				cmp		edi, gpBufEnd
				jb		ret_465F33_2B
				add		edi, edx
				mov		ecx, 20h
				sub		ecx, edx
				shr		ecx, 2
				jnb		short loc_465DC3
				mov		[edi], ax
				add		edi, 2
				test	ecx, ecx
				jz		short loc_465DCB
			loc_465DC3:
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_465DC3
			loc_465DCB:
				sub		edi, 320h
				add		edx, 2
				cmp		edx, 20h
				jnz		short loc_465D9F
			ret_465F33_2B:
			}
			break;
		case 3: // upper (solid), black
			__asm {
				mov		edx, 1Eh
				xor		eax, eax
			loc_465DE5:
				cmp		edi, gpBufEnd
				jb		ret_465F33_3B
				mov		ecx, 20h
				sub		ecx, edx
				shr		ecx, 2
				jnb		short loc_465E07
				mov		[edi], ax
				add		edi, 2
				test	ecx, ecx
				jz		short loc_465E0F
			loc_465E07:
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_465E07
			loc_465E0F:
				sub		edi, 320h
				test	edx, edx
				jz		short loc_465E20
				add		edi, edx
				sub		edx, 2
				jmp		short loc_465DE5

			loc_465E20:
				mov		edx, 2
			loc_465E25:
				cmp		edi, gpBufEnd
				jb		ret_465F33_3B
				mov		ecx, 20h
				sub		ecx, edx
				shr		ecx, 2
				jnb		short loc_465E47
				mov		[edi], ax
				add		edi, 2
				test	ecx, ecx
				jz		short loc_465E4F
			loc_465E47:
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_465E47
			loc_465E4F:
				sub		edi, 320h
				add		edi, edx
				add		edx, 2
				cmp		edx, 20h
				jnz		short loc_465E25
			ret_465F33_3B:
			}
			break;
		case 4: // upper (solid), black
			__asm {
				mov		edx, 1Eh
				xor		eax, eax
			loc_465E6B:
				cmp		edi, gpBufEnd
				jb		ret_465F33_4B
				add		edi, edx
				mov		ecx, 20h
				sub		ecx, edx
				shr		ecx, 2
				jnb		short loc_465E8F
				mov		[edi], ax
				add		edi, 2
				test	ecx, ecx
				jz		short loc_465E97
			loc_465E8F:
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_465E8F
			loc_465E97:
				sub		edi, 320h
				test	edx, edx
				jz		short loc_465EA6
				sub		edx, 2
				jmp		short loc_465E6B

			loc_465EA6:
				mov		edx, 10h
			loc_465EAB:
				cmp		edi, gpBufEnd
				jb		ret_465F33_4B
				mov		ecx, 8
			loc_465EBC:
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_465EBC
				sub		edi, 320h
				dec		edx
				jnz		short loc_465EAB
			ret_465F33_4B:
			}
			break;
		default: // upper (solid), black
			__asm {
				mov		edx, 1Eh
				xor		eax, eax
			loc_465ED6:
				cmp		edi, gpBufEnd
				jb		short ret_465F33_5B
				mov		ecx, 20h
				sub		ecx, edx
				shr		ecx, 2
				jnb		short loc_465EF4
				mov		[edi], ax
				add		edi, 2
				test	ecx, ecx
				jz		short loc_465EFC
			loc_465EF4:
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_465EF4
			loc_465EFC:
				sub		edi, 320h
				test	edx, edx
				jz		short loc_465F0D
				add		edi, edx
				sub		edx, 2
				jmp		short loc_465ED6

			loc_465F0D:
				mov		edx, 10h
			loc_465F12:
				cmp		edi, gpBufEnd
				jb		short ret_465F33_5B
				mov		ecx, 8
			loc_465F1F:
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_465F1F
				sub		edi, 320h
				dec		edx
				jnz		short loc_465F12
			ret_465F33_5B:
			}
			break;
	}
}

void __fastcall drawTopArchesLowerScreen(unsigned char *pbDst)
{
	unsigned char *dst; // edi MAPDST
	unsigned char *tbl; // ebx
	unsigned char *src; // esi MAPDST
	short cel_type_16; // ax MAPDST

	gpCelFrame = (unsigned char *)speed_cel_frame_num_from_light_index_frame_num;
	dst = pbDst;
	if ( !(_BYTE)light_table_index )
	{
		if ( level_cel_block & 0x8000 )
			level_cel_block = *(_DWORD *)&gpCelFrame[64 * (level_cel_block & 0xFFF)]
							+ (unsigned short)(level_cel_block & 0xF000);
		src = (unsigned char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
		cel_type_16 = ((level_cel_block >> 12) & 7) + 8;
		goto LABEL_11;
	}
	if ( (_BYTE)light_table_index == lightmax )
	{
		if ( level_cel_block & 0x8000 )
			level_cel_block = *(_DWORD *)&gpCelFrame[64 * (level_cel_block & 0xFFF)]
							+ (unsigned short)(level_cel_block & 0xF000);
		src = (unsigned char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
		cel_type_16 = (level_cel_block >> 12) & 7;
		__asm {
			xor		edx, edx
			xor		ecx, ecx
			mov		edi, dst
			mov		esi, src
		}
		switch ( cel_type_16 )
		{
			case 0: // lower (top transparent), black
				__asm {
					mov		edx, 10h
					xor		eax, eax
				loc_467484:
					cmp		edi, gpBufEnd
					jb		short loc_467494
					add		esi, 20h
					add		edi, 20h
					jmp		short loc_4674A5

				loc_467494:
					mov		ecx, 8
				loc_467499:
					mov		[edi+1], al
					mov		[edi+3], al
					add		edi, 4
					dec		ecx
					jnz		short loc_467499
				loc_4674A5:
					sub		edi, 320h
					cmp		edi, gpBufEnd
					jb		short loc_4674BB
					add		esi, 20h
					add		edi, 20h
					jmp		short loc_4674CB

				loc_4674BB:
					mov		ecx, 8
				loc_4674C0:
					mov		[edi], al
					mov		[edi+2], al
					add		edi, 4
					dec		ecx
					jnz		short loc_4674C0
				loc_4674CB:
					sub		edi, 320h
					dec		edx
					jnz		short loc_467484
				}
				break;
			case 1: // lower (top transparent), black
				__asm {
					mov		eax, edi
					and		eax, 1
					mov		WorldBoolFlag, eax
					mov		ecx, 20h
				loc_4674E8:
					push	ecx
					mov		edx, 20h
				loc_4674EE:
					xor		eax, eax
					mov		al, [esi]
					inc		esi
					test	al, al
					js		short loc_46756C
					sub		edx, eax
					cmp		edi, gpBufEnd
					jb		short loc_467507
					add		esi, eax
					add		edi, eax
					jmp		short loc_467566

				loc_467507:
					mov		ecx, eax
					add		esi, ecx
					mov		eax, edi
					and		eax, 1
					cmp		eax, WorldBoolFlag
					jnz		short loc_46753F
					xor		eax, eax
					shr		ecx, 1
					jnb		short loc_467525
					inc		edi
					test	ecx, ecx
					jz		short loc_467566
					jmp		short loc_46754E

				loc_467525:
					shr		ecx, 1
					jnb		short loc_467531
					inc		edi
					mov		[edi], al
					inc		edi
					test	ecx, ecx
					jz		short loc_467566
				loc_467531:
					mov		[edi+1], al
					mov		[edi+3], al
					add		edi, 4
					dec		ecx
					jnz		short loc_467531
					jmp		short loc_467566

				loc_46753F:
					xor		eax, eax
					shr		ecx, 1
					jnb		short loc_46754E
					mov		[edi], al
					inc		edi
					test	ecx, ecx
					jz		short loc_467566
					jmp		short loc_467525

				loc_46754E:
					shr		ecx, 1
					jnb		short loc_46755B
					mov		[edi], al
					add		edi, 2
					test	ecx, ecx
					jz		short loc_467566
				loc_46755B:
					mov		[edi], al
					mov		[edi+2], al
					add		edi, 4
					dec		ecx
					jnz		short loc_46755B
				loc_467566:
					test	edx, edx
					jz		short loc_467578
					jmp		short loc_4674EE

				loc_46756C:
					neg		al
					add		edi, eax
					sub		edx, eax
					jnz		loc_4674EE
				loc_467578:
					pop		ecx
					mov		eax, WorldBoolFlag
					inc		eax
					and		eax, 1
					mov		WorldBoolFlag, eax
					sub		edi, 320h
					dec		ecx
					jnz		loc_4674E8
				}
				break;
			case 2: // lower (top transparent), black
				__asm {
					xor		eax, eax
					mov		WorldBoolFlag, eax
					mov		edx, 1Eh
				loc_4675A5:
					cmp		edi, gpBufEnd
					jb		short loc_4675B7
					add		esi, 20h
					sub		esi, edx
					add		edi, 20h
					jmp		short loc_467608

				loc_4675B7:
					add		edi, edx
					mov		ecx, 20h
					sub		ecx, edx
					mov		eax, WorldBoolFlag
					inc		eax
					and		eax, 1
					mov		WorldBoolFlag, eax
					jz		short loc_4675ED
					xor		eax, eax
					shr		ecx, 2
					jnb		short loc_4675DF
					inc		edi
					mov		[edi], al
					inc		edi
					test	ecx, ecx
					jz		short loc_467608
				loc_4675DF:
					mov		[edi+1], al
					mov		[edi+3], al
					add		edi, 4
					dec		ecx
					jnz		short loc_4675DF
					jmp		short loc_467608

				loc_4675ED:
					xor		eax, eax
					shr		ecx, 2
					jnb		short loc_4675FD
					mov		[edi], al
					add		edi, 2
					test	ecx, ecx
					jz		short loc_467608
				loc_4675FD:
					mov		[edi], al
					mov		[edi+2], al
					add		edi, 4
					dec		ecx
					jnz		short loc_4675FD
				loc_467608:
					sub		edi, 320h
					test	edx, edx
					jz		short loc_467617
					sub		edx, 2
					jmp		short loc_4675A5

				loc_467617:
					mov		edx, 2
				loc_46761C:
					cmp		edi, gpBufEnd
					jb		short loc_46762E
					add		esi, 20h
					sub		esi, edx
					add		edi, 20h
					jmp		short loc_46767F

				loc_46762E:
					add		edi, edx
					mov		ecx, 20h
					sub		ecx, edx
					mov		eax, WorldBoolFlag
					inc		eax
					and		eax, 1
					mov		WorldBoolFlag, eax
					jz		short loc_467664
					xor		eax, eax
					shr		ecx, 2
					jnb		short loc_467656
					inc		edi
					mov		[edi], al
					inc		edi
					test	ecx, ecx
					jz		short loc_46767F
				loc_467656:
					mov		[edi+1], al
					mov		[edi+3], al
					add		edi, 4
					dec		ecx
					jnz		short loc_467656
					jmp		short loc_46767F

				loc_467664:
					xor		eax, eax
					shr		ecx, 2
					jnb		short loc_467674
					mov		[edi], al
					add		edi, 2
					test	ecx, ecx
					jz		short loc_46767F
				loc_467674:
					mov		[edi], al
					mov		[edi+2], al
					add		edi, 4
					dec		ecx
					jnz		short loc_467674
				loc_46767F:
					sub		edi, 320h
					add		edx, 2
					cmp		edx, 20h
					jnz		short loc_46761C
				}
				break;
			case 3: // lower (top transparent), black
				__asm {
					xor		eax, eax
					mov		WorldBoolFlag, eax
					mov		edx, 1Eh
				loc_46769E:
					cmp		edi, gpBufEnd
					jb		short loc_4676B2
					add		esi, 20h
					sub		esi, edx
					add		edi, 20h
					sub		edi, edx
					jmp		short loc_467701

				loc_4676B2:
					mov		ecx, 20h
					sub		ecx, edx
					mov		eax, WorldBoolFlag
					inc		eax
					and		eax, 1
					mov		WorldBoolFlag, eax
					jz		short loc_4676E6
					xor		eax, eax
					shr		ecx, 2
					jnb		short loc_4676D8
					inc		edi
					mov		[edi], al
					inc		edi
					test	ecx, ecx
					jz		short loc_467701
				loc_4676D8:
					mov		[edi+1], al
					mov		[edi+3], al
					add		edi, 4
					dec		ecx
					jnz		short loc_4676D8
					jmp		short loc_467701

				loc_4676E6:
					xor		eax, eax
					shr		ecx, 2
					jnb		short loc_4676F6
					mov		[edi], al
					add		edi, 2
					test	ecx, ecx
					jz		short loc_467701
				loc_4676F6:
					mov		[edi], al
					mov		[edi+2], al
					add		edi, 4
					dec		ecx
					jnz		short loc_4676F6
				loc_467701:
					sub		edi, 320h
					test	edx, edx
					jz		short loc_467712
					add		edi, edx
					sub		edx, 2
					jmp		short loc_46769E

				loc_467712:
					mov		edx, 2
				loc_467717:
					cmp		edi, gpBufEnd
					jb		short loc_46772B
					add		esi, 20h
					sub		esi, edx
					add		edi, 20h
					sub		edi, edx
					jmp		short loc_46777A

				loc_46772B:
					mov		ecx, 20h
					sub		ecx, edx
					mov		eax, WorldBoolFlag
					inc		eax
					and		eax, 1
					mov		WorldBoolFlag, eax
					jz		short loc_46775F
					xor		eax, eax
					shr		ecx, 2
					jnb		short loc_467751
					inc		edi
					mov		[edi], al
					inc		edi
					test	ecx, ecx
					jz		short loc_46777A
				loc_467751:
					mov		[edi+1], al
					mov		[edi+3], al
					add		edi, 4
					dec		ecx
					jnz		short loc_467751
					jmp		short loc_46777A

				loc_46775F:
					xor		eax, eax
					shr		ecx, 2
					jnb		short loc_46776F
					mov		[edi], al
					add		edi, 2
					test	ecx, ecx
					jz		short loc_46777A
				loc_46776F:
					mov		[edi], al
					mov		[edi+2], al
					add		edi, 4
					dec		ecx
					jnz		short loc_46776F
				loc_46777A:
					sub		edi, 320h
					add		edi, edx
					add		edx, 2
					cmp		edx, 20h
					jnz		short loc_467717
				}
				break;
			case 4: // lower (top transparent), black
				__asm {
					xor		eax, eax
					mov		WorldBoolFlag, eax
					mov		edx, 1Eh
				loc_46779B:
					cmp		edi, gpBufEnd
					jb		short loc_4677AD
					add		esi, 20h
					sub		esi, edx
					add		edi, 20h
					jmp		short loc_4677FE

				loc_4677AD:
					add		edi, edx
					mov		ecx, 20h
					sub		ecx, edx
					mov		eax, WorldBoolFlag
					inc		eax
					and		eax, 1
					mov		WorldBoolFlag, eax
					jz		short loc_4677E3
					xor		eax, eax
					shr		ecx, 2
					jnb		short loc_4677D5
					inc		edi
					mov		[edi], al
					inc		edi
					test	ecx, ecx
					jz		short loc_4677FE
				loc_4677D5:
					mov		[edi+1], al
					mov		[edi+3], al
					add		edi, 4
					dec		ecx
					jnz		short loc_4677D5
					jmp		short loc_4677FE

				loc_4677E3:
					xor		eax, eax
					shr		ecx, 2
					jnb		short loc_4677F3
					mov		[edi], al
					add		edi, 2
					test	ecx, ecx
					jz		short loc_4677FE
				loc_4677F3:
					mov		[edi], al
					mov		[edi+2], al
					add		edi, 4
					dec		ecx
					jnz		short loc_4677F3
				loc_4677FE:
					sub		edi, 320h
					test	edx, edx
					jz		short loc_46780D
					sub		edx, 2
					jmp		short loc_46779B

				loc_46780D:
					mov		edx, 8
				loc_467812:
					cmp		edi, gpBufEnd
					jb		short loc_467822
					add		esi, 20h
					add		edi, 20h
					jmp		short loc_467835

				loc_467822:
					mov		ecx, 8
					xor		eax, eax
				loc_467829:
					mov		[edi+1], al
					mov		[edi+3], al
					add		edi, 4
					dec		ecx
					jnz		short loc_467829
				loc_467835:
					sub		edi, 320h
					cmp		edi, gpBufEnd
					jb		short loc_46784B
					add		esi, 20h
					add		edi, 20h
					jmp		short loc_46785D

				loc_46784B:
					mov		ecx, 8
					xor		eax, eax
				loc_467852:
					mov		[edi], al
					mov		[edi+2], al
					add		edi, 4
					dec		ecx
					jnz		short loc_467852
				loc_46785D:
					sub		edi, 320h
					dec		edx
					jnz		short loc_467812
				}
				break;
			default: // lower (top transparent), black
				__asm {
					xor		eax, eax
					mov		WorldBoolFlag, eax
					mov		edx, 1Eh
				loc_467877:
					cmp		edi, gpBufEnd
					jb		short loc_46788B
					add		esi, 20h
					sub		esi, edx
					add		edi, 20h
					sub		edi, edx
					jmp		short loc_4678DA

				loc_46788B:
					mov		ecx, 20h
					sub		ecx, edx
					mov		eax, WorldBoolFlag
					inc		eax
					and		eax, 1
					mov		WorldBoolFlag, eax
					jz		short loc_4678BF
					xor		eax, eax
					shr		ecx, 2
					jnb		short loc_4678B1
					inc		edi
					mov		[edi], al
					inc		edi
					test	ecx, ecx
					jz		short loc_4678DA
				loc_4678B1:
					mov		[edi+1], al
					mov		[edi+3], al
					add		edi, 4
					dec		ecx
					jnz		short loc_4678B1
					jmp		short loc_4678DA

				loc_4678BF:
					xor		eax, eax
					shr		ecx, 2
					jnb		short loc_4678CF
					mov		[edi], al
					add		edi, 2
					test	ecx, ecx
					jz		short loc_4678DA
				loc_4678CF:
					mov		[edi], al
					mov		[edi+2], al
					add		edi, 4
					dec		ecx
					jnz		short loc_4678CF
				loc_4678DA:
					sub		edi, 320h
					test	edx, edx
					jz		short loc_4678EB
					add		edi, edx
					sub		edx, 2
					jmp		short loc_467877

				loc_4678EB:
					mov		edx, 8
				loc_4678F0:
					cmp		edi, gpBufEnd
					jb		short loc_467900
					add		esi, 20h
					add		edi, 20h
					jmp		short loc_467913

				loc_467900:
					mov		ecx, 8
					xor		eax, eax
				loc_467907:
					mov		[edi+1], al
					mov		[edi+3], al
					add		edi, 4
					dec		ecx
					jnz		short loc_467907
				loc_467913:
					sub		edi, 320h
					cmp		edi, gpBufEnd
					jb		short loc_467929
					add		esi, 20h
					add		edi, 20h
					jmp		short loc_46793B

				loc_467929:
					mov		ecx, 8
					xor		eax, eax
				loc_467930:
					mov		[edi], al
					mov		[edi+2], al
					add		edi, 4
					dec		ecx
					jnz		short loc_467930
				loc_46793B:
					sub		edi, 320h
					dec		edx
					jnz		short loc_4678F0
				}
				break;
		}
		return;
	}
	if ( !(level_cel_block & 0x8000) )
	{
		src = (unsigned char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
		tbl = (unsigned char *)&pLightTbl[256 * light_table_index];
		cel_type_16 = (unsigned char)(level_cel_block >> 12);
		__asm {
			xor		edx, edx
			xor		ecx, ecx
			mov		ebx, tbl
			mov		edi, dst
			mov		esi, src
		}
		switch ( cel_type_16 )
		{
			case 0: // lower (top transparent), with lighting
				__asm {
					push	ebp
					mov		ebp, 10h
				loc_466133:
					cmp		edi, gpBufEnd
					jb		short loc_466143
					add		esi, 20h
					add		edi, 20h
					jmp		short loc_466166

				loc_466143:
					mov		ecx, 8
				loc_466148:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, ah
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi+1], dl
					mov		dl, ah
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-1], dl
					jnz		short loc_466148
				loc_466166:
					sub		edi, 320h
					cmp		edi, gpBufEnd
					jb		short loc_46617C
					add		esi, 20h
					add		edi, 20h
					jmp		short loc_46619E

				loc_46617C:
					mov		ecx, 8
				loc_466181:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, al
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi], dl
					mov		dl, al
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-2], dl
					jnz		short loc_466181
				loc_46619E:
					sub		edi, 320h
					dec		ebp
					jnz		short loc_466133
					pop		ebp
				}
				break;
			case 1: // lower (top transparent), with lighting
				__asm {
					push	ebp
					mov		eax, edi
					and		eax, 1
					mov		WorldBoolFlag, eax
					mov		ecx, 20h
				loc_4661BD:
					push	ecx
					mov		ebp, 20h
				loc_4661C3:
					xor		eax, eax
					mov		al, [esi]
					inc		esi
					test	al, al
					js		loc_4662E2
					sub		ebp, eax
					cmp		edi, gpBufEnd
					jb		short loc_4661E3
					add		esi, eax
					add		edi, eax
					jmp		loc_4662D9

				loc_4661E3:
					mov		ecx, eax
					mov		eax, edi
					and		eax, 1
					cmp		eax, WorldBoolFlag
					jnz		short loc_466263
					shr		ecx, 1
					jb		short loc_46622D
					shr		ecx, 1
					jnb		short loc_466209
					mov		dl, [esi+1]
					mov		dl, [ebx+edx]
					add		esi, 2
					mov		[edi+1], dl
					add		edi, 2
				loc_466209:
					test	cl, cl
					jz		short loc_46622B
				loc_46620D:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, ah
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi+1], dl
					mov		dl, ah
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-1], dl
					jnz		short loc_46620D
				loc_46622B:
					jmp		short loc_466261

				loc_46622D:
					inc		esi
					inc		edi
					shr		ecx, 1
					jnb		short loc_466240
					mov		dl, [esi]
					mov		dl, [ebx+edx]
					add		esi, 2
					mov		[edi], dl
					add		edi, 2
				loc_466240:
					test	cl, cl
					jz		short loc_466261
				loc_466244:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, al
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi], dl
					mov		dl, al
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-2], dl
					jnz		short loc_466244
				loc_466261:
					jmp		short loc_4662D9

				loc_466263:
					shr		ecx, 1
					jb		short loc_46629B
					shr		ecx, 1
					jnb		short loc_466278
					mov		dl, [esi]
					mov		dl, [ebx+edx]
					add		esi, 2
					mov		[edi], dl
					add		edi, 2
				loc_466278:
					test	cl, cl
					jz		short loc_466299
				loc_46627C:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, al
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi], dl
					mov		dl, al
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-2], dl
					jnz		short loc_46627C
				loc_466299:
					jmp		short loc_4662D9

				loc_46629B:
					mov		dl, [esi]
					mov		dl, [ebx+edx]
					inc		esi
					mov		[edi], dl
					inc		edi
					shr		ecx, 1
					jnb		short loc_4662B7
					mov		dl, [esi+1]
					mov		dl, [ebx+edx]
					add		esi, 2
					mov		[edi+1], dl
					add		edi, 2
				loc_4662B7:
					test	cl, cl
					jz		short loc_4662D9
				loc_4662BB:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, ah
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi+1], dl
					mov		dl, ah
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-1], dl
					jnz		short loc_4662BB
				loc_4662D9:
					test	ebp, ebp
					jz		short loc_4662EE
					jmp		loc_4661C3

				loc_4662E2:
					neg		al
					add		edi, eax
					sub		ebp, eax
					jnz		loc_4661C3
				loc_4662EE:
					pop		ecx
					mov		eax, WorldBoolFlag
					inc		eax
					and		eax, 1
					mov		WorldBoolFlag, eax
					sub		edi, 320h
					dec		ecx
					jnz		loc_4661BD
					pop		ebp
				}
				break;
			case 2: // lower (top transparent), with lighting
				__asm {
					push	ebp
					xor		eax, eax
					mov		WorldBoolFlag, eax
					mov		ebp, 1Eh
					mov		eax, edi
					sub		eax, gpBufEnd
					jb		short loc_466370
					add		eax, 3FFh
					shr		eax, 8
					cmp		eax, 2Dh
					jg		short loc_46635F
					mov		ecx, WorldTbl3x16[eax*4]
					mov		eax, ecx
					add		esi, WorldTbl17_1[ecx]
					shl		eax, 6
					lea		eax, [eax+eax*2]
					shr		ecx, 1
					sub		edi, eax
					sub		ebp, ecx
					mov		eax, WorldBoolFlag
					shr		ecx, 1
					add		eax, ecx
					mov		WorldBoolFlag, eax
					jmp		short loc_466370

				loc_46635F:
					sub		edi, 3000h
					add		esi, 120h
					jmp		loc_466490

				loc_466370:
					add		edi, ebp
					mov		ecx, 20h
					sub		ecx, ebp
					mov		eax, WorldBoolFlag
					inc		eax
					and		eax, 1
					mov		WorldBoolFlag, eax
					jz		short loc_466404
					mov		edx, ecx
					and		edx, 2
					add		esi, edx
					shr		ecx, 1
					jb		short loc_4663CB
					shr		ecx, 1
					jnb		short loc_4663A7
					mov		dl, [esi+1]
					mov		dl, [ebx+edx]
					add		esi, 2
					mov		[edi+1], dl
					add		edi, 2
				loc_4663A7:
					test	cl, cl
					jz		short loc_4663C9
				loc_4663AB:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, ah
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi+1], dl
					mov		dl, ah
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-1], dl
					jnz		short loc_4663AB
				loc_4663C9:
					jmp		short loc_4663FF

				loc_4663CB:
					inc		esi
					inc		edi
					shr		ecx, 1
					jnb		short loc_4663DE
					mov		dl, [esi]
					mov		dl, [ebx+edx]
					add		esi, 2
					mov		[edi], dl
					add		edi, 2
				loc_4663DE:
					test	cl, cl
					jz		short loc_4663FF
				loc_4663E2:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, al
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi], dl
					mov		dl, al
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-2], dl
					jnz		short loc_4663E2
				loc_4663FF:
					jmp		loc_466481

				loc_466404:
					mov		edx, ecx
					and		edx, 2
					add		esi, edx
					shr		ecx, 1
					jb		short loc_466443
					shr		ecx, 1
					jnb		short loc_466420
					mov		dl, [esi]
					mov		dl, [ebx+edx]
					add		esi, 2
					mov		[edi], dl
					add		edi, 2
				loc_466420:
					test	cl, cl
					jz		short loc_466441
				loc_466424:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, al
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi], dl
					mov		dl, al
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-2], dl
					jnz		short loc_466424
				loc_466441:
					jmp		short loc_466481

				loc_466443:
					mov		dl, [esi]
					mov		dl, [ebx+edx]
					inc		esi
					mov		[edi], dl
					inc		edi
					shr		ecx, 1
					jnb		short loc_46645F
					mov		dl, [esi+1]
					mov		dl, [ebx+edx]
					add		esi, 2
					mov		[edi+1], dl
					add		edi, 2
				loc_46645F:
					test	cl, cl
					jz		short loc_466481
				loc_466463:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, ah
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi+1], dl
					mov		dl, ah
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-1], dl
					jnz		short loc_466463
				loc_466481:
					sub		edi, 320h
					sub		ebp, 2
					jge		loc_466370
				loc_466490:
					mov		ebp, 2
					mov		eax, edi
					sub		eax, gpBufEnd
					jb		short loc_4664E8
					add		eax, 3FFh
					shr		eax, 8
					cmp		eax, 2Ah
					jg		short loc_4664D7
					mov		ecx, WorldTbl3x16[eax*4]
					mov		eax, ecx
					add		esi, WorldTbl17_2[ecx]
					shl		eax, 6
					lea		eax, [eax+eax*2]
					shr		ecx, 1
					sub		edi, eax
					add		ebp, ecx
					mov		eax, WorldBoolFlag
					shr		ecx, 1
					add		eax, ecx
					mov		WorldBoolFlag, eax
					jmp		short loc_4664E8

				loc_4664D7:
					sub		edi, 2D00h
					add		esi, 100h
					jmp		loc_46660B

				loc_4664E8:
					add		edi, ebp
					mov		ecx, 20h
					sub		ecx, ebp
					mov		eax, WorldBoolFlag
					inc		eax
					and		eax, 1
					mov		WorldBoolFlag, eax
					jz		short loc_46657C
					mov		edx, ecx
					and		edx, 2
					add		esi, edx
					shr		ecx, 1
					jb		short loc_466543
					shr		ecx, 1
					jnb		short loc_46651F
					mov		dl, [esi+1]
					mov		dl, [ebx+edx]
					add		esi, 2
					mov		[edi+1], dl
					add		edi, 2
				loc_46651F:
					test	cl, cl
					jz		short loc_466541
				loc_466523:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, ah
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi+1], dl
					mov		dl, ah
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-1], dl
					jnz		short loc_466523
				loc_466541:
					jmp		short loc_466577

				loc_466543:
					inc		esi
					inc		edi
					shr		ecx, 1
					jnb		short loc_466556
					mov		dl, [esi]
					mov		dl, [ebx+edx]
					add		esi, 2
					mov		[edi], dl
					add		edi, 2
				loc_466556:
					test	cl, cl
					jz		short loc_466577
				loc_46655A:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, al
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi], dl
					mov		dl, al
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-2], dl
					jnz		short loc_46655A
				loc_466577:
					jmp		loc_4665F9

				loc_46657C:
					mov		edx, ecx
					and		edx, 2
					add		esi, edx
					shr		ecx, 1
					jb		short loc_4665BB
					shr		ecx, 1
					jnb		short loc_466598
					mov		dl, [esi]
					mov		dl, [ebx+edx]
					add		esi, 2
					mov		[edi], dl
					add		edi, 2
				loc_466598:
					test	cl, cl
					jz		short loc_4665B9
				loc_46659C:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, al
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi], dl
					mov		dl, al
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-2], dl
					jnz		short loc_46659C
				loc_4665B9:
					jmp		short loc_4665F9

				loc_4665BB:
					mov		dl, [esi]
					mov		dl, [ebx+edx]
					inc		esi
					mov		[edi], dl
					inc		edi
					shr		ecx, 1
					jnb		short loc_4665D7
					mov		dl, [esi+1]
					mov		dl, [ebx+edx]
					add		esi, 2
					mov		[edi+1], dl
					add		edi, 2
				loc_4665D7:
					test	cl, cl
					jz		short loc_4665F9
				loc_4665DB:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, ah
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi+1], dl
					mov		dl, ah
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-1], dl
					jnz		short loc_4665DB
				loc_4665F9:
					sub		edi, 320h
					add		ebp, 2
					cmp		ebp, 20h
					jnz		loc_4664E8
				loc_46660B:
					pop		ebp
				}
				break;
			case 3: // lower (top transparent), with lighting
				__asm {
					push	ebp
					xor		eax, eax
					mov		WorldBoolFlag, eax
					mov		ebp, 1Eh
					mov		eax, edi
					sub		eax, gpBufEnd
					jb		short loc_466671
					add		eax, 3FFh
					shr		eax, 8
					cmp		eax, 2Dh
					jg		short loc_466660
					mov		ecx, WorldTbl3x16[eax*4]
					mov		eax, ecx
					add		esi, WorldTbl17_1[ecx]
					shl		eax, 6
					lea		eax, [eax+eax*2]
					shr		ecx, 1
					sub		edi, eax
					sub		ebp, ecx
					mov		eax, WorldBoolFlag
					shr		ecx, 1
					add		eax, ecx
					mov		WorldBoolFlag, eax
					jmp		short loc_466671

				loc_466660:
					sub		edi, 3000h
					add		esi, 120h
					jmp		loc_466791

				loc_466671:
					mov		ecx, 20h
					sub		ecx, ebp
					mov		eax, WorldBoolFlag
					inc		eax
					and		eax, 1
					mov		WorldBoolFlag, eax
					jz		short loc_466703
					shr		ecx, 1
					jb		short loc_4666C3
					shr		ecx, 1
					jnb		short loc_46669F
					mov		dl, [esi+1]
					mov		dl, [ebx+edx]
					add		esi, 2
					mov		[edi+1], dl
					add		edi, 2
				loc_46669F:
					test	cl, cl
					jz		short loc_4666C1
				loc_4666A3:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, ah
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi+1], dl
					mov		dl, ah
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-1], dl
					jnz		short loc_4666A3
				loc_4666C1:
					jmp		short loc_4666F7

				loc_4666C3:
					inc		esi
					inc		edi
					shr		ecx, 1
					jnb		short loc_4666D6
					mov		dl, [esi]
					mov		dl, [ebx+edx]
					add		esi, 2
					mov		[edi], dl
					add		edi, 2
				loc_4666D6:
					test	cl, cl
					jz		short loc_4666F7
				loc_4666DA:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, al
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi], dl
					mov		dl, al
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-2], dl
					jnz		short loc_4666DA
				loc_4666F7:
					mov		edx, esi
					and		edx, 2
					add		esi, edx
					jmp		loc_466780

				loc_466703:
					shr		ecx, 1
					jb		short loc_46673B
					shr		ecx, 1
					jnb		short loc_466718
					mov		dl, [esi]
					mov		dl, [ebx+edx]
					add		esi, 2
					mov		[edi], dl
					add		edi, 2
				loc_466718:
					test	cl, cl
					jz		short loc_466739
				loc_46671C:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, al
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi], dl
					mov		dl, al
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-2], dl
					jnz		short loc_46671C
				loc_466739:
					jmp		short loc_466779

				loc_46673B:
					mov		dl, [esi]
					mov		dl, [ebx+edx]
					inc		esi
					mov		[edi], dl
					inc		edi
					shr		ecx, 1
					jnb		short loc_466757
					mov		dl, [esi+1]
					mov		dl, [ebx+edx]
					add		esi, 2
					mov		[edi+1], dl
					add		edi, 2
				loc_466757:
					test	cl, cl
					jz		short loc_466779
				loc_46675B:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, ah
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi+1], dl
					mov		dl, ah
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-1], dl
					jnz		short loc_46675B
				loc_466779:
					mov		edx, esi
					and		edx, 2
					add		esi, edx
				loc_466780:
					sub		edi, 320h
					add		edi, ebp
					sub		ebp, 2
					jge		loc_466671
				loc_466791:
					mov		ebp, 2
					mov		eax, edi
					sub		eax, gpBufEnd
					jb		short loc_4667E9
					add		eax, 3FFh
					shr		eax, 8
					cmp		eax, 2Ah
					jg		short loc_4667D8
					mov		ecx, WorldTbl3x16[eax*4]
					mov		eax, ecx
					add		esi, WorldTbl17_2[ecx]
					shl		eax, 6
					lea		eax, [eax+eax*2]
					shr		ecx, 1
					sub		edi, eax
					add		ebp, ecx
					mov		eax, WorldBoolFlag
					shr		ecx, 1
					add		eax, ecx
					mov		WorldBoolFlag, eax
					jmp		short loc_4667E9

				loc_4667D8:
					sub		edi, 2D00h
					add		esi, 100h
					jmp		loc_46690C

				loc_4667E9:
					mov		ecx, 20h
					sub		ecx, ebp
					mov		eax, WorldBoolFlag
					inc		eax
					and		eax, 1
					mov		WorldBoolFlag, eax
					jz		short loc_46687B
					shr		ecx, 1
					jb		short loc_46683B
					shr		ecx, 1
					jnb		short loc_466817
					mov		dl, [esi+1]
					mov		dl, [ebx+edx]
					add		esi, 2
					mov		[edi+1], dl
					add		edi, 2
				loc_466817:
					test	cl, cl
					jz		short loc_466839
				loc_46681B:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, ah
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi+1], dl
					mov		dl, ah
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-1], dl
					jnz		short loc_46681B
				loc_466839:
					jmp		short loc_46686F

				loc_46683B:
					inc		esi
					inc		edi
					shr		ecx, 1
					jnb		short loc_46684E
					mov		dl, [esi]
					mov		dl, [ebx+edx]
					add		esi, 2
					mov		[edi], dl
					add		edi, 2
				loc_46684E:
					test	cl, cl
					jz		short loc_46686F
				loc_466852:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, al
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi], dl
					mov		dl, al
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-2], dl
					jnz		short loc_466852
				loc_46686F:
					mov		edx, esi
					and		edx, 2
					add		esi, edx
					jmp		loc_4668F8

				loc_46687B:
					shr		ecx, 1
					jb		short loc_4668B3
					shr		ecx, 1
					jnb		short loc_466890
					mov		dl, [esi]
					mov		dl, [ebx+edx]
					add		esi, 2
					mov		[edi], dl
					add		edi, 2
				loc_466890:
					test	cl, cl
					jz		short loc_4668B1
				loc_466894:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, al
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi], dl
					mov		dl, al
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-2], dl
					jnz		short loc_466894
				loc_4668B1:
					jmp		short loc_4668F1

				loc_4668B3:
					mov		dl, [esi]
					mov		dl, [ebx+edx]
					inc		esi
					mov		[edi], dl
					inc		edi
					shr		ecx, 1
					jnb		short loc_4668CF
					mov		dl, [esi+1]
					mov		dl, [ebx+edx]
					add		esi, 2
					mov		[edi+1], dl
					add		edi, 2
				loc_4668CF:
					test	cl, cl
					jz		short loc_4668F1
				loc_4668D3:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, ah
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi+1], dl
					mov		dl, ah
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-1], dl
					jnz		short loc_4668D3
				loc_4668F1:
					mov		edx, esi
					and		edx, 2
					add		esi, edx
				loc_4668F8:
					sub		edi, 320h
					add		edi, ebp
					add		ebp, 2
					cmp		ebp, 20h
					jnz		loc_4667E9
				loc_46690C:
					pop		ebp
				}
				break;
			case 4: // lower (top transparent), with lighting
				__asm {
					push	ebp
					xor		eax, eax
					mov		WorldBoolFlag, eax
					mov		ebp, 1Eh
					mov		eax, edi
					sub		eax, gpBufEnd
					jb		short loc_466972
					add		eax, 3FFh
					shr		eax, 8
					cmp		eax, 2Dh
					jg		short loc_466961
					mov		ecx, WorldTbl3x16[eax*4]
					mov		eax, ecx
					add		esi, WorldTbl17_1[ecx]
					shl		eax, 6
					lea		eax, [eax+eax*2]
					shr		ecx, 1
					sub		edi, eax
					sub		ebp, ecx
					mov		eax, WorldBoolFlag
					shr		ecx, 1
					add		eax, ecx
					mov		WorldBoolFlag, eax
					jmp		short loc_466972

				loc_466961:
					sub		edi, 3000h
					add		esi, 120h
					jmp		loc_466A92

				loc_466972:
					add		edi, ebp
					mov		ecx, 20h
					sub		ecx, ebp
					mov		eax, WorldBoolFlag
					inc		eax
					and		eax, 1
					mov		WorldBoolFlag, eax
					jz		short loc_466A06
					mov		edx, ecx
					and		edx, 2
					add		esi, edx
					shr		ecx, 1
					jb		short loc_4669CD
					shr		ecx, 1
					jnb		short loc_4669A9
					mov		dl, [esi+1]
					mov		dl, [ebx+edx]
					add		esi, 2
					mov		[edi+1], dl
					add		edi, 2
				loc_4669A9:
					test	cl, cl
					jz		short loc_4669CB
				loc_4669AD:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, ah
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi+1], dl
					mov		dl, ah
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-1], dl
					jnz		short loc_4669AD
				loc_4669CB:
					jmp		short loc_466A01

				loc_4669CD:
					inc		esi
					inc		edi
					shr		ecx, 1
					jnb		short loc_4669E0
					mov		dl, [esi]
					mov		dl, [ebx+edx]
					add		esi, 2
					mov		[edi], dl
					add		edi, 2
				loc_4669E0:
					test	cl, cl
					jz		short loc_466A01
				loc_4669E4:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, al
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi], dl
					mov		dl, al
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-2], dl
					jnz		short loc_4669E4
				loc_466A01:
					jmp		loc_466A83

				loc_466A06:
					mov		edx, ecx
					and		edx, 2
					add		esi, edx
					shr		ecx, 1
					jb		short loc_466A45
					shr		ecx, 1
					jnb		short loc_466A22
					mov		dl, [esi]
					mov		dl, [ebx+edx]
					add		esi, 2
					mov		[edi], dl
					add		edi, 2
				loc_466A22:
					test	cl, cl
					jz		short loc_466A43
				loc_466A26:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, al
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi], dl
					mov		dl, al
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-2], dl
					jnz		short loc_466A26
				loc_466A43:
					jmp		short loc_466A83

				loc_466A45:
					mov		dl, [esi]
					mov		dl, [ebx+edx]
					inc		esi
					mov		[edi], dl
					inc		edi
					shr		ecx, 1
					jnb		short loc_466A61
					mov		dl, [esi+1]
					mov		dl, [ebx+edx]
					add		esi, 2
					mov		[edi+1], dl
					add		edi, 2
				loc_466A61:
					test	cl, cl
					jz		short loc_466A83
				loc_466A65:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, ah
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi+1], dl
					mov		dl, ah
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-1], dl
					jnz		short loc_466A65
				loc_466A83:
					sub		edi, 320h
					sub		ebp, 2
					jge		loc_466972
				loc_466A92:
					mov		ebp, 8
				loc_466A97:
					cmp		edi, gpBufEnd
					jb		short loc_466AA7
					add		esi, 20h
					add		edi, 20h
					jmp		short loc_466ACA

				loc_466AA7:
					mov		ecx, 8
				loc_466AAC:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, ah
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi+1], dl
					mov		dl, ah
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-1], dl
					jnz		short loc_466AAC
				loc_466ACA:
					sub		edi, 320h
					cmp		edi, gpBufEnd
					jb		short loc_466AE0
					add		esi, 20h
					add		edi, 20h
					jmp		short loc_466B02

				loc_466AE0:
					mov		ecx, 8
				loc_466AE5:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, al
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi], dl
					mov		dl, al
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-2], dl
					jnz		short loc_466AE5
				loc_466B02:
					sub		edi, 320h
					dec		ebp
					jnz		short loc_466A97
					pop		ebp
				}
				break;
			default: // lower (top transparent), with lighting
				__asm {
					push	ebp
					xor		eax, eax
					mov		WorldBoolFlag, eax
					mov		ebp, 1Eh
					mov		eax, edi
					sub		eax, gpBufEnd
					jb		short loc_466B71
					add		eax, 3FFh
					shr		eax, 8
					cmp		eax, 2Dh
					jg		short loc_466B60
					mov		ecx, WorldTbl3x16[eax*4]
					mov		eax, ecx
					add		esi, WorldTbl17_1[ecx]
					shl		eax, 6
					lea		eax, [eax+eax*2]
					shr		ecx, 1
					sub		edi, eax
					sub		ebp, ecx
					mov		eax, WorldBoolFlag
					shr		ecx, 1
					add		eax, ecx
					mov		WorldBoolFlag, eax
					jmp		short loc_466B71

				loc_466B60:
					sub		edi, 3000h
					add		esi, 120h
					jmp		loc_466C91

				loc_466B71:
					mov		ecx, 20h
					sub		ecx, ebp
					mov		eax, WorldBoolFlag
					inc		eax
					and		eax, 1
					mov		WorldBoolFlag, eax
					jz		short loc_466C03
					shr		ecx, 1
					jb		short loc_466BC3
					shr		ecx, 1
					jnb		short loc_466B9F
					mov		dl, [esi+1]
					mov		dl, [ebx+edx]
					add		esi, 2
					mov		[edi+1], dl
					add		edi, 2
				loc_466B9F:
					test	cl, cl
					jz		short loc_466BC1
				loc_466BA3:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, ah
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi+1], dl
					mov		dl, ah
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-1], dl
					jnz		short loc_466BA3
				loc_466BC1:
					jmp		short loc_466BF7

				loc_466BC3:
					inc		esi
					inc		edi
					shr		ecx, 1
					jnb		short loc_466BD6
					mov		dl, [esi]
					mov		dl, [ebx+edx]
					add		esi, 2
					mov		[edi], dl
					add		edi, 2
				loc_466BD6:
					test	cl, cl
					jz		short loc_466BF7
				loc_466BDA:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, al
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi], dl
					mov		dl, al
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-2], dl
					jnz		short loc_466BDA
				loc_466BF7:
					mov		edx, esi
					and		edx, 2
					add		esi, edx
					jmp		loc_466C80

				loc_466C03:
					shr		ecx, 1
					jb		short loc_466C3B
					shr		ecx, 1
					jnb		short loc_466C18
					mov		dl, [esi]
					mov		dl, [ebx+edx]
					add		esi, 2
					mov		[edi], dl
					add		edi, 2
				loc_466C18:
					test	cl, cl
					jz		short loc_466C39
				loc_466C1C:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, al
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi], dl
					mov		dl, al
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-2], dl
					jnz		short loc_466C1C
				loc_466C39:
					jmp		short loc_466C79

				loc_466C3B:
					mov		dl, [esi]
					mov		dl, [ebx+edx]
					inc		esi
					mov		[edi], dl
					inc		edi
					shr		ecx, 1
					jnb		short loc_466C57
					mov		dl, [esi+1]
					mov		dl, [ebx+edx]
					add		esi, 2
					mov		[edi+1], dl
					add		edi, 2
				loc_466C57:
					test	cl, cl
					jz		short loc_466C79
				loc_466C5B:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, ah
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi+1], dl
					mov		dl, ah
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-1], dl
					jnz		short loc_466C5B
				loc_466C79:
					mov		edx, esi
					and		edx, 2
					add		esi, edx
				loc_466C80:
					sub		edi, 320h
					add		edi, ebp
					sub		ebp, 2
					jge		loc_466B71
				loc_466C91:
					mov		ebp, 8
				loc_466C96:
					cmp		edi, gpBufEnd
					jb		short loc_466CA6
					add		esi, 20h
					add		edi, 20h
					jmp		short loc_466CC9

				loc_466CA6:
					mov		ecx, 8
				loc_466CAB:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, ah
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi+1], dl
					mov		dl, ah
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-1], dl
					jnz		short loc_466CAB
				loc_466CC9:
					sub		edi, 320h
					cmp		edi, gpBufEnd
					jb		short loc_466CDF
					add		esi, 20h
					add		edi, 20h
					jmp		short loc_466D01

				loc_466CDF:
					mov		ecx, 8
				loc_466CE4:
					mov		eax, [esi]
					add		esi, 4
					mov		dl, al
					shr		eax, 10h
					mov		dl, [ebx+edx]
					mov		[edi], dl
					mov		dl, al
					add		edi, 4
					mov		dl, [ebx+edx]
					dec		ecx
					mov		[edi-2], dl
					jnz		short loc_466CE4
				loc_466D01:
					sub		edi, 320h
					dec		ebp
					jnz		short loc_466C96
					pop		ebp
				}
				break;
		}
		return;
	}
	src = (unsigned char *)pSpeedCels + *(_DWORD *)&gpCelFrame[4 * (light_table_index + 16 * (level_cel_block & 0xFFF))];
	cel_type_16 = (unsigned char)(level_cel_block >> 12);
LABEL_11:
	__asm {
		xor		edx, edx
		xor		ecx, ecx
		mov		edi, dst
		mov		esi, src
	}
	switch ( cel_type_16 )
	{
		case 8: // lower (top transparent), without lighting
			__asm {
				mov		edx, 10h
			loc_466D15:
				cmp		edi, gpBufEnd
				jb		short loc_466D25
				add		esi, 20h
				add		edi, 20h
				jmp		short loc_466D41

			loc_466D25:
				mov		ecx, 8
			loc_466D2A:
				mov		eax, [esi]
				add		esi, 4
				inc		edi
				ror		eax, 8
				mov		[edi], al
				add		edi, 2
				ror		eax, 10h
				mov		[edi], al
				inc		edi
				dec		ecx
				jnz		short loc_466D2A
			loc_466D41:
				sub		edi, 320h
				cmp		edi, gpBufEnd
				jb		short loc_466D57
				add		esi, 20h
				add		edi, 20h
				jmp		short loc_466D71

			loc_466D57:
				mov		ecx, 8
			loc_466D5C:
				mov		eax, [esi]
				add		esi, 4
				mov		[edi], al
				add		edi, 2
				ror		eax, 10h
				mov		[edi], al
				add		edi, 2
				dec		ecx
				jnz		short loc_466D5C
			loc_466D71:
				sub		edi, 320h
				dec		edx
				jnz		short loc_466D15
			}
			break;
		case 9: // lower (top transparent), without lighting
			__asm {
				mov		eax, edi
				and		eax, 1
				mov		WorldBoolFlag, eax
				mov		ecx, 20h
			loc_466D8E:
				push	ecx
				mov		edx, 20h
			loc_466D94:
				xor		eax, eax
				mov		al, [esi]
				inc		esi
				test	al, al
				js		loc_466E35
				sub		edx, eax
				cmp		edi, gpBufEnd
				jb		short loc_466DB1
				add		esi, eax
				add		edi, eax
				jmp		short loc_466E2C

			loc_466DB1:
				mov		ecx, eax
				mov		eax, edi
				and		eax, 1
				cmp		eax, WorldBoolFlag
				jnz		short loc_466DF5
				shr		ecx, 1
				jnb		short loc_466DCC
				inc		esi
				inc		edi
				test	ecx, ecx
				jz		short loc_466E2C
				jmp		short loc_466E05

			loc_466DCC:
				shr		ecx, 1
				jnb		short loc_466DDC
				inc		esi
				inc		edi
				mov		al, [esi]
				inc		esi
				mov		[edi], al
				inc		edi
				test	ecx, ecx
				jz		short loc_466E2C
			loc_466DDC:
				mov		eax, [esi]
				add		esi, 4
				inc		edi
				ror		eax, 8
				mov		[edi], al
				add		edi, 2
				ror		eax, 10h
				mov		[edi], al
				inc		edi
				dec		ecx
				jnz		short loc_466DDC
				jmp		short loc_466E2C

			loc_466DF5:
				shr		ecx, 1
				jnb		short loc_466E05
				mov		al, [esi]
				inc		esi
				mov		[edi], al
				inc		edi
				test	ecx, ecx
				jz		short loc_466E2C
				jmp		short loc_466DCC

			loc_466E05:
				shr		ecx, 1
				jnb		short loc_466E17
				mov		al, [esi]
				add		esi, 2
				mov		[edi], al
				add		edi, 2
				test	ecx, ecx
				jz		short loc_466E2C
			loc_466E17:
				mov		eax, [esi]
				add		esi, 4
				mov		[edi], al
				add		edi, 2
				ror		eax, 10h
				mov		[edi], al
				add		edi, 2
				dec		ecx
				jnz		short loc_466E17
			loc_466E2C:
				test	edx, edx
				jz		short loc_466E41
				jmp		loc_466D94

			loc_466E35:
				neg		al
				add		edi, eax
				sub		edx, eax
				jnz		loc_466D94
			loc_466E41:
				pop		ecx
				mov		eax, WorldBoolFlag
				inc		eax
				and		eax, 1
				mov		WorldBoolFlag, eax
				sub		edi, 320h
				dec		ecx
				jnz		loc_466D8E
			}
			break;
		case 10: // lower (top transparent), without lighting
			__asm {
				xor		eax, eax
				mov		WorldBoolFlag, eax
				mov		edx, 1Eh
				mov		eax, edi
				sub		eax, gpBufEnd
				jb		short loc_466EC1
				add		eax, 3FFh
				shr		eax, 8
				cmp		eax, 2Dh
				jg		short loc_466EB0
				mov		ecx, WorldTbl3x16[eax*4]
				mov		eax, ecx
				add		esi, WorldTbl17_1[ecx]
				shl		eax, 6
				lea		eax, [eax+eax*2]
				shr		ecx, 1
				sub		edi, eax
				sub		edx, ecx
				mov		eax, WorldBoolFlag
				shr		ecx, 1
				add		eax, ecx
				mov		WorldBoolFlag, eax
				jmp		short loc_466EC1

			loc_466EB0:
				sub		edi, 3000h
				add		esi, 120h
				jmp		loc_466F3F

			loc_466EC1:
				add		edi, edx
				mov		ecx, 20h
				sub		ecx, edx
				mov		eax, WorldBoolFlag
				inc		eax
				and		eax, 1
				mov		WorldBoolFlag, eax
				jz		short loc_466F0A
				shr		ecx, 2
				jnb		short loc_466EF1
				mov		ax, [esi+2]
				add		esi, 4
				inc		edi
				ror		eax, 8
				mov		[edi], al
				inc		edi
				test	ecx, ecx
				jz		short loc_466F34
			loc_466EF1:
				mov		eax, [esi]
				add		esi, 4
				inc		edi
				ror		eax, 8
				mov		[edi], al
				add		edi, 2
				ror		eax, 10h
				mov		[edi], al
				inc		edi
				dec		ecx
				jnz		short loc_466EF1
				jmp		short loc_466F34

			loc_466F0A:
				shr		ecx, 2
				jnb		short loc_466F1F
				mov		ax, [esi+2]
				add		esi, 4
				mov		[edi], al
				add		edi, 2
				test	ecx, ecx
				jz		short loc_466F34
			loc_466F1F:
				mov		eax, [esi]
				add		esi, 4
				mov		[edi], al
				add		edi, 2
				ror		eax, 10h
				mov		[edi], al
				add		edi, 2
				dec		ecx
				jnz		short loc_466F1F
			loc_466F34:
				sub		edi, 320h
				sub		edx, 2
				jge		short loc_466EC1
			loc_466F3F:
				mov		edx, 2
				mov		eax, edi
				sub		eax, gpBufEnd
				jb		short loc_466F97
				add		eax, 3FFh
				shr		eax, 8
				cmp		eax, 2Ah
				jg		short loc_466F86
				mov		ecx, WorldTbl3x16[eax*4]
				mov		eax, ecx
				add		esi, WorldTbl17_2[ecx]
				shl		eax, 6
				lea		eax, [eax+eax*2]
				shr		ecx, 1
				sub		edi, eax
				add		edx, ecx
				mov		eax, WorldBoolFlag
				shr		ecx, 1
				add		eax, ecx
				mov		WorldBoolFlag, eax
				jmp		short loc_466F97

			loc_466F86:
				sub		edi, 2D00h
				add		esi, 100h
				jmp		ret_467944_10S

			loc_466F97:
				add		edi, edx
				mov		ecx, 20h
				sub		ecx, edx
				mov		eax, WorldBoolFlag
				inc		eax
				and		eax, 1
				mov		WorldBoolFlag, eax
				jz		short loc_466FE0
				shr		ecx, 2
				jnb		short loc_466FC7
				mov		ax, [esi+2]
				add		esi, 4
				inc		edi
				ror		eax, 8
				mov		[edi], al
				inc		edi
				test	ecx, ecx
				jz		short loc_467009
			loc_466FC7:
				mov		eax, [esi]
				add		esi, 4
				inc		edi
				ror		eax, 8
				mov		[edi], al
				add		edi, 2
				ror		eax, 10h
				mov		[edi], al
				inc		edi
				dec		ecx
				jnz		short loc_466FC7
				jmp		short loc_467009

			loc_466FE0:
				shr		ecx, 2
				jnb		short loc_466FF4
				mov		ax, [esi+2]
				add		esi, 4
				mov		[edi], al
				add		edi, 2
				dec		ecx
				jz		short loc_467009
			loc_466FF4:
				mov		eax, [esi]
				add		esi, 4
				mov		[edi], al
				add		edi, 2
				ror		eax, 10h
				mov		[edi], al
				add		edi, 2
				dec		ecx
				jnz		short loc_466FF4
			loc_467009:
				sub		edi, 320h
				add		edx, 2
				cmp		edx, 20h
				jnz		short loc_466F97
			ret_467944_10S:
			}
			break;
		case 11: // lower (top transparent), without lighting
			__asm {
				push	ebp
				xor		eax, eax
				mov		WorldBoolFlag, eax
				mov		edx, 1Eh
				mov		eax, edi
				sub		eax, gpBufEnd
				jb		short loc_46707C
				add		eax, 3FFh
				shr		eax, 8
				cmp		eax, 2Dh
				jg		short loc_46706B
				mov		ecx, WorldTbl3x16[eax*4]
				mov		eax, ecx
				add		esi, WorldTbl17_1[ecx]
				shl		eax, 6
				lea		eax, [eax+eax*2]
				shr		ecx, 1
				sub		edi, eax
				sub		edx, ecx
				mov		eax, WorldBoolFlag
				shr		ecx, 1
				add		eax, ecx
				mov		WorldBoolFlag, eax
				jmp		short loc_46707C

			loc_46706B:
				sub		edi, 3000h
				add		esi, 120h
				jmp		loc_4670FC

			loc_46707C:
				mov		ecx, 20h
				sub		ecx, edx
				mov		eax, WorldBoolFlag
				inc		eax
				and		eax, 1
				mov		ebp, ecx
				mov		WorldBoolFlag, eax
				jz		short loc_4670C5
				shr		ecx, 2
				jz		short loc_4670B1
			loc_46709A:
				mov		eax, [esi]
				add		esi, 4
				inc		edi
				ror		eax, 8
				mov		[edi], al
				add		edi, 2
				ror		eax, 10h
				mov		[edi], al
				inc		edi
				dec		ecx
				jnz		short loc_46709A
			loc_4670B1:
				and		ebp, 2
				jz		short loc_4670EF
				mov		ax, [esi]
				add		esi, 4
				inc		edi
				ror		eax, 8
				mov		[edi], al
				inc		edi
				jmp		short loc_4670EF

			loc_4670C5:
				shr		ecx, 2
				jz		short loc_4670DF
			loc_4670CA:
				mov		eax, [esi]
				add		esi, 4
				mov		[edi], al
				add		edi, 2
				ror		eax, 10h
				mov		[edi], al
				add		edi, 2
				dec		ecx
				jnz		short loc_4670CA
			loc_4670DF:
				and		ebp, 2
				jz		short loc_4670EF
				mov		ax, [esi]
				add		esi, 4
				mov		[edi], al
				add		edi, 2
			loc_4670EF:
				sub		edi, 320h
				add		edi, edx
				sub		edx, 2
				jge		short loc_46707C
			loc_4670FC:
				mov		edx, 2
				mov		eax, edi
				sub		eax, gpBufEnd
				jb		short loc_467154
				add		eax, 3FFh
				shr		eax, 8
				cmp		eax, 2Ah
				jg		short loc_467143
				mov		ecx, WorldTbl3x16[eax*4]
				mov		eax, ecx
				add		esi, WorldTbl17_2[ecx]
				shl		eax, 6
				lea		eax, [eax+eax*2]
				shr		ecx, 1
				sub		edi, eax
				add		edx, ecx
				mov		eax, WorldBoolFlag
				shr		ecx, 1
				add		eax, ecx
				mov		WorldBoolFlag, eax
				jmp		short loc_467154

			loc_467143:
				sub		edi, 2D00h
				add		esi, 100h
				jmp		loc_4671DB

			loc_467154:
				mov		ecx, 20h
				sub		ecx, edx
				mov		eax, WorldBoolFlag
				inc		eax
				and		eax, 1
				mov		ebp, ecx
				mov		WorldBoolFlag, eax
				jz		short loc_46719D
				shr		ecx, 2
				jz		short loc_467189
			loc_467172:
				mov		eax, [esi]
				add		esi, 4
				inc		edi
				ror		eax, 8
				mov		[edi], al
				add		edi, 2
				ror		eax, 10h
				mov		[edi], al
				inc		edi
				dec		ecx
				jnz		short loc_467172
			loc_467189:
				and		ebp, 2
				jz		short loc_4671C7
				mov		ax, [esi]
				add		esi, 4
				inc		edi
				ror		eax, 8
				mov		[edi], al
				inc		edi
				jmp		short loc_4671C7

			loc_46719D:
				shr		ecx, 2
				jz		short loc_4671B7
			loc_4671A2:
				mov		eax, [esi]
				add		esi, 4
				mov		[edi], al
				add		edi, 2
				ror		eax, 10h
				mov		[edi], al
				add		edi, 2
				dec		ecx
				jnz		short loc_4671A2
			loc_4671B7:
				and		ebp, 2
				jz		short loc_4671C7
				mov		ax, [esi]
				add		esi, 4
				mov		[edi], al
				add		edi, 2
			loc_4671C7:
				sub		edi, 320h
				add		edi, edx
				add		edx, 2
				cmp		edx, 20h
				jnz		loc_467154
			loc_4671DB:
				pop		ebp
			}
			break;
		case 12: // lower (top transparent), without lighting
			__asm {
				xor		eax, eax
				mov		WorldBoolFlag, eax
				mov		edx, 1Eh
				mov		eax, edi
				sub		eax, gpBufEnd
				jb		short loc_467240
				add		eax, 3FFh
				shr		eax, 8
				cmp		eax, 2Dh
				jg		short loc_46722F
				mov		ecx, WorldTbl3x16[eax*4]
				mov		eax, ecx
				add		esi, WorldTbl17_1[ecx]
				shl		eax, 6
				lea		eax, [eax+eax*2]
				shr		ecx, 1
				sub		edi, eax
				sub		edx, ecx
				mov		eax, WorldBoolFlag
				shr		ecx, 1
				add		eax, ecx
				mov		WorldBoolFlag, eax
				jmp		short loc_467240

			loc_46722F:
				sub		edi, 3000h
				add		esi, 120h
				jmp		loc_4672BE

			loc_467240:
				add		edi, edx
				mov		ecx, 20h
				sub		ecx, edx
				mov		eax, WorldBoolFlag
				inc		eax
				and		eax, 1
				mov		WorldBoolFlag, eax
				jz		short loc_467289
				shr		ecx, 2
				jnb		short loc_467270
				mov		ax, [esi+2]
				add		esi, 4
				inc		edi
				ror		eax, 8
				mov		[edi], al
				inc		edi
				test	ecx, ecx
				jz		short loc_4672B3
			loc_467270:
				mov		eax, [esi]
				add		esi, 4
				inc		edi
				ror		eax, 8
				mov		[edi], al
				add		edi, 2
				ror		eax, 10h
				mov		[edi], al
				inc		edi
				dec		ecx
				jnz		short loc_467270
				jmp		short loc_4672B3

			loc_467289:
				shr		ecx, 2
				jnb		short loc_46729E
				mov		ax, [esi+2]
				add		esi, 4
				mov		[edi], al
				test	ecx, ecx
				lea		edi, [edi+2]
				jz		short loc_4672B3
			loc_46729E:
				mov		eax, [esi]
				add		esi, 4
				mov		[edi], al
				add		edi, 2
				ror		eax, 10h
				mov		[edi], al
				dec		ecx
				lea		edi, [edi+2]
				jnz		short loc_46729E
			loc_4672B3:
				sub		edi, 320h
				sub		edx, 2
				jge		short loc_467240
			loc_4672BE:
				mov		edx, 8
			loc_4672C3:
				cmp		edi, gpBufEnd
				jb		short loc_4672D3
				add		esi, 20h
				add		edi, 20h
				jmp		short loc_4672EF

			loc_4672D3:
				mov		ecx, 8
			loc_4672D8:
				mov		eax, [esi]
				add		esi, 4
				inc		edi
				ror		eax, 8
				mov		[edi], al
				add		edi, 2
				ror		eax, 10h
				mov		[edi], al
				inc		edi
				dec		ecx
				jnz		short loc_4672D8
			loc_4672EF:
				sub		edi, 320h
				cmp		edi, gpBufEnd
				jb		short loc_467305
				add		esi, 20h
				add		edi, 20h
				jmp		short loc_46731F

			loc_467305:
				mov		ecx, 8
			loc_46730A:
				mov		eax, [esi]
				add		esi, 4
				mov		[edi], al
				add		edi, 2
				ror		eax, 10h
				mov		[edi], al
				add		edi, 2
				dec		ecx
				jnz		short loc_46730A
			loc_46731F:
				sub		edi, 320h
				dec		edx
				jnz		short loc_4672C3
			}
			break;
		default: // lower (top transparent), without lighting
			__asm {
				push	ebp
				xor		eax, eax
				mov		WorldBoolFlag, eax
				mov		edx, 1Eh
				mov		eax, edi
				sub		eax, gpBufEnd
				jb		short loc_46738D
				add		eax, 3FFh
				shr		eax, 8
				cmp		eax, 2Dh
				jg		short loc_46737C
				mov		ecx, WorldTbl3x16[eax*4]
				mov		eax, ecx
				add		esi, WorldTbl17_1[ecx]
				shl		eax, 6
				lea		eax, [eax+eax*2]
				shr		ecx, 1
				sub		edi, eax
				sub		edx, ecx
				mov		eax, WorldBoolFlag
				shr		ecx, 1
				add		eax, ecx
				mov		WorldBoolFlag, eax
				jmp		short loc_46738D

			loc_46737C:
				sub		edi, 3000h
				add		esi, 120h
				jmp		loc_46740D

			loc_46738D:
				mov		ecx, 20h
				sub		ecx, edx
				mov		eax, WorldBoolFlag
				inc		eax
				and		eax, 1
				mov		ebp, ecx
				mov		WorldBoolFlag, eax
				jz		short loc_4673D6
				shr		ecx, 2
				jz		short loc_4673C2
			loc_4673AB:
				mov		eax, [esi]
				add		esi, 4
				inc		edi
				ror		eax, 8
				mov		[edi], al
				add		edi, 2
				ror		eax, 10h
				mov		[edi], al
				inc		edi
				dec		ecx
				jnz		short loc_4673AB
			loc_4673C2:
				and		ebp, 2
				jz		short loc_467400
				mov		ax, [esi]
				add		esi, 4
				inc		edi
				ror		eax, 8
				mov		[edi], al
				inc		edi
				jmp		short loc_467400

			loc_4673D6:
				shr		ecx, 2
				jz		short loc_4673F0
			loc_4673DB:
				mov		eax, [esi]
				add		esi, 4
				mov		[edi], al
				add		edi, 2
				ror		eax, 10h
				mov		[edi], al
				add		edi, 2
				dec		ecx
				jnz		short loc_4673DB
			loc_4673F0:
				and		ebp, 2
				jz		short loc_467400
				mov		ax, [esi]
				add		esi, 4
				mov		[edi], al
				add		edi, 2
			loc_467400:
				sub		edi, 320h
				add		edi, edx
				sub		edx, 2
				jge		short loc_46738D
			loc_46740D:
				mov		edx, 8
			loc_467412:
				cmp		edi, gpBufEnd
				jb		short loc_467422
				add		esi, 20h
				add		edi, 20h
				jmp		short loc_46743E

			loc_467422:
				mov		ecx, 8
			loc_467427:
				mov		eax, [esi]
				add		esi, 4
				inc		edi
				ror		eax, 8
				mov		[edi], al
				add		edi, 2
				ror		eax, 10h
				mov		[edi], al
				inc		edi
				dec		ecx
				jnz		short loc_467427
			loc_46743E:
				sub		edi, 320h
				cmp		edi, gpBufEnd
				jb		short loc_467454
				add		esi, 20h
				add		edi, 20h
				jmp		short loc_46746E

			loc_467454:
				mov		ecx, 8
			loc_467459:
				mov		eax, [esi]
				add		esi, 4
				mov		[edi], al
				add		edi, 2
				ror		eax, 10h
				mov		[edi], al
				add		edi, 2
				dec		ecx
				jnz		short loc_467459
			loc_46746E:
				sub		edi, 320h
				dec		edx
				jnz		short loc_467412
				pop		ebp
			}
			break;
	}
}

void __fastcall drawBottomArchesLowerScreen(unsigned char *pbDst, unsigned int *pMask)
{
	unsigned char *dst; // edi MAPDST
	short cel_type_16; // ax MAPDST
	unsigned char *src; // esi MAPDST
	unsigned char *tbl;

	gpCelFrame = (unsigned char *)speed_cel_frame_num_from_light_index_frame_num;
	dst = pbDst;
	gpDrawMask = pMask;
	if ( (_BYTE)light_table_index )
	{
		if ( (_BYTE)light_table_index == lightmax )
		{
			if ( level_cel_block & 0x8000 )
				level_cel_block = *(_DWORD *)&gpCelFrame[64 * (level_cel_block & 0xFFF)]
								+ (unsigned short)(level_cel_block & 0xF000);
			src = (unsigned char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
			cel_type_16 = (level_cel_block >> 12) & 7;
			__asm {
				xor		edx, edx
				xor		ecx, ecx
				mov		edi, dst
				mov		esi, src
			}
			switch ( cel_type_16 )
			{
				case 0: // lower (bottom transparent), black
					__asm {
						mov		edx, 20h
					loc_46852E:
						cmp		edi, gpBufEnd
						jb		short loc_46853E
						add		esi, 20h
						add		edi, 20h
						jmp		short loc_468558

					loc_46853E:
						push	edx
						mov		eax, gpDrawMask
						mov		edx, [eax]
						xor		eax, eax
						mov		ecx, 20h
					loc_46854D:
						shl		edx, 1
						jnb		short loc_468553
						mov		[edi], al
					loc_468553:
						inc		edi
						dec		ecx
						jnz		short loc_46854D
						pop		edx
					loc_468558:
						sub		edi, 320h
						mov		eax, gpDrawMask
						sub		eax, 4
						mov		gpDrawMask, eax
						dec		edx
						jnz		short loc_46852E
					}
					break;
				case 1: // lower (bottom transparent), black
					__asm {
						mov		ecx, 20h
					loc_468578:
						push	ecx
						mov		eax, gpDrawMask
						mov		eax, [eax]
						mov		gdwCurrentMask, eax
						mov		edx, 20h
					loc_46858A:
						xor		eax, eax
						mov		al, [esi]
						inc		esi
						test	al, al
						js		short loc_4685C7
						sub		edx, eax
						cmp		edi, gpBufEnd
						jb		short loc_4685A3
						add		esi, eax
						add		edi, eax
						jmp		short loc_4685C1

					loc_4685A3:
						mov		ecx, eax
						add		esi, ecx
						push	edx
						mov		edx, gdwCurrentMask
						xor		eax, eax
					loc_4685B0:
						shl		edx, 1
						jnb		short loc_4685B6
						mov		[edi], al
					loc_4685B6:
						inc		edi
						dec		ecx
						jnz		short loc_4685B0
						mov		gdwCurrentMask, edx
						pop		edx
					loc_4685C1:
						test	edx, edx
						jz		short loc_4685E4
						jmp		short loc_46858A

					loc_4685C7:
						neg		al
						add		edi, eax
						mov		ecx, eax
						and		ecx, 1Fh
						jz		short loc_4685E0
						mov		ebx, gdwCurrentMask
						shl		ebx, cl
						mov		gdwCurrentMask, ebx
					loc_4685E0:
						sub		edx, eax
						jnz		short loc_46858A
					loc_4685E4:
						pop		ecx
						sub		edi, 320h
						mov		eax, gpDrawMask
						sub		eax, 4
						mov		gpDrawMask, eax
						dec		ecx
						jnz		loc_468578
					}
					break;
				case 2: // lower (bottom transparent), black
					__asm {
						mov		edx, 1Eh
						xor		eax, eax
					loc_46860B:
						cmp		edi, gpBufEnd
						jb		short loc_46861D
						add		esi, 20h
						sub		esi, edx
						add		edi, 20h
						jmp		short loc_46863D

					loc_46861D:
						add		edi, edx
						mov		ecx, 20h
						sub		ecx, edx
						shr		ecx, 2
						jnb		short loc_468635
						mov		[edi], ax
						add		edi, 2
						test	ecx, ecx
						jz		short loc_46863D
					loc_468635:
						mov		[edi], eax
						add		edi, 4
						dec		ecx
						jnz		short loc_468635
					loc_46863D:
						sub		edi, 320h
						test	edx, edx
						jz		short loc_46864C
						sub		edx, 2
						jmp		short loc_46860B

					loc_46864C:
						mov		edx, 2
					loc_468651:
						cmp		edi, gpBufEnd
						jb		short loc_468663
						add		esi, 20h
						sub		esi, edx
						add		edi, 20h
						jmp		short loc_468683

					loc_468663:
						add		edi, edx
						mov		ecx, 20h
						sub		ecx, edx
						shr		ecx, 2
						jnb		short loc_46867B
						mov		[edi], ax
						add		edi, 2
						test	ecx, ecx
						jz		short loc_468683
					loc_46867B:
						mov		[edi], eax
						add		edi, 4
						dec		ecx
						jnz		short loc_46867B
					loc_468683:
						sub		edi, 320h
						add		edx, 2
						cmp		edx, 20h
						jnz		short loc_468651
					}
					break;
				case 3: // lower (bottom transparent), black
					__asm {
						mov		edx, 1Eh
						xor		eax, eax
					loc_46869D:
						cmp		edi, gpBufEnd
						jb		short loc_4686B1
						add		esi, 20h
						sub		esi, edx
						add		edi, 20h
						sub		edi, edx
						jmp		short loc_4686CF

					loc_4686B1:
						mov		ecx, 20h
						sub		ecx, edx
						shr		ecx, 2
						jnb		short loc_4686C7
						mov		[edi], ax
						add		edi, 2
						test	ecx, ecx
						jz		short loc_4686CF
					loc_4686C7:
						mov		[edi], eax
						add		edi, 4
						dec		ecx
						jnz		short loc_4686C7
					loc_4686CF:
						sub		edi, 320h
						test	edx, edx
						jz		short loc_4686E0
						add		edi, edx
						sub		edx, 2
						jmp		short loc_46869D

					loc_4686E0:
						mov		edx, 2
					loc_4686E5:
						cmp		edi, gpBufEnd
						jb		short loc_4686F9
						add		esi, 20h
						sub		esi, edx
						add		edi, 20h
						sub		edi, edx
						jmp		short loc_468717

					loc_4686F9:
						mov		ecx, 20h
						sub		ecx, edx
						shr		ecx, 2
						jnb		short loc_46870F
						mov		[edi], ax
						add		edi, 2
						test	ecx, ecx
						jz		short loc_468717
					loc_46870F:
						mov		[edi], eax
						add		edi, 4
						dec		ecx
						jnz		short loc_46870F
					loc_468717:
						sub		edi, 320h
						add		edi, edx
						add		edx, 2
						cmp		edx, 20h
						jnz		short loc_4686E5
					}
					break;
				case 4: // lower (bottom transparent), black
					__asm {
						mov		edx, 1Eh
						xor		eax, eax
					loc_468733:
						cmp		edi, gpBufEnd
						jb		short loc_468745
						add		esi, 20h
						sub		esi, edx
						add		edi, 20h
						jmp		short loc_468765

					loc_468745:
						add		edi, edx
						mov		ecx, 20h
						sub		ecx, edx
						shr		ecx, 2
						jnb		short loc_46875D
						mov		[edi], ax
						add		edi, 2
						test	ecx, ecx
						jz		short loc_468765
					loc_46875D:
						mov		[edi], eax
						add		edi, 4
						dec		ecx
						jnz		short loc_46875D
					loc_468765:
						sub		edi, 320h
						test	edx, edx
						jz		short loc_468774
						sub		edx, 2
						jmp		short loc_468733

					loc_468774:
						mov		eax, gpDrawMask
						sub		eax, 40h
						mov		gpDrawMask, eax
						mov		edx, 10h
					loc_468786:
						cmp		edi, gpBufEnd
						jb		short loc_468796
						add		esi, 20h
						add		edi, 20h
						jmp		short loc_4687B0

					loc_468796:
						push	edx
						mov		eax, gpDrawMask
						mov		edx, [eax]
						xor		eax, eax
						mov		ecx, 20h
					loc_4687A5:
						shl		edx, 1
						jnb		short loc_4687AB
						mov		[edi], al
					loc_4687AB:
						inc		edi
						dec		ecx
						jnz		short loc_4687A5
						pop		edx
					loc_4687B0:
						sub		edi, 320h
						mov		eax, gpDrawMask
						sub		eax, 4
						mov		gpDrawMask, eax
						dec		edx
						jnz		short loc_468786
					}
					break;
				default: // lower (bottom transparent), black
					__asm {
						mov		edx, 1Eh
						xor		eax, eax
					loc_4687D2:
						cmp		edi, gpBufEnd
						jb		short loc_4687E6
						add		esi, 20h
						sub		esi, edx
						add		edi, 20h
						sub		edi, edx
						jmp		short loc_468804

					loc_4687E6:
						mov		ecx, 20h
						sub		ecx, edx
						shr		ecx, 2
						jnb		short loc_4687FC
						mov		[edi], ax
						add		edi, 2
						test	ecx, ecx
						jz		short loc_468804
					loc_4687FC:
						mov		[edi], eax
						add		edi, 4
						dec		ecx
						jnz		short loc_4687FC
					loc_468804:
						sub		edi, 320h
						test	edx, edx
						jz		short loc_468815
						add		edi, edx
						sub		edx, 2
						jmp		short loc_4687D2

					loc_468815:
						mov		eax, gpDrawMask
						sub		eax, 40h
						mov		gpDrawMask, eax
						mov		edx, 10h
					loc_468827:
						cmp		edi, gpBufEnd
						jb		short loc_468837
						add		esi, 20h
						add		edi, 20h
						jmp		short loc_468851

					loc_468837:
						push	edx
						mov		eax, gpDrawMask
						mov		edx, [eax]
						xor		eax, eax
						mov		ecx, 20h
					loc_468846:
						shl		edx, 1
						jnb		short loc_46884C
						mov		[edi], al
					loc_46884C:
						inc		edi
						dec		ecx
						jnz		short loc_468846
						pop		edx
					loc_468851:
						sub		edi, 320h
						mov		eax, gpDrawMask
						sub		eax, 4
						mov		gpDrawMask, eax
						dec		edx
						jnz		short loc_468827
					}
					break;
			}
			return;
		}
		if ( !(level_cel_block & 0x8000) )
		{
			src = (unsigned char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
			tbl = (unsigned char *)&pLightTbl[256 * light_table_index];
			cel_type_16 = (unsigned char)(level_cel_block >> 12);
			__asm {
				xor		edx, edx
				xor		ecx, ecx
				mov		ebx, tbl
				mov		edi, dst
				mov		esi, src
			}
			switch ( cel_type_16 )
			{
				case 0: // lower (bottom transparent), with lighting
					__asm {
						push	ebp
						mov		ebp, 20h
					loc_467B49:
						cmp		edi, gpBufEnd
						jb		short loc_467B59
						add		esi, 20h
						add		edi, 20h
						jmp		short loc_467B73

					loc_467B59:
						mov		eax, gpDrawMask
						mov		edx, [eax]
						mov		ecx, 20h
					loc_467B65:
						mov		al, [esi]
						inc		esi
						shl		edx, 1
						jnb		short loc_467B6F
						xlat
						mov		[edi], al
					loc_467B6F:
						inc		edi
						dec		ecx
						jnz		short loc_467B65
					loc_467B73:
						sub		edi, 320h
						mov		eax, gpDrawMask
						sub		eax, 4
						mov		gpDrawMask, eax
						dec		ebp
						jnz		short loc_467B49
						pop		ebp
					}
					break;
				case 1: // lower (bottom transparent), with lighting
					__asm {
						mov		ecx, 20h
					loc_467B94:
						push	ecx
						mov		eax, gpDrawMask
						mov		eax, [eax]
						mov		gdwCurrentMask, eax
						mov		edx, 20h
					loc_467BA6:
						xor		eax, eax
						mov		al, [esi]
						inc		esi
						test	al, al
						js		short loc_467BE3
						sub		edx, eax
						cmp		edi, gpBufEnd
						jb		short loc_467BBF
						add		esi, eax
						add		edi, eax
						jmp		short loc_467BDD

					loc_467BBF:
						mov		ecx, eax
						push	edx
						mov		edx, gdwCurrentMask
					loc_467BC8:
						mov		al, [esi]
						inc		esi
						shl		edx, 1
						jnb		short loc_467BD2
						xlat
						mov		[edi], al
					loc_467BD2:
						inc		edi
						dec		ecx
						jnz		short loc_467BC8
						mov		gdwCurrentMask, edx
						pop		edx
					loc_467BDD:
						test	edx, edx
						jz		short loc_467C00
						jmp		short loc_467BA6

					loc_467BE3:
						neg		al
						add		edi, eax
						mov		ecx, eax
						and		ecx, 1Fh
						jz		short loc_467BFC
						push	eax
						mov		eax, gdwCurrentMask
						shl		eax, cl
						mov		gdwCurrentMask, eax
						pop		eax
					loc_467BFC:
						sub		edx, eax
						jnz		short loc_467BA6
					loc_467C00:
						pop		ecx
						sub		edi, 320h
						mov		eax, gpDrawMask
						sub		eax, 4
						mov		gpDrawMask, eax
						dec		ecx
						jnz		loc_467B94
					}
					break;
				case 2: // lower (bottom transparent), with lighting
					__asm {
						mov		edx, 1Eh
						mov		eax, edi
						sub		eax, gpBufEnd
						jb		short loc_467C67
						add		eax, 3FFh
						shr		eax, 8
						cmp		eax, 2Dh
						jg		short loc_467C59
						mov		ecx, WorldTbl3x16[eax*4]
						mov		eax, ecx
						add		esi, WorldTbl17_1[ecx]
						shl		eax, 6
						lea		eax, [eax+eax*2]
						shr		ecx, 1
						sub		edi, eax
						sub		edx, ecx
						jmp		short loc_467C67

					loc_467C59:
						sub		edi, 3000h
						add		esi, 120h
						jmp		short loc_467CB8

					loc_467C67:
						add		edi, edx
						mov		ecx, 20h
						sub		ecx, edx
						shr		ecx, 2
						jnb		short loc_467C90
						mov		ax, [esi+2]
						add		esi, 4
						xlat
						ror		ax, 8
						xlat
						ror		ax, 8
						mov		[edi], ax
						add		edi, 2
						test	ecx, ecx
						jz		short loc_467CAD
					loc_467C90:
						mov		eax, [esi]
						add		esi, 4
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						mov		[edi], eax
						add		edi, 4
						dec		ecx
						jnz		short loc_467C90
					loc_467CAD:
						sub		edi, 320h
						sub		edx, 2
						jge		short loc_467C67
					loc_467CB8:
						mov		edx, 2
						mov		eax, edi
						sub		eax, gpBufEnd
						jb		short loc_467D02
						add		eax, 3FFh
						shr		eax, 8
						cmp		eax, 2Ah
						jg		short loc_467CF1
						mov		ecx, WorldTbl3x16[eax*4]
						mov		eax, ecx
						add		esi, WorldTbl17_2[ecx]
						shl		eax, 6
						lea		eax, [eax+eax*2]
						shr		ecx, 1
						sub		edi, eax
						add		edx, ecx
						jmp		short loc_467D02

					loc_467CF1:
						sub		edi, 2D00h
						add		esi, 100h
						jmp		ret_468867_2L

					loc_467D02:
						add		edi, edx
						mov		ecx, 20h
						sub		ecx, edx
						shr		ecx, 2
						jnb		short loc_467D2B
						mov		ax, [esi+2]
						add		esi, 4
						xlat
						ror		ax, 8
						xlat
						ror		ax, 8
						mov		[edi], ax
						add		edi, 2
						test	ecx, ecx
						jz		short loc_467D48
					loc_467D2B:
						mov		eax, [esi]
						add		esi, 4
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						mov		[edi], eax
						add		edi, 4
						dec		ecx
						jnz		short loc_467D2B
					loc_467D48:
						sub		edi, 320h
						add		edx, 2
						cmp		edx, 20h
						jnz		short loc_467D02
					ret_468867_2L:
					}
					break;
				case 3: // lower (bottom transparent), with lighting
					__asm {
						push	ebp
						mov		edx, 1Eh
						mov		eax, edi
						sub		eax, gpBufEnd
						jb		short loc_467DA3
						add		eax, 3FFh
						shr		eax, 8
						cmp		eax, 2Dh
						jg		short loc_467D95
						mov		ecx, WorldTbl3x16[eax*4]
						mov		eax, ecx
						add		esi, WorldTbl17_1[ecx]
						shl		eax, 6
						lea		eax, [eax+eax*2]
						shr		ecx, 1
						sub		edi, eax
						sub		edx, ecx
						jmp		short loc_467DA3

					loc_467D95:
						sub		edi, 3000h
						add		esi, 120h
						jmp		short loc_467DF6

					loc_467DA3:
						mov		ecx, 20h
						sub		ecx, edx
						mov		ebp, ecx
						shr		ecx, 2
						jz		short loc_467DCE
					loc_467DB1:
						mov		eax, [esi]
						add		esi, 4
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						mov		[edi], eax
						add		edi, 4
						dec		ecx
						jnz		short loc_467DB1
					loc_467DCE:
						and		ebp, 2
						jz		short loc_467DE9
						mov		ax, [esi]
						add		esi, 4
						xlat
						ror		ax, 8
						xlat
						ror		ax, 8
						mov		[edi], ax
						add		edi, 2
					loc_467DE9:
						sub		edi, 320h
						add		edi, edx
						sub		edx, 2
						jge		short loc_467DA3
					loc_467DF6:
						mov		edx, 2
						mov		eax, edi
						sub		eax, gpBufEnd
						jb		short loc_467E3D
						add		eax, 3FFh
						shr		eax, 8
						cmp		eax, 2Ah
						jg		short loc_467E2F
						mov		ecx, WorldTbl3x16[eax*4]
						mov		eax, ecx
						add		esi, WorldTbl17_2[ecx]
						shl		eax, 6
						lea		eax, [eax+eax*2]
						shr		ecx, 1
						sub		edi, eax
						add		edx, ecx
						jmp		short loc_467E3D

					loc_467E2F:
						sub		edi, 2D00h
						add		esi, 100h
						jmp		short loc_467E93

					loc_467E3D:
						mov		ecx, 20h
						sub		ecx, edx
						mov		ebp, ecx
						shr		ecx, 2
						jz		short loc_467E68
					loc_467E4B:
						mov		eax, [esi]
						add		esi, 4
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						mov		[edi], eax
						add		edi, 4
						dec		ecx
						jnz		short loc_467E4B
					loc_467E68:
						and		ebp, 2
						jz		short loc_467E83
						mov		ax, [esi]
						add		esi, 2
						xlat
						ror		ax, 8
						xlat
						ror		ax, 8
						mov		[edi], ax
						add		edi, 2
					loc_467E83:
						sub		edi, 320h
						add		edi, edx
						add		edx, 2
						cmp		edx, 20h
						jnz		short loc_467E3D
					loc_467E93:
						pop		ebp
					}
					break;
				case 4: // lower (bottom transparent), with lighting
					__asm {
						mov		edx, 1Eh
						mov		eax, edi
						sub		eax, gpBufEnd
						jb		short loc_467EE0
						add		eax, 3FFh
						shr		eax, 8
						cmp		eax, 2Dh
						jg		short loc_467ED2
						mov		ecx, WorldTbl3x16[eax*4]
						mov		eax, ecx
						add		esi, WorldTbl17_1[ecx]
						shl		eax, 6
						lea		eax, [eax+eax*2]
						shr		ecx, 1
						sub		edi, eax
						sub		edx, ecx
						jmp		short loc_467EE0

					loc_467ED2:
						sub		edi, 3000h
						add		esi, 120h
						jmp		short loc_467F31

					loc_467EE0:
						add		edi, edx
						mov		ecx, 20h
						sub		ecx, edx
						shr		ecx, 2
						jnb		short loc_467F09
						mov		ax, [esi+2]
						add		esi, 4
						xlat
						ror		ax, 8
						xlat
						ror		ax, 8
						mov		[edi], ax
						add		edi, 2
						test	ecx, ecx
						jz		short loc_467F26
					loc_467F09:
						mov		eax, [esi]
						add		esi, 4
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						mov		[edi], eax
						add		edi, 4
						dec		ecx
						jnz		short loc_467F09
					loc_467F26:
						sub		edi, 320h
						sub		edx, 2
						jge		short loc_467EE0
					loc_467F31:
						mov		eax, gpDrawMask
						sub		eax, 40h
						mov		gpDrawMask, eax
						mov		edx, 10h
					loc_467F43:
						cmp		edi, gpBufEnd
						jb		short loc_467F53
						add		esi, 20h
						add		edi, 20h
						jmp		short loc_467F6F

					loc_467F53:
						push	edx
						mov		eax, gpDrawMask
						mov		edx, [eax]
						mov		ecx, 20h
					loc_467F60:
						mov		al, [esi]
						inc		esi
						shl		edx, 1
						jnb		short loc_467F6A
						xlat
						mov		[edi], al
					loc_467F6A:
						inc		edi
						dec		ecx
						jnz		short loc_467F60
						pop		edx
					loc_467F6F:
						sub		edi, 320h
						mov		eax, gpDrawMask
						sub		eax, 4
						mov		gpDrawMask, eax
						dec		edx
						jnz		short loc_467F43
					}
					break;
				default: // lower (bottom transparent), with lighting
					__asm {
						push	ebp
						mov		edx, 1Eh
						mov		eax, edi
						sub		eax, gpBufEnd
						jb		short loc_467FD2
						add		eax, 3FFh
						shr		eax, 8
						cmp		eax, 2Dh
						jg		short loc_467FC4
						mov		ecx, WorldTbl3x16[eax*4]
						mov		eax, ecx
						add		esi, WorldTbl17_1[ecx]
						shl		eax, 6
						lea		eax, [eax+eax*2]
						shr		ecx, 1
						sub		edi, eax
						sub		edx, ecx
						jmp		short loc_467FD2

					loc_467FC4:
						sub		edi, 3000h
						add		esi, 120h
						jmp		short loc_468025

					loc_467FD2:
						mov		ecx, 20h
						sub		ecx, edx
						mov		ebp, ecx
						shr		ecx, 2
						jz		short loc_467FFD
					loc_467FE0:
						mov		eax, [esi]
						add		esi, 4
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						xlat
						ror		eax, 8
						mov		[edi], eax
						add		edi, 4
						dec		ecx
						jnz		short loc_467FE0
					loc_467FFD:
						and		ebp, 2
						jz		short loc_468018
						mov		ax, [esi]
						add		esi, 4
						xlat
						ror		ax, 8
						xlat
						ror		ax, 8
						mov		[edi], ax
						add		edi, 2
					loc_468018:
						sub		edi, 320h
						add		edi, edx
						sub		edx, 2
						jge		short loc_467FD2
					loc_468025:
						mov		eax, gpDrawMask
						sub		eax, 40h
						mov		gpDrawMask, eax
						mov		edx, 10h
					loc_468037:
						cmp		edi, gpBufEnd
						jb		short loc_468047
						add		esi, 20h
						add		edi, 20h
						jmp		short loc_46806A

					loc_468047:
						push	edx
						mov		eax, gpDrawMask
						mov		edx, [eax]
						mov		ecx, 20h
					loc_468054:
						mov		al, [esi]
						inc		esi
						shl		edx, 1
						jnb		short loc_46805E
						xlat
						mov		[edi], al
					loc_46805E:
						inc		edi
						dec		ecx
						jnz		short loc_468054
						mov		ebp, esi
						and		ebp, 2
						add		esi, ebp
						pop		edx
					loc_46806A:
						sub		edi, 320h
						mov		eax, gpDrawMask
						sub		eax, 4
						mov		gpDrawMask, eax
						dec		edx
						jnz		short loc_468037
						pop		ebp
					}
					break;
			}
			return;
		}
		src = (unsigned char *)pSpeedCels
				   + *(_DWORD *)&gpCelFrame[4 * (light_table_index + 16 * (level_cel_block & 0xFFF))];
		cel_type_16 = (unsigned char)(level_cel_block >> 12);
	}
	else
	{
		if ( level_cel_block & 0x8000 )
			level_cel_block = *(_DWORD *)&gpCelFrame[64 * (level_cel_block & 0xFFF)]
							+ (unsigned short)(level_cel_block & 0xF000);
		src = (unsigned char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
		cel_type_16 = ((level_cel_block >> 12) & 7) + 8;
	}
	__asm {
		xor		edx, edx
		xor		ecx, ecx
		mov		edi, dst
		mov		esi, src
	}
	switch ( cel_type_16 )
	{
		case 8: // lower (bottom transparent), without lighting
			__asm {
				mov		edx, 20h
			loc_46808B:
				cmp		edi, gpBufEnd
				jb		short loc_46809B
				add		esi, 20h
				add		edi, 20h
				jmp		short loc_4680B6

			loc_46809B:
				push	edx
				mov		eax, gpDrawMask
				mov		edx, [eax]
				mov		ecx, 20h
			loc_4680A8:
				mov		al, [esi]
				inc		esi
				shl		edx, 1
				jnb		short loc_4680B1
				mov		[edi], al
			loc_4680B1:
				inc		edi
				dec		ecx
				jnz		short loc_4680A8
				pop		edx
			loc_4680B6:
				sub		edi, 320h
				mov		eax, gpDrawMask
				sub		eax, 4
				mov		gpDrawMask, eax
				dec		edx
				jnz		short loc_46808B
			}
			break;
		case 9: // lower (bottom transparent), without lighting
			__asm {
				mov		ecx, 20h
			loc_4680D6:
				push	ecx
				mov		eax, gpDrawMask
				mov		eax, [eax]
				mov		gdwCurrentMask, eax
				mov		edx, 20h
			loc_4680E8:
				xor		eax, eax
				mov		al, [esi]
				inc		esi
				test	al, al
				js		short loc_468124
				sub		edx, eax
				cmp		edi, gpBufEnd
				jb		short loc_468101
				add		esi, eax
				add		edi, eax
				jmp		short loc_46811E

			loc_468101:
				mov		ecx, eax
				push	edx
				mov		edx, gdwCurrentMask
			loc_46810A:
				mov		al, [esi]
				inc		esi
				shl		edx, 1
				jnb		short loc_468113
				mov		[edi], al
			loc_468113:
				inc		edi
				dec		ecx
				jnz		short loc_46810A
				mov		gdwCurrentMask, edx
				pop		edx
			loc_46811E:
				test	edx, edx
				jz		short loc_468141
				jmp		short loc_4680E8

			loc_468124:
				neg		al
				add		edi, eax
				mov		ecx, eax
				and		ecx, 1Fh
				jz		short loc_46813D
				mov		ebx, gdwCurrentMask
				shl		ebx, cl
				mov		gdwCurrentMask, ebx
			loc_46813D:
				sub		edx, eax
				jnz		short loc_4680E8
			loc_468141:
				pop		ecx
				sub		edi, 320h
				mov		eax, gpDrawMask
				sub		eax, 4
				mov		gpDrawMask, eax
				dec		ecx
				jnz		loc_4680D6
			}
			break;
		case 10: // lower (bottom transparent), without lighting
			__asm {
				mov		edx, 1Eh
				mov		eax, edi
				sub		eax, gpBufEnd
				jb		short loc_4681A8
				add		eax, 3FFh
				shr		eax, 8
				cmp		eax, 2Dh
				jg		short loc_46819A
				mov		ecx, WorldTbl3x16[eax*4]
				mov		eax, ecx
				add		esi, WorldTbl17_1[ecx]
				shl		eax, 6
				lea		eax, [eax+eax*2]
				shr		ecx, 1
				sub		edi, eax
				sub		edx, ecx
				jmp		short loc_4681A8

			loc_46819A:
				sub		edi, 3000h
				add		esi, 120h
				jmp		short loc_4681DF

			loc_4681A8:
				add		edi, edx
				mov		ecx, 20h
				sub		ecx, edx
				shr		ecx, 2
				jnb		short loc_4681C7
				mov		ax, [esi+2]
				add		esi, 4
				mov		[edi], ax
				add		edi, 2
				test	ecx, ecx
				jz		short loc_4681D4
			loc_4681C7:
				mov		eax, [esi]
				add		esi, 4
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_4681C7
			loc_4681D4:
				sub		edi, 320h
				sub		edx, 2
				jge		short loc_4681A8
			loc_4681DF:
				mov		edx, 2
				mov		eax, edi
				sub		eax, gpBufEnd
				jb		short loc_468229
				add		eax, 3FFh
				shr		eax, 8
				cmp		eax, 2Ah
				jg		short loc_468218
				mov		ecx, WorldTbl3x16[eax*4]
				mov		eax, ecx
				add		esi, WorldTbl17_2[ecx]
				shl		eax, 6
				lea		eax, [eax+eax*2]
				shr		ecx, 1
				sub		edi, eax
				add		edx, ecx
				jmp		short loc_468229

			loc_468218:
				sub		edi, 2D00h
				add		esi, 100h
				jmp		ret_468867_10S

			loc_468229:
				add		edi, edx
				mov		ecx, 20h
				sub		ecx, edx
				shr		ecx, 2
				jnb		short loc_468248
				mov		ax, [esi+2]
				add		esi, 4
				mov		[edi], ax
				add		edi, 2
				test	ecx, ecx
				jz		short loc_468255
			loc_468248:
				mov		eax, [esi]
				add		esi, 4
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_468248
			loc_468255:
				sub		edi, 320h
				add		edx, 2
				cmp		edx, 20h
				jnz		short loc_468229
			ret_468867_10S:
			}
			break;
		case 11: // lower (bottom transparent), without lighting
			__asm {
				push	ebp
				mov		edx, 1Eh
				mov		eax, edi
				sub		eax, gpBufEnd
				jb		short loc_4682B0
				add		eax, 3FFh
				shr		eax, 8
				cmp		eax, 2Dh
				jg		short loc_4682A2
				mov		ecx, WorldTbl3x16[eax*4]
				mov		eax, ecx
				add		esi, WorldTbl17_1[ecx]
				shl		eax, 6
				lea		eax, [eax+eax*2]
				shr		ecx, 1
				sub		edi, eax
				sub		edx, ecx
				jmp		short loc_4682B0

			loc_4682A2:
				sub		edi, 3000h
				add		esi, 120h
				jmp		short loc_4682E9

			loc_4682B0:
				mov		ecx, 20h
				sub		ecx, edx
				mov		ebp, ecx
				shr		ecx, 2
				jz		short loc_4682CB
			loc_4682BE:
				mov		eax, [esi]
				add		esi, 4
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_4682BE
			loc_4682CB:
				and		ebp, 2
				jz		short loc_4682DC
				mov		ax, [esi]
				add		esi, 4
				mov		[edi], ax
				add		edi, 2
			loc_4682DC:
				sub		edi, 320h
				add		edi, edx
				sub		edx, 2
				jge		short loc_4682B0
			loc_4682E9:
				mov		edx, 2
				mov		eax, edi
				sub		eax, gpBufEnd
				jb		short loc_468330
				add		eax, 3FFh
				shr		eax, 8
				cmp		eax, 2Ah
				jg		short loc_468322
				mov		ecx, WorldTbl3x16[eax*4]
				mov		eax, ecx
				add		esi, WorldTbl17_2[ecx]
				shl		eax, 6
				lea		eax, [eax+eax*2]
				shr		ecx, 1
				sub		edi, eax
				add		edx, ecx
				jmp		short loc_468330

			loc_468322:
				sub		edi, 2D00h
				add		esi, 100h
				jmp		short loc_46836C

			loc_468330:
				mov		ecx, 20h
				sub		ecx, edx
				mov		ebp, ecx
				shr		ecx, 2
				jz		short loc_46834B
			loc_46833E:
				mov		eax, [esi]
				add		esi, 4
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_46833E
			loc_46834B:
				and		ebp, 2
				jz		short loc_46835C
				mov		ax, [esi]
				add		esi, 4
				mov		[edi], ax
				add		edi, 2
			loc_46835C:
				sub		edi, 320h
				add		edi, edx
				add		edx, 2
				cmp		edx, 20h
				jnz		short loc_468330
			loc_46836C:
				pop		ebp
			}
			break;
		case 12: // lower (bottom transparent), without lighting
			__asm {
				mov		edx, 1Eh
				mov		eax, edi
				sub		eax, gpBufEnd
				jb		short loc_4683B9
				add		eax, 3FFh
				shr		eax, 8
				cmp		eax, 2Dh
				jg		short loc_4683AB
				mov		ecx, WorldTbl3x16[eax*4]
				mov		eax, ecx
				add		esi, WorldTbl17_1[ecx]
				shl		eax, 6
				lea		eax, [eax+eax*2]
				shr		ecx, 1
				sub		edi, eax
				sub		edx, ecx
				jmp		short loc_4683B9

			loc_4683AB:
				sub		edi, 3000h
				add		esi, 120h
				jmp		short loc_4683F0

			loc_4683B9:
				add		edi, edx
				mov		ecx, 20h
				sub		ecx, edx
				shr		ecx, 2
				jnb		short loc_4683D8
				mov		ax, [esi+2]
				add		esi, 4
				mov		[edi], ax
				add		edi, 2
				test	ecx, ecx
				jz		short loc_4683E5
			loc_4683D8:
				mov		eax, [esi]
				add		esi, 4
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_4683D8
			loc_4683E5:
				sub		edi, 320h
				sub		edx, 2
				jge		short loc_4683B9
			loc_4683F0:
				mov		eax, gpDrawMask
				sub		eax, 40h
				mov		gpDrawMask, eax
				mov		edx, 10h
			loc_468402:
				cmp		edi, gpBufEnd
				jb		short loc_468412
				add		esi, 20h
				add		edi, 20h
				jmp		short loc_46842D

			loc_468412:
				push	edx
				mov		eax, gpDrawMask
				mov		edx, [eax]
				mov		ecx, 20h
			loc_46841F:
				mov		al, [esi]
				inc		esi
				shl		edx, 1
				jnb		short loc_468428
				mov		[edi], al
			loc_468428:
				inc		edi
				dec		ecx
				jnz		short loc_46841F
				pop		edx
			loc_46842D:
				sub		edi, 320h
				mov		eax, gpDrawMask
				sub		eax, 4
				mov		gpDrawMask, eax
				dec		edx
				jnz		short loc_468402
			}
			break;
		default: // lower (bottom transparent), without lighting
			__asm {
				push	ebp
				mov		edx, 1Eh
				mov		eax, edi
				sub		eax, gpBufEnd
				jb		short loc_468490
				add		eax, 3FFh
				shr		eax, 8
				cmp		eax, 2Dh
				jg		short loc_468482
				mov		ecx, WorldTbl3x16[eax*4]
				mov		eax, ecx
				add		esi, WorldTbl17_1[ecx]
				shl		eax, 6
				lea		eax, [eax+eax*2]
				shr		ecx, 1
				sub		edi, eax
				sub		edx, ecx
				jmp		short loc_468490

			loc_468482:
				sub		edi, 3000h
				add		esi, 120h
				jmp		short loc_4684C9

			loc_468490:
				mov		ecx, 20h
				sub		ecx, edx
				mov		ebp, ecx
				shr		ecx, 2
				jz		short loc_4684AB
			loc_46849E:
				mov		eax, [esi]
				add		esi, 4
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_46849E
			loc_4684AB:
				and		ebp, 2
				jz		short loc_4684BC
				mov		ax, [esi]
				add		esi, 4
				mov		[edi], ax
				add		edi, 2
			loc_4684BC:
				sub		edi, 320h
				add		edi, edx
				sub		edx, 2
				jge		short loc_468490
			loc_4684C9:
				mov		eax, gpDrawMask
				sub		eax, 40h
				mov		gpDrawMask, eax
				mov		edx, 10h
			loc_4684DB:
				cmp		edi, gpBufEnd
				jb		short loc_4684EB
				add		esi, 20h
				add		edi, 20h
				jmp		short loc_46850D

			loc_4684EB:
				push	edx
				mov		eax, gpDrawMask
				mov		edx, [eax]
				mov		ecx, 20h
			loc_4684F8:
				mov		al, [esi]
				inc		esi
				shl		edx, 1
				jnb		short loc_468501
				mov		[edi], al
			loc_468501:
				inc		edi
				dec		ecx
				jnz		short loc_4684F8
				mov		ebp, esi
				and		ebp, 2
				add		esi, ebp
				pop		edx
			loc_46850D:
				sub		edi, 320h
				mov		eax, gpDrawMask
				sub		eax, 4
				mov		gpDrawMask, eax
				dec		edx
				jnz		short loc_4684DB
				pop		ebp
			}
			break;
	}
}

void __fastcall drawLowerScreen(unsigned char *pbDst)
{
	unsigned char *dst; // edi MAPDST
	unsigned char *src; // esi MAPDST
	unsigned char *tbl; // ebx
	short cel_type_16; // ax MAPDST

	if ( cel_transparency_active )
	{
		if ( !arch_draw_type )
		{
			drawTopArchesLowerScreen(pbDst);
			return;
		}
		if ( arch_draw_type == 1 )
		{
			if ( block_lvid[level_piece_id] == 1 || block_lvid[level_piece_id] == 3 )
			{
				drawBottomArchesLowerScreen(pbDst, &LeftMask[31]);
				return;
			}
		}
		if ( arch_draw_type == 2 )
		{
			if ( block_lvid[level_piece_id] == 2 || block_lvid[level_piece_id] == 3 )
			{
				drawBottomArchesLowerScreen(pbDst, &RightMask[31]);
				return;
			}
		}
	}
	gpCelFrame = (unsigned char *)speed_cel_frame_num_from_light_index_frame_num;
	dst = pbDst;
	if ( (_BYTE)light_table_index )
	{
		if ( (_BYTE)light_table_index == lightmax )
		{
			if ( level_cel_block & 0x8000 )
				level_cel_block = *(_DWORD *)&gpCelFrame[64 * (level_cel_block & 0xFFF)]
								+ (unsigned short)(level_cel_block & 0xF000);
			src = (unsigned char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
			cel_type_16 = (level_cel_block >> 12) & 7;
			__asm {
				xor		edx, edx
				xor		ecx, ecx
				mov		edi, dst
				mov		esi, src
			}
			switch ( cel_type_16 )
			{
				case 0: // lower (solid), black
					__asm {
						mov		edx, 20h
						xor		eax, eax
					loc_469414:
						cmp		edi, gpBufEnd
						jb		short loc_469424
						add		esi, 20h
						add		edi, 20h
						jmp		short loc_469431

					loc_469424:
						mov		ecx, 8
					loc_469429:
						mov		[edi], eax
						add		edi, 4
						dec		ecx
						jnz		short loc_469429
					loc_469431:
						sub		edi, 320h
						dec		edx
						jnz		short loc_469414
					}
					break;
				case 1: // lower (solid), black
					__asm {
						mov		ecx, 20h
					loc_469444:
						push	ecx
						mov		edx, 20h
					loc_46944A:
						xor		eax, eax
						mov		al, [esi]
						inc		esi
						test	al, al
						js		short loc_469490
						sub		edx, eax
						cmp		edi, gpBufEnd
						jb		short loc_469463
						add		esi, eax
						add		edi, eax
						jmp		short loc_46948A

					loc_469463:
						mov		ecx, eax
						add		esi, ecx
						xor		eax, eax
						shr		ecx, 1
						jnb		short loc_469474
						mov		[edi], al
						inc		edi
						test	ecx, ecx
						jz		short loc_46948A
					loc_469474:
						shr		ecx, 1
						jnb		short loc_469482
						mov		[edi], ax
						add		edi, 2
						test	ecx, ecx
						jz		short loc_46948A
					loc_469482:
						mov		[edi], eax
						add		edi, 4
						dec		ecx
						jnz		short loc_469482
					loc_46948A:
						test	edx, edx
						jz		short loc_469498
						jmp		short loc_46944A

					loc_469490:
						neg		al
						add		edi, eax
						sub		edx, eax
						jnz		short loc_46944A
					loc_469498:
						pop		ecx
						sub		edi, 320h
						dec		ecx
						jnz		short loc_469444
					}
					break;
				case 2: // lower (solid), black
					__asm {
						mov		edx, 1Eh
						xor		eax, eax
					loc_4694AE:
						cmp		edi, gpBufEnd
						jb		short loc_4694C0
						add		esi, 20h
						sub		esi, edx
						add		edi, 20h
						jmp		short loc_4694E0

					loc_4694C0:
						add		edi, edx
						mov		ecx, 20h
						sub		ecx, edx
						shr		ecx, 2
						jnb		short loc_4694D8
						mov		[edi], ax
						add		edi, 2
						test	ecx, ecx
						jz		short loc_4694E0
					loc_4694D8:
						mov		[edi], eax
						add		edi, 4
						dec		ecx
						jnz		short loc_4694D8
					loc_4694E0:
						sub		edi, 320h
						test	edx, edx
						jz		short loc_4694EF
						sub		edx, 2
						jmp		short loc_4694AE

					loc_4694EF:
						mov		edx, 2
					loc_4694F4:
						cmp		edi, gpBufEnd
						jb		short loc_469506
						add		esi, 20h
						sub		esi, edx
						add		edi, 20h
						jmp		short loc_469526

					loc_469506:
						add		edi, edx
						mov		ecx, 20h
						sub		ecx, edx
						shr		ecx, 2
						jnb		short loc_46951E
						mov		[edi], ax
						add		edi, 2
						test	ecx, ecx
						jz		short loc_469526
					loc_46951E:
						mov		[edi], eax
						add		edi, 4
						dec		ecx
						jnz		short loc_46951E
					loc_469526:
						sub		edi, 320h
						add		edx, 2
						cmp		edx, 20h
						jnz		short loc_4694F4
					}
					break;
				case 3: // lower (solid), black
					__asm {
						mov		edx, 1Eh
						xor		eax, eax
					loc_469540:
						cmp		edi, gpBufEnd
						jb		short loc_469554
						add		esi, 20h
						sub		esi, edx
						add		edi, 20h
						sub		edi, edx
						jmp		short loc_469572

					loc_469554:
						mov		ecx, 20h
						sub		ecx, edx
						shr		ecx, 2
						jnb		short loc_46956A
						mov		[edi], ax
						add		edi, 2
						test	ecx, ecx
						jz		short loc_469572
					loc_46956A:
						mov		[edi], eax
						add		edi, 4
						dec		ecx
						jnz		short loc_46956A
					loc_469572:
						sub		edi, 320h
						test	edx, edx
						jz		short loc_469583
						add		edi, edx
						sub		edx, 2
						jmp		short loc_469540

					loc_469583:
						mov		edx, 2
					loc_469588:
						cmp		edi, gpBufEnd
						jb		short loc_46959C
						add		esi, 20h
						sub		esi, edx
						add		edi, 20h
						sub		edi, edx
						jmp		short loc_4695BA

					loc_46959C:
						mov		ecx, 20h
						sub		ecx, edx
						shr		ecx, 2
						jnb		short loc_4695B2
						mov		[edi], ax
						add		edi, 2
						test	ecx, ecx
						jz		short loc_4695BA
					loc_4695B2:
						mov		[edi], eax
						add		edi, 4
						dec		ecx
						jnz		short loc_4695B2
					loc_4695BA:
						sub		edi, 320h
						add		edi, edx
						add		edx, 2
						cmp		edx, 20h
						jnz		short loc_469588
					}
					break;
				case 4: // lower (solid), black
					__asm {
						mov		edx, 1Eh
						xor		eax, eax
					loc_4695D6:
						cmp		edi, gpBufEnd
						jb		short loc_4695E8
						add		esi, 20h
						sub		esi, edx
						add		edi, 20h
						jmp		short loc_469608

					loc_4695E8:
						add		edi, edx
						mov		ecx, 20h
						sub		ecx, edx
						shr		ecx, 2
						jnb		short loc_469600
						mov		[edi], ax
						add		edi, 2
						test	ecx, ecx
						jz		short loc_469608
					loc_469600:
						mov		[edi], eax
						add		edi, 4
						dec		ecx
						jnz		short loc_469600
					loc_469608:
						sub		edi, 320h
						test	edx, edx
						jz		short loc_469617
						sub		edx, 2
						jmp		short loc_4695D6

					loc_469617:
						mov		edx, 10h
					loc_46961C:
						cmp		edi, gpBufEnd
						jb		short loc_46962C
						add		esi, 20h
						add		edi, 20h
						jmp		short loc_469639

					loc_46962C:
						mov		ecx, 8
					loc_469631:
						mov		[edi], eax
						add		edi, 4
						dec		ecx
						jnz		short loc_469631
					loc_469639:
						sub		edi, 320h
						dec		edx
						jnz		short loc_46961C
					}
					break;
				default: // lower (solid), black
					__asm {
						mov		edx, 1Eh
						xor		eax, eax
					loc_46964B:
						cmp		edi, gpBufEnd
						jb		short loc_46965F
						add		esi, 20h
						sub		esi, edx
						add		edi, 20h
						sub		edi, edx
						jmp		short loc_46967D

					loc_46965F:
						mov		ecx, 20h
						sub		ecx, edx
						shr		ecx, 2
						jnb		short loc_469675
						mov		[edi], ax
						add		edi, 2
						test	ecx, ecx
						jz		short loc_46967D
					loc_469675:
						mov		[edi], eax
						add		edi, 4
						dec		ecx
						jnz		short loc_469675
					loc_46967D:
						sub		edi, 320h
						test	edx, edx
						jz		short loc_46968E
						add		edi, edx
						sub		edx, 2
						jmp		short loc_46964B

					loc_46968E:
						mov		edx, 10h
					loc_469693:
						cmp		edi, gpBufEnd
						jb		short loc_4696A3
						add		esi, 20h
						add		edi, 20h
						jmp		short loc_4696B0

					loc_4696A3:
						mov		ecx, 8
					loc_4696A8:
						mov		[edi], eax
						add		edi, 4
						dec		ecx
						jnz		short loc_4696A8
					loc_4696B0:
						sub		edi, 320h
						dec		edx
						jnz		short loc_469693
					}
					break;
			}
			return;
		}
		if ( !(level_cel_block & 0x8000) )
		{
			src = (unsigned char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
			tbl = (unsigned char *)&pLightTbl[256 * light_table_index];
			cel_type_16 = (unsigned short)level_cel_block >> 12;
			__asm {
				xor		edx, edx
				xor		ecx, ecx
				mov		ebx, tbl
				mov		edi, dst
				mov		esi, src
			}
			switch ( cel_type_16 )
			{
				case 0: // lower (solid), with lighting
					__asm {
						mov		edx, 20h
						push	ebp
					loc_468B09:
						push	edx
						cmp		edi, gpBufEnd
						jb		short loc_468B1A
						add		esi, 20h
						add		edi, 20h
						jmp		short loc_468B4B

					loc_468B1A:
						xor		edx, edx
						mov		ebp, 8
					loc_468B21:
						mov		eax, [esi]
						add		esi, 4
						ror		eax, 10h
						mov		dl, al
						mov		cl, [ebx+edx]
						mov		dl, ah
						mov		ch, [ebx+edx]
						ror		eax, 10h
						shl		ecx, 10h
						mov		dl, al
						mov		cl, [ebx+edx]
						mov		dl, ah
						mov		ch, [ebx+edx]
						mov		[edi], ecx
						add		edi, 4
						dec		ebp
						jnz		short loc_468B21
					loc_468B4B:
						sub		edi, 320h
						pop		edx
						dec		edx
						jnz		short loc_468B09
						pop		ebp
					}
					break;
				case 1: // lower (solid), with lighting
					__asm {
						push	ebp
						mov		ecx, 20h
					loc_468B61:
						push	ecx
						mov		ebp, 20h
					loc_468B67:
						xor		eax, eax
						mov		al, [esi]
						inc		esi
						test	al, al
						jns		short loc_468B78
						neg		al
						add		edi, eax
						sub		ebp, eax
						jmp		short loc_468BEA

					loc_468B78:
						sub		ebp, eax
						cmp		edi, gpBufEnd
						jb		short loc_468B88
						add		esi, eax
						add		edi, eax
						jmp		short loc_468BEA

					loc_468B88:
						mov		ecx, eax
						cmp		cl, 4
						jl		short loc_468BC1
					loc_468B8F:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						mov		ch, [ebx+edx]
						mov		dl, ah
						ror		eax, 10h
						mov		[edi], ch
						mov		ch, [ebx+edx]
						mov		dl, al
						mov		[edi+1], ch
						mov		ch, [ebx+edx]
						mov		dl, ah
						mov		[edi+2], ch
						mov		ch, [ebx+edx]
						mov		[edi+3], ch
						add		edi, 4
						sub		cl, 4
						cmp		cl, 4
						jge		short loc_468B8F
					loc_468BC1:
						cmp		cl, 2
						jl		short loc_468BDC
						mov		dl, [esi]
						mov		ch, [ebx+edx]
						mov		[edi], ch
						mov		dl, [esi+1]
						mov		ch, [ebx+edx]
						mov		[edi+1], ch
						add		esi, 2
						add		edi, 2
					loc_468BDC:
						and		cl, 1
						jz		short loc_468BEA
						mov		dl, [esi]
						inc		esi
						mov		dl, [ebx+edx]
						mov		[edi], dl
						inc		edi
					loc_468BEA:
						test	ebp, ebp
						jnz		loc_468B67
						pop		ecx
						sub		edi, 320h
						dec		ecx
						jnz		loc_468B61
						pop		ebp
					}
					break;
				case 2: // lower (solid), with lighting
					__asm {
						push	ebp
						mov		ebp, 1Eh
						mov		eax, edi
						sub		eax, gpBufEnd
						jb		short loc_468C4E
						add		eax, 3FFh
						shr		eax, 8
						cmp		eax, 2Dh
						jg		short loc_468C40
						mov		ecx, WorldTbl3x16[eax*4]
						mov		eax, ecx
						add		esi, WorldTbl17_1[ecx]
						shl		eax, 6
						lea		eax, [eax+eax*2]
						shr		ecx, 1
						sub		edi, eax
						sub		ebp, ecx
						jmp		short loc_468C4E

					loc_468C40:
						sub		edi, 3000h
						add		esi, 120h
						jmp		short loc_468C75

					loc_468C4E:
						add		edi, ebp
						mov		ecx, 20h
						sub		ecx, ebp
						mov		edx, ecx
						and		edx, 2
						add		esi, edx
					loc_468C5E:
						mov		dl, [esi]
						inc		esi
						mov		dl, [ebx+edx]
						mov		[edi], dl
						inc		edi
						dec		ecx
						jnz		short loc_468C5E
						sub		edi, 320h
						sub		ebp, 2
						jge		short loc_468C4E
					loc_468C75:
						mov		ebp, 2
						mov		eax, edi
						sub		eax, gpBufEnd
						jb		short loc_468CBC
						add		eax, 3FFh
						shr		eax, 8
						cmp		eax, 2Ah
						jg		short loc_468CAE
						mov		ecx, WorldTbl3x16[eax*4]
						mov		eax, ecx
						add		esi, WorldTbl17_2[ecx]
						shl		eax, 6
						lea		eax, [eax+eax*2]
						shr		ecx, 1
						sub		edi, eax
						add		ebp, ecx
						jmp		short loc_468CBC

					loc_468CAE:
						sub		edi, 2D00h
						add		esi, 100h
						jmp		short loc_468CE6

					loc_468CBC:
						add		edi, ebp
						mov		ecx, 20h
						sub		ecx, ebp
						mov		edx, ecx
						and		edx, 2
						add		esi, edx
					loc_468CCC:
						mov		dl, [esi]
						inc		esi
						mov		dl, [ebx+edx]
						mov		[edi], dl
						inc		edi
						dec		ecx
						jnz		short loc_468CCC
						add		ebp, 2
						sub		edi, 320h
						cmp		ebp, 20h
						jnz		short loc_468CBC
					loc_468CE6:
						pop		ebp
					}
					break;
				case 3: // lower (solid), with lighting
					__asm {
						push	ebp
						mov		ebp, 1Eh
						mov		eax, edi
						sub		eax, gpBufEnd
						jb		short loc_468D34
						add		eax, 3FFh
						shr		eax, 8
						cmp		eax, 2Dh
						jg		short loc_468D26
						mov		ecx, WorldTbl3x16[eax*4]
						mov		eax, ecx
						add		esi, WorldTbl17_1[ecx]
						shl		eax, 6
						lea		eax, [eax+eax*2]
						shr		ecx, 1
						sub		edi, eax
						sub		ebp, ecx
						jmp		short loc_468D34

					loc_468D26:
						sub		edi, 3000h
						add		esi, 120h
						jmp		short loc_468D5B

					loc_468D34:
						mov		ecx, 20h
						sub		ecx, ebp
					loc_468D3B:
						mov		dl, [esi]
						inc		esi
						mov		dl, [ebx+edx]
						mov		[edi], dl
						inc		edi
						dec		ecx
						jnz		short loc_468D3B
						mov		edx, esi
						and		edx, 2
						add		esi, edx
						sub		edi, 320h
						add		edi, ebp
						sub		ebp, 2
						jge		short loc_468D34
					loc_468D5B:
						mov		ebp, 2
						mov		eax, edi
						sub		eax, gpBufEnd
						jb		short loc_468DA2
						add		eax, 3FFh
						shr		eax, 8
						cmp		eax, 2Ah
						jg		short loc_468D94
						mov		ecx, WorldTbl3x16[eax*4]
						mov		eax, ecx
						add		esi, WorldTbl17_2[ecx]
						shl		eax, 6
						lea		eax, [eax+eax*2]
						shr		ecx, 1
						sub		edi, eax
						add		ebp, ecx
						jmp		short loc_468DA2

					loc_468D94:
						sub		edi, 2D00h
						add		esi, 100h
						jmp		short loc_468DCC

					loc_468DA2:
						mov		ecx, 20h
						sub		ecx, ebp
					loc_468DA9:
						mov		dl, [esi]
						inc		esi
						mov		dl, [ebx+edx]
						mov		[edi], dl
						inc		edi
						dec		ecx
						jnz		short loc_468DA9
						mov		edx, esi
						and		edx, 2
						add		esi, edx
						sub		edi, 320h
						add		edi, ebp
						add		ebp, 2
						cmp		ebp, 20h
						jnz		short loc_468DA2
					loc_468DCC:
						pop		ebp
					}
					break;
				case 4: // lower (solid), with lighting
					__asm {
						push	ebp
						mov		ebp, 1Eh
						mov		eax, edi
						sub		eax, gpBufEnd
						jb		short loc_468E1A
						add		eax, 3FFh
						shr		eax, 8
						cmp		eax, 2Dh
						jg		short loc_468E0C
						mov		ecx, WorldTbl3x16[eax*4]
						mov		eax, ecx
						add		esi, WorldTbl17_1[ecx]
						shl		eax, 6
						lea		eax, [eax+eax*2]
						shr		ecx, 1
						sub		edi, eax
						sub		ebp, ecx
						jmp		short loc_468E1A

					loc_468E0C:
						sub		edi, 3000h
						add		esi, 120h
						jmp		short loc_468E87

					loc_468E1A:
						add		edi, ebp
						mov		ecx, 20h
						sub		ecx, ebp
						mov		edx, ecx
						and		edx, 2
						add		esi, edx
						cmp		cl, 4
						jl		short loc_468E61
					loc_468E2F:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						mov		ch, [ebx+edx]
						mov		dl, ah
						ror		eax, 10h
						mov		[edi], ch
						mov		ch, [ebx+edx]
						mov		dl, al
						mov		[edi+1], ch
						mov		ch, [ebx+edx]
						mov		dl, ah
						mov		[edi+2], ch
						mov		ch, [ebx+edx]
						mov		[edi+3], ch
						add		edi, 4
						sub		cl, 4
						cmp		cl, 4
						jge		short loc_468E2F
					loc_468E61:
						cmp		cl, 2
						jl		short loc_468E7C
						mov		dl, [esi]
						mov		ch, [ebx+edx]
						mov		[edi], ch
						mov		dl, [esi+1]
						mov		ch, [ebx+edx]
						mov		[edi+1], ch
						add		esi, 2
						add		edi, 2
					loc_468E7C:
						sub		edi, 320h
						sub		ebp, 2
						jge		short loc_468E1A
					loc_468E87:
						mov		ebp, 10h
					loc_468E8C:
						cmp		edi, gpBufEnd
						jb		short loc_468E9C
						add		esi, 20h
						add		edi, 20h
						jmp		short loc_468ED3

					loc_468E9C:
						mov		ecx, 20h
					loc_468EA1:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						mov		ch, [ebx+edx]
						mov		dl, ah
						ror		eax, 10h
						mov		[edi], ch
						mov		ch, [ebx+edx]
						mov		dl, al
						mov		[edi+1], ch
						mov		ch, [ebx+edx]
						mov		dl, ah
						mov		[edi+2], ch
						mov		ch, [ebx+edx]
						mov		[edi+3], ch
						add		edi, 4
						sub		cl, 4
						cmp		cl, 4
						jge		short loc_468EA1
					loc_468ED3:
						sub		edi, 320h
						dec		ebp
						jnz		short loc_468E8C
						pop		ebp
					}
					break;
				default: // lower (solid), with lighting
					__asm {
						push	ebp
						mov		ebp, 1Eh
						mov		eax, edi
						sub		eax, gpBufEnd
						jb		short loc_468F2A
						add		eax, 3FFh
						shr		eax, 8
						cmp		eax, 2Dh
						jg		short loc_468F1C
						mov		ecx, WorldTbl3x16[eax*4]
						mov		eax, ecx
						add		esi, WorldTbl17_1[ecx]
						shl		eax, 6
						lea		eax, [eax+eax*2]
						shr		ecx, 1
						sub		edi, eax
						sub		ebp, ecx
						jmp		short loc_468F2A

					loc_468F1C:
						sub		edi, 3000h
						add		esi, 120h
						jmp		short loc_468F97

					loc_468F2A:
						mov		ecx, 20h
						sub		ecx, ebp
						cmp		cl, 4
						jl		short loc_468F68
					loc_468F36:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						mov		ch, [ebx+edx]
						mov		dl, ah
						ror		eax, 10h
						mov		[edi], ch
						mov		ch, [ebx+edx]
						mov		dl, al
						mov		[edi+1], ch
						mov		ch, [ebx+edx]
						mov		dl, ah
						mov		[edi+2], ch
						mov		ch, [ebx+edx]
						mov		[edi+3], ch
						add		edi, 4
						sub		cl, 4
						cmp		cl, 4
						jge		short loc_468F36
					loc_468F68:
						cmp		cl, 2
						jl		short loc_468F83
						mov		dl, [esi]
						mov		ch, [ebx+edx]
						mov		[edi], ch
						mov		dl, [esi+1]
						mov		ch, [ebx+edx]
						mov		[edi+1], ch
						add		esi, 2
						add		edi, 2
					loc_468F83:
						mov		edx, esi
						and		edx, 2
						add		esi, edx
						sub		edi, 320h
						add		edi, ebp
						sub		ebp, 2
						jge		short loc_468F2A
					loc_468F97:
						mov		ebp, 10h
					loc_468F9C:
						cmp		edi, gpBufEnd
						jb		short loc_468FAC
						add		esi, 20h
						add		edi, 20h
						jmp		short loc_468FE3

					loc_468FAC:
						mov		ecx, 20h
					loc_468FB1:
						mov		eax, [esi]
						add		esi, 4
						mov		dl, al
						mov		ch, [ebx+edx]
						mov		dl, ah
						ror		eax, 10h
						mov		[edi], ch
						mov		ch, [ebx+edx]
						mov		dl, al
						mov		[edi+1], ch
						mov		ch, [ebx+edx]
						mov		dl, ah
						mov		[edi+2], ch
						mov		ch, [ebx+edx]
						mov		[edi+3], ch
						add		edi, 4
						sub		cl, 4
						cmp		cl, 4
						jge		short loc_468FB1
					loc_468FE3:
						sub		edi, 320h
						dec		ebp
						jnz		short loc_468F9C
						pop		ebp
					}
					break;
			}
			return;
		}
		src = (unsigned char *)pSpeedCels
				   + *(_DWORD *)&gpCelFrame[4 * (light_table_index + 16 * (level_cel_block & 0xFFF))];
		cel_type_16 = (unsigned short)level_cel_block >> 12;
	}
	else
	{
		if ( level_cel_block & 0x8000 )
			level_cel_block = *(_DWORD *)&gpCelFrame[64 * (level_cel_block & 0xFFF)]
							+ (unsigned short)(level_cel_block & 0xF000);
		src = (unsigned char *)pDungeonCels + *((_DWORD *)pDungeonCels + (level_cel_block & 0xFFF));
		cel_type_16 = (((unsigned int)level_cel_block >> 12) & 7) + 8;
	}
	__asm {
		xor		edx, edx
		xor		ecx, ecx
		mov		edi, dst
		mov		esi, src
	}
	switch ( cel_type_16 )
	{
		case 8: // lower (solid), without lighting
			__asm {
				mov		edx, 20h
			loc_468FF7:
				cmp		edi, gpBufEnd
				jb		short loc_469007
				add		esi, 20h
				add		edi, 20h
				jmp		short loc_469019

			loc_469007:
				mov		ecx, 8
			loc_46900C:
				mov		eax, [esi]
				add		esi, 4
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_46900C
			loc_469019:
				sub		edi, 320h
				dec		edx
				jnz		short loc_468FF7
			}
			break;
		case 9: // lower (solid), without lighting
			__asm {
				mov		ecx, 20h
			loc_46902C:
				push	ecx
				mov		edx, 20h
			loc_469032:
				xor		eax, eax
				mov		al, [esi]
				inc		esi
				test	al, al
				js		short loc_469082
				sub		edx, eax
				cmp		edi, gpBufEnd
				jb		short loc_46904B
				add		esi, eax
				add		edi, eax
				jmp		short loc_46907C

			loc_46904B:
				mov		ecx, eax
				shr		ecx, 1
				jnb		short loc_46905B
				mov		al, [esi]
				inc		esi
				mov		[edi], al
				inc		edi
				test	ecx, ecx
				jz		short loc_46907C
			loc_46905B:
				shr		ecx, 1
				jnb		short loc_46906F
				mov		ax, [esi]
				add		esi, 2
				mov		[edi], ax
				add		edi, 2
				test	ecx, ecx
				jz		short loc_46907C
			loc_46906F:
				mov		eax, [esi]
				add		esi, 4
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_46906F
			loc_46907C:
				test	edx, edx
				jz		short loc_46908A
				jmp		short loc_469032

			loc_469082:
				neg		al
				add		edi, eax
				sub		edx, eax
				jnz		short loc_469032
			loc_46908A:
				pop		ecx
				sub		edi, 320h
				dec		ecx
				jnz		short loc_46902C
			}
			break;
		case 10: // lower (solid), without lighting
			__asm {
				mov		edx, 1Eh
				mov		eax, edi
				sub		eax, gpBufEnd
				jb		short loc_4690E0
				add		eax, 3FFh
				shr		eax, 8
				cmp		eax, 2Dh
				jg		short loc_4690D2
				mov		ecx, WorldTbl3x16[eax*4]
				mov		eax, ecx
				add		esi, WorldTbl17_1[ecx]
				shl		eax, 6
				lea		eax, [eax+eax*2]
				shr		ecx, 1
				sub		edi, eax
				sub		edx, ecx
				jmp		short loc_4690E0

			loc_4690D2:
				sub		edi, 3000h
				add		esi, 120h
				jmp		short loc_469117

			loc_4690E0:
				add		edi, edx
				mov		ecx, 20h
				sub		ecx, edx
				shr		ecx, 2
				jnb		short loc_4690FF
				mov		ax, [esi+2]
				add		esi, 4
				mov		[edi], ax
				add		edi, 2
				test	ecx, ecx
				jz		short loc_46910C
			loc_4690FF:
				mov		eax, [esi]
				add		esi, 4
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_4690FF
			loc_46910C:
				sub		edi, 320h
				sub		edx, 2
				jge		short loc_4690E0
			loc_469117:
				mov		edx, 2
				mov		eax, edi
				sub		eax, gpBufEnd
				jb		short loc_46915E
				add		eax, 3FFh
				shr		eax, 8
				cmp		eax, 2Ah
				jg		short loc_469150
				mov		ecx, WorldTbl3x16[eax*4]
				mov		eax, ecx
				add		esi, WorldTbl17_2[ecx]
				shl		eax, 6
				lea		eax, [eax+eax*2]
				shr		ecx, 1
				sub		edi, eax
				add		edx, ecx
				jmp		short loc_46915E

			loc_469150:
				sub		edi, 2D00h
				add		esi, 100h
				jmp		short ret_469198_10S

			loc_46915E:
				mov		ecx, 20h
				add		edi, edx
				sub		ecx, edx
				shr		ecx, 2
				jnb		short loc_46917D
				mov		ax, [esi+2]
				add		esi, 4
				mov		[edi], ax
				add		edi, 2
				test	ecx, ecx
				jz		short loc_46918A
			loc_46917D:
				mov		eax, [esi]
				add		esi, 4
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_46917D
			loc_46918A:
				add		edx, 2
				sub		edi, 320h
				cmp		edx, 20h
				jl		short loc_46915E
			ret_469198_10S:
			}
			break;
		case 11: // lower (solid), without lighting
			__asm {
				mov		edx, 1Eh
				mov		eax, edi
				sub		eax, gpBufEnd
				jb		short loc_4691E4
				add		eax, 3FFh
				shr		eax, 8
				cmp		eax, 2Dh
				jg		short loc_4691D6
				mov		ecx, WorldTbl3x16[eax*4]
				mov		eax, ecx
				add		esi, WorldTbl17_1[ecx]
				shl		eax, 6
				lea		eax, [eax+eax*2]
				shr		ecx, 1
				sub		edi, eax
				sub		edx, ecx
				jmp		short loc_4691E4

			loc_4691D6:
				sub		edi, 3000h
				add		esi, 120h
				jmp		short loc_46921D

			loc_4691E4:
				mov		ecx, 20h
				sub		ecx, edx
				mov		ebx, ecx
				shr		ecx, 2
				jz		short loc_4691FF
			loc_4691F2:
				mov		eax, [esi]
				add		esi, 4
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_4691F2
			loc_4691FF:
				and		ebx, 2
				jz		short loc_469210
				mov		ax, [esi]
				add		esi, 4
				mov		[edi], ax
				add		edi, 2
			loc_469210:
				add		edi, edx
				sub		edi, 320h
				sub		edx, 2
				jge		short loc_4691E4
			loc_46921D:
				mov		edx, 2
				mov		eax, edi
				sub		eax, gpBufEnd
				jb		short loc_469264
				add		eax, 3FFh
				shr		eax, 8
				cmp		eax, 2Ah
				jg		short loc_469256
				mov		ecx, WorldTbl3x16[eax*4]
				mov		eax, ecx
				add		esi, WorldTbl17_2[ecx]
				shl		eax, 6
				lea		eax, [eax+eax*2]
				shr		ecx, 1
				sub		edi, eax
				add		edx, ecx
				jmp		short loc_469264

			loc_469256:
				sub		edi, 2D00h
				add		esi, 100h
				jmp		short ret_4692A0_11S

			loc_469264:
				mov		ecx, 20h
				sub		ecx, edx
				mov		ebx, ecx
				shr		ecx, 2
				jz		short loc_46927F
			loc_469272:
				mov		eax, [esi]
				add		esi, 4
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_469272
			loc_46927F:
				and		ebx, 2
				jz		short loc_469290
				mov		ax, [esi]
				add		esi, 4
				mov		[edi], ax
				add		edi, 2
			loc_469290:
				add		edi, edx
				add		edx, 2
				sub		edi, 320h
				cmp		edx, 20h
				jl		short loc_469264
			ret_4692A0_11S:
			}
			break;
		case 12: // lower (solid), without lighting
			__asm {
				mov		edx, 1Eh
				mov		eax, edi
				sub		eax, gpBufEnd
				jb		short loc_4692EC
				add		eax, 3FFh
				shr		eax, 8
				cmp		eax, 2Dh
				jg		short loc_4692DE
				mov		ecx, WorldTbl3x16[eax*4]
				mov		eax, ecx
				add		esi, WorldTbl17_1[ecx]
				shl		eax, 6
				lea		eax, [eax+eax*2]
				shr		ecx, 1
				sub		edi, eax
				sub		edx, ecx
				jmp		short loc_4692EC

			loc_4692DE:
				sub		edi, 3000h
				add		esi, 120h
				jmp		short loc_469323

			loc_4692EC:
				add		edi, edx
				mov		ecx, 20h
				sub		ecx, edx
				shr		ecx, 2
				jnb		short loc_46930B
				mov		ax, [esi+2]
				add		esi, 4
				mov		[edi], ax
				add		edi, 2
				test	ecx, ecx
				jz		short loc_469318
			loc_46930B:
				mov		eax, [esi]
				add		esi, 4
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_46930B
			loc_469318:
				sub		edi, 320h
				sub		edx, 2
				jge		short loc_4692EC
			loc_469323:
				mov		edx, 10h
			loc_469328:
				cmp		edi, gpBufEnd
				jb		short loc_469338
				add		esi, 20h
				add		edi, 20h
				jmp		short loc_46934A

			loc_469338:
				mov		ecx, 8
			loc_46933D:
				mov		eax, [esi]
				add		esi, 4
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_46933D
			loc_46934A:
				sub		edi, 320h
				dec		edx
				jnz		short loc_469328
			}
			break;
		default: // lower (solid), without lighting
			__asm {
				mov		edx, 1Eh
				mov		eax, edi
				sub		eax, gpBufEnd
				jb		short loc_46939F
				add		eax, 3FFh
				shr		eax, 8
				cmp		eax, 2Dh
				jg		short loc_469391
				mov		ecx, WorldTbl3x16[eax*4]
				mov		eax, ecx
				add		esi, WorldTbl17_1[ecx]
				shl		eax, 6
				lea		eax, [eax+eax*2]
				shr		ecx, 1
				sub		edi, eax
				sub		edx, ecx
				jmp		short loc_46939F

			loc_469391:
				sub		edi, 3000h
				add		esi, 120h
				jmp		short loc_4693D8

			loc_46939F:
				mov		ecx, 20h
				sub		ecx, edx
				mov		ebx, ecx
				shr		ecx, 2
				jz		short loc_4693BA
			loc_4693AD:
				mov		eax, [esi]
				add		esi, 4
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_4693AD
			loc_4693BA:
				and		ebx, 2
				jz		short loc_4693CB
				mov		ax, [esi]
				add		esi, 4
				mov		[edi], ax
				add		edi, 2
			loc_4693CB:
				sub		edi, 320h
				add		edi, edx
				sub		edx, 2
				jge		short loc_46939F
			loc_4693D8:
				mov		edx, 10h
			loc_4693DD:
				cmp		edi, gpBufEnd
				jb		short loc_4693ED
				add		esi, 20h
				add		edi, 20h
				jmp		short loc_4693FF

			loc_4693ED:
				mov		ecx, 8
			loc_4693F2:
				mov		eax, [esi]
				add		esi, 4
				mov		[edi], eax
				add		edi, 4
				dec		ecx
				jnz		short loc_4693F2
			loc_4693FF:
				sub		edi, 320h
				dec		edx
				jnz		short loc_4693DD
			}
			break;
	}
}

void __fastcall world_draw_black_tile(unsigned char *pbDst)
{
	__asm {
		mov		edi, ecx
		mov		edx, 1Eh
		mov		ebx, 1
		xor		eax, eax
	loc_4696D0:
		add		edi, edx
		mov		ecx, ebx
	loc_4696D4:
		mov		[edi], eax
		add		edi, 4
		dec		ecx
		jnz		short loc_4696D4
		add		edi, edx
		sub		edi, 340h
		test	edx, edx
		jz		short loc_4696EE
		sub		edx, 2
		inc		ebx
		jmp		short loc_4696D0

	loc_4696EE:
		mov		edx, 2
		mov		ebx, 0Fh
	loc_4696F8:
		add		edi, edx
		mov		ecx, ebx
	loc_4696FC:
		mov		[edi], eax
		add		edi, 4
		dec		ecx
		jnz		short loc_4696FC
		add		edi, edx
		sub		edi, 340h
		dec		ebx
		add		edx, 2
		cmp		edx, 20h
		jnz		short loc_4696F8
	}
}
