#ifndef __EPOC_KERNEL_H
#define __EPOC_KERNEL_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __S60_50__
    #include <epoc/syscall_s60v5.h>
#else
    #error Unsupport Symbian version
#endif

#include <epoc/common.h>

/*! \brief Print a string to debugger.
 *
 * There is no way to tell if this succeed or failed.
*/
E32_API void e32_debug_print(const char *msg, const int32 len);

#ifdef __cplusplus
}
#endif

#endif
