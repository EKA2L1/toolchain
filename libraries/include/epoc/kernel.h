#ifndef __EPOC_KERNEL
#define __EPOC_KERNEL

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __S60_50__
    #include <epoc/syscall_s60v5.h>
#else
    #error Unsupport Symbian version
#endif

#ifdef __cplusplus
}
#endif

#endif
