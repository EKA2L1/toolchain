#include <epoc/common.h>

extern int32 e32_dll_main();

E32_API int32 _E32Dll() 
{
  e32_dll_main();
}
