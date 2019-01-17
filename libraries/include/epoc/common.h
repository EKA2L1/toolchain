#ifndef __EPOC_COMMON_H
#define __EPOC_COMMON_H

typedef int int32;
typedef short int16;
typedef char int8;

typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

typedef long long int64;
typedef unsigned long long uint64;

typedef uint32 handle;

typedef uint16* ucs2str;

#define HANDLE_OWNER_THREAD 0
#define HANDLE_OWNER_PROCESS 1

#ifdef __GNUC__
#define E32_API __attribute__ ((visibility ("default")))
#endif

#endif
