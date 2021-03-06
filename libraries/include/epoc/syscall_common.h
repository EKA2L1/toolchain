/** 
 * Copyright (c) 2019 EKA2L1 Project. All rights reserved.
 * 
 * This work is licensed under the terms of the MIT license.  
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */

#ifndef __EPOC_SYSCALL_COMMON_H
#define __EPOC_SYSCALL_COMMON_H

#define SYSCALL_INTERFACE(ret, name, ...)  \
__attribute__((naked)) E32_API ret name (__VA_ARGS__) ;

#define SYSCALL_V1(ordinal, ret, name, ...)         \
__attribute__((naked)) E32_API ret name (__VA_ARGS__)       \
{                                                   \
    asm("swi " #ordinal);                           \
    asm("bx lr");                                   \
}

#endif
