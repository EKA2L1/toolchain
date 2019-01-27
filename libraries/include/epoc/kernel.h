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

/*! \brief Flag for a normal chunk.
 *
 * A normal chunk don't let you access to things like bottom or top.
 * When you want to expand the memory chunk, by committing more memory to it, call e32_chunk_commit(new_size).
*/
#define E32_CHUNK_ATTRIB_NORMAL 0

/*! \brief Flag for a double end chunk.
 *
 * Double end chunk let you choose which part of the chunk will be the committed one.
 *
 * For example, your chunk has max size of 0x200 000, and you can choose 0x1000 as the begin (bottom), and 0x30 000 as the end (top)
 * of the committed region. 
*/
#define E32_CHUNK_ATTRIB_DOUBLE_ENDED 1

/*! \brief Flag for disconnected chunk.
 *
 * Disconnected chunk are like double ended, but it allows multiple commit region.
 * It's like a bunch of double ended chunk in a big big chunk.
*/
#define E32_CHUNK_ATTRIB_DISCONNECTED 2

/*! \brief Flag for making a chunk readable and writeable
*/
#define E32_CHUNK_ATTRIB_READ_WRITE 0

/*! \brief Flag for making a chunk memory executable.
 *
 * This flag won't work if the chunk is global, for obivious region.
*/
#define E32_CHUNK_ATTRIB_EXECUTABLE 0x20

/*! \brief Flag for making a chunk read-only.
*/
#define E32_CHUNK_ATTRIB_READ_ONLY 0x100

/*! \brief Unknown usage 
*/
#define E32_CHUNK_ATTRIB_CACHE 3

/*! \brief This flag indicates that the chunk memory is only valid in current process.
*/
#define E32_CHUNK_ATTRIB_LOCAL 0

/*! \brief This flag indicates that the chunk memory can also be seen by other process.
*/
#define E32_CHUNK_ATTRIB_GLOBAL 0x10

/*! \brief This flag forced the local chunk to be named.
 *
 * Usually, only global chunk can have name. But making exception for Heap chunk,
 * Symbian adds this.
*/
#define E32_CHUNK_ATTRIB_LOCAL_NAMED 0x80

/*! \brief Flag specified the chunk memory to be paged.
 *
 * Available with Symbian 9.3 onwards, most likely added because of ARMv6.
*/
#define E32_CHUNK_ATTRIB_PAGED 0x80000000

/*! \brief Flag specified the chunk memory to be unpaged.
 *
 * Available with Symbian 9.3 onwards, most likely added because of ARMv6.
 * Please don't use this, only when you need to.
*/
#define E32_CHUNK_ATTRIB_UNPAGED 0x40000000

/*! \brief Create info that passed to e32_create_chunk(_des)
*/
typedef struct e32_chunk_create_info
{
    uint32 attrib;          ///< Attribute of the chunk
    bool   force_fixed;     ///< Force name to be fixed
    int    initial_bottom;  ///< The initial bottom of the committed region
    int    initial_top;     ///< The initial top of the committed region
    int    max_size;        ///< Max size that this chunk can grow/commit
    uint8  clear_byte;      ///< Byte to clear commit region. It's like 0xCC are used to clear committed region on Windows
} e32_chunk_create_info;

/*! \brief Adjust the chunk normally
 *
 * Adjust the committed size of the chunk
*/
#define E32_CHUNK_ADJUST_TYPE_NORMAL 0

/*! \brief Adjust the bottom and top offset of the committed region
 *         in the chunk.
*/
#define E32_CHUNK_ADJUST_TYPE_DOUBLE_END 1

/*! \brief Commit a region of chunk memory.
 *
 * This freely commits a memory region in the chunk.
*/
#define E32_CHUNK_ADJUST_TYPE_COMMIT 2

/*! \brief Decommit a range of memory, use for disconnected chunk.
*/
#define E32_CHUNK_ADJUST_TYPE_DECOMMIT 3

/*! \brief Work just like adjust type normal, for disconnected chunk.
*/
#define E32_CHUNK_ADJUST_TYPE_ALLOCATE 4

/*! \brief Lock access from a memory region in the chunk.
 *
 * This disallows any threads from any process to edit the memory region,
 * even the one who lock the chunk.
 * 
 * The one who lock the chunk must unlock the chunk itself.
*/
#define E32_CHUNK_ADJUST_TYPE_LOCK 5

/*! \brief Unlock access to a memory region in the chunk.
 *
 * Unlock operation must be from the one who lock it.
*/
#define E32_CHUNK_ADJUST_TYPE_UNLOCK 6

typedef struct e32_arm_thread_context {
    uint32 r[16];
    uint32 cpsr;

    uint32 dacr;
} e32_arm_thread_context;

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

/*! \brief Create a new chunk.
 *
 * \param chunk_name Name of the chunk.
 * \param owner_type The owner of this chunk, either E32_HANDLE_OWNER_THREAD or E32_HANDLE_OWNER_PROCESS.
 * \param info Chunk creation info.
 * 
 * \returns < 0 is error code, else handle to the chunk.
*/
E32_API int32 e32_chunk_create(const char *chunk_name, const int32 owner_type,
    const e32_chunk_create_info *info);

/*! \brief Get ARM CPU context of a thread.
 *
 * This is based on an undocumented system call found on Symbian's source code.
 * Intergrated with debugger client like TRK and CODA.
 * 
 * \param thread_handle Handle of the thread to get context from.
 * \param context       Pointer to arm thread context.
*/
E32_API void e32_get_arm_thread_context(const handle thread_handle, e32_arm_thread_context *context);

#ifdef __cplusplus
}
#endif

#endif
