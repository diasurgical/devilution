//HEADER_GOES_HERE

#include "../types.h"

DWORD hashtable[1280];

void __fastcall Decrypt(void *block, DWORD size, DWORD key)
{
    DWORD *castBlock = (DWORD *)block;
    DWORD seed = 0xEEEEEEEE;
    for (DWORD i = 0; i < (size >> 2); i++) {
        seed += hashtable[0x400 + (key & 0xFF)];
        *castBlock ^= seed + key;
        seed += *castBlock + (seed << 5) + 3;
        key = ((~key << 0x15) + 0x11111111) | (key >> 0x0B);
        castBlock++;
    }
}

void __fastcall Encrypt(void *block, DWORD size, DWORD key)
{
    DWORD *castBlock = (DWORD *)block;
    DWORD seed = 0xEEEEEEEE;
    for (DWORD i = 0; i < (size >> 2); i++) {
        DWORD ch = *castBlock;
        seed += hashtable[0x400 + (key & 0xFF)];
        *castBlock ^= seed + key;
        seed += ch + (seed << 5) + 3;
        key = ((~key << 0x15) + 0x11111111) | (key >> 0x0B);
        castBlock++;
    }
}

DWORD __fastcall Hash(const char *s, int type)
{
    char ch;
    DWORD seed1 = 0x7FED7FED;
    DWORD seed2 = 0xEEEEEEEE;
    while (s != NULL && *s) {
        ch = *s++;
        ch = toupper(ch);
        seed1 = hashtable[(type << 8) + ch] ^ (seed1 + seed2);
        seed2 += ch + seed1 + (seed2 << 5) + 3;
    }
    return seed1;
}

void __cdecl InitHash()
{
    DWORD seed = 0x00100001;

    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 5; j++) {
            seed = (125 * seed + 3) % 0x2AAAAB;
            DWORD ch = (seed & 0xFFFF);
            seed = (125 * seed + 3) % 0x2AAAAB;
            hashtable[i + j * 256] = ch << 16 | (seed & 0xFFFF);
        }
    }
}

int __fastcall PkwareCompress(void *buf, int size)
{
    BYTE *srcData = (BYTE *)buf;
    char *ptr = (char *)DiabloAllocPtr(CMP_BUFFER_SIZE);

    unsigned int destSize = 2 * size;
    if (destSize < 8192)
        destSize = 8192;

    BYTE *destData = (BYTE *)DiabloAllocPtr(destSize);

    TDataInfo param;
    param.srcData = srcData;
    param.srcOffset = 0;
    param.destData = destData;
    param.destOffset = 0;
    param.size = size;

    unsigned int type = 0;
    unsigned int dsize = 4096;
    implode(PkwareBufferRead, PkwareBufferWrite, ptr, &param, &type, &dsize);

    if (param.destOffset < size) {
        memcpy(srcData, destData, param.destOffset);
        size = param.destOffset;
    }

    mem_free_dbg(ptr);
    mem_free_dbg(destData);

    return size;
}

unsigned int __cdecl PkwareBufferRead(char *buf, unsigned int *size, void *param)
{
    TDataInfo *pInfo = (TDataInfo *)param;

    DWORD sSize;
    if (*size >= pInfo->size - pInfo->srcOffset) {
        sSize = pInfo->size - pInfo->srcOffset;
    } else {
        sSize = *size;
    }

    memcpy(buf, pInfo->srcData + pInfo->srcOffset, sSize);
    pInfo->srcOffset += sSize;

    return sSize;
}

void __cdecl PkwareBufferWrite(char *buf, unsigned int *size, void *param)
{
    TDataInfo *pInfo = (TDataInfo *)param;

    memcpy(pInfo->destData + pInfo->destOffset, buf, *size);
    pInfo->destOffset += *size;
}

void __fastcall PkwareDecompress(void *param, int recv_size, int dwMaxBytes)
{
    char *ptr = (char *)DiabloAllocPtr(CMP_BUFFER_SIZE);
    BYTE *pbInBuff = (BYTE *)param;
    BYTE *pbOutBuff = DiabloAllocPtr(dwMaxBytes);

    TDataInfo info;
    info.srcData = pbInBuff;
    info.srcOffset = 0;
    info.destData = pbOutBuff;
    info.destOffset = 0;
    info.size = recv_size;

    explode(PkwareBufferRead, PkwareBufferWrite, ptr, &info);
    memcpy(pbInBuff, pbOutBuff, info.destOffset);
    mem_free_dbg(ptr);
    mem_free_dbg(pbOutBuff);
}
