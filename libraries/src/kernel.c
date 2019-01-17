#include <epoc/kernel.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __S60_50__
    #include "syscall_s60v5.c"
#else
  #error Unsupport Symbian version
#endif

#ifdef __cplusplus
}
#endif
