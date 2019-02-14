/** 
 * Copyright (c) 2019 EKA2L1 Project. All rights reserved.
 * 
 * This work is licensed under the terms of the MIT license.  
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */

#include <epoc/common.h>

extern int32 e32_dll_main();

E32_API int32 _E32Dll() 
{
  e32_dll_main();
}
