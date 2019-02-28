/** 
 * Copyright (c) 2019 EKA2L1 Project. All rights reserved.
 * 
 * This work is licensed under the terms of the MIT license.  
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */

#include <epoc/common.h>
#include <epoc/kernel.h>

#ifdef __GCC32__
typedef void (*PFV)();
extern PFV __CTOR_LIST__[];
extern PFV __DTOR_LIST__[];

void e32_global_destructor_func() {
    uint32 i = 1;
    
    while (__DTOR_LIST__[i]) {
        (*__DTOR_LIST__[i++])();
    }
}

void e32_global_constructor_func() {
    uint32 i = 1;

    while (__CTOR_LIST__[i]) {
        (*__CTOR_LIST__[i++])();
    }
}
#endif

extern int32 e32_dll_main(const int reason);

E32_API int32 _E32Dll(const int reason) 
{
  if (reason == E32_ENTRY_REASON_ATTACH) 
  {
    e32_global_constructor_func();
  }

  if (reason == E32_ENTRY_REASON_DETATCH) {
    e32_global_destructor_func();
  }

  e32_dll_main(reason);
}
