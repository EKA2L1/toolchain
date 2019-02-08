#include <epoc/descriptor.h>
#include <epoc/kernel.h>
#include <epoc/err.h>

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

  e32_debug_print_des((void*)&wrapstr, 0);
}

E32_API int32 e32_session_create(const char *server_name, const int32 async_msg_slot_count,
    const e32_security_policy *sec_policy, const int32 type)
{
  ptrc_descriptor wrapstr;
  e32_create_descriptor_const(&wrapstr, server_name, -1);

  return e32_session_create_des((void*)(&wrapstr), async_msg_slot_count, (void*)(sec_policy), type);
}

E32_API int32 e32_chunk_create(const char *chunk_name, const int32 owner_type,
    const e32_chunk_create_info *info)
{
  ptrc_descriptor wrapstr;
  e32_create_descriptor_const(&wrapstr, chunk_name, -1);

  return e32_chunk_create_des(owner_type, (void*)(&wrapstr), (const void*)info);
}

E32_API void e32_get_arm_thread_context(const handle thread_handle, e32_arm_thread_context *context) 
{
  ptr_descriptor wrapstr;
  e32_create_descriptor(&wrapstr, (const char*)context, 0, sizeof(e32_arm_thread_context));

  return e32_get_thread_context_des(thread_handle, (void*)(&wrapstr));
}

E32_API int32 e32_pin_ipc_arg(e32_ipc_args *args, const int32 index)
{
  if (index < 0 || index >= 4) 
  {
    return E32_ERR_ARGUMENT;
  }

  // Set the pin bit
  args->flags |= (1 << (12 + index));
  return E32_ERR_NONE;
}

E32_API int32 e32_unpin_ipc_arg(e32_ipc_args *args, const int32 index)
{
  if (index < 0 || index >= 4) 
  {
    return E32_ERR_ARGUMENT;
  }

  // Reset the pin bit
  args->flags &= ~(1 << (12 + index));
  return E32_ERR_NONE;
}

E32_API int32 e32_set_ipc_arg(e32_ipc_args *args, const int32 index, const int32 arg)
{
  if (index < 0 || index >= 4) 
  {
    return E32_ERR_ARGUMENT;
  }

  // Clear the previous type
  args->flags |= (E32_IPC_ARG_FLAG_UNSPECIFIED << (index * 3));
  args->args[index] = arg;

  return E32_ERR_NONE;
}

E32_API int32 e32_set_ipc_arg_handle(e32_ipc_args *args, const int32 index, const handle arg)
{
  if (index < 0 || index >= 4) 
  {
    return E32_ERR_ARGUMENT;
  }

  // Clear the previous type
  args->flags |= (E32_IPC_ARG_FLAG_HANDLE << (index * 3));
  args->args[index] = arg;

  return E32_ERR_NONE;
}

E32_API int32 e32_set_ipc_arg_string(e32_ipc_args *args, const int32 index, void *descriptor,
    bool modifiable, bool ucs2)
{
  if (index < 0 || index >= 4) 
  {
    return E32_ERR_ARGUMENT;
  }

  int32 flag = E32_IPC_ARG_FLAG_DES;

  if (ucs2)
  {
    flag |= E32_IPC_ARG_FLAG_16BIT;
  }

  if (!modifiable)
  {
    flag |= E32_IPC_ARG_FLAG_CONST;
  }

  // Clear the previous type
  args->flags |= (flag << (index * 3));
  args->args[index] = (int32)descriptor;

  return E32_ERR_NONE;
}

E32_API e32_thread_global_storage *e32_get_global_storage() {
  return (e32_thread_global_storage*)(e32_get_thread_heap_allocator());
}

E32_API int32 e32_dll_main() 
{
  return 0;
}

#ifdef __cplusplus
}
#endif
