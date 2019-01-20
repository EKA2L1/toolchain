#include <epoc/descriptor.h>
#include <epoc/kernel.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __S60_50__
    #include "syscall_s60v5.c"
#else
  #error Unsupport Symbian version
#endif

E32_API void e32_debug_print(const char *msg, const int32 len)
{
  ptrc_descriptor wrapstr;
  e32_create_descriptor_const(&wrapstr, msg, len);

  e32_debug_print_des((descriptor*)&wrapstr, 0);
}

E32_API int32 e32_session_create(const char *server_name, const int32 async_msg_slot_count,
    const e32_security_policy *sec_policy, const int32 type)
{
  ptrc_descriptor wrapstr;
  e32_create_descriptor_const(&wrapstr, server_name, -1);

  return e32_session_create_des((descriptor*)(&wrapstr), async_msg_slot_count, (void*)(sec_policy), type);
}

E32_API int32 e32_dll_entry_point() 
{
  return 0;
}

#ifdef __cplusplus
}
#endif
