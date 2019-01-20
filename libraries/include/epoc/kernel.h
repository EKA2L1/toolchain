#ifndef __EPOC_KERNEL_H
#define __EPOC_KERNEL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <epoc/common.h>
#include <epoc/std.h>

// Session share type

// Session only for use on current thread, not usable on many thread
#define E32_IPC_SESSION_UNSHAREABLE 0

// Session can be shared across current process
#define E32_IPC_SESSION_SHAREABLE 1

// Session can be shared globally
#define E32_IPC_SESSION_GLOBAL_SHAREABLE 2

#ifdef __S60_50__
    #include <epoc/syscall_s60v5.h>
#else
    #error Unsupport Symbian version
#endif

/*! \brief Print a string to debugger.
 *
 * There is no way to tell if this succeed or failed.
*/
E32_API void e32_debug_print(const char *msg, const int32 len);

/*! \brief Create a new session to a server.
 *
 * \param server_name Name of server we want to create a connection to.
 * \param async_msg_slot_count Total async message slots. -1 for using sync message slot of current thread.
 * \param sec_policy The security policy for the session. Use E32_NULL to ignore.
 * \param type Session type. See E32_IPC_SESSION* macros
 * 
*/
E32_API int32 e32_session_create(const char *server_name, const int32 async_msg_slot_count,
    const e32_security_policy *sec_policy, const int32 type);

#ifdef __cplusplus
}
#endif

#endif
