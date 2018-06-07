/*
 * UNPUBLISHED -- Rights  reserved  under  the  copyright  laws  of the
 * United States.  Use  of a copyright notice is precautionary only and
 * does not imply publication or disclosure.
 *
 * THIS DOCUMENTATION CONTAINS CONFIDENTIAL AND PROPRIETARY INFORMATION
 * OF    BLIZZARD   ENTERTAINMENT.    ANY   DUPLICATION,  MODIFICATION,
 * DISTRIBUTION, OR DISCLOSURE IS STRICTLY PROHIBITED WITHOUT THE PRIOR
 * EXPRESS WRITTEN PERMISSION OF BLIZZARD ENTERTAINMENT.
 */

//quests
extern int qtopline; // idb
extern int questlog; // weak
extern void *pQLogCel;
extern QuestStruct quests[16];
extern int qline; // weak
extern int qlist[16];
extern int numqlines; // weak
extern int WaterDone; // idb
extern int ReturnLvlY; // idb
extern int ReturnLvlX; // idb
extern int ReturnLvlT; // idb
extern int ALLQUESTS; // idb
extern int ReturnLvl; // idb

void __cdecl InitQuests();
void __cdecl CheckQuests();
bool __cdecl ForceQuests();
bool __fastcall QuestStatus(int i);
void __fastcall CheckQuestKill(int m, unsigned char sendmsg);
void __cdecl DrawButcher();
void __fastcall DrawSkelKing(int quest_id, int xx, int yy);
void __fastcall DrawWarLord(int xx, int yy);
void __fastcall DrawSChamber(int quest_id, int xx, int yy);
void __fastcall DrawLTBanner(int xx, int yy);
void __fastcall DrawBlind(int xx, int yy);
void __fastcall DrawBlood(int xx, int yy);
void __fastcall DRLG_CheckQuests(int xx, int yy);
void __cdecl SetReturnLvlPos();
void __cdecl GetReturnLvlPos();
void __cdecl ResyncMPQuests();
void __cdecl ResyncQuests();
void __fastcall PrintQLString(int x, int y, unsigned char cjustflag, char *str, int col);
void __cdecl DrawQuestLog();
void __cdecl StartQuestlog();
void __cdecl QuestlogUp();
void __cdecl QuestlogDown();
void __cdecl QuestlogEnter();
void __cdecl QuestlogESC();
void __fastcall SetMultiQuest(int q, int s, unsigned char l, int v1);

/* rdata */
extern QuestData questlist[16];
extern char questxoff[7];
extern char questyoff[7];
extern char *questtrigstr[5];
extern int QuestGroup1[3];
extern int QuestGroup2[3];
extern int QuestGroup3[3];
extern int QuestGroup4[2];
