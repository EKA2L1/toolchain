#ifndef __EPOC_SYSCALL_COMMON
#define __EPOC_SYSCALL_COMMON

#define SYSCALL_INTERFACE(ret, name, ...)  \
__attribute__((naked)) E32_API ret name (__VA_ARGS__) ;

#define SYSCALL_V1(ordinal, ret, name, ...)         \
__attribute__((naked)) E32_API ret name (__VA_ARGS__)       \
{                                                   \
    asm("swi " #ordinal);                           \
    asm("bx lr");                                   \
}

#endif
