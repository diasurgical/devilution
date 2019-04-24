//HEADER_GOES_HERE
#ifndef __CODEC_H__
#define __CODEC_H__

int codec_decode(void *pbSrcDst, int size, char *pszPassword);
void codec_init_key(int unused, char *pszPassword);
int codec_get_encoded_len(int dwSrcBytes);
void codec_encode(void *pbSrcDst, int size, int size_64, char *pszPassword);

#endif /* __CODEC_H__ */
