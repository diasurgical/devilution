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

//encrypt
extern int encrypt_table[1280];
//int encrypt_52B564[257];

void __fastcall encrypt_decrypt_block(void *block, int size, int key);
void __fastcall encrypt_encrypt_block(void *block, int size, int key);
int __fastcall encrypt_hash(char *s, int type);
void __cdecl encrypt_init_lookup_table();
int __fastcall encrypt_compress(void *buf, int size);
unsigned int __cdecl encrypt_pkware_read(char *buf, unsigned int *size, void *param);
void __cdecl encrypt_pkware_write(char *buf, unsigned int *size, void *param);
void __fastcall encrypt_decompress(void *param, int recv_size, int dwMaxBytes);