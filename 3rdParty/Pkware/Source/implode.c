
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
   "Copyright 1989-1995 PKWARE Inc.  All Rights Reserved\r\n" \
   "Patent No. 5,051,745\r\n" \
   "PKWARE Data Compression Library Reg. U.S. Pat. and Tm. Off.\r\n" \
   "Version 1.11" };

#define VOID   void
#define CHAR   char            /* 8 bits,  signed   */
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

typedef struct CMP_DATA
{
   UINT  Distance;
   UINT  OutPtr;
   UINT  OutPos;
   UINT  ExtDistBits;
   UINT  ExtDistMask;
   UINT  Mode;
   UINT  DictSize;
   UCHAR DistBits[SIZE_DIST];
   UCHAR DistCode[SIZE_DIST];
   UCHAR LitBits[SIZE_LIT];
   USHORT LitCode[SIZE_LIT];
   VOID  *Param;
   #ifdef SYSLINK
     UINT (* _System GetBuf)(UCHAR *buffer, UINT *size, VOID *Param);
     VOID (* _System PutBuf)(UCHAR *buffer, UINT *size, VOID *Param);
   #else
     UINT (*GetBuf)(UCHAR *buffer, UINT *size, VOID *Param);
     VOID (*PutBuf)(UCHAR *buffer, UINT *size, VOID *Param);
   #endif
   SHORT  Next[MAXREP+2];
   USHORT Index[FOO_SIZE+1];
   UCHAR  OutBuf[OUT_SIZE+2];
   UCHAR  Buffer[(MAX_DICT_SIZE*2)+MAXREP];
   USHORT SortBuf[(MAX_DICT_SIZE*2)+MAXREP];
};

#define FOO(x)    (4*(x)[0] + 5*(x)[1])

/****************************************************
     Function Declarations
****************************************************/

static VOID WriteCmpData(struct CMP_DATA *Cmp);
static VOID SortBuffer(struct CMP_DATA *Cmp, UCHAR *low, UCHAR *hi);
static UINT FindRep(struct CMP_DATA *Cmp, UCHAR  *Start);
static VOID OutputBits(struct CMP_DATA *Cmp, UINT Cnt, UINT Code);
static VOID lmemcpy(VOID *Dest, VOID *Source, UINT Size);
static VOID lmemset(VOID *Buf, UCHAR ch, UINT Size);
static VOID FlushBuf(struct CMP_DATA *Cmp);


/*******************************************
 Function: Implode
********************************************
*/

#ifdef SYSLINK
UINT _System implode_sys(
      UINT  (* _System ReadBuf)(UCHAR *buffer, UINT *size, VOID *Param),
      VOID  (* _System WriteBuf)(UCHAR *buffer,UINT *size, VOID *Param),
#else
UINT implode(
      UINT (*ReadBuf)(CHAR *buffer, UINT *size, VOID *Param),
      VOID (*WriteBuf)(CHAR *buffer,UINT *size, VOID *Param),
#endif
   CHAR *WorkBuf, VOID *Param, UINT *Mode, UINT *DictSize)
{
   UINT i, j, k;
   struct CMP_DATA *Cmp = (struct CMP_DATA *)WorkBuf;

   Cmp->GetBuf = ReadBuf;
   Cmp->PutBuf = WriteBuf;
   Cmp->DictSize = *DictSize;
   Cmp->Mode = *Mode;
   Cmp->Param = Param;

   Cmp->ExtDistBits = 4;
   Cmp->ExtDistMask = 0xF;
   switch (*DictSize)
   {
      case 4096:
    Cmp->ExtDistBits++;
    Cmp->ExtDistMask |= 0x20;
      case 2048:
    Cmp->ExtDistBits++;
    Cmp->ExtDistMask |= 0x10;
      case 1024:
    break;
      default:
    return CMP_INVALID_DICTSIZE;
   }

   switch (*Mode)
   {
      case CMP_ASCII:
    for (k=0; k<256; k++)
    {
       Cmp->LitBits[k] = (UCHAR)(ChBitsAsc[k] + 1);
       Cmp->LitCode[k] = (USHORT)(ChCodeAsc[k] << 1);
    }
    break;
      case CMP_BINARY:
    for (k=0; k<256; k++)
    {
       Cmp->LitBits[k] = 9;
       Cmp->LitCode[k] = (USHORT)(k << 1);
    }
         break;
      default:
         return CMP_INVALID_MODE;
   }


   for (i=0; i<16; i++)
   {
      for (j=0; j < ( 1U<<ExLenBits[i]); j++, k++)
      {
         Cmp->LitBits[k] = (UCHAR)(LenBits[i] + ExLenBits[i] + 1);
    Cmp->LitCode[k] = (USHORT)((j<<(LenBits[i]+1)) | (LenCode[i]<<1) | 1);
      }
   }

   lmemcpy(Cmp->DistCode,DistCode,sizeof(DistCode));
   lmemcpy(Cmp->DistBits,DistBits,sizeof(DistBits));

   WriteCmpData(Cmp);

   return CMP_NO_ERROR;
}

/*************************************************
  Function: WriteCmpData
**************************************************
*/
static VOID WriteCmpData(struct CMP_DATA *Cmp)
{
   UINT Len, Pass=0, InCnt, CmpEnd = FALSE, i;
   UINT Request, PassReq;
   UCHAR  *Cur,  *Lim;

   Cur = (UCHAR  *)&Cmp->Buffer[Cmp->DictSize+MAXREP];

   Cmp->OutBuf[0] = (UCHAR)Cmp->Mode;
   Cmp->OutBuf[1] = (UCHAR)Cmp->ExtDistBits;
   Cmp->OutPtr = 2;
   lmemset(Cmp->OutBuf+2,0,OUT_SIZE);
   Cmp->OutPos = 0;

   do
   {
      Request = MAX_DICT_SIZE;
      InCnt = 0;
      do
      {
         PassReq = Request;
         if ((i = (*Cmp->GetBuf)((VOID  *)(Cmp->Buffer+Cmp->DictSize+MAXREP+InCnt),
             &PassReq, Cmp->Param)) == 0)
         {
            if (InCnt == 0 && Pass == 0)
            { 
               OutputBits(Cmp, Cmp->LitBits[EOF_CODE], Cmp->LitCode[EOF_CODE]);
               if (Cmp->OutPos != 0)
                  ++Cmp->OutPtr;
               (*Cmp->PutBuf)(Cmp->OutBuf, &Cmp->OutPtr, Cmp->Param);
               return;
            }
            CmpEnd = TRUE;
            break;
         }
         InCnt += i;
         Request -= i;
      } while (Request);

      Lim = (UCHAR  *)&Cmp->Buffer[Cmp->DictSize+InCnt];
      if (CmpEnd)
         Lim += MAXREP;

      switch (Pass)
      {
         case 0:
            SortBuffer(Cmp, Cur,Lim+1);
            ++Pass;  
            if (Cmp->DictSize != 4096)		// Added: 12-14-94
               ++Pass;
            break;
    	 case 1:
            SortBuffer(Cmp, Cur-Cmp->DictSize+MAXREP,Lim+1); ++Pass;  break;
         default:
            SortBuffer(Cmp, Cur-Cmp->DictSize, Lim+1);                break;
      }

      while (Cur < Lim)
      {
         Len = FindRep(Cmp, Cur);

      SkipFindRep:
         if (Len == 0 || (Len == MINREP && Cmp->Distance >= 256))
         {
	    #ifdef DEBUG_LIT
	       printf("Ch=%02x\n",*Cur);
	    #endif
            OutputBits(Cmp, Cmp->LitBits[*Cur],Cmp->LitCode[*Cur]);
            Cur++;
            continue;
         }

         if (CmpEnd && Cur+Len > Lim)
         {
            Len = (unsigned)(Lim - Cur);
            if (Len < MINREP || (Len == MINREP && Cmp->Distance >= 256))
            { 
 	       #ifdef DEBUG_LIT
	          printf("Ch=%02x\n",*Cur);
	       #endif
               OutputBits(Cmp, Cmp->LitBits[*Cur],Cmp->LitCode[*Cur]);
               Cur++;
               continue;
            }
         }
         else if (Len < 8 && Cur+1 < Lim)
         {
            unsigned savd,savl;

            savd=Cmp->Distance;
            savl=Len;
            Len=FindRep(Cmp, Cur + 1);
            if (Len > savl && (Len > savl+1 || savd > 128))
            {
               #ifdef DEBUG_LIT
                  printf("Ch=%02x\n",*Cur);
	       #endif
               OutputBits(Cmp, Cmp->LitBits[*Cur], Cmp->LitCode[*Cur]);
               ++Cur;
               goto SkipFindRep;
            }
            Len=savl;
            Cmp->Distance=savd;
         }

		 #ifdef DEBUG_COPY
			printf("Copy-%d %d\n",Len,Cmp->Distance+1);
		 #endif
         OutputBits(Cmp, Cmp->LitBits[Len - MINREP + 256],
         Cmp->LitCode[Len - MINREP + 256]);

         if (Len == MINREP)
         {
            OutputBits(Cmp, Cmp->DistBits[Cmp->Distance>>2],
            Cmp->DistCode[Cmp->Distance>>2]);
            OutputBits(Cmp, 2, Cmp->Distance & 3);
         }
         else
         {
            OutputBits(Cmp, Cmp->DistBits[Cmp->Distance>>Cmp->ExtDistBits],
             Cmp->DistCode[Cmp->Distance>>Cmp->ExtDistBits]);
            OutputBits(Cmp, Cmp->ExtDistBits, Cmp->Distance & Cmp->ExtDistMask);
         }
         Cur+=Len;
      }

      if (CmpEnd == FALSE)
      {
         lmemcpy(Cmp->Buffer, Cmp->Buffer+MAX_DICT_SIZE,
         Cmp->DictSize+MAXREP);
         Cur -= MAX_DICT_SIZE;
      }
   } while (CmpEnd == FALSE);

   OutputBits(Cmp, Cmp->LitBits[EOF_CODE], Cmp->LitCode[EOF_CODE]);

   if (Cmp->OutPos != 0)
      ++Cmp->OutPtr;
   (* Cmp->PutBuf)(Cmp->OutBuf, &Cmp->OutPtr, Cmp->Param);
}

/**************************************************
 Function: FindRep
***************************************************
*/
#define KMP_THRESHOLD    10

static UINT FindRep(struct CMP_DATA *Cmp, UCHAR *Start)
{
   INT CurLen=1;
   register INT Len;
   UCHAR  *Pat;
   register UCHAR  *Ptr;
   UINT ind;
   UCHAR  *Lim;
   UINT  HashVal;
   UINT MinIndex;

   ind=Cmp->Index[HashVal=FOO(Start)];
   MinIndex = (UINT)(Start - Cmp->DictSize + 1 - Cmp->Buffer);

   if (MinIndex > Cmp->SortBuf[ind])
   {
      do {
    ++ind;
      } while (MinIndex > Cmp->SortBuf[ind]); /* enddo */
      Cmp->Index[HashVal] = (USHORT)ind;
   }

   Lim=Start-1;

   if ((Ptr = &Cmp->Buffer[Cmp->SortBuf[ind]]) >= Lim)
      return 0;

   Pat=Start;

   do
   {
      if (*(Ptr+CurLen-1) == *(Pat+CurLen-1) && *Ptr == *Pat)
      {
         ++Ptr; ++Pat; Len=2;
         while (*++Ptr==*++Pat && ++Len<MAXREP);
         Pat = Start;
         if (Len >= CurLen)
         {
            Cmp->Distance = (unsigned)(Pat-Ptr+Len-1);
       if ((CurLen=Len) > KMP_THRESHOLD)
       {
               if (Len == MAXREP)
               {
        --(Cmp->Distance);
                  return Len;
               }
          goto DoKMP;
            }
         }
      }
   }
   while ((Ptr = &Cmp->Buffer[Cmp->SortBuf[++ind]]) < Lim);
   return CurLen >= MINREP ? CurLen : 0;
{
SHORT i1, j1;
UCHAR  *BasePtr;

DoKMP:
if (&Cmp->Buffer[Cmp->SortBuf[ind+1]] >= Lim)
  return CurLen;

j1 = Cmp->Next[1] = 0;
Cmp->Next[0] = -1;
i1 = 1;
do
  { if (Pat[i1] == Pat[j1] || (j1 = Cmp->Next[j1]) == -1)
      Cmp->Next[++i1] = ++j1;
  }
while (i1 < CurLen);

Len = CurLen;
Ptr = &Cmp->Buffer[Cmp->SortBuf[ind]+CurLen];

while (TRUE)
  { if ((Len = Cmp->Next[Len]) == -1)
      Len = 0;

    do
    { if ((BasePtr=&Cmp->Buffer[Cmp->SortBuf[++ind]]) >= Lim)
   return CurLen;
    } while (BasePtr+Len < Ptr);

    if (*(BasePtr+CurLen-2) != *(Pat+CurLen-2))
    {
       do {
     if ((BasePtr=&Cmp->Buffer[Cmp->SortBuf[++ind]]) >= Lim)
            return CurLen;
       } while (*(BasePtr+CurLen-2) != *(Pat+CurLen-2) || *BasePtr != *Pat);
      Len = 2;
      Ptr = BasePtr+Len;
    }
    else if (BasePtr+Len != Ptr)
    { Len = 0;
      Ptr = BasePtr;
    }

    while (*Ptr == Pat[Len] && ++Len < MAXREP)
       Ptr++;

    if (Len >= CurLen)
    { Cmp->Distance = (UINT)(Start-BasePtr-1);
      if (Len > CurLen)
        { if (Len == MAXREP)
       return Len;
          CurLen = Len;
     do
       { if (Pat[i1] == Pat[j1] || (j1 = Cmp->Next[j1]) == -1)
      Cmp->Next[++i1] = ++j1;
       }
     while (i1 < CurLen);
        }
    }
  }
}

}

/***************************************************
 Function: OutputBits
****************************************************
*/
static VOID OutputBits(struct CMP_DATA *Cmp, UINT Cnt, UINT Code)
{
   unsigned p;

   if (Cnt > 8)
   {
      OutputBits(Cmp, 8,Code);
      Cnt -= 8;
      Code >>= 8;
   }

   *(Cmp->OutBuf+Cmp->OutPtr) |= Code << (p = Cmp->OutPos);

   if ((Cmp->OutPos = p + Cnt) > 8)
   {
      ++Cmp->OutPtr;
      *(Cmp->OutBuf+Cmp->OutPtr) = (UCHAR)(Code >> (8 - p));
      Cmp->OutPos &= 7;
   }
   else if ((Cmp->OutPos &= 7) == 0)
      ++Cmp->OutPtr;

   if (Cmp->OutPtr >= OUT_SIZE)
      FlushBuf(Cmp);
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
      do 
      {
         *t++=*s++;
      } while (--Size);
}


/**************************************************
 Function: lmemset
***************************************************
*/
static VOID lmemset(VOID *Buf, UCHAR ch, UINT Size)
{
   UCHAR  *s=(UCHAR  *)Buf;
#ifndef _ALPHA
   UINT count=Size/4;
   ULONG Ch2=ch;
   ULONG LongCh = (((((Ch2 << 8) | Ch2) << 8) | Ch2) << 8) | Ch2;

   if (count)
     { do
         { *(ULONG *)s = LongCh;
      s+=4;
    }
      while (--count);
     }

   if (Size %= 4)
#endif
   do {
      *s++=(UCHAR)ch;
   } while (--Size);
}


/**************************************************
 Function: FlushBuf
***************************************************
*/
static VOID FlushBuf(struct CMP_DATA *Cmp)
{
   UCHAR s1, s2;
   UINT i = OUT_SIZE;

   (* Cmp->PutBuf)(Cmp->OutBuf, &i, Cmp->Param);

   s1 = Cmp->OutBuf[Cmp->OutPtr];
   s2 = Cmp->OutBuf[OUT_SIZE];
   Cmp->OutPtr -= OUT_SIZE;
   lmemset(Cmp->OutBuf,0,OUT_SIZE+2);
   if (Cmp->OutPtr > 0)
      Cmp->OutBuf[0] = s2;
   if (Cmp->OutPos != 0)
      Cmp->OutBuf[Cmp->OutPtr] = s1;
}

/****************************************************
 Function: SortBuffer
*****************************************************
   Do a distribution sort on a 3 character hash value of the passed buffer.
*/

static VOID SortBuffer(struct CMP_DATA *Cmp, UCHAR *low, UCHAR *hi)
{
   UINT *Ptr;
   USHORT Accum = 0, *IndexPtr;
   UCHAR *p;

   Ptr = (UINT *)Cmp->Index;
   do {                               /* Zero all index values */
      *Ptr = 0;
   } while (++Ptr < (UINT *)&Cmp->Index[FOO_SIZE]);

   p = low;                            /* Get hash counts */
   do
   {
      ++(Cmp->Index[FOO(p)]);
   } while (++p < hi);

   IndexPtr = Cmp->Index;
   do                                  /* Accumulate counts */
   {
      Accum += *IndexPtr;
      *IndexPtr = Accum;
   } while (++IndexPtr < &Cmp->Index[FOO_SIZE]);

   p = hi - 1;                         /* Complete sort buffer */
   do {
      IndexPtr = &Cmp->Index[FOO(p)];
      --(*IndexPtr);
      Cmp->SortBuf[*IndexPtr] = (USHORT)(p - Cmp->Buffer);
   } while (--p >= low);
}


