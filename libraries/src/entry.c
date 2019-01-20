#include <epoc/common.h>

extern int32 e32_dll_entry_point();

E32_API int32 _E32Dll() 
{
  e32_dll_entry_point();
}
