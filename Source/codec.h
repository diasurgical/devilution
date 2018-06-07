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

int __fastcall codec_decode(void *pbSrcDst, int size, char *pszPassword);
void __fastcall codec_init_key(int unused, char *pszPassword);
int __fastcall codec_get_encoded_len(int dwSrcBytes);
void __fastcall codec_encode(void *pbSrcDst, int size, int size_64, char *pszPassword);