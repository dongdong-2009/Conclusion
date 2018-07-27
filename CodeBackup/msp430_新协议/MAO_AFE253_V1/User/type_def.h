
#ifndef _TYPEDEF_H
#define _TYPEDEF_H

typedef   unsigned char   BOOLEAN;
typedef   unsigned char   INT8U;
typedef   unsigned int    INT16U;
typedef   unsigned long   INT32U;  

typedef   signed   char   INT8S;
typedef   signed   int    INT16S;
typedef   signed   long   INT32S;
typedef            float  FP32;
typedef            double FP64;


typedef  signed char     S8;
typedef  unsigned char   U8;
typedef  signed short    S16;
typedef  unsigned short  U16;
typedef  signed long     S32;
typedef  unsigned long   U32;
typedef  signed char     BOOL;



#ifndef code 
#define code   const
#endif

#ifndef INT8
#define INT8   signed char
#endif

#ifndef INT16
#define INT16  signed short
#endif

#ifndef INT32
#define INT32  signed long
#endif

#ifndef UINT8
#define UINT8  unsigned char
#endif

#ifndef UINT16
#define UINT16 unsigned short
#endif

#ifndef UINT32
#define UINT32 unsigned long
#endif

#ifndef VOID
#define VOID   void
#endif

#ifndef NULL
#define NULL	(void *)0
#endif


#ifndef __PI 
#define __PI            3.141592653589793238462643
#endif

typedef union
{
  unsigned int is_int;  //
  struct
  {
    char lo_byte;  //整数的低字节
    char hi_byte;
  };
}UINT_TO_2_CHAR;  //无符号整数

typedef union
{
  signed int is_int;  //
  struct
  {
    char lo_byte;  //整数的低字节
    char hi_byte;
  };
}SINT_TO_2_CHAR;

typedef union
{
  unsigned long is_long;  //
  struct
  {
    char byte_0;  //长整数的低字节
    char byte_1;
    char byte_2;
    char byte_3;
  };
}ULONG_TO_4_CHAR;

typedef union
{
  long is_long;  //
  struct
  {
    char byte_0;  //长整数的低字节
    char byte_1;
    char byte_2;
    char byte_3;
  };
}SLONG_TO_4_CHAR;

#define  FALSE    0
#define  TRUE     1
#ifndef  NULL
#define  NULL     (void *)0
#endif
#define  Pn0  0x01
#define  Pn1  0x02
#define  Pn2  0x04
#define  Pn3  0x08
#define  Pn4  0x10
#define  Pn5  0x20
#define  Pn6  0x40
#define  Pn7  0x80


typedef void (*PFUNC)(void);
#endif /* #ifndef _YPEDEF_H */


