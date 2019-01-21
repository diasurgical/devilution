//HEADER_GOES_HERE
#ifndef __MULTI_H__
#define __MULTI_H__

extern char gbSomebodyWonGameKludge; // weak
extern char szPlayerDescript[128];
extern short sgwPackPlrOffsetTbl[MAX_PLRS];
extern PkPlayerStruct netplr[MAX_PLRS];
extern int dword_678628; // weak
extern BYTE gbActivePlayers;
extern char gbGameDestroyed; // weak
extern char byte_678640;     // weak
extern BYTE gbMaxPlayers;
extern char szPlayerName[128];
extern BYTE gbDeltaSender; // weak
extern int player_state[MAX_PLRS];

void __fastcall multi_msg_add(BYTE *a1, unsigned char a2);
void __fastcall NetSendLoPri(BYTE *pbMsg, BYTE bLen);
void __fastcall multi_copy_packet(TBuffer *a1, void *packet, BYTE size);
void __fastcall multi_send_packet(void *packet, BYTE dwSize);
void __fastcall NetRecvPlrData(TPkt *pkt);
void __fastcall NetSendHiPri(BYTE *pbMsg, BYTE bLen);
unsigned char *__fastcall multi_recv_packet(TBuffer *packet, unsigned char *a2, int *a3);
void __fastcall multi_send_msg_packet(int a1, BYTE *a2, BYTE len);
void __cdecl multi_msg_countdown();
void __fastcall multi_parse_turn(int pnum, int turn);
void __fastcall multi_handle_turn_upper_bit(int pnum);
void __fastcall multi_player_left(int pnum, int reason);
void __cdecl multi_clear_left_tbl();
void __fastcall multi_player_left_msg(int pnum, int left);
void __cdecl multi_net_ping();
int __cdecl multi_handle_delta();
int __fastcall multi_check_pkt_valid(TBuffer *a1);
void __cdecl multi_mon_seeds();
void __cdecl multi_begin_timeout();
void __cdecl multi_check_drop_player();
void __cdecl multi_process_network_packets();
void __fastcall multi_handle_all_packets(int players, TPkt *packet, int a3);
void __cdecl multi_process_tmsgs();
void __fastcall multi_send_zero_packet(int pnum, char a2, void *pbSrc, int dwLen);
void __cdecl NetClose();
char __fastcall multi_event_handler(int a1);
void __stdcall multi_handle_events(_SNETEVENT *pEvt);
int __fastcall NetInit(int bSinglePlayer, int *pfExitProgram);
void __fastcall buffer_init(TBuffer *pBuf);
void __fastcall multi_send_pinfo(int pnum, char cmd);
int __fastcall InitNewSeed(int newseed);
void __cdecl SetupLocalCoords();
int __fastcall multi_init_single(_SNETPROGRAMDATA *client_info, _SNETPLAYERDATA *user_info, _SNETUIDATA *ui_info);
int __fastcall multi_init_multi(_SNETPROGRAMDATA *client_info, _SNETPLAYERDATA *user_info, _SNETUIDATA *ui_info, int *a4);
int __fastcall multi_upgrade(int *a1);
void __fastcall multi_player_joins(int pnum, TCmdPlrInfoHdr *cmd, int a3);

/* rdata */

extern const int multi_inf; // weak
extern const int event_types[3];

#endif /* __MULTI_H__ */
