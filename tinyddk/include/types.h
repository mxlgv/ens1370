#ifndef __TYPES_H__
#define __TYPES_H__

#define __import   __attribute__ ((dllimport))
#define __stdcall  __attribute__ ((stdcall))
#define __fastcall  __attribute__ ((fastcall))

#define likely(x)   __builtin_expect((x),1)
#define unlikely(x) __builtin_expect((x),0)

#define va_start(v,l)   __builtin_va_start(v,l)
#define va_end(v)       __builtin_va_end(v)
#define va_arg(v,l)     __builtin_va_arg(v,l)
#define __va_copy(d,s)	__builtin_va_copy(d,s)
#define va_list         __builtin_va_list

#define __packed        __attribute__((packed, aligned(1)))

typedef char i8;
typedef short i16;
typedef int i32;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef _Bool bool;

#define true 1
#define false 0

#endif // __TYPES_H__
