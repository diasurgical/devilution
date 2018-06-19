//HEADER_GOES_HERE

//error
extern char msgtable[80];
extern char msgdelay; // weak
extern char msgflag; // weak
extern char msgcnt; // weak

void __fastcall InitDiabloMsg(char e);
void __cdecl ClrDiabloMsg();
void __cdecl DrawDiabloMsg();

/* data */
extern char *MsgStrings[44];