#ifndef __EPOC_SYSCALL_S60V5_H
#define __EPOC_SYSCALL_S60V5_H

#include <epoc/common.h>
#include <epoc/syscall_common.h>

// Foward declare
struct descriptor;

/*! \brief Put the current thread on wait until a request signal the current 
 *         thread's signal semaphore
 *
 *  This is a blocking-type function.
*/
SYSCALL_INTERFACE(void, e32_wait_for_any_request);

/*! \brief Get current thread's heap allocator.
 *
 * The thread allocs some memory to store global stuff. Heap allocator is the one.
 * You don't need to use this as a heap allocator, but instead store your stuff :D
 *
 * Likely this gonna be use with malloc though.
 *
 * \returns Pointer to the heap allocator of current thread.
*/
SYSCALL_INTERFACE(void*, e32_get_thread_heap_allocator);

/*! \brief Set the current thread's heap allocator.
 *
 * \returns The old heap's allocator
*/
SYSCALL_INTERFACE(void*, e32_set_thread_heap_allocator, const void *new_allocator);

/*! \brief Get current thread's active scheduler
*/
SYSCALL_INTERFACE(void*, e32_get_active_scheduler);

/*! \brief Set current thread's active scheduler
*/
SYSCALL_INTERFACE(void, e32_set_active_scheduler, void* new_scheduler);

/*! \brief Get current thread's trap handler
*/
SYSCALL_INTERFACE(void*, e32_get_thread_trap_handler);

/*! \brief Set current thread's trap handler
 *
 * \returns New trap handler
*/
SYSCALL_INTERFACE(void*, e32_set_thread_trap_handler, const void *new_trap);

/*! \brief Close a valid handle.
 *
 * !Panic: 0 KERN-EXEC if the handle can not be found or is invalid
 *
 * \returns E32_ERR_NONE indicates success, else other system-related error code
*/
SYSCALL_INTERFACE(uint32, e32_close_handle, const handle target_handle);

/*! \brief Print an 8-bit descriptor to the debugger with specified mode
*/
SYSCALL_INTERFACE(void, e32_debug_print_des, descriptor *des, const int mode);

/*! \brief Get the base address of the chunk in current process's memory space
 *
 * \param chunk_handle Handle to the chunk to get address. 
 * 
 * \returns 0 if not successful (rarely, most of the times it will throw a panic).
 *          Otherwise, pointer to the chunk base
*/
SYSCALL_INTERFACE(void*, e32_get_chunk_base, const handle chunk_handle);

/*! \brief Get the chunk max size
 *
 * \param chunk_handle Handle to the chunk.
 * \returns < 0 for error code, else the max size of the chunk.
*/
SYSCALL_INTERFACE(int32, e32_get_chunk_max_size, const handle chunk_handle);

/*! \brief Flush the instruction cache on a code range.
 *         The data must be in an allocated code chunk and executable.
 * 
 * \param start Start of executable code to be flushed
 * \param size Size of code to flush
*/
SYSCALL_INTERFACE(void, e32_imb_range, const void *start, const int32 size);

/*! \brief Create a new session to a server.
 *
 * \param server_name An 8-bit descriptor contains the name of the server we want to connect to.
 * \param async_msg_slot_count Total async messages slot. Max is 255, -1 for sync slot using thread's message slot.
 * \param sec_policy Pointer to a e32_security_policy. Use E32_NULL to ignore.
 * \param type  Type of this session. See E32_IPC_SESSION* macros.
 * 
 * \returns < 0 is error code. Else it's the session handle.
*/
SYSCALL_INTERFACE(int32, e32_session_create_des, descriptor *server_name, const int32 async_msg_slot_count,
    const void *sec_policy, const int32 type);

/*! \brief Send a message using current thread's message slot.
 *
 * Because each thread only has one message slot, this means that message that send using this
 * method will be put on queue until current thread's message slot is free again.
 * 
 * \param session_handle Handle to the session.
 * \param opcode The opcode to sends to the server.
 * \param ipc_args The args of to send.
 * \param req_sts Status that will be notified when the message is completed from server side.
 * 
 * \returns E32_ERR_NONE if sending success.
*/
SYSCALL_INTERFACE(int32, e32_session_send_sync, handle sesion_handle, const int32 opcode, 
    const void *ipc_args, const void *req_sts);

/*! \brief Send a message async using session's async message slots.
 *
 * Total async message slots are declared when create the session.
 * 
 * \param session_handle Handle to the session.
 * \param opcode The opcode to sends to the server.
 * \param ipc_args The args of to send.
 * \param req_sts Status that will be notified when the message is completed from server side.
 * 
 * \returns E32_ERR_NONE if sending success.
*/
SYSCALL_INTERFACE(int32, e32_session_send, handle sesion_handle, const int32 opcode, 
    const void *ipc_args, const void *req_sts);

/*! \brief Create a new chunk.
 *
 * \param owner_type The owner of this chunk, either the current thread or current process.
 * \param name Name of this chunk. Won't work with local chunk unless you set E32_CHUNK_ATTRIB_FORCE_NAMED.
 * \param chunk_create_info Pointer to e32_chunk_create_info struct.
 * 
 * \returns <0 is error code, else a handle to the chunk.
*/
SYSCALL_INTERFACE(int32, e32_chunk_create_des, const int owner_type, descriptor *name,
    const void *chunk_create_info);

#endif
