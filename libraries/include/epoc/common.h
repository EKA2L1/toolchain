/** 
 * Copyright (c) 2019 EKA2L1 Project. All rights reserved.
 * 
 * This work is licensed under the terms of the MIT license.  
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */

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
typedef uint16 *ucs2str;

typedef int bool;

#define E32_NULL 0
#define E32_FALSE 0
#define E32_TRUE 1

#define E32_HANDLE_OWNER_THREAD 0
#define E32_HANDLE_OWNER_PROCESS 1

#ifdef __GNUC__
#define E32_API __attribute__ ((visibility ("default")))
#endif

int32 e32_get_str16_length(const ucs2str str);
int32 e32_get_str_length(const char *str);

typedef void(*e32_thread_func)(void *data);

#endif
