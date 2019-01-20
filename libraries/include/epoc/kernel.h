#ifndef __EPOC_KERNEL_H
#define __EPOC_KERNEL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <epoc/common.h>
#include <epoc/std.h>

/*! Session only for use on current thread, not usable on many thread
 */
#define E32_IPC_SESSION_UNSHAREABLE 0

/*! Session can be shared across current process
 */
#define E32_IPC_SESSION_SHAREABLE 1

/*! Session can be shared globally
*/
#define E32_IPC_SESSION_GLOBAL_SHAREABLE 2

/*! Server role default to standalone.
*/
#define E32_IPC_SERVER_ROLE_DEFAULT 0

/*! Indicates this server won't have any connection whatsoever to other servers.
*/
#define E32_IPC_SERVER_ROLE_STANDALONE

/*! Indicates this server can transfers sessions to slave
*/
#define E32_IPC_SERVER_ROLE_MASTER

/*! Indicates this server can accepts sessions from master
*/
#define E32_IPC_SERVER_ROLE_SLAVE

#define E32_IPC_ARG_FLAG_UNSPECIFIED 0

#define E32_IPC_ARG_FLAG_HANDLE 1

#define E32_IPC_ARG_FLAG_DES 4

#define E32_IPC_ARG_FLAG_CONST 2 

#define E32_IPC_ARG_FLAG_16BIT 1

typedef struct e32_ipc_args
{
    int32 args[4];  ///< Arguments storage
    int32 flags;    ///< Each 3 low bits are used for storing the type. The last 4 bit are used to store pins
} e32_ipc_args;

/*! \brief Pin an IPC argument
 *
 * \param index The index of argument, in range of 0-3
 * 
 * \returns E32_ERR_NONE for success.
 *          E32_ERR_ARGUMENT if the index is out of range.
*/
E32_API int32 e32_pin_ipc_arg(e32_ipc_args *args, const int32 index);

/*! \brief Unpin an IPC argument
 *
 * \param index The index of argument, in range of 0-3
 * 
 * \returns E32_ERR_NONE for success.
 *          E32_ERR_ARGUMENT if the index is out of range.
*/
E32_API int32 e32_unpin_ipc_arg(e32_ipc_args *args, const int32 index);

/*! \brief Set an IPC argument to an integer
 *
 * \param index The index of the argument, in range of 0 - 3.
 * \param arg   The argument to be set.
 * 
 * \returns E32_ERR_NONE for success.
 *          E32_ERR_ARGUMENT if the index is out of range.
*/
E32_API int32 e32_set_ipc_arg(e32_ipc_args *args, const int32 index, const int32 arg);

/*! \brief Set an IPC argument to a handle
 *
 * \param index The index of the argument, in range of 0 - 3.
 * \param arg   The handle to be set.
 * 
 * \returns E32_ERR_NONE for success.
 *          E32_ERR_ARGUMENT if the index is out of range.
*/
E32_API int32 e32_set_ipc_arg_handle(e32_ipc_args *args, const int32 index, const handle arg);

/*! \brief Set an IPC argument to a string
 *
 * \param index The index of the argument, in range of 0 - 3.
 * \param descriptor   The descriptor to be set.
 * \param modifiable True if the descriptor can be modified.
 * \param ucs2 True if the string is 16-bit
 * 
 * \returns E32_ERR_NONE for success.
 *          E32_ERR_ARGUMENT if the index is out of range.
*/
E32_API int32 e32_set_ipc_arg_string(e32_ipc_args *args, const int32 index, void *descriptor,
    bool modifiable, bool ucs2);

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
