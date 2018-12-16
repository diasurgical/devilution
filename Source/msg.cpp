//HEADER_GOES_HERE

#include "../types.h"

static DWORD sgdwOwnerWait;
static DWORD sgdwRecvOffset;
static int sgnCurrMegaPlayer;
static DLevel sgLevels[NUMLEVELS];
static BYTE sbLastCmd;
static TMegaPkt *sgpCurrPkt;
static char sgRecvBuf[sizeof(DLevel) + 1];
static BYTE sgbRecvCmd;
static LocalLevel sgLocals[NUMLEVELS];
static DJunk sgJunk;
static TMegaPkt *sgpMegaPkt;
static BYTE sgbDeltaChanged;
static BYTE sgbDeltaChunks;
int deltaload;
BYTE gbBufferMsgs;
int pkt_counter;

static float msg_cpp_init_value = INFINITY;

void __fastcall msg_send_drop_pkt(int pnum, int reason)
{
	TFakeDropPlr cmd;

	cmd.dwReason = reason;
	cmd.bCmd = FAKE_CMD_DROPID;
	cmd.bPlr = pnum;
	msg_send_packet(pnum, &cmd, sizeof(cmd));
}

void __fastcall msg_send_packet(int pnum, const void *packet, DWORD dwSize)
{
	TMegaPkt *packeta;
	TFakeCmdPlr cmd;

	if (pnum != sgnCurrMegaPlayer) {
		sgnCurrMegaPlayer = pnum;
		cmd.bCmd = FAKE_CMD_SETID;
		cmd.bPlr = pnum;
		msg_send_packet(pnum, &cmd, sizeof(cmd));
	}
	packeta = sgpCurrPkt;
	if (sgpCurrPkt->dwSpaceLeft < dwSize) {
		msg_get_next_packet();
		packeta = sgpCurrPkt;
	}
	memcpy((char *)&packeta[1] - packeta->dwSpaceLeft, packet, dwSize);
	sgpCurrPkt->dwSpaceLeft -= dwSize;
}
// 65AB24: using guessed type int sgnCurrMegaPlayer;

TMegaPkt *__cdecl msg_get_next_packet()
{
	TMegaPkt *result;

	sgpCurrPkt = (TMegaPkt *)DiabloAllocPtr(32008);
	sgpCurrPkt->pNext = 0;
	sgpCurrPkt->dwSpaceLeft = 32000;

	result = (TMegaPkt *)&sgpMegaPkt;
	while (result->pNext) {
		result = result->pNext;
	}
	result->pNext = sgpCurrPkt;

	return result;
}

BOOL __cdecl msg_wait_resync()
{
	int v0; // eax

	msg_get_next_packet();
	sgbDeltaChunks = 0;
	sgnCurrMegaPlayer = -1;
	sgbRecvCmd = CMD_DLEVEL_END;
	gbBufferMsgs = 1;
	sgdwOwnerWait = GetTickCount();
	v0 = UiProgressDialog(ghMainWnd, "Waiting for game data...", 1, msg_wait_for_turns, 20);
	gbBufferMsgs = 0;
	if (!v0)
		goto LABEL_6;
	if (gbGameDestroyed) {
		DrawDlg("The game ended");
	LABEL_6:
		msg_free_packets();
		return 0;
	}
	if (sgbDeltaChunks != 21) {
		DrawDlg("Unable to get level data");
		goto LABEL_6;
	}
	return 1;
}
// 65AB18: using guessed type int sgdwOwnerWait;
// 65AB24: using guessed type int sgnCurrMegaPlayer;
// 67618D: using guessed type char sgbDeltaChunks;
// 676194: using guessed type char gbBufferMsgs;
// 67862D: using guessed type char gbGameDestroyed;

void __cdecl msg_free_packets()
{
	TMegaPkt *v0; // eax
	TMegaPkt *v1; // ecx

	v0 = sgpMegaPkt;
	while (v0) {
		v1 = v0->pNext;
		sgpMegaPkt = 0;
		sgpCurrPkt = v1;
		mem_free_dbg(v0);
		v0 = sgpCurrPkt;
		sgpMegaPkt = sgpCurrPkt;
	}
}

int __cdecl msg_wait_for_turns()
{
	int recieved;
	DWORD turns;

	if (!sgbDeltaChunks) {
		nthread_send_and_recv_turn(0, 0);
		if (!SNetGetOwnerTurnsWaiting(&turns) && SErrGetLastError() == STORM_ERROR_NOT_IN_GAME)
			return 100;
		if (GetTickCount() - sgdwOwnerWait <= 2000 && turns < gdwTurnsInTransit)
			return 0;
		sgbDeltaChunks++;
	}
	multi_process_network_packets();
	nthread_send_and_recv_turn(0, 0);
	if (nthread_has_500ms_passed(0))
		nthread_recv_turns(&recieved);

	if (gbGameDestroyed)
		return 100;
	if (gbDeltaSender >= MAX_PLRS) {
		sgbDeltaChunks = 0;
		sgbRecvCmd = CMD_DLEVEL_END;
		gbDeltaSender = myplr;
		nthread_set_turn_upper_bit();
	}
	if (sgbDeltaChunks == 20) {
		sgbDeltaChunks = 21;
		return 99;
	}
	return 100 * sgbDeltaChunks / 21;
}
// 65AB18: using guessed type int sgdwOwnerWait;
// 67618D: using guessed type char sgbDeltaChunks;
// 67862D: using guessed type char gbGameDestroyed;
// 6796E4: using guessed type char gbDeltaSender;
// 679738: using guessed type int gdwTurnsInTransit;

void __cdecl msg_process_net_packets()
{
	if (gbMaxPlayers != 1) {
		gbBufferMsgs = 2;
		msg_pre_packet();
		gbBufferMsgs = 0;
		msg_free_packets();
	}
}
// 676194: using guessed type char gbBufferMsgs;
// 679660: using guessed type char gbMaxPlayers;

void __cdecl msg_pre_packet()
{
	int i;
	int spaceLeft, pktSize;
	TMegaPkt *pkt;
	TFakeCmdPlr *cmd, *tmpCmd;
	TFakeDropPlr *dropCmd;

	pkt = sgpMegaPkt;
	for (i = -1; pkt; pkt = pkt->pNext) {
		spaceLeft = 32000;
		cmd = (TFakeCmdPlr *)pkt->data;
		while (spaceLeft != pkt->dwSpaceLeft) {
			if (cmd->bCmd == FAKE_CMD_SETID) {
				tmpCmd = cmd;
				cmd++;
				i = tmpCmd->bPlr;
				spaceLeft -= sizeof(*cmd);
			} else if (cmd->bCmd == FAKE_CMD_DROPID) {
				dropCmd = (TFakeDropPlr *)cmd;
				cmd += 3;
				spaceLeft -= sizeof(*dropCmd);
				multi_player_left(dropCmd->bPlr, dropCmd->dwReason);
			} else {
				pktSize = ParseCmd(i, (TCmd *)cmd);
				cmd = (TFakeCmdPlr *)((char *)cmd + pktSize);
				spaceLeft -= pktSize;
			}
		}
	}
}

void __fastcall DeltaExportData(int pnum)
{
	char *v1;       // edi
	DObjectStr *v2; // esi
	void *v3;       // ebx
	void *v4;       // eax
	void *v5;       // eax
	void *v6;       // eax
	int v7;         // eax
	void *v8;       // eax
	int v9;         // eax
	int player_num; // [esp+0h] [ebp-Ch]
	int v11;        // [esp+4h] [ebp-8h]
	char src;       // [esp+Bh] [ebp-1h]

	player_num = pnum;
	if (sgbDeltaChanged) {
		v11 = 0;
		v1 = (char *)DiabloAllocPtr(4722);
		v2 = sgLevels[0].object;
		v3 = v1 + 1;
		do {
			v4 = DeltaExportItem(v3, &v2[-2794]);
			v5 = DeltaExportObject(v4, v2);
			v6 = DeltaExportMonster(v5, &v2[127]);
			v7 = msg_comp_level(v1, v6);
			dthread_send_delta(player_num, (_BYTE)v11++ + CMD_DLEVEL_0, v1, v7);
			v2 += 4721;
		} while ((signed int)v2 < (signed int)&sgLevels[NUMLEVELS].object);
		v8 = DeltaExportJunk(v3);
		v9 = msg_comp_level(v1, v8);
		dthread_send_delta(player_num, CMD_DLEVEL_JUNK, v1, v9);
		mem_free_dbg(v1);
	}
	src = 0;
	dthread_send_delta(player_num, CMD_DLEVEL_END, &src, 1);
}
// 67618C: using guessed type char sgbDeltaChanged;

void *__fastcall DeltaExportItem(void *dst, void *src)
{
	_BYTE *v2;     // edi
	_BYTE *v3;     // esi
	signed int v4; // ebx

	v2 = (unsigned char *)src;
	v3 = (unsigned char *)dst;
	v4 = 127;
	do {
		if (*v2 == -1) {
			*v3++ = -1;
		} else {
			memcpy(v3, v2, 0x16u);
			v3 += 22;
		}
		v2 += 22;
		--v4;
	} while (v4);
	return v3;
}

void *__fastcall DeltaExportObject(void *dst, void *src)
{
	char *v2; // esi

	v2 = (char *)dst;
	memcpy(dst, src, 0x7Fu);
	return v2 + 127;
}

void *__fastcall DeltaExportMonster(void *dst, void *src)
{
	_BYTE *v2;     // edi
	_BYTE *v3;     // esi
	signed int v4; // ebx

	v2 = (unsigned char *)src;
	v3 = (unsigned char *)dst;
	v4 = MAXMONSTERS;
	do {
		if (*v2 == -1) {
			*v3++ = -1;
		} else {
			memcpy(v3, v2, 9u);
			v3 += 9;
		}
		v2 += 9;
		--v4;
	} while (v4);
	return v3;
}

void *__fastcall DeltaExportJunk(void *dst)
{
	char *v1;          // ebx
	DJunk *v2;         // edi
	MultiQuests *v3;   // esi
	unsigned char *v4; // edi
	int *v5;           // ebp

	v1 = (char *)dst;
	v2 = &sgJunk;
	v3 = sgJunk.quests;
	do {
		if (v2->portal[0].x == LOBYTE(-1)) {
			*v1++ = -1;
		} else {
			memcpy(v1, v2, 5u);
			v1 += 5;
		}
		v2 = (DJunk *)((char *)v2 + 5);
	} while ((signed int)v2 < (signed int)sgJunk.quests);
	v4 = &quests[0]._qactive;
	v5 = &questlist[0]._qflags;
	do {
		if (*(_BYTE *)v5 & 1) {
			v3->qlog = v4[18];
			v3->qstate = *v4;
			v3->qvar1 = v4[13];
			memcpy(v1, v3, 3u);
			v1 += 3;
			++v3;
		}
		v5 += 5;
		v4 += 24;
	} while ((signed int)v5 < (signed int)&questlist[16]._qflags);
	return v1;
}

int __fastcall msg_comp_level(char *begin, void *end)
{
	char *v2; // esi
	int v3;   // edi
	int v4;   // eax

	v2 = begin;
	v3 = (char *)end - begin - 1;
	v4 = PkwareCompress(begin + 1, v3);
	*v2 = v3 != v4;
	return v4 + 1;
}

void __cdecl delta_init()
{
	sgbDeltaChanged = 0;
	memset(&sgJunk, 255, sizeof(sgJunk));
	memset(sgLevels, 255, sizeof(sgLevels));
	memset(sgLocals, 0, sizeof(sgLocals));
	deltaload = 0;
}
// 67618C: using guessed type char sgbDeltaChanged;
// 676190: using guessed type int deltaload;

void __fastcall delta_kill_monster(int mi, BYTE x, BYTE y, BYTE bLevel)
{
	DMonsterStr *pD;

	if (gbMaxPlayers != 1) {
		sgbDeltaChanged = 1;
		pD = &sgLevels[bLevel].monster[mi];
		pD->_mx = x;
		pD->_my = y;
		pD->_mdir = monster[mi]._mdir;
		pD->_mhitpoints = 0;
	}
}
// 67618C: using guessed type char sgbDeltaChanged;
// 679660: using guessed type char gbMaxPlayers;

void __fastcall delta_monster_hp(int mi, int hp, BYTE bLevel)
{
	DMonsterStr *pD;

	if (gbMaxPlayers != 1) {
		sgbDeltaChanged = 1;
		pD = &sgLevels[bLevel].monster[mi];
		if (pD->_mhitpoints > hp)
			pD->_mhitpoints = hp;
	}
}
// 67618C: using guessed type char sgbDeltaChanged;
// 679660: using guessed type char gbMaxPlayers;

void __fastcall delta_sync_monster(TCmdLocParam1 *packet, BYTE level)
{
	DMonsterStr *pD;

	if (gbMaxPlayers != 1) {
		sgbDeltaChanged = 1;
		pD = &sgLevels[level].monster[(BYTE)packet->bCmd];
		if (pD->_mhitpoints) {
			pD->_mx = packet->x;
			pD->_my = packet->y;
			pD->_mactive = -1;
			pD->_menemy = packet->wParam1;
		}
	}
}
// 67618C: using guessed type char sgbDeltaChanged;
// 679660: using guessed type char gbMaxPlayers;

void __fastcall delta_sync_golem(TCmdGolem *pG, int pnum, BYTE bLevel)
{
	DMonsterStr *pD;

	if (gbMaxPlayers != 1) {
		sgbDeltaChanged = 1;
		pD = &sgLevels[bLevel].monster[pnum];
		pD->_mx = pG->_mx;
		pD->_my = pG->_my;
		pD->_mactive = -1;
		pD->_menemy = pG->_menemy;
		pD->_mdir = pG->_mdir;
		pD->_mhitpoints = pG->_mhitpoints;
	}
}
// 67618C: using guessed type char sgbDeltaChanged;
// 679660: using guessed type char gbMaxPlayers;

void __fastcall delta_leave_sync(BYTE bLevel)
{
	int i, ma;
	DMonsterStr *pD;

	if (gbMaxPlayers != 1) {
		if (currlevel == 0) {
			glSeedTbl[0] = GetRndSeed();
		}
		if (currlevel > 0) {
			for (i = 0; i < nummonsters; ++i) {
				ma = monstactive[i];
				if (monster[ma]._mhitpoints) {
					sgbDeltaChanged = 1;
					pD = &sgLevels[bLevel].monster[ma];
					pD->_mx = monster[ma]._mx;
					pD->_my = monster[ma]._my;
					pD->_mdir = monster[ma]._mdir;
					pD->_menemy = encode_enemy(ma);
					pD->_mhitpoints = monster[ma]._mhitpoints;
					pD->_mactive = monster[ma]._msquelch;
				}
			}
			memcpy(&sgLocals[bLevel], automapview, sizeof(automapview));
		}
	}
}
// 43C17D: could not find valid save-restore pair for edi
// 67618C: using guessed type char sgbDeltaChanged;
// 679660: using guessed type char gbMaxPlayers;

BOOL __fastcall delta_portal_inited(int i)
{
	return sgJunk.portal[i].x == -1;
}

BOOL __fastcall delta_quest_inited(int i)
{
	return sgJunk.quests[i].qstate != -1;
}

void __fastcall DeltaAddItem(int ii)
{
	int v1;        // eax
	int v2;        // ecx
	signed int v3; // ebp
	DLevel *v4;    // edx
	DLevel *v5;    // edi
	char v6;       // bl
	int v7;        // esi
	signed int v8; // esi
	int v9;        // eax
	char v10;      // cl
	char v11;      // cl

	v1 = ii;
	if (gbMaxPlayers != 1) {
		v2 = currlevel;
		v3 = 0;
		v4 = &sgLevels[v2];
		v5 = &sgLevels[v2];
		while (1) {
			v6 = v5->item[0].bCmd;
			if (v5->item[0].bCmd != -1) {
				v7 = v1;
				if ((unsigned short)v5->item[0].wIndx == item[v1].IDidx
				    && v5->item[0].wCI == item[v7]._iCreateInfo
				    && v5->item[0].dwSeed == item[v7]._iSeed
				    && (v6 == 1 || !v6)) {
					break;
				}
			}
			++v3;
			v5 = (DLevel *)((char *)v5 + 22);
			if (v3 >= 127) {
				v8 = 0;
				while (v4->item[0].bCmd != -1) {
					++v8;
					v4 = (DLevel *)((char *)v4 + 22);
					if (v8 >= 127)
						return;
				}
				v4->item[0].bCmd = 0;
				v9 = 368 * v1;
				v10 = *((_BYTE *)&item[0]._ix + v9);
				sgbDeltaChanged = 1;
				v4->item[0].x = v10;
				v4->item[0].y = *((_BYTE *)&item[0]._iy + v9);
				v4->item[0].wIndx = *(_WORD *)((char *)&item[0].IDidx + v9);
				v4->item[0].wCI = *(short *)((char *)&item[0]._iCreateInfo + v9);
				v4->item[0].dwSeed = *(int *)((char *)&item[0]._iSeed + v9);
				v4->item[0].bId = *((_BYTE *)&item[0]._iIdentified + v9);
				v4->item[0].bDur = *((_BYTE *)&item[0]._iDurability + v9);
				v4->item[0].bMDur = *((_BYTE *)&item[0]._iMaxDur + v9);
				v4->item[0].bCh = *((_BYTE *)&item[0]._iCharges + v9);
				v11 = *((_BYTE *)&item[0]._iMaxCharges + v9);
				_LOWORD(v9) = *(_WORD *)((char *)&item[0]._ivalue + v9);
				v4->item[0].bMCh = v11;
				v4->item[0].wValue = v9;
				return;
			}
		}
	}
}
// 67618C: using guessed type char sgbDeltaChanged;
// 679660: using guessed type char gbMaxPlayers;

void __cdecl DeltaSaveLevel()
{
	int i;

	if (gbMaxPlayers != 1) {
		for (i = 0; i < MAX_PLRS; i++) {
			if (i != myplr)
				plr[i]._pGFXLoad = 0;
		}
		plr[myplr]._pLvlVisited[currlevel] = 1;
		delta_leave_sync(currlevel);
	}
}
// 679660: using guessed type char gbMaxPlayers;

void __cdecl DeltaLoadLevel()
{
	int v0;             // ebx
	int *v1;            // esi
	int v2;             // eax
	int v3;             // ecx
	int v4;             // edx
	int v5;             // edi
	char v6;            // al
	int v7;             // eax
	signed int v8;      // esi
	int v9;             // eax
	char v10;           // cl
	int v11;            // eax
	char *v12;          // edx
	int v13;            // eax
	int v14;            // ebx
	int *v15;           // edx
	unsigned short v16; // cx
	int v17;            // ST1C_4
	int v18;            // ST18_4
	int v19;            // eax
	int v20;            // ecx
	int v21;            // edx
	int v22;            // eax
	int v23;            // eax
	int v24;            // esi
	int v25;            // edi
	int v26;            // eax
	int v27;            // eax
	int v28;            // esi
	unsigned char v29;  // al
	int j;              // esi
	int v31;            // eax
	signed int v32;     // [esp+0h] [ebp-24h]
	int v33;            // [esp+4h] [ebp-20h]
	int o2;             // [esp+8h] [ebp-1Ch]
	int i;              // [esp+Ch] [ebp-18h]
	signed int v36;     // [esp+10h] [ebp-14h]
	int v37;            // [esp+14h] [ebp-10h]
	signed int v38;     // [esp+18h] [ebp-Ch]
	signed int v39;     // [esp+1Ch] [ebp-8h]
	int v40;            // [esp+20h] [ebp-4h]
	signed int v41;     // [esp+20h] [ebp-4h]

	if (gbMaxPlayers != 1) {
		deltaload = 1;
		if (currlevel != 0) {
			v0 = 0;
			if (nummonsters > 0) {
				v40 = 0;
				v1 = &monster[0]._mfuty;
				do {
					if (sgLevels[currlevel].monster[v40]._mx != -1) {
						M_ClearSquares(v0);
						v2 = v40 * 9 + 4721 * currlevel;
						v3 = *((unsigned char *)&sgLevels[0].monster[0]._mx + v2);
						v4 = *((unsigned char *)&sgLevels[0].monster[0]._my + v2);
						v5 = *(int *)((char *)&sgLevels[0].monster[0]._mhitpoints + v2);
						*(v1 - 3) = v3;
						*(v1 - 2) = v4;
						v1[1] = v3;
						v1[2] = v4;
						*(v1 - 1) = v3;
						*v1 = v4;
						if (v5 != -1)
							v1[26] = v5;
						if (v5) {
							decode_enemy(v0, *((unsigned char *)&sgLevels[0].monster[0]._menemy + v2));
							v7 = *(v1 - 3);
							if (v7 && v7 != 1 || *(v1 - 2))
								dMonster[v7][*(v1 - 2)] = v0 + 1;
							if ((signed int)v1 >= (signed int)&monster[4]._mfuty) {
								M_StartStand(v0, v1[7]);
							} else {
								MAI_Golum(v0);
								v1[28] |= 0x30u;
							}
							*((_BYTE *)v1 + 116) = sgLevels[currlevel].monster[v40]._mactive;
						} else {
							v1[1] = v3;
							v1[2] = v4;
							M_ClearSquares(v0);
							if (*((_BYTE *)v1 + 108) != 27) {
								if (*((_BYTE *)v1 + 144))
									v6 = *((_BYTE *)v1 + 146);
								else
									v6 = *(_BYTE *)(v1[44] + 317);
								AddDead(*(v1 - 3), *(v1 - 2), v6, (direction)v1[7]);
							}
							v1[16] = 1;
							M_UpdateLeader(v0);
						}
					}
					++v40;
					++v0;
					v1 += 57;
				} while (v0 < nummonsters);
			}
			memcpy(automapview, &sgLocals[currlevel], sizeof(automapview));
		}
		v8 = 0;
		i = 0;
		v32 = 0;
		do {
			v9 = v8 + 4721 * currlevel;
			v10 = *(&sgLevels[0].item[0].bCmd + v9);
			if (v10 != -1) {
				if (v10 == 1) {
					v11 = FindGetItem(
					    *(unsigned short *)((char *)&sgLevels[0].item[0].wIndx + v9),
					    *(short *)((char *)&sgLevels[0].item[0].wCI + v9),
					    *(int *)((char *)&sgLevels[0].item[0].dwSeed + v9));
					if (v11 != -1) {
						v12 = &dItem[item[v11]._ix][item[v11]._iy];
						if (*v12 == v11 + 1)
							*v12 = 0;
						DeleteItem(v11, i);
					}
				}
				v13 = v8 + 4721 * currlevel;
				if (*(&sgLevels[0].item[0].bCmd + v13) == 2) {
					v14 = itemavail[0];
					v33 = itemavail[0];
					v15 = &itemavail[MAXITEMS - numitems - 1];
					itemactive[numitems] = itemavail[0];
					v16 = *(short *)((char *)&sgLevels[0].item[0].wIndx + v13);
					itemavail[0] = *v15;
					if (v16 == IDI_EAR) {
						RecreateEar(
						    v14,
						    *(short *)((char *)&sgLevels[0].item[0].wCI + v13),
						    *(int *)((char *)&sgLevels[0].item[0].dwSeed + v13),
						    *(&sgLevels[0].item[0].bId + v13),
						    *((unsigned char *)&sgLevels[0].item[0].bDur + v13),
						    *((unsigned char *)&sgLevels[0].item[0].bMDur + v13),
						    *((unsigned char *)&sgLevels[0].item[0].bCh + v13),
						    *((unsigned char *)&sgLevels[0].item[0].bMCh + v13),
						    *(unsigned short *)((char *)&sgLevels[0].item[0].wValue + v13),
						    *(int *)((char *)&sgLevels[0].item[0].dwBuff + v13));
					} else {
						v17 = *(unsigned short *)((char *)&sgLevels[0].item[0].wValue + v13);
						v18 = *(int *)((char *)&sgLevels[0].item[0].dwSeed + v13);
						_LOWORD(v13) = *(short *)((char *)&sgLevels[0].item[0].wCI + v13);
						RecreateItem(v14, v16, v13, v18, v17);
						v19 = v8 + 4721 * currlevel;
						if (*(&sgLevels[0].item[0].bId + v19))
							item[v14]._iIdentified = TRUE;
						v20 = v14;
						item[v20]._iDurability = *((unsigned char *)&sgLevels[0].item[0].bDur + v19);
						item[v20]._iMaxDur = *((unsigned char *)&sgLevels[0].item[0].bMDur + v19);
						v21 = *((unsigned char *)&sgLevels[0].item[0].bCh + v19);
						v22 = *((unsigned char *)&sgLevels[0].item[0].bMCh + v19);
						item[v20]._iCharges = v21;
						item[v20]._iMaxCharges = v22;
					}
					v23 = v8 + 4721 * currlevel;
					v24 = *((unsigned char *)&sgLevels[0].item[0].x + v23);
					v25 = *((unsigned char *)&sgLevels[0].item[0].y + v23);
					if (!CanPut(v24, v25)) {
						v39 = 0;
						v26 = -1;
						v41 = 1;
						v36 = -1;
						do {
							if (v39)
								break;
							v37 = v26;
							while (v26 <= v41 && !v39) {
								o2 = v25 + v37;
								v38 = v36;
								do {
									if (v39)
										break;
									if (CanPut(v38 + v24, o2)) {
										v25 = o2;
										v39 = 1;
										v24 += v38;
									}
									++v38;
									v14 = v33;
								} while (v38 <= v41);
								v26 = ++v37;
							}
							++v41;
							v26 = v36-- - 1;
						} while (v36 > -50);
					}
					v27 = v14;
					item[v27]._ix = v24;
					item[v27]._iy = v25;
					dItem[v24][v25] = v14 + 1;
					RespawnItem(v14, 0);
					++numitems;
					v8 = v32;
				}
			}
			++i;
			v8 += 22;
			v32 = v8;
		} while (v8 < 2794);
		if (currlevel != 0) {
			v28 = 0;
			do {
				v29 = sgLevels[currlevel].object[v28].bCmd;
				if (v29 >= CMD_OPENDOOR) {
					if (v29 <= CMD_PLROPOBJ) {
						SyncOpObject(-1, v29, v28);
					} else if (v29 == CMD_BREAKOBJ) {
						SyncBreakObj(-1, v28);
					}
				}
				++v28;
			} while (v28 < 127);
			for (j = 0; j < nobjects; ++j) {
				v31 = object[objectactive[j]]._otype;
				if (v31 == OBJ_TRAPL || v31 == OBJ_TRAPR)
					Obj_Trap(objectactive[j]);
			}
		}
		deltaload = 0;
	}
}
// 676190: using guessed type int deltaload;
// 679660: using guessed type char gbMaxPlayers;

void __fastcall NetSendCmd(BOOL bHiPri, BYTE bCmd)
{
	TCmd cmd;

	cmd.bCmd = bCmd;
	if (bHiPri)
		NetSendHiPri((BYTE *)&cmd, sizeof(cmd));
	else
		NetSendLoPri((BYTE *)&cmd, sizeof(cmd));
}

void __fastcall NetSendCmdGolem(BYTE mx, BYTE my, BYTE dir, BYTE menemy, int hp, BYTE cl)
{
	TCmdGolem cmd;

	cmd.bCmd = CMD_AWAKEGOLEM;
	cmd._mx = mx;
	cmd._my = my;
	cmd._mdir = dir;
	cmd._menemy = menemy;
	cmd._mhitpoints = hp;
	cmd._currlevel = cl;
	NetSendLoPri((BYTE *)&cmd, sizeof(cmd));
}

void __fastcall NetSendCmdLoc(BOOL bHiPri, BYTE bCmd, BYTE x, BYTE y)
{
	TCmdLoc cmd;

	cmd.bCmd = bCmd;
	cmd.x = x;
	cmd.y = y;
	if (bHiPri)
		NetSendHiPri((BYTE *)&cmd, sizeof(cmd));
	else
		NetSendLoPri((BYTE *)&cmd, sizeof(cmd));
}

void __fastcall NetSendCmdLocParam1(BOOL bHiPri, BYTE bCmd, BYTE x, BYTE y, WORD wParam1)
{
	TCmdLocParam1 cmd;

	cmd.bCmd = bCmd;
	cmd.x = x;
	cmd.y = y;
	cmd.wParam1 = wParam1;
	if (bHiPri)
		NetSendHiPri((BYTE *)&cmd, sizeof(cmd));
	else
		NetSendLoPri((BYTE *)&cmd, sizeof(cmd));
}

void __fastcall NetSendCmdLocParam2(BOOL bHiPri, BYTE bCmd, BYTE x, BYTE y, WORD wParam1, WORD wParam2)
{
	TCmdLocParam2 cmd;

	cmd.bCmd = bCmd;
	cmd.x = x;
	cmd.y = y;
	cmd.wParam1 = wParam1;
	cmd.wParam2 = wParam2;
	if (bHiPri)
		NetSendHiPri((BYTE *)&cmd, sizeof(cmd));
	else
		NetSendLoPri((BYTE *)&cmd, sizeof(cmd));
}

void __fastcall NetSendCmdLocParam3(BOOL bHiPri, BYTE bCmd, BYTE x, BYTE y, WORD wParam1, WORD wParam2, WORD wParam3)
{
	TCmdLocParam3 cmd;

	cmd.bCmd = bCmd;
	cmd.x = x;
	cmd.y = y;
	cmd.wParam1 = wParam1;
	cmd.wParam2 = wParam2;
	cmd.wParam3 = wParam3;
	if (bHiPri)
		NetSendHiPri((BYTE *)&cmd, sizeof(cmd));
	else
		NetSendLoPri((BYTE *)&cmd, sizeof(cmd));
}

void __fastcall NetSendCmdParam1(BOOL bHiPri, BYTE bCmd, WORD wParam1)
{
	TCmdParam1 cmd;

	cmd.bCmd = bCmd;
	cmd.wParam1 = wParam1;
	if (bHiPri)
		NetSendHiPri((BYTE *)&cmd, sizeof(cmd));
	else
		NetSendLoPri((BYTE *)&cmd, sizeof(cmd));
}

void __fastcall NetSendCmdParam2(BOOL bHiPri, BYTE bCmd, WORD wParam1, WORD wParam2)
{
	TCmdParam2 cmd;

	cmd.bCmd = bCmd;
	cmd.wParam1 = wParam1;
	cmd.wParam2 = wParam2;
	if (bHiPri)
		NetSendHiPri((BYTE *)&cmd, sizeof(cmd));
	else
		NetSendLoPri((BYTE *)&cmd, sizeof(cmd));
}

void __fastcall NetSendCmdParam3(BOOL bHiPri, BYTE bCmd, WORD wParam1, WORD wParam2, WORD wParam3)
{
	TCmdParam3 cmd;

	cmd.bCmd = bCmd;
	cmd.wParam1 = wParam1;
	cmd.wParam2 = wParam2;
	cmd.wParam3 = wParam3;
	if (bHiPri)
		NetSendHiPri((BYTE *)&cmd, sizeof(cmd));
	else
		NetSendLoPri((BYTE *)&cmd, sizeof(cmd));
}

void __fastcall NetSendCmdQuest(BOOL bHiPri, BYTE q)
{
	TCmdQuest cmd;

	cmd.q = q;
	cmd.bCmd = CMD_SYNCQUEST;
	cmd.qstate = quests[q]._qactive;
	cmd.qlog = quests[q]._qlog;
	cmd.qvar1 = quests[q]._qvar1;
	if (bHiPri)
		NetSendHiPri((BYTE *)&cmd, sizeof(cmd));
	else
		NetSendLoPri((BYTE *)&cmd, sizeof(cmd));
}

void __fastcall NetSendCmdGItem(BOOL bHiPri, BYTE bCmd, BYTE mast, BYTE pnum, BYTE ii)
{
	TCmdGItem cmd;

	cmd.bCmd = bCmd;
	cmd.bPnum = pnum;
	cmd.bMaster = mast;
	cmd.bLevel = currlevel;
	cmd.bCursitem = ii;
	cmd.dwTime = 0;
	cmd.x = item[ii]._ix;
	cmd.y = item[ii]._iy;
	cmd.wIndx = item[ii].IDidx;

	if (item[ii].IDidx == IDI_EAR) {
		cmd.wCI = item[ii]._iName[8] | (item[ii]._iName[7] << 8);
		cmd.dwSeed = item[ii]._iName[12] | ((item[ii]._iName[11] | ((item[ii]._iName[10] | (item[ii]._iName[9] << 8)) << 8)) << 8);
		cmd.bId = item[ii]._iName[13];
		cmd.bDur = item[ii]._iName[14];
		cmd.bMDur = item[ii]._iName[15];
		cmd.bCh = item[ii]._iName[16];
		cmd.bMCh = item[ii]._iName[17];
		cmd.wValue = item[ii]._ivalue | (item[ii]._iName[18] << 8) | ((item[ii]._iCurs - 19) << 6);
		cmd.dwBuff = item[ii]._iName[22] | ((item[ii]._iName[21] | ((item[ii]._iName[20] | (item[ii]._iName[19] << 8)) << 8)) << 8);
	} else {
		cmd.wCI = item[ii]._iCreateInfo;
		cmd.dwSeed = item[ii]._iSeed;
		cmd.bId = item[ii]._iIdentified;
		cmd.bDur = item[ii]._iDurability;
		cmd.bMDur = item[ii]._iMaxDur;
		cmd.bCh = item[ii]._iCharges;
		cmd.bMCh = item[ii]._iMaxCharges;
		cmd.wValue = item[ii]._ivalue;
	}

	if (bHiPri)
		NetSendHiPri((BYTE *)&cmd, sizeof(cmd));
	else
		NetSendLoPri((BYTE *)&cmd, sizeof(cmd));
}

void __fastcall NetSendCmdGItem2(BOOL usonly, BYTE bCmd, BYTE mast, BYTE pnum, TCmdGItem *p)
{
	int ticks;
	TCmdGItem cmd;

	memcpy(&cmd, p, sizeof(cmd));
	cmd.bPnum = pnum;
	cmd.bCmd = bCmd;
	cmd.bMaster = mast;

	if (!usonly) {
		cmd.dwTime = 0;
		NetSendHiPri((BYTE *)&cmd, sizeof(cmd));
		return;
	}

	ticks = GetTickCount();
	if (!cmd.dwTime) {
		cmd.dwTime = ticks;
	} else if (ticks - cmd.dwTime > 5000) {
		return;
	}

	multi_msg_add((BYTE *)&cmd.bCmd, sizeof(cmd));
}

BOOL __fastcall NetSendCmdReq2(BYTE bCmd, BYTE mast, BYTE pnum, TCmdGItem *p)
{
	int ticks;
	TCmdGItem cmd;

	memcpy(&cmd, p, sizeof(cmd));
	cmd.bCmd = bCmd;
	cmd.bPnum = pnum;
	cmd.bMaster = mast;

	ticks = GetTickCount();
	if (!cmd.dwTime) {
		cmd.dwTime = ticks;
	} else if (ticks - cmd.dwTime > 5000) {
		return FALSE;
	}

	multi_msg_add((BYTE *)&cmd.bCmd, sizeof(cmd));

	return TRUE;
}

void __fastcall NetSendCmdExtra(TCmdGItem *p)
{
	TCmdGItem cmd;

	memcpy(&cmd, p, sizeof(cmd));
	cmd.dwTime = 0;
	cmd.bCmd = CMD_ITEMEXTRA;
	NetSendHiPri((BYTE *)&cmd, sizeof(cmd));
}

void __fastcall NetSendCmdPItem(BOOL bHiPri, BYTE bCmd, BYTE x, BYTE y)
{
	TCmdPItem cmd;

	cmd.bCmd = bCmd;
	cmd.x = x;
	cmd.y = y;
	cmd.wIndx = plr[myplr].HoldItem.IDidx;

	if (plr[myplr].HoldItem.IDidx == IDI_EAR) {
		cmd.wCI = plr[myplr].HoldItem._iName[8] | (plr[myplr].HoldItem._iName[7] << 8);
		cmd.dwSeed = plr[myplr].HoldItem._iName[12] | ((plr[myplr].HoldItem._iName[11] | ((plr[myplr].HoldItem._iName[10] | (plr[myplr].HoldItem._iName[9] << 8)) << 8)) << 8);
		cmd.bId = plr[myplr].HoldItem._iName[13];
		cmd.bDur = plr[myplr].HoldItem._iName[14];
		cmd.bMDur = plr[myplr].HoldItem._iName[15];
		cmd.bCh = plr[myplr].HoldItem._iName[16];
		cmd.bMCh = plr[myplr].HoldItem._iName[17];
		cmd.wValue = plr[myplr].HoldItem._ivalue | (plr[myplr].HoldItem._iName[18] << 8) | ((plr[myplr].HoldItem._iCurs - 19) << 6);
		cmd.dwBuff = plr[myplr].HoldItem._iName[22] | ((plr[myplr].HoldItem._iName[21] | ((plr[myplr].HoldItem._iName[20] | (plr[myplr].HoldItem._iName[19] << 8)) << 8)) << 8);
	} else {
		cmd.wCI = plr[myplr].HoldItem._iCreateInfo;
		cmd.dwSeed = plr[myplr].HoldItem._iSeed;
		cmd.bId = plr[myplr].HoldItem._iIdentified;
		cmd.bDur = plr[myplr].HoldItem._iDurability;
		cmd.bMDur = plr[myplr].HoldItem._iMaxDur;
		cmd.bCh = plr[myplr].HoldItem._iCharges;
		cmd.bMCh = plr[myplr].HoldItem._iMaxCharges;
		cmd.wValue = plr[myplr].HoldItem._ivalue;
	}

	if (bHiPri)
		NetSendHiPri((BYTE *)&cmd, sizeof(cmd));
	else
		NetSendLoPri((BYTE *)&cmd, sizeof(cmd));
}

void __fastcall NetSendCmdChItem(BOOL bHiPri, BYTE bLoc)
{
	TCmdChItem cmd;

	cmd.bCmd = CMD_CHANGEPLRITEMS;
	cmd.bLoc = bLoc;
	cmd.wIndx = plr[myplr].HoldItem.IDidx;
	cmd.wCI = plr[myplr].HoldItem._iCreateInfo;
	cmd.dwSeed = plr[myplr].HoldItem._iSeed;
	cmd.bId = plr[myplr].HoldItem._iIdentified;

	if (bHiPri)
		NetSendHiPri((BYTE *)&cmd, sizeof(cmd));
	else
		NetSendLoPri((BYTE *)&cmd, sizeof(cmd));
}

void __fastcall NetSendCmdDelItem(BOOL bHiPri, BYTE bLoc)
{
	TCmdDelItem cmd;

	cmd.bLoc = bLoc;
	cmd.bCmd = CMD_DELPLRITEMS;
	if (bHiPri)
		NetSendHiPri((BYTE *)&cmd, sizeof(cmd));
	else
		NetSendLoPri((BYTE *)&cmd, sizeof(cmd));
}

void __fastcall NetSendCmdDItem(BOOL bHiPri, int ii)
{
	int v2;        // eax
	short *v3;     // edx
	BOOLEAN v4;    // zf
	short v5;      // dx
	short v6;      // bx
	int v7;        // esi
	int v8;        // esi
	char v9;       // dl
	short v10;     // ax
	TCmdPItem cmd; // [esp+4h] [ebp-18h]

	v2 = ii;
	cmd.bCmd = CMD_DROPITEM;
	cmd.x = item[ii]._ix;
	cmd.y = item[ii]._iy;
	v3 = (short *)&item[ii].IDidx;
	v4 = *(_DWORD *)v3 == IDI_EAR;
	cmd.wIndx = *v3;
	if (v4) {
		_LOBYTE(v5) = 0;
		_HIBYTE(v5) = item[v2]._iName[7];
		_LOBYTE(v6) = 0;
		_HIBYTE(v6) = item[v2]._iName[18];
		v7 = item[v2]._iName[10];
		cmd.wCI = item[v2]._iName[8] | v5;
		cmd.dwSeed = item[v2]._iName[12] | ((item[v2]._iName[11] | ((v7 | (item[v2]._iName[9] << 8)) << 8)) << 8);
		cmd.bId = item[v2]._iName[13];
		cmd.bDur = item[v2]._iName[14];
		cmd.bMDur = item[v2]._iName[15];
		cmd.bCh = item[v2]._iName[16];
		cmd.bMCh = item[v2]._iName[17];
		v8 = item[v2]._iName[20];
		cmd.wValue = _LOWORD(item[v2]._ivalue) | v6 | ((_LOWORD(item[v2]._iCurs) - 19) << 6);
		cmd.dwBuff = item[v2]._iName[22] | ((item[v2]._iName[21] | ((v8 | (item[v2]._iName[19] << 8)) << 8)) << 8);
	} else {
		cmd.wCI = item[v2]._iCreateInfo;
		cmd.dwSeed = item[v2]._iSeed;
		cmd.bId = item[v2]._iIdentified;
		cmd.bDur = item[v2]._iDurability;
		cmd.bMDur = item[v2]._iMaxDur;
		cmd.bCh = item[v2]._iCharges;
		v9 = item[v2]._iMaxCharges;
		v10 = item[v2]._ivalue;
		cmd.bMCh = v9;
		cmd.wValue = v10;
	}
	if (bHiPri)
		NetSendHiPri((BYTE *)&cmd, sizeof(cmd));
	else
		NetSendLoPri((BYTE *)&cmd, sizeof(cmd));
}

void __fastcall NetSendCmdDamage(BOOL bHiPri, BYTE bPlr, DWORD dwDam)
{
	TCmdDamage cmd;

	cmd.bCmd = CMD_PLRDAMAGE;
	cmd.bPlr = bPlr;
	cmd.dwDam = dwDam;
	if (bHiPri)
		NetSendHiPri((BYTE *)&cmd, sizeof(cmd));
	else
		NetSendLoPri((BYTE *)&cmd, sizeof(cmd));
}

void __fastcall NetSendCmdString(int pmask, const char *pszStr)
{
	int dwStrLen;
	TCmdString cmd;

	cmd.bCmd = CMD_STRING;
	dwStrLen = strlen(pszStr);
	strcpy(cmd.str, pszStr);
	multi_send_msg_packet(pmask, (BYTE *)&cmd.bCmd, dwStrLen + 2);
}

void __fastcall RemovePlrPortal(int pnum)
{
	memset(&sgJunk.portal[pnum], 255, sizeof(sgJunk.portal[pnum]));
	sgbDeltaChanged = 1;
}
// 67618C: using guessed type char sgbDeltaChanged;

int __fastcall ParseCmd(int pnum, TCmd *pCmd)
{
	BOOLEAN v2;          // zf
	TCmd *v3;         // eax
	char v4;          // dl
	unsigned char v5; // bl

	v2 = sgwPackPlrOffsetTbl[pnum] == 0;
	v3 = pCmd;
	v4 = pCmd->bCmd;
	sbLastCmd = v4;
	if (!v2 && v4 != CMD_ACK_PLRINFO && v4 != CMD_SEND_PLRINFO)
		return 0;
	v5 = v3->bCmd;
	switch (v3->bCmd) {
	case CMD_WALKXY:
		return On_WALKXY((TCmdLoc *)v3, pnum);
	case CMD_ACK_PLRINFO:
		return On_ACK_PLRINFO((TCmdPlrInfoHdr *)v3, pnum);
	case CMD_ADDSTR:
		return On_ADDSTR((TCmdParam1 *)v3, pnum);
	case CMD_ADDMAG:
		return On_ADDMAG((TCmdParam1 *)v3, pnum);
	case CMD_ADDDEX:
		return On_ADDDEX((TCmdParam1 *)v3, pnum);
	case CMD_ADDVIT:
		return On_ADDVIT((TCmdParam1 *)v3, pnum);
	case CMD_SBSPELL:
		return On_SBSPELL((TCmdParam1 *)v3, pnum);
	case CMD_GETITEM:
		return On_GETITEM((TCmdGItem *)v3, pnum);
	case CMD_AGETITEM:
		return On_AGETITEM((TCmdGItem *)v3, pnum);
	case CMD_PUTITEM:
		return On_PUTITEM((TCmdPItem *)v3, pnum);
	case CMD_RESPAWNITEM:
		return On_RESPAWNITEM((TCmdPItem *)v3, pnum);
	case CMD_ATTACKXY:
		return On_ATTACKXY((TCmdLoc *)v3, pnum);
	case CMD_RATTACKXY:
		return On_RATTACKXY((TCmdLoc *)v3, pnum);
	case CMD_SPELLXY:
		return On_SPELLXY((TCmdLocParam2 *)v3, pnum);
	case CMD_TSPELLXY:
		return On_TSPELLXY((TCmdLocParam2 *)v3, pnum);
	case CMD_OPOBJXY:
		return On_OPOBJXY((TCmdLocParam1 *)v3, pnum);
	case CMD_DISARMXY:
		return On_DISARMXY((TCmdLocParam1 *)v3, pnum);
	case CMD_ATTACKID:
		return On_ATTACKID((TCmdParam1 *)v3, pnum);
	case CMD_ATTACKPID:
		return On_ATTACKPID((TCmdParam1 *)v3, pnum);
	case CMD_RATTACKID:
		return On_RATTACKID((TCmdParam1 *)v3, pnum);
	case CMD_RATTACKPID:
		return On_RATTACKPID((TCmdParam1 *)v3, pnum);
	case CMD_SPELLID:
		return On_SPELLID((TCmdParam3 *)v3, pnum);
	case CMD_SPELLPID:
		return On_SPELLPID((TCmdParam3 *)v3, pnum);
	case CMD_TSPELLID:
		return On_TSPELLID((TCmdParam3 *)v3, pnum);
	case CMD_TSPELLPID:
		return On_TSPELLPID((TCmdParam3 *)v3, pnum);
	case CMD_RESURRECT:
		return On_RESURRECT((TCmdParam1 *)v3, pnum);
	case CMD_OPOBJT:
		return On_OPOBJT((TCmdParam1 *)v3, pnum);
	case CMD_KNOCKBACK:
		return On_KNOCKBACK((TCmdParam1 *)v3, pnum);
	case CMD_TALKXY:
		return On_TALKXY((TCmdLocParam1 *)v3, pnum);
	case CMD_NEWLVL:
		return On_NEWLVL((TCmdParam2 *)v3, pnum);
	case CMD_WARP:
		return On_WARP((TCmdParam1 *)v3, pnum);
	case CMD_CHEAT_EXPERIENCE:
		return On_CHEAT_EXPERIENCE(v3, pnum);
	case CMD_CHEAT_SPELL_LEVEL:
		return On_CHEAT_SPELL_LEVEL(v3, pnum);
	case CMD_DEBUG:
		return On_DEBUG(v3);
	case CMD_SYNCDATA:
		return On_SYNCDATA(v3, pnum);
	case CMD_MONSTDEATH:
		return On_MONSTDEATH((TCmdLocParam1 *)v3, pnum);
	case CMD_MONSTDAMAGE:
		return On_MONSTDAMAGE((TCmdParam2 *)v3, pnum);
	case CMD_PLRDEAD:
		return On_PLRDEAD((TCmdParam1 *)v3, pnum);
	case CMD_REQUESTGITEM:
		return On_REQUESTGITEM((TCmdGItem *)v3, pnum);
	case CMD_REQUESTAGITEM:
		return On_REQUESTAGITEM((TCmdGItem *)v3, pnum);
	case CMD_GOTOGETITEM:
		return On_GOTOGETITEM((TCmdLocParam1 *)v3, pnum);
	case CMD_GOTOAGETITEM:
		return On_GOTOAGETITEM((TCmdLocParam1 *)v3, pnum);
	case CMD_OPENDOOR:
		return On_OPENDOOR((TCmdParam1 *)v3, pnum);
	case CMD_CLOSEDOOR:
		return On_CLOSEDOOR((TCmdParam1 *)v3, pnum);
	case CMD_OPERATEOBJ:
		return On_OPERATEOBJ((TCmdParam1 *)v3, pnum);
	case CMD_PLROPOBJ:
		return On_PLROPOBJ((TCmdParam2 *)v3, pnum);
	case CMD_BREAKOBJ:
		return On_BREAKOBJ((TCmdParam2 *)v3, pnum);
	case CMD_CHANGEPLRITEMS:
		return On_CHANGEPLRITEMS((TCmdChItem *)v3, pnum);
	case CMD_DELPLRITEMS:
		return On_DELPLRITEMS((TCmdDelItem *)v3, pnum);
	case CMD_PLRDAMAGE:
		return On_PLRDAMAGE((TCmdDamage *)v3, pnum);
	case CMD_PLRLEVEL:
		return On_PLRLEVEL((TCmdParam1 *)v3, pnum);
	case CMD_DROPITEM:
		return On_DROPITEM((TCmdPItem *)v3, pnum);
	case CMD_PLAYER_JOINLEVEL:
		return On_PLAYER_JOINLEVEL((TCmdLocParam1 *)v3, pnum);
	case CMD_SEND_PLRINFO:
		return On_SEND_PLRINFO((TCmdPlrInfoHdr *)v3, pnum);
	case CMD_SATTACKXY:
		return On_SATTACKXY((TCmdLoc *)v3, pnum);
	case CMD_ACTIVATEPORTAL:
		return On_ACTIVATEPORTAL((TCmdLocParam3 *)v3, pnum);
	case CMD_DEACTIVATEPORTAL:
		return On_DEACTIVATEPORTAL(v3, pnum);
	case CMD_HEALOTHER:
		return On_HEALOTHER((TCmdParam1 *)v3, pnum);
	case CMD_STRING:
		return On_STRING((TCmdString *)v3, pnum);
	case CMD_SETSTR:
		return On_SETSTR((TCmdParam1 *)v3, pnum);
	case CMD_SETMAG:
		return On_SETMAG((TCmdParam1 *)v3, pnum);
	case CMD_SETDEX:
		return On_SETDEX((TCmdParam1 *)v3, pnum);
	case CMD_SETVIT:
		return On_SETVIT((TCmdParam1 *)v3, pnum);
	case CMD_RETOWN:
		return On_RETOWN(v3, pnum);
	case CMD_SPELLXYD:
		return On_SPELLXYD((TCmdLocParam3 *)v3, pnum);
	case CMD_ITEMEXTRA:
		return On_ITEMEXTRA((TCmdGItem *)v3, pnum);
	case CMD_SYNCPUTITEM:
		return On_SYNCPUTITEM((TCmdPItem *)v3, pnum);
	case CMD_KILLGOLEM:
		return On_KILLGOLEM((TCmdLocParam1 *)v3, pnum);
	case CMD_SYNCQUEST:
		return On_SYNCQUEST((TCmdQuest *)v3, pnum);
	case CMD_ENDSHIELD:
		return On_ENDSHIELD(v3, pnum);
	case CMD_AWAKEGOLEM:
		return On_AWAKEGOLEM((TCmdGolem *)v3, pnum);
	case CMD_NOVA:
		return On_NOVA((TCmdLoc *)v3, pnum);
	case CMD_SETSHIELD:
		return On_SETSHIELD(v3, pnum);
	case CMD_REMSHIELD:
		return On_REMSHIELD(v3, pnum);
	default:
		if (v5 < CMD_DLEVEL_0 || v5 > CMD_DLEVEL_END) {
			SNetDropPlayer(pnum, 0x40000006);
			return 0;
		}
		return On_DLEVEL(pnum, (TCmdPlrInfoHdr *)v3);
	}
}
// 66E4A9: using guessed type char sbLastCmd;
// 67618D: using guessed type char sgbDeltaChunks;
// 6796E4: using guessed type char gbDeltaSender;

int __fastcall On_DLEVEL(int pnum, TCmdPlrInfoHdr *pCmd)
{
	if ( (unsigned char)gbDeltaSender == pnum )
	{
		if ( sgbRecvCmd != CMD_DLEVEL_END )
		{
			if ( sgbRecvCmd == pCmd->bCmd )
			{
LABEL_17:
				memcpy(&sgRecvBuf[pCmd->wOffset], &pCmd[1], pCmd->wBytes);
				sgdwRecvOffset += pCmd->wBytes;
				return pCmd->wBytes + 5;
			}
			DeltaImportData(sgbRecvCmd, sgdwRecvOffset);
			if ( pCmd->bCmd == CMD_DLEVEL_END )
			{
				sgbDeltaChunks = 20;
				sgbRecvCmd = CMD_DLEVEL_END;
				return pCmd->wBytes + 5;
			}
			sgdwRecvOffset = 0;
LABEL_16:
			sgbRecvCmd = pCmd->bCmd;
			goto LABEL_17;
		}
	}
	else
	{
		if ( pCmd->bCmd != CMD_DLEVEL_END && (pCmd->bCmd != CMD_DLEVEL_0 || pCmd->wOffset) )
			return pCmd->wBytes + 5;
		gbDeltaSender = pnum;
		sgbRecvCmd = CMD_DLEVEL_END;
	}
	if ( pCmd->bCmd == CMD_DLEVEL_END )
	{
		sgbDeltaChunks = 20;
		return pCmd->wBytes + 5;
	}
	if ( pCmd->bCmd == CMD_DLEVEL_0 && !pCmd->wOffset )
	{
		sgdwRecvOffset = 0;
		goto LABEL_16;
	}
	return pCmd->wBytes + 5;
}

void __fastcall DeltaImportData(BYTE cmd, DWORD recv_offset)
{
	unsigned char v2; // bl
	int v3;           // esi
	void *v4;         // eax
	void *v5;         // eax

	v2 = cmd;
	if (sgRecvBuf[0])
		PkwareDecompress(&sgRecvBuf[1], recv_offset, 4721);
	if (v2 == CMD_DLEVEL_JUNK) {
		DeltaImportJunk(&sgRecvBuf[1]);
	} else if (v2 < CMD_DLEVEL_0 || v2 > CMD_DLEVEL_16) {
		TermMsg("msg:1");
	} else {
		v3 = (unsigned char)(v2 - CMD_DLEVEL_0);
		v4 = DeltaImportItem(&sgRecvBuf[1], &sgLevels[v3]);
		v5 = DeltaImportObject(v4, sgLevels[v3].object);
		DeltaImportMonster(v5, sgLevels[v3].monster);
	}
	++sgbDeltaChunks;
	sgbDeltaChanged = 1;
}
// 67618C: using guessed type char sgbDeltaChanged;
// 67618D: using guessed type char sgbDeltaChunks;

void *__fastcall DeltaImportItem(void *src, void *dst)
{
	char *v2;      // edi
	_BYTE *v3;     // esi
	signed int v4; // ebx

	v2 = (char *)dst;
	v3 = (unsigned char *)src;
	v4 = 127;
	do {
		if (*v3 == -1) {
			memset(v2, 255, 0x16u);
			++v3;
		} else {
			memcpy(v2, v3, 0x16u);
			v3 += 22;
		}
		v2 += 22;
		--v4;
	} while (v4);
	return v3;
}

void *__fastcall DeltaImportObject(void *src, void *dst)
{
	char *v2; // esi

	v2 = (char *)src;
	memcpy(dst, src, 0x7Fu);
	return v2 + 127;
}

void *__fastcall DeltaImportMonster(void *src, void *dst)
{
	char *v2;      // edi
	_BYTE *v3;     // esi
	signed int v4; // ebx

	v2 = (char *)dst;
	v3 = (unsigned char *)src;
	v4 = MAXMONSTERS;
	do {
		if (*v3 == -1) {
			memset(v2, 255, 9u);
			++v3;
		} else {
			memcpy(v2, v3, 9u);
			v3 += 9;
		}
		v2 += 9;
		--v4;
	} while (v4);
	return v3;
}

void __fastcall DeltaImportJunk(void *src)
{
	_BYTE *v1;         // ebx
	int v2;            // edi
	DJunk *v3;         // esi
	char result;       // al
	MultiQuests *v5;   // esi
	unsigned char *v6; // edi
	int *v7;           // ebp

	v1 = (_BYTE *)src;
	v2 = 0;
	v3 = &sgJunk;
	do {
		if (*v1 == -1) {
			memset(v3, 255, 5u);
			++v1;
			SetPortalStats(v2, 0, 0, 0, 0, 0);
		} else {
			memcpy(v3, v1, 5u);
			v1 += 5;
			SetPortalStats(
			    v2,
			    1,
			    (unsigned char)v3->portal[0].x,
			    (unsigned char)v3->portal[0].y,
			    (unsigned char)v3->portal[0].level,
			    (unsigned char)v3->portal[0].ltype);
		}
		v3 = (DJunk *)((char *)v3 + 5);
		++v2;
	} while ((signed int)v3 < (signed int)sgJunk.quests);
	v5 = sgJunk.quests;
	v6 = &quests[0]._qactive;
	v7 = &questlist[0]._qflags;
	do {
		if (*(_BYTE *)v7 & 1) {
			memcpy(v5, v1, 3u);
			*(_DWORD *)(v6 + 18) = (unsigned char)v5->qlog;
			*v6 = v5->qstate;
			result = v5->qvar1;
			v1 += 3;
			v6[13] = result;
			++v5;
		}
		v7 += 5;
		v6 += 24;
	} while ((signed int)v7 < (signed int)&questlist[16]._qflags);
}

int __fastcall On_SYNCDATA(void *packet, int pnum)
{
	return SyncData(pnum, (TSyncHeader *)packet);
}

int __fastcall On_WALKXY(TCmdLoc *pCmd, int pnum)
{
	if (gbBufferMsgs != 1 && currlevel == plr[pnum].plrlevel) {
		ClrPlrPath(pnum);
		MakePlrPath(pnum, pCmd->x, pCmd->y, TRUE);
		plr[pnum].destAction = ACTION_NONE;
	}

	return sizeof(*pCmd);
}

int __fastcall On_ADDSTR(TCmdParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else if (pCmd->wParam1 <= 256)
		ModifyPlrStr(pnum, pCmd->wParam1);

	return sizeof(*pCmd);
}

int __fastcall On_ADDMAG(TCmdParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else if (pCmd->wParam1 <= 256)
		ModifyPlrMag(pnum, pCmd->wParam1);

	return sizeof(*pCmd);
}

int __fastcall On_ADDDEX(TCmdParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else if (pCmd->wParam1 <= 256)
		ModifyPlrDex(pnum, pCmd->wParam1);

	return sizeof(*pCmd);
}

int __fastcall On_ADDVIT(TCmdParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else if (pCmd->wParam1 <= 256)
		ModifyPlrVit(pnum, pCmd->wParam1);

	return sizeof(*pCmd);
}

int __fastcall On_SBSPELL(TCmdParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs != 1) {
		if (currlevel != 0 || spelldata[pCmd->wParam1].sTownSpell) {
			plr[pnum]._pSpell = pCmd->wParam1;
			plr[pnum]._pSplType = plr[pnum]._pSBkSplType;
			plr[pnum]._pSplFrom = 1;
			plr[pnum].destAction = ACTION_SPELL;
		} else
			msg_errorf("%s has cast an illegal spell.", plr[pnum]._pName);
	}

	return sizeof(*pCmd);
}

void msg_errorf(const char *pszFmt, ...)
{
	static DWORD msg_err_timer;
	DWORD v1;     // eax
	char v2[256]; // [esp+0h] [ebp-100h]
	va_list va;   // [esp+10Ch] [ebp+Ch]

	va_start(va, pszFmt);
	v1 = GetTickCount();
	if (v1 - msg_err_timer >= 5000) {
		msg_err_timer = v1;
		vsprintf(v2, pszFmt, va);
		ErrorPlrMsg(v2);
	}
	va_end(va);
}

int __fastcall On_GOTOGETITEM(TCmdLocParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs != 1 && currlevel == plr[pnum].plrlevel) {
		MakePlrPath(pnum, pCmd->x, pCmd->y, FALSE);
		plr[pnum].destAction = ACTION_PICKUPITEM;
		plr[pnum].destParam1 = pCmd->wParam1;
	}

	return sizeof(*pCmd);
}

int __fastcall On_REQUESTGITEM(TCmdGItem *pCmd, int pnum)
{
	if (gbBufferMsgs != 1 && i_own_level(plr[pnum].plrlevel)) {
		if (GetItemRecord(pCmd->dwSeed, pCmd->wCI, pCmd->wIndx)) {
			int ii = FindGetItem(pCmd->wIndx, pCmd->wCI, pCmd->dwSeed);
			if (ii != -1) {
				NetSendCmdGItem2(FALSE, CMD_GETITEM, myplr, pCmd->bPnum, pCmd);
				if (pCmd->bPnum != myplr)
					SyncGetItem(pCmd->x, pCmd->y, pCmd->wIndx, pCmd->wCI, pCmd->dwSeed);
				else
					InvGetItem(myplr, ii);
				SetItemRecord(pCmd->dwSeed, pCmd->wCI, pCmd->wIndx);
			} else if (!NetSendCmdReq2(CMD_REQUESTGITEM, myplr, pCmd->bPnum, pCmd))
				NetSendCmdExtra(pCmd);
		}
	}

	return sizeof(*pCmd);
}

BOOL __fastcall i_own_level(int nReqLevel)
{
	int v1;            // edx
	unsigned char *v2; // eax

	v1 = 0;
	v2 = &plr[0]._pLvlChanging;
	do {
		if (*(v2 - 290) && !*v2 && *(_DWORD *)(v2 - 267) == nReqLevel && (v1 != myplr || !gbBufferMsgs))
			break;
		v2 += 21720;
		++v1;
	} while ((signed int)v2 < (signed int)&plr[4]._pLvlChanging);
	return v1 == myplr;
}
// 676194: using guessed type char gbBufferMsgs;

int __fastcall On_GETITEM(TCmdGItem *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else {
		int ii = FindGetItem(pCmd->wIndx, pCmd->wCI, pCmd->dwSeed);
		if (delta_get_item(pCmd, pCmd->bLevel)) {
			if ((currlevel == pCmd->bLevel || pCmd->bPnum == myplr) && pCmd->bMaster != myplr) {
				if (pCmd->bPnum == myplr) {
					if (currlevel != pCmd->bLevel) {
						ii = SyncPutItem(myplr, plr[myplr].WorldX, plr[myplr].WorldY, pCmd->wIndx, pCmd->wCI, pCmd->dwSeed, pCmd->bId, pCmd->bDur, pCmd->bMDur, pCmd->bCh, pCmd->bMCh, pCmd->wValue, pCmd->dwBuff);
						if (ii != -1)
							InvGetItem(myplr, ii);
					} else
						InvGetItem(myplr, ii);
				} else
					SyncGetItem(pCmd->x, pCmd->y, pCmd->wIndx, pCmd->wCI, pCmd->dwSeed);
			}
		} else
			NetSendCmdGItem2(TRUE, CMD_GETITEM, pCmd->bMaster, pCmd->bPnum, pCmd);
	}

	return sizeof(*pCmd);
}

BOOL __fastcall delta_get_item(TCmdGItem *pI, BYTE bLevel)
{
	TCmdGItem *v2; // esi
	signed int v3;        // ecx
	DLevel *v4;           // edi
	DLevel *v5;           // eax
	char v6;              // cl
	DLevel *v8;           // eax
	signed int v9;        // ecx

	v2 = pI;
	if (gbMaxPlayers != 1) {
		v3 = 0;
		v4 = &sgLevels[bLevel];
		v5 = &sgLevels[bLevel];
		while (v5->item[0].bCmd == -1
		    || v5->item[0].wIndx != v2->wIndx
		    || v5->item[0].wCI != v2->wCI
		    || v5->item[0].dwSeed != v2->dwSeed) {
			++v3;
			v5 = (DLevel *)((char *)v5 + 22);
			if (v3 >= 127)
				goto LABEL_15;
		}
		v6 = v5->item[0].bCmd;
		if (v5->item[0].bCmd == 1)
			return 1;
		if (!v6) {
			sgbDeltaChanged = 1;
			v5->item[0].bCmd = 1;
			return 1;
		}
		if (v6 == 2) {
			v5->item[0].bCmd = -1;
			sgbDeltaChanged = 1;
			return 1;
		}
		TermMsg("delta:1");
	LABEL_15:
		if (v2->wCI >= 0)
			return 0;
		v8 = v4;
		v9 = 0;
		while (v8->item[0].bCmd != -1) {
			++v9;
			v8 = (DLevel *)((char *)v8 + 22);
			if (v9 >= 127)
				return 1;
		}
		sgbDeltaChanged = 1;
		v8->item[0].bCmd = 1;
		v8->item[0].x = v2->x;
		v8->item[0].y = v2->y;
		v8->item[0].wIndx = v2->wIndx;
		v8->item[0].wCI = v2->wCI;
		v8->item[0].dwSeed = v2->dwSeed;
		v8->item[0].bId = v2->bId;
		v8->item[0].bDur = v2->bDur;
		v8->item[0].bMDur = v2->bMDur;
		v8->item[0].bCh = v2->bCh;
		v8->item[0].bMCh = v2->bMCh;
		v8->item[0].wValue = v2->wValue;
		v8->item[0].dwBuff = v2->dwBuff;
	}
	return 1;
}
// 67618C: using guessed type char sgbDeltaChanged;
// 679660: using guessed type char gbMaxPlayers;

int __fastcall On_GOTOAGETITEM(TCmdLocParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs != 1 && currlevel == plr[pnum].plrlevel) {
		MakePlrPath(pnum, pCmd->x, pCmd->y, FALSE);
		plr[pnum].destAction = ACTION_PICKUPAITEM;
		plr[pnum].destParam1 = pCmd->wParam1;
	}

	return sizeof(*pCmd);
}

int __fastcall On_REQUESTAGITEM(TCmdGItem *pCmd, int pnum)
{
	if (gbBufferMsgs != 1 && i_own_level(plr[pnum].plrlevel)) {
		if (GetItemRecord(pCmd->dwSeed, pCmd->wCI, pCmd->wIndx)) {
			int ii = FindGetItem(pCmd->wIndx, pCmd->wCI, pCmd->dwSeed);
			if (ii != -1) {
				NetSendCmdGItem2(FALSE, CMD_AGETITEM, myplr, pCmd->bPnum, pCmd);
				if (pCmd->bPnum != myplr)
					SyncGetItem(pCmd->x, pCmd->y, pCmd->wIndx, pCmd->wCI, pCmd->dwSeed);
				else
					AutoGetItem(myplr, pCmd->bCursitem);
				SetItemRecord(pCmd->dwSeed, pCmd->wCI, pCmd->wIndx);
			} else if (!NetSendCmdReq2(CMD_REQUESTAGITEM, myplr, pCmd->bPnum, pCmd))
				NetSendCmdExtra(pCmd);
		}
	}

	return sizeof(*pCmd);
}

int __fastcall On_AGETITEM(TCmdGItem *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else {
		FindGetItem(pCmd->wIndx, pCmd->wCI, pCmd->dwSeed);
		if (delta_get_item(pCmd, pCmd->bLevel)) {
			if ((currlevel == pCmd->bLevel || pCmd->bPnum == myplr) && pCmd->bMaster != myplr) {
				if (pCmd->bPnum == myplr) {
					if (currlevel != pCmd->bLevel) {
						int ii = SyncPutItem(myplr, plr[myplr].WorldX, plr[myplr].WorldY, pCmd->wIndx, pCmd->wCI, pCmd->dwSeed, pCmd->bId, pCmd->bDur, pCmd->bMDur, pCmd->bCh, pCmd->bMCh, pCmd->wValue, pCmd->dwBuff);
						if (ii != -1)
							AutoGetItem(myplr, ii);
					} else
						AutoGetItem(myplr, pCmd->bCursitem);
				} else
					SyncGetItem(pCmd->x, pCmd->y, pCmd->wIndx, pCmd->wCI, pCmd->dwSeed);
			}
		} else
			NetSendCmdGItem2(TRUE, CMD_AGETITEM, pCmd->bMaster, pCmd->bPnum, pCmd);
	}

	return sizeof(*pCmd);
}

int __fastcall On_ITEMEXTRA(TCmdGItem *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else {
		delta_get_item(pCmd, pCmd->bLevel);
		if (currlevel == plr[pnum].plrlevel)
			SyncGetItem(pCmd->x, pCmd->y, pCmd->wIndx, pCmd->wCI, pCmd->dwSeed);
	}

	return sizeof(*pCmd);
}

int __fastcall On_PUTITEM(TCmdPItem *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else if (currlevel == plr[pnum].plrlevel) {
		int ii;
		if (pnum == myplr)
			ii = InvPutItem(pnum, pCmd->x, pCmd->y);
		else
			ii = SyncPutItem(pnum, pCmd->x, pCmd->y, pCmd->wIndx, pCmd->wCI, pCmd->dwSeed, pCmd->bId, pCmd->bDur, pCmd->bMDur, pCmd->bCh, pCmd->bMCh, pCmd->wValue, pCmd->dwBuff);
		if (ii != -1) {
			PutItemRecord(pCmd->dwSeed, pCmd->wCI, pCmd->wIndx);
			delta_put_item(pCmd, item[ii]._ix, item[ii]._iy, plr[pnum].plrlevel);
			check_update_plr(pnum);
		}
		return sizeof(*pCmd);
	} else {
		PutItemRecord(pCmd->dwSeed, pCmd->wCI, pCmd->wIndx);
		delta_put_item(pCmd, pCmd->x, pCmd->y, plr[pnum].plrlevel);
		check_update_plr(pnum);
	}

	return sizeof(*pCmd);
}

void __fastcall delta_put_item(TCmdPItem *pI, int x, int y, BYTE bLevel)
{
	TCmdPItem *v4; // ebx
	int v5;               // eax
	DLevel *v6;           // esi
	DLevel *v7;           // edi
	char v8;              // al
	signed int v9;        // eax
	char v10;             // [esp+Ch] [ebp-4h]
	signed int bLevela;   // [esp+1Ch] [ebp+Ch]

	v10 = x;
	v4 = pI;
	if (gbMaxPlayers != 1) {
		v5 = bLevel;
		bLevela = 0;
		v6 = &sgLevels[v5];
		v7 = &sgLevels[v5];
		do {
			v8 = v7->item[0].bCmd;
			if (v7->item[0].bCmd != 1
			    && v8 != -1
			    && v7->item[0].wIndx == v4->wIndx
			    && v7->item[0].wCI == v4->wCI
			    && v7->item[0].dwSeed == v4->dwSeed) {
				if (v8 == 2)
					return;
				TermMsg("Trying to drop a floor item?");
			}
			++bLevela;
			v7 = (DLevel *)((char *)v7 + 22);
		} while (bLevela < 127);
		v9 = 0;
		while (v6->item[0].bCmd != -1) {
			++v9;
			v6 = (DLevel *)((char *)v6 + 22);
			if (v9 >= 127)
				return;
		}
		sgbDeltaChanged = 1;
		memcpy(v6, v4, sizeof(TCmdPItem));
		v6->item[0].x = v10;
		v6->item[0].bCmd = 2;
		v6->item[0].y = y;
	}
}
// 67618C: using guessed type char sgbDeltaChanged;
// 679660: using guessed type char gbMaxPlayers;

void __fastcall check_update_plr(int pnum)
{
	if (gbMaxPlayers != 1 && pnum == myplr)
		pfile_update(1);
}
// 679660: using guessed type char gbMaxPlayers;

int __fastcall On_SYNCPUTITEM(TCmdPItem *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else if (currlevel == plr[pnum].plrlevel) {
		int ii = SyncPutItem(pnum, pCmd->x, pCmd->y, pCmd->wIndx, pCmd->wCI, pCmd->dwSeed, pCmd->bId, pCmd->bDur, pCmd->bMDur, pCmd->bCh, pCmd->bMCh, pCmd->wValue, pCmd->dwBuff);
		if (ii != -1) {
			PutItemRecord(pCmd->dwSeed, pCmd->wCI, pCmd->wIndx);
			delta_put_item(pCmd, item[ii]._ix, item[ii]._iy, plr[pnum].plrlevel);
			check_update_plr(pnum);
		}
		return sizeof(*pCmd);
	} else {
		PutItemRecord(pCmd->dwSeed, pCmd->wCI, pCmd->wIndx);
		delta_put_item(pCmd, pCmd->x, pCmd->y, plr[pnum].plrlevel);
		check_update_plr(pnum);
	}

	return sizeof(*pCmd);
}

int __fastcall On_RESPAWNITEM(TCmdPItem *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else {
		if (currlevel == plr[pnum].plrlevel && pnum != myplr)
			SyncPutItem(pnum, pCmd->x, pCmd->y, pCmd->wIndx, pCmd->wCI, pCmd->dwSeed, pCmd->bId, pCmd->bDur, pCmd->bMDur, pCmd->bCh, pCmd->bMCh, pCmd->wValue, pCmd->dwBuff);
		PutItemRecord(pCmd->dwSeed, pCmd->wCI, pCmd->wIndx);
		delta_put_item(pCmd, pCmd->x, pCmd->y, plr[pnum].plrlevel);
	}

	return sizeof(*pCmd);
}

int __fastcall On_ATTACKXY(TCmdLoc *pCmd, int pnum)
{
	if (gbBufferMsgs != 1 && currlevel == plr[pnum].plrlevel) {
		MakePlrPath(pnum, pCmd->x, pCmd->y, FALSE);
		plr[pnum].destAction = ACTION_ATTACK;
		plr[pnum].destParam1 = pCmd->x;
		plr[pnum].destParam2 = pCmd->y;
	}

	return sizeof(*pCmd);
}

int __fastcall On_SATTACKXY(TCmdLoc *pCmd, int pnum)
{
	if (gbBufferMsgs != 1 && currlevel == plr[pnum].plrlevel) {
		ClrPlrPath(pnum);
		plr[pnum].destAction = ACTION_ATTACK;
		plr[pnum].destParam1 = pCmd->x;
		plr[pnum].destParam2 = pCmd->y;
	}

	return sizeof(*pCmd);
}

int __fastcall On_RATTACKXY(TCmdLoc *pCmd, int pnum)
{
	if (gbBufferMsgs != 1 && currlevel == plr[pnum].plrlevel) {
		ClrPlrPath(pnum);
		plr[pnum].destAction = ACTION_RATTACK;
		plr[pnum].destParam1 = pCmd->x;
		plr[pnum].destParam2 = pCmd->y;
	}

	return sizeof(*pCmd);
}

int __fastcall On_SPELLXYD(TCmdLocParam3 *pCmd, int pnum)
{
	if (gbBufferMsgs != 1 && currlevel == plr[pnum].plrlevel) {
		if (currlevel != 0 || spelldata[pCmd->wParam1].sTownSpell) {
			ClrPlrPath(pnum);
			plr[pnum].destAction = ACTION_SPELLWALL;
			plr[pnum].destParam1 = pCmd->x;
			plr[pnum].destParam2 = pCmd->y;
			plr[pnum].destParam3 = pCmd->wParam2;
			plr[pnum].destParam4 = pCmd->wParam3;
			plr[pnum]._pSpell = pCmd->wParam1;
			plr[pnum]._pSplType = plr[pnum]._pRSplType;
			plr[pnum]._pSplFrom = 0;
		} else
			msg_errorf("%s has cast an illegal spell.", plr[pnum]._pName);
	}

	return sizeof(*pCmd);
}

int __fastcall On_SPELLXY(TCmdLocParam2 *pCmd, int pnum)
{
	if (gbBufferMsgs != 1 && currlevel == plr[pnum].plrlevel) {
		if (currlevel != 0 || spelldata[pCmd->wParam1].sTownSpell) {
			ClrPlrPath(pnum);
			plr[pnum].destAction = ACTION_SPELL;
			plr[pnum].destParam1 = pCmd->x;
			plr[pnum].destParam2 = pCmd->y;
			plr[pnum].destParam3 = pCmd->wParam2;
			plr[pnum]._pSpell = pCmd->wParam1;
			plr[pnum]._pSplType = plr[pnum]._pRSplType;
			plr[pnum]._pSplFrom = 0;
		} else
			msg_errorf("%s has cast an illegal spell.", plr[pnum]._pName);
	}

	return sizeof(*pCmd);
}

int __fastcall On_TSPELLXY(TCmdLocParam2 *pCmd, int pnum)
{
	if (gbBufferMsgs != 1 && currlevel == plr[pnum].plrlevel) {
		if (currlevel != 0 || spelldata[pCmd->wParam1].sTownSpell) {
			ClrPlrPath(pnum);
			plr[pnum].destAction = ACTION_SPELL;
			plr[pnum].destParam1 = pCmd->x;
			plr[pnum].destParam2 = pCmd->y;
			plr[pnum].destParam3 = pCmd->wParam2;
			plr[pnum]._pSpell = pCmd->wParam1;
			plr[pnum]._pSplType = plr[pnum]._pTSplType;
			plr[pnum]._pSplFrom = 2;
		} else
			msg_errorf("%s has cast an illegal spell.", plr[pnum]._pName);
	}

	return sizeof(*pCmd);
}

int __fastcall On_OPOBJXY(TCmdLocParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs != 1 && currlevel == plr[pnum].plrlevel) {
		if (object[pCmd->wParam1]._oSolidFlag || object[pCmd->wParam1]._oDoorFlag)
			MakePlrPath(pnum, pCmd->x, pCmd->y, FALSE);
		else
			MakePlrPath(pnum, pCmd->x, pCmd->y, TRUE);
		plr[pnum].destAction = ACTION_OPERATE;
		plr[pnum].destParam1 = pCmd->wParam1;
	}

	return sizeof(*pCmd);
}

int __fastcall On_DISARMXY(TCmdLocParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs != 1 && currlevel == plr[pnum].plrlevel) {
		if (object[pCmd->wParam1]._oSolidFlag || object[pCmd->wParam1]._oDoorFlag)
			MakePlrPath(pnum, pCmd->x, pCmd->y, FALSE);
		else
			MakePlrPath(pnum, pCmd->x, pCmd->y, TRUE);
		plr[pnum].destAction = ACTION_DISARM;
		plr[pnum].destParam1 = pCmd->wParam1;
	}

	return sizeof(*pCmd);
}

int __fastcall On_OPOBJT(TCmdParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs != 1 && currlevel == plr[pnum].plrlevel) {
		plr[pnum].destAction = ACTION_OPERATETK;
		plr[pnum].destParam1 = pCmd->wParam1;
	}

	return sizeof(*pCmd);
}

int __fastcall On_ATTACKID(TCmdParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs != 1 && currlevel == plr[pnum].plrlevel) {
		int distx = abs(plr[pnum].WorldX - monster[pCmd->wParam1]._mfutx);
		int disty = abs(plr[pnum].WorldY - monster[pCmd->wParam1]._mfuty);
		if (distx > 1 || disty > 1)
			MakePlrPath(pnum, monster[pCmd->wParam1]._mfutx, monster[pCmd->wParam1]._mfuty, FALSE);
		plr[pnum].destAction = ACTION_ATTACKMON;
		plr[pnum].destParam1 = pCmd->wParam1;
	}

	return sizeof(*pCmd);
}

int __fastcall On_ATTACKPID(TCmdParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs != 1 && currlevel == plr[pnum].plrlevel) {
		MakePlrPath(pnum, plr[pCmd->wParam1]._px, plr[pCmd->wParam1]._py, FALSE);
		plr[pnum].destAction = ACTION_ATTACKPLR;
		plr[pnum].destParam1 = pCmd->wParam1;
	}

	return sizeof(*pCmd);
}

int __fastcall On_RATTACKID(TCmdParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs != 1 && currlevel == plr[pnum].plrlevel) {
		ClrPlrPath(pnum);
		plr[pnum].destAction = ACTION_RATTACKMON;
		plr[pnum].destParam1 = pCmd->wParam1;
	}

	return sizeof(*pCmd);
}

int __fastcall On_RATTACKPID(TCmdParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs != 1 && currlevel == plr[pnum].plrlevel) {
		ClrPlrPath(pnum);
		plr[pnum].destAction = ACTION_RATTACKPLR;
		plr[pnum].destParam1 = pCmd->wParam1;
	}

	return sizeof(*pCmd);
}

int __fastcall On_SPELLID(TCmdParam3 *pCmd, int pnum)
{
	if (gbBufferMsgs != 1 && currlevel == plr[pnum].plrlevel) {
		if (currlevel != 0 || spelldata[pCmd->wParam2].sTownSpell) {
			ClrPlrPath(pnum);
			plr[pnum].destAction = ACTION_SPELLMON;
			plr[pnum].destParam1 = pCmd->wParam1;
			plr[pnum].destParam2 = pCmd->wParam3;
			plr[pnum]._pSpell = pCmd->wParam2;
			plr[pnum]._pSplType = plr[pnum]._pRSplType;
			plr[pnum]._pSplFrom = 0;
		} else
			msg_errorf("%s has cast an illegal spell.", plr[pnum]._pName);
	}

	return sizeof(*pCmd);
}

int __fastcall On_SPELLPID(TCmdParam3 *pCmd, int pnum)
{
	if (gbBufferMsgs != 1 && currlevel == plr[pnum].plrlevel) {
		if (currlevel != 0 || spelldata[pCmd->wParam2].sTownSpell) {
			ClrPlrPath(pnum);
			plr[pnum].destAction = ACTION_SPELLPLR;
			plr[pnum].destParam1 = pCmd->wParam1;
			plr[pnum].destParam2 = pCmd->wParam3;
			plr[pnum]._pSpell = pCmd->wParam2;
			plr[pnum]._pSplType = plr[pnum]._pRSplType;
			plr[pnum]._pSplFrom = 0;
		} else
			msg_errorf("%s has cast an illegal spell.", plr[pnum]._pName);
	}

	return sizeof(*pCmd);
}

int __fastcall On_TSPELLID(TCmdParam3 *pCmd, int pnum)
{
	if (gbBufferMsgs != 1 && currlevel == plr[pnum].plrlevel) {
		if (currlevel != 0 || spelldata[pCmd->wParam2].sTownSpell) {
			ClrPlrPath(pnum);
			plr[pnum].destAction = ACTION_SPELLMON;
			plr[pnum].destParam1 = pCmd->wParam1;
			plr[pnum].destParam2 = pCmd->wParam3;
			plr[pnum]._pSpell = pCmd->wParam2;
			plr[pnum]._pSplType = plr[pnum]._pTSplType;
			plr[pnum]._pSplFrom = 2;
		} else
			msg_errorf("%s has cast an illegal spell.", plr[pnum]._pName);
	}

	return sizeof(*pCmd);
}

int __fastcall On_TSPELLPID(TCmdParam3 *pCmd, int pnum)
{
	if (gbBufferMsgs != 1 && currlevel == plr[pnum].plrlevel) {
		if (currlevel != 0 || spelldata[pCmd->wParam2].sTownSpell) {
			ClrPlrPath(pnum);
			plr[pnum].destAction = ACTION_SPELLPLR;
			plr[pnum].destParam1 = pCmd->wParam1;
			plr[pnum].destParam2 = pCmd->wParam3;
			plr[pnum]._pSpell = pCmd->wParam2;
			plr[pnum]._pSplType = plr[pnum]._pTSplType;
			plr[pnum]._pSplFrom = 2;
		} else
			msg_errorf("%s has cast an illegal spell.", plr[pnum]._pName);
	}

	return sizeof(*pCmd);
}

int __fastcall On_KNOCKBACK(TCmdParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs != 1 && currlevel == plr[pnum].plrlevel) {
		M_GetKnockback(pCmd->wParam1);
		M_StartHit(pCmd->wParam1, pnum, 0);
	}

	return sizeof(*pCmd);
}

int __fastcall On_RESURRECT(TCmdParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else {
		DoResurrect(pnum, pCmd->wParam1);
		check_update_plr(pnum);
	}

	return sizeof(*pCmd);
}

int __fastcall On_HEALOTHER(TCmdParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs != 1 && currlevel == plr[pnum].plrlevel)
		DoHealOther(pnum, pCmd->wParam1);

	return sizeof(*pCmd);
}

int __fastcall On_TALKXY(TCmdLocParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs != 1 && currlevel == plr[pnum].plrlevel) {
		MakePlrPath(pnum, pCmd->x, pCmd->y, FALSE);
		plr[pnum].destAction = ACTION_TALK;
		plr[pnum].destParam1 = pCmd->wParam1;
	}

	return sizeof(*pCmd);
}

int __fastcall On_NEWLVL(TCmdParam2 *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else if (pnum != myplr)
		StartNewLvl(pnum, pCmd->wParam1, pCmd->wParam2);

	return sizeof(*pCmd);
}

int __fastcall On_WARP(TCmdParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else {
		StartWarpLvl(pnum, pCmd->wParam1);
		if (pnum == myplr && pcurs >= CURSOR_FIRSTITEM) {
			item[MAXITEMS] = plr[myplr].HoldItem;
			AutoGetItem(myplr, MAXITEMS);
		}
	}

	return sizeof(*pCmd);
}

int __fastcall On_MONSTDEATH(TCmdLocParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else if (pnum != myplr) {
		if (currlevel == plr[pnum].plrlevel)
			M_SyncStartKill(pCmd->wParam1, pCmd->x, pCmd->y, pnum);
		delta_kill_monster(pCmd->wParam1, pCmd->x, pCmd->y, plr[pnum].plrlevel);
	}

	return sizeof(*pCmd);
}

int __fastcall On_KILLGOLEM(TCmdLocParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else if (pnum != myplr) {
		if (currlevel == pCmd->wParam1)
			M_SyncStartKill(pnum, pCmd->x, pCmd->y, pnum);
		delta_kill_monster(pnum, pCmd->x, pCmd->y, plr[pnum].plrlevel);
	}

	return sizeof(*pCmd);
}

int __fastcall On_AWAKEGOLEM(TCmdGolem *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else if (currlevel != plr[pnum].plrlevel)
		delta_sync_golem(pCmd, pnum, pCmd->_currlevel);
	else if (pnum != myplr) {
		int i;
		// check if this player already has an active golem
		BOOL addGolem = TRUE;
		for (i = 0; i < nummissiles; i++) {
			int mi = missileactive[i];
			if (missile[mi]._mitype == MIS_GOLEM && missile[mi]._misource == pnum) {
				addGolem = FALSE;
				// BUGFIX: break, don't need to check the rest
			}
		}
		if (addGolem)
			AddMissile(plr[pnum].WorldX, plr[pnum].WorldY, pCmd->_mx, pCmd->_my, pCmd->_mdir, MIS_GOLEM, 0, pnum, 0, 1);
	}

	return sizeof(*pCmd);
}

int __fastcall On_MONSTDAMAGE(TCmdParam2 *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else if (pnum != myplr) {
		if (currlevel == plr[pnum].plrlevel) {
			monster[pCmd->wParam1].mWhoHit |= 1 << pnum;

			if (monster[pCmd->wParam1]._mhitpoints) {
				monster[pCmd->wParam1]._mhitpoints -= pCmd->wParam2;
				if ((monster[pCmd->wParam1]._mhitpoints >> 6) < 1)
					monster[pCmd->wParam1]._mhitpoints = 1 << 6;
				delta_monster_hp(pCmd->wParam1, monster[pCmd->wParam1]._mhitpoints, plr[pnum].plrlevel);
			}
		}
	}

	return sizeof(*pCmd);
}

int __fastcall On_PLRDEAD(TCmdParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else if (pnum != myplr)
		StartPlayerKill(pnum, pCmd->wParam1);
	else
		check_update_plr(pnum);

	return sizeof(*pCmd);
}

int __fastcall On_PLRDAMAGE(TCmdDamage *pCmd, int pnum)
{
	if (pCmd->bPlr == myplr && currlevel != 0) {
		if (gbBufferMsgs != 1 && currlevel == plr[pnum].plrlevel && pCmd->dwDam <= 192000) {
			if ((plr[myplr]._pHitPoints >> 6) > 0) {
				drawhpflag = TRUE;
				plr[myplr]._pHitPoints -= pCmd->dwDam;
				plr[myplr]._pHPBase -= pCmd->dwDam;
				if (plr[myplr]._pHitPoints > plr[myplr]._pMaxHP) {
					plr[myplr]._pHitPoints = plr[myplr]._pMaxHP;
					plr[myplr]._pHPBase = plr[myplr]._pMaxHPBase;
				}
				if ((plr[myplr]._pHitPoints >> 6) <= 0)
					SyncPlrKill(myplr, 1);
			}
		}
	}

	return sizeof(*pCmd);
}

int __fastcall On_OPENDOOR(TCmdParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else {
		if (currlevel == plr[pnum].plrlevel)
			SyncOpObject(pnum, CMD_OPENDOOR, pCmd->wParam1);
		delta_sync_object(pCmd->wParam1, CMD_OPENDOOR, plr[pnum].plrlevel);
	}

	return sizeof(*pCmd);
}

void __fastcall delta_sync_object(int oi, BYTE bCmd, BYTE bLevel)
{
	if (gbMaxPlayers != 1) {
		sgbDeltaChanged = 1;
		sgLevels[bLevel].object[oi].bCmd = bCmd;
	}
}
// 67618C: using guessed type char sgbDeltaChanged;
// 679660: using guessed type char gbMaxPlayers;

int __fastcall On_CLOSEDOOR(TCmdParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else {
		if (currlevel == plr[pnum].plrlevel)
			SyncOpObject(pnum, CMD_CLOSEDOOR, pCmd->wParam1);
		delta_sync_object(pCmd->wParam1, CMD_CLOSEDOOR, plr[pnum].plrlevel);
	}

	return sizeof(*pCmd);
}

int __fastcall On_OPERATEOBJ(TCmdParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else {
		if (currlevel == plr[pnum].plrlevel)
			SyncOpObject(pnum, CMD_OPERATEOBJ, pCmd->wParam1);
		delta_sync_object(pCmd->wParam1, CMD_OPERATEOBJ, plr[pnum].plrlevel);
	}

	return sizeof(*pCmd);
}

int __fastcall On_PLROPOBJ(TCmdParam2 *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else {
		if (currlevel == plr[pnum].plrlevel)
			SyncOpObject(pCmd->wParam1, CMD_PLROPOBJ, pCmd->wParam2);
		delta_sync_object(pCmd->wParam2, CMD_PLROPOBJ, plr[pnum].plrlevel);
	}

	return sizeof(*pCmd);
}

int __fastcall On_BREAKOBJ(TCmdParam2 *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else {
		if (currlevel == plr[pnum].plrlevel)
			SyncBreakObj(pCmd->wParam1, pCmd->wParam2);
		delta_sync_object(pCmd->wParam2, CMD_BREAKOBJ, plr[pnum].plrlevel);
	}

	return sizeof(*pCmd);
}

int __fastcall On_CHANGEPLRITEMS(TCmdChItem *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else if (pnum != myplr)
		CheckInvSwap(pnum, pCmd->bLoc, pCmd->wIndx, pCmd->wCI, pCmd->dwSeed, pCmd->bId);

	return sizeof(*pCmd);
}

int __fastcall On_DELPLRITEMS(TCmdDelItem *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else if (pnum != myplr)
		inv_update_rem_item(pnum, pCmd->bLoc);

	return sizeof(*pCmd);
}

int __fastcall On_PLRLEVEL(TCmdParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else if (pCmd->wParam1 <= MAXCHARLEVEL && pnum != myplr)
		plr[pnum]._pLevel = pCmd->wParam1;

	return sizeof(*pCmd);
}

int __fastcall On_DROPITEM(TCmdPItem *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else
		delta_put_item(pCmd, pCmd->x, pCmd->y, plr[pnum].plrlevel);

	return sizeof(*pCmd);
}

int __fastcall On_SEND_PLRINFO(TCmdPlrInfoHdr *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, pCmd->wBytes + sizeof(*pCmd));
	else
		multi_player_joins(pnum, pCmd, pCmd->bCmd == CMD_ACK_PLRINFO);

	return pCmd->wBytes + sizeof(*pCmd);
}

int __fastcall On_ACK_PLRINFO(TCmdPlrInfoHdr *pCmd, int pnum)
{
	return On_SEND_PLRINFO(pCmd, pnum);
}

int __fastcall On_PLAYER_JOINLEVEL(TCmdLocParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else {
		plr[pnum]._pLvlChanging = 0;
		if (plr[pnum]._pName[0] && !plr[pnum].plractive) {
			plr[pnum].plractive = 1;
			gbActivePlayers++;
			EventPlrMsg("Player '%s' (level %d) just joined the game", plr[pnum]._pName, plr[pnum]._pLevel);
		}

		if (plr[pnum].plractive && myplr != pnum) {
			plr[pnum].WorldX = pCmd->x;
			plr[pnum].WorldY = pCmd->y;
			plr[pnum].plrlevel = pCmd->wParam1;
			plr[pnum]._pGFXLoad = 0;
			if (currlevel == plr[pnum].plrlevel) {
				LoadPlrGFX(pnum, PFILE_STAND);
				SyncInitPlr(pnum);
				if ((plr[pnum]._pHitPoints >> 6) > 0)
					StartStand(pnum, 0);
				else {
					plr[pnum]._pgfxnum = 0;
					LoadPlrGFX(pnum, PFILE_DEATH);
					plr[pnum]._pmode = PM_DEATH;
					NewPlrAnim(pnum, plr[pnum]._pDAnim[0], plr[pnum]._pDFrames, 1, plr[pnum]._pDWidth);
					plr[pnum]._pAnimFrame = plr[pnum]._pAnimLen - 1;
					plr[pnum]._pVar8 = plr[pnum]._pAnimLen << 1;
					dFlags[plr[pnum].WorldX][plr[pnum].WorldY] |= DFLAG_DEAD_PLAYER;
				}

				plr[pnum]._pvid = AddVision(plr[pnum].WorldX, plr[pnum].WorldY, plr[pnum]._pLightRad, pnum == myplr);
				plr[pnum]._plid = -1;
			}
		}
	}

	return sizeof(*pCmd);
}

int __fastcall On_ACTIVATEPORTAL(TCmdLocParam3 *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else {
		ActivatePortal(pnum, pCmd->x, pCmd->y, pCmd->wParam1, pCmd->wParam2, pCmd->wParam3);
		if (pnum != myplr) {
			if (currlevel == 0)
				AddInTownPortal(pnum);
			else if (currlevel == plr[pnum].plrlevel) {
				int i;
				BOOL addPortal = TRUE;
				for (i = 0; i < nummissiles; i++) {
					int mi = missileactive[i];
					if (missile[mi]._mitype == MIS_TOWN && missile[mi]._misource == pnum) {
						addPortal = FALSE;
						// BUGFIX: break
					}
				}
				if (addPortal)
					AddWarpMissile(pnum, pCmd->x, pCmd->y);
			} else
				RemovePortalMissile(pnum);
		}
		delta_open_portal(pnum, pCmd->x, pCmd->y, pCmd->wParam1, pCmd->wParam2, pCmd->wParam3);
	}

	return sizeof(*pCmd);
}

void __fastcall delta_open_portal(int pnum, BYTE x, BYTE y, BYTE bLevel, BYTE bLType, BYTE bSetLvl)
{
	sgbDeltaChanged = 1;
	sgJunk.portal[pnum].x = x;
	sgJunk.portal[pnum].y = y;
	sgJunk.portal[pnum].level = bLevel;
	sgJunk.portal[pnum].ltype = bLType;
	sgJunk.portal[pnum].setlvl = bSetLvl;
}
// 67618C: using guessed type char sgbDeltaChanged;

int __fastcall On_DEACTIVATEPORTAL(TCmd *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else {
		if (PortalOnLevel(pnum))
			RemovePortalMissile(pnum);
		DeactivatePortal(pnum);
		RemovePlrPortal(pnum);
	}

	return sizeof(*pCmd);
}

int __fastcall On_RETOWN(TCmd *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else {
		if (pnum == myplr) {
			deathflag = FALSE;
			gamemenu_off();
		}
		RestartTownLvl(pnum);
	}

	return sizeof(*pCmd);
}

int __fastcall On_SETSTR(TCmdParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else if (pCmd->wParam1 <= 750 && pnum != myplr)
		SetPlrStr(pnum, pCmd->wParam1);

	return sizeof(*pCmd);
}

int __fastcall On_SETDEX(TCmdParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else if (pCmd->wParam1 <= 750 && pnum != myplr)
		SetPlrDex(pnum, pCmd->wParam1);

	return sizeof(*pCmd);
}

int __fastcall On_SETMAG(TCmdParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else if (pCmd->wParam1 <= 750 && pnum != myplr)
		SetPlrMag(pnum, pCmd->wParam1);

	return sizeof(*pCmd);
}

int __fastcall On_SETVIT(TCmdParam1 *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else if (pCmd->wParam1 <= 750 && pnum != myplr)
		SetPlrVit(pnum, pCmd->wParam1);

	return sizeof(*pCmd);
}

int __fastcall On_STRING(TCmdString *pCmd, int pnum)
{
	return On_STRING2(pnum, pCmd);
}

int __fastcall On_STRING2(int pnum, TCmdString *pCmd)
{
	int len = strlen(pCmd->str);
	if (!gbBufferMsgs)
		SendPlrMsg(pnum, pCmd->str);

	return len + 2; // length of string + nul terminator + sizeof(pCmd->bCmd)
}

int __fastcall On_SYNCQUEST(TCmdQuest *pCmd, int pnum)
{
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else {
		if (pnum != myplr)
			SetMultiQuest(pCmd->q, pCmd->qstate, pCmd->qlog, pCmd->qvar1);
		sgbDeltaChanged = 1;
	}

	return sizeof(*pCmd);
}

int __fastcall On_ENDSHIELD(TCmd *pCmd, int pnum)
{
	int i;

	if (gbBufferMsgs != 1 && pnum != myplr && currlevel == plr[pnum].plrlevel) {
		for (i = 0; i < nummissiles; i++) {
			int mi = missileactive[i];
			if (missile[mi]._mitype == MIS_MANASHIELD && missile[mi]._misource == pnum) {
				ClearMissileSpot(mi);
				DeleteMissile(mi, i);
			}
		}
	}

	return sizeof(*pCmd);
}

int __fastcall On_CHEAT_EXPERIENCE(TCmd *pCmd, int pnum)
{
#ifdef _DEBUG
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else if (plr[pnum]._pLevel < MAXCHARLEVEL - 1) {
		plr[pnum]._pExperience = plr[pnum]._pNextExper;
		NextPlrLevel(pnum);
	}
#endif
	return sizeof(*pCmd);
}

int __fastcall On_CHEAT_SPELL_LEVEL(TCmd *pCmd, int pnum)
{
#ifdef _DEBUG
	if (gbBufferMsgs == 1)
		msg_send_packet(pnum, pCmd, sizeof(*pCmd));
	else
		plr[pnum]._pSplLvl[plr[pnum]._pRSpell]++;
#endif
	return sizeof(*pCmd);
}

int __cdecl On_DEBUG(TCmd *pCmd)
{
	return sizeof(*pCmd);
}

int __fastcall On_NOVA(TCmdLoc *pCmd, int pnum)
{
	if (gbBufferMsgs != 1 && currlevel == plr[pnum].plrlevel && pnum != myplr) {
		ClrPlrPath(pnum);
		plr[pnum]._pSpell = SPL_NOVA;
		plr[pnum]._pSplType = 4;
		plr[pnum]._pSplFrom = 3;
		plr[pnum].destAction = ACTION_SPELL;
		plr[pnum].destParam1 = pCmd->x;
		plr[pnum].destParam2 = pCmd->y;
	}

	return sizeof(*pCmd);
}

int __fastcall On_SETSHIELD(TCmd *pCmd, int pnum)
{
	if (gbBufferMsgs != 1)
		plr[pnum].pManaShield = 1;

	return sizeof(*pCmd);
}

int __fastcall On_REMSHIELD(TCmd *pCmd, int pnum)
{
	if (gbBufferMsgs != 1)
		plr[pnum].pManaShield = 0;

	return sizeof(*pCmd);
}
