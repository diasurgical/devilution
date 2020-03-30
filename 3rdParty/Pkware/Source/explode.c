
#define EXPLODE
#include "tables.inc"

#include "implode.h"

#ifndef FALSE
   #define FALSE   0
#endif

#ifndef TRUE		
   #define TRUE    1
#endif

#ifndef NULL
   #define NULL ((void *)0)
#endif

//#define DEBUG_COPY
//#define DEBUG_LIT
//#include <stdio.h>

static char Copyright[] = { \
   "PKWARE Data Compression Library for Win32\r\n" \
   "Copyright 1989-1995 PKWARE Inc.  All Rights Reserved.\r\n" \
   "Patent No. 5,051,745\r\n" \
   "PKWARE Data Compression Library Reg. U.S. Pat. and Tm. Off.\r\n" \
   "Version 1.11" };

#define VOID   void
#define CHAR   char           /* 8 bits,  signed   */
#define UCHAR  unsigned char   /* 8 bits,  unsigned */
#define SHORT  signed short    /* 16 bits, signed   */
#define USHORT unsigned short  /* 16 bits, unsigned */
#define UINT   unsigned int
#define INT    int
#define LONG   signed long     /* 32 bits, signed   */
#define ULONG  unsigned long   /* 32 bits, unsigned */

#define MAX_DICT_SIZE 4096
#define EXP_BUFSIZE   4096
#define OUT_SIZE      2048
#define FOO_SIZE      2304
#define MINREP        2
#define SIZE_DIST     64
#define SIZE_LEN      16
#define MAXREP       (MINREP+(8*1)+2+4+8+16+32+64+128+256-4)
#define SIZE_LIT     (256+MAXREP+2)
#define EOF_CODE     (SIZE_LIT-1)
#define ABORT_CODE   (EOF_CODE+1)

typedef struct EXP_DATA
{
   UINT   Distance;
   UINT   Mode;
   UINT   OutPtr;
   UINT   ExtDistBits;
   UINT   ExtDistMask;
   UINT   LookAhead;
   UINT   LookBits;
   UINT   InPtr;
   UINT   InBufCnt;
   VOID   *Param;
   #ifdef SYSLINK
      UINT (* _System GetBuf)(CHAR *buffer, UINT *size, VOID *Param);
      VOID (* _System PutBuf)(CHAR *buffer, UINT *size, VOID *Param);
   #else
      UINT (*GetBuf)(CHAR *buffer, UINT *size, VOID *Param);
      VOID   (*PutBuf)(CHAR *buffer, UINT *size, VOID *Param);
   #endif
   UCHAR  OutBuf[(EXP_BUFSIZE*2)+MAXREP];
   UCHAR  InBuf[OUT_SIZE];
   UCHAR DistDecode[256];
   UCHAR LenDecode[256];
   UCHAR ChLow[256];
   UCHAR ChMid1[256];
   UCHAR ChMid2[128];
   UCHAR ChHi[256];
   UCHAR ChBits[256];
   UCHAR DistBits[SIZE_DIST];
   UCHAR LenBits[SIZE_LEN];
   UCHAR ExLenBits[SIZE_LEN];
   USHORT LenBase[SIZE_LEN];
};

/****************************************************
     Function Declarations
****************************************************/

static UINT Expand(struct EXP_DATA *Exp);
static UINT DecodeLit(struct EXP_DATA *Exp);
static UINT DecodeDist(struct EXP_DATA *Exp, UINT Len);
static UINT WasteBits(struct EXP_DATA *Exp, UINT Bits);
static VOID GenDecodeTabs(UINT Len, UCHAR *Bits, UCHAR *Code, UCHAR *Decode);
static VOID GenAscTabs(struct EXP_DATA *Exp);
static VOID lmemcpy(VOID *Dest, VOID *Source, UINT Size);

/*************************************************
 Function: explode
**************************************************
*/
#ifdef SYSLINK
UINT _System explode_sys(
   UINT (* _System ReadBuf )(CHAR *Buf, UINT *Size, VOID *Param),
   VOID   (* _System WriteBuf)(CHAR *Buf, UINT *Size, VOID *Param),
#else
UINT explode(
   UINT (*ReadBuf )(CHAR *Buf, UINT *Size, VOID *Param),
   VOID (*WriteBuf)(CHAR *Buf, UINT *Size, VOID *Param),
#endif
   CHAR *WorkBuf, VOID *Param)
{
   struct EXP_DATA *Exp = (struct EXP_DATA  *)WorkBuf;

   Exp->GetBuf = ReadBuf;
   Exp->PutBuf = WriteBuf;
   Exp->Param = Param;

   Exp->InPtr = OUT_SIZE;
   if ((Exp->InBufCnt = (*Exp->GetBuf)((VOID  *)(Exp->InBuf), &Exp->InPtr,
           Exp->Param)) <= 4)
      return CMP_BAD_DATA;

   Exp->Mode = Exp->InBuf[0];
   Exp->ExtDistBits = Exp->InBuf[1];
   Exp->LookAhead = Exp->InBuf[2];
   Exp->LookBits = 0;
   Exp->InPtr = 3;

   if (Exp->ExtDistBits < 4 || Exp->ExtDistBits > 6)
      return CMP_INVALID_DICTSIZE;
   Exp->ExtDistMask = 0xFFFF >> (16 - Exp->ExtDistBits);

   switch (Exp->Mode)
   {
      case CMP_ASCII:
    lmemcpy(Exp->ChBits,ChBitsAsc,sizeof(ChBitsAsc));
    GenAscTabs(Exp);
         break;
      case CMP_BINARY:
    break;
      default:
    return CMP_INVALID_MODE;
   }

   lmemcpy(Exp->LenBits,LenBits,sizeof(LenBits));
   GenDecodeTabs(SIZE_LEN, Exp->LenBits, LenCode, Exp->LenDecode);
   lmemcpy(Exp->ExLenBits,ExLenBits,sizeof(ExLenBits));
   lmemcpy(Exp->LenBase,LenBase,sizeof(LenBase));

   lmemcpy(Exp->DistBits,DistBits,sizeof(DistBits));
   GenDecodeTabs(SIZE_DIST, Exp->DistBits, DistCode, Exp->DistDecode);

   if (Expand(Exp) == ABORT_CODE)
      return CMP_ABORT;

   return CMP_NO_ERROR;
}

/**************************************************
 Function: Expand
***************************************************
*/
static UINT Expand(struct EXP_DATA *Exp)
{
   UINT Len, Dist, i;
   CHAR *Src, *Dest;

   Exp->OutPtr = EXP_BUFSIZE;
   while ((Len = DecodeLit(Exp)) < EOF_CODE)
   {
      if (Len < 256)
	  {
		 #ifdef DEBUG_LIT
			printf("Ch=%02x\n",Len);
		 #endif
         Exp->OutBuf[Exp->OutPtr++] = (UCHAR)Len;
	  }
      else
      {
         Len -= (256 - MINREP);
         if ((Dist = DecodeDist(Exp, Len)) == 0)
         {
            Len = ABORT_CODE;
            break;
         }
		 #ifdef DEBUG_COPY
			printf("Copy-%d %d\n",Len,Dist);
		 #endif
         Dest = &Exp->OutBuf[Exp->OutPtr];
         Src = Dest - Dist;
         Exp->OutPtr += Len;
         do {
            *Dest++ = *Src++;
         } while (--Len);
      }

      if (Exp->OutPtr >= EXP_BUFSIZE*2)
      {
         Len = EXP_BUFSIZE;
         (* Exp->PutBuf)(&Exp->OutBuf[EXP_BUFSIZE], &Len, Exp->Param);
         lmemcpy(Exp->OutBuf, &Exp->OutBuf[EXP_BUFSIZE],
            Exp->OutPtr-EXP_BUFSIZE);
         Exp->OutPtr -= EXP_BUFSIZE;
      }
   }

   i = Exp->OutPtr - EXP_BUFSIZE;
   (* Exp->PutBuf)(&Exp->OutBuf[EXP_BUFSIZE], &i, Exp->Param);

   return Len;
}

/**************************************************
 Function: DecodeLit
***************************************************
*/
static UINT DecodeLit(struct EXP_DATA *Exp)
{
   UINT LitChar, i;

   if (Exp->LookAhead & 1)          /* Length found */
   {
      if (WasteBits(Exp, 1))
         return ABORT_CODE;
      LitChar = Exp->LenDecode[Exp->LookAhead & 0xFF];
      if (WasteBits(Exp, Exp->LenBits[LitChar]))
         return ABORT_CODE;
      if (Exp->ExLenBits[LitChar])
      {
         i = Exp->LookAhead & ((1 << Exp->ExLenBits[LitChar]) - 1);
         if (WasteBits(Exp, Exp->ExLenBits[LitChar]))
         {
            if (LitChar + i != 15 + 255)     /* If not EOF */
               return ABORT_CODE;
         }
         LitChar = Exp->LenBase[LitChar] + i;
      }
      LitChar += 256;
   }
   else                        /* Character found */
   {
      if (WasteBits(Exp, 1))
         return ABORT_CODE;
      if (Exp->Mode == CMP_BINARY)
      {
         LitChar = Exp->LookAhead & 0xFF;
         if (WasteBits(Exp, 8))
            return ABORT_CODE;
      }
      else
      {
    if (Exp->LookAhead & 0xFF)           /* Low/Mid tab */
    {
       if ((LitChar = Exp->ChLow[Exp->LookAhead & 0xFF]) == 0xFF)
       {
          if (Exp->LookAhead & 0x3F)     /* Mid tab 1 */
          {
        if (WasteBits(Exp, 4))
           return ABORT_CODE;
        LitChar = Exp->ChMid1[Exp->LookAhead & 0xFF];
          }
          else                           /* Mid tab 2 */
          {
        if (WasteBits(Exp, 6))
           return ABORT_CODE;
        LitChar = Exp->ChMid2[Exp->LookAhead & 0x7F];
          }
       }
    }
    else                                 /* High tab */
    {
       if (WasteBits(Exp, 8))
          return ABORT_CODE;
       LitChar = Exp->ChHi[Exp->LookAhead & 0xFF];
    }
    if (WasteBits(Exp, Exp->ChBits[LitChar]))
       return ABORT_CODE;
      }
   }
   return LitChar;
}

/**************************************************
 Function: DecodeDist
***************************************************
*/
static UINT DecodeDist(struct EXP_DATA *Exp, UINT Len)
{
   UINT Dist;

   Dist = Exp->DistDecode[Exp->LookAhead & 0xFF];
   if (WasteBits(Exp, Exp->DistBits[Dist]))
      return 0;

   if (Len == MINREP)
   {
      Dist <<= 2;
      Dist |= Exp->LookAhead & 3;
      if (WasteBits(Exp, 2))
    return 0;
   }
   else
   {
      Dist <<= Exp->ExtDistBits;
      Dist |= Exp->LookAhead & Exp->ExtDistMask;
      if (WasteBits(Exp, Exp->ExtDistBits))
         return 0;
   }

   return Dist+1;
}

/**************************************************
 Function: WasteBits
***************************************************
*/
static UINT WasteBits(struct EXP_DATA *Exp, UINT Bits)
{
   if (Bits <= Exp->LookBits)
   {
      Exp->LookAhead >>= Bits;
      Exp->LookBits -= Bits;
      return 0;
   }

   Exp->LookAhead >>= Exp->LookBits;

   if (Exp->InPtr == Exp->InBufCnt)
   {
      Exp->InPtr = OUT_SIZE;
      if ((Exp->InBufCnt = (*Exp->GetBuf)((VOID  *)(Exp->InBuf), &Exp->InPtr,
              Exp->Param)) == 0)
         return 1;
      Exp->InPtr = 0;
   }

   Exp->LookAhead |= (Exp->InBuf[Exp->InPtr])<<8;
   ++Exp->InPtr;
   Exp->LookAhead >>= (Bits - Exp->LookBits);
   Exp->LookBits = 8-(Bits-Exp->LookBits);
   return 0;
}

/*************************************************
 Function: GenDecodeTabs
**************************************************
*/
static VOID GenDecodeTabs(UINT Len, UCHAR *Bits, UCHAR *Code, UCHAR *Decode)
{
   UINT j, Incr;
   INT i;

   for (i=Len-1; i>=0; i--)
   {
      Incr = 1 << Bits[i];
      j = Code[i];
      do
      {
         Decode[j] = (UCHAR)i;
         j += Incr;
      } while (j<256);
   }
}

/*#pragma optimize("z",off)*/

/**************************************************
 Function: GenAscTabs
***************************************************
*/
static VOID GenAscTabs(struct EXP_DATA *Exp)
{
   UINT j, Incr;
   INT  i;

   for (i=255; i>=0; i--)
   {
      if (Exp->ChBits[i] <= 8)
      {
    Incr = 1 << Exp->ChBits[i];
    j = ChCodeAsc[i];
    do
    {
       Exp->ChLow[j] = (UCHAR)i;
            j += Incr;
         } while (j < 256);
      }
      else if (ChCodeAsc[i] & 0xFF)
      {
         Exp->ChLow[ChCodeAsc[i] & 0xFF] = 0xFF;
    if (ChCodeAsc[i] & 0x3F)
         {
            Exp->ChBits[i] -= 4;
            Incr= 1 << Exp->ChBits[i];
            j = ChCodeAsc[i] >> 4;
            do
       {
               Exp->ChMid1[j] = (UCHAR)i;
               j += Incr;
            } while (j < 256);
         }
         else
         {
       Exp->ChBits[i] -= 6;
            Incr = 1 << Exp->ChBits[i];
            j = ChCodeAsc[i] >> 6;
            do
            {
               Exp->ChMid2[j] = (UCHAR)i;
          j += Incr;
            } while (j<128);
         }
      }
      else
      {
         Exp->ChBits[i] -= 8;
    Incr = 1 << Exp->ChBits[i];
         j = ChCodeAsc[i] >> 8;
         do
         {
            Exp->ChHi[j] = (UCHAR)i;
            j += Incr;
    } while (j < 256);
      }
   }
}


/***************************************************
 Function: lmemcpy
****************************************************
*/

static VOID lmemcpy(VOID *Dest, VOID *Source, UINT Size)
{
   UCHAR  *s=(UCHAR  *)Source,  *t=(UCHAR  *)Dest;
#ifndef _ALPHA
   UINT count=Size/4;

   if (count)
     { do
         { *(ULONG *)t = *(ULONG *)s;
           s+=4;
      t+=4;
    }
      while (--count);
     }

   if (Size %= 4)
#endif
     do {
      *t++=*s++;
   } while (--Size);
}





