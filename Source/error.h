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