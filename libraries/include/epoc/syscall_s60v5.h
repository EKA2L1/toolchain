/** 
 * Copyright (c) 2019 EKA2L1 Project. All rights reserved.
 * 
 * This work is licensed under the terms of the MIT license.  
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */

#ifndef __EPOC_SYSCALL_S60V5_H
#define __EPOC_SYSCALL_S60V5_H

#include <epoc/common.h>
#include <epoc/syscall_common.h>

/**
 * \brief Put the current thread on wait until a request signal the current 
 *         thread's signal semaphore
 *
 * This is a blocking-type function.
 */
SYSCALL_INTERFACE(void, e32_wait_for_any_request);

/**
 * \brief Get current thread's heap allocator.
 *
 * The thread allocs some memory to store global stuff. Heap allocator is the one.
 * You don't need to use this as a heap allocator, but instead store your stuff :D
 *
 * Likely this gonna be use with malloc though.
 *
 * \returns Pointer to the heap allocator of current thread.
 */
SYSCALL_INTERFACE(void*, e32_get_thread_heap_allocator);

/**
 * \brief Set the current thread's heap allocator.
 *
 * \returns The old heap's allocator
 */
SYSCALL_INTERFACE(void*, e32_set_thread_heap_allocator, const void *new_allocator);

/** \brief Get current thread's active scheduler. */
SYSCALL_INTERFACE(void*, e32_get_active_scheduler);

/** \brief Set current thread's active scheduler. */
SYSCALL_INTERFACE(void, e32_set_active_scheduler, void* new_scheduler);

/** \brief Get current thread's trap handler. */
SYSCALL_INTERFACE(void*, e32_get_thread_trap_handler);

/**
 * \brief Set current thread's trap handler.
 *
 * \returns New trap handler.
*/
SYSCALL_INTERFACE(void*, e32_set_thread_trap_handler, const void *new_trap);

/** 
 * \brief Close a valid handle.
 *
 * !Panic: 0 KERN-EXEC if the handle can not be found or is invalid
 *
 * \returns E32_ERR_NONE indicates success, else other system-related error code
 */
SYSCALL_INTERFACE(uint32, e32_close_handle, const handle target_handle);

/** \brief Print an 8-bit descriptor to the debugger with specified mode. */
SYSCALL_INTERFACE(void, e32_debug_print_des, void *des, const int mode);

/**
 * \brief Get the base address of the chunk in current process's memory space
 *
 * \param chunk_handle Handle to the chunk to get address. 
 * 
 * \returns 0 if not successful (rarely, most of the times it will throw a panic).
 *          Otherwise, pointer to the chunk base
 */
SYSCALL_INTERFACE(void*, e32_get_chunk_base, const handle chunk_handle);

/**
 * \brief Get the chunk max size
 *
 * \param chunk_handle Handle to the chunk.
 * \returns < 0 for error code, else the max size of the chunk.
*/
SYSCALL_INTERFACE(int32, e32_get_chunk_max_size, const handle chunk_handle);

/**
 * \brief Flush the instruction cache on a code range.
 *         The data must be in an allocated code chunk and executable.
 * 
 * \param start Start of executable code to be flushed
 * \param size Size of code to flush
 */
SYSCALL_INTERFACE(void, e32_imb_range, const void *start, const int32 size);

/**
 * \brief Create a new session to a server.
 *
 * \param server_name An 8-bit descriptor contains the name of the server we want to connect to.
 * \param async_msg_slot_count Total async messages slot. Max is 255, -1 for sync slot using thread's message slot.
 * \param sec_policy Pointer to a e32_security_policy. Use E32_NULL to ignore.
 * \param type  Type of this session. See E32_IPC_SESSION* macros.
 * 
 * \returns < 0 is error code. Else it's the session handle.
 */
SYSCALL_INTERFACE(int32, e32_session_create_des, void *server_name, const int32 async_msg_slot_count,
    const void *sec_policy, const int32 type);

/**
 * \brief Send a message using current thread's message slot.
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

/**
 * \brief Send a message async using session's async message slots.
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

/**
 * \brief Create a new chunk.
 *
 * \param owner_type The owner of this chunk, either the current thread or current process.
 * \param name Name of this chunk. Won't work with local chunk unless you set E32_CHUNK_ATTRIB_FORCE_NAMED.
 * \param chunk_create_info Pointer to e32_chunk_create_info struct.
 * 
 * \returns <0 is error code, else a handle to the chunk.
*/
SYSCALL_INTERFACE(int32, e32_chunk_create_des, const int owner_type, void *name,
    const void *chunk_create_info);

/**
 * \brief Adjust the chunk.
 *
 * Operations include: Commit/decommit, adjust chunk committed size, adjust bottom
 * and top of chunk's committed region, lock and unlock a region of chunk.
 * 
 * \param chunk_handle Handle to the chunk
 * \param type         The adjustment type. See E32_CHUNK_ADJUST_TYPE*
 * \param a1           The first argument passed to target adjust operation
 * \param a2           The second argument passed to target adjust operation.
 *                     If this is not used, passed 0 instead.
 * 
 * \returns E32_ERR_NONE indicates success, else other system-related error codes.
*/
SYSCALL_INTERFACE(int32, e32_chunk_adjust, handle chunk_handle, const int adjust_type, const int a1,
    const int a2);

/**
 * \brief Get the context of a thread
 *
 * Depends on CPU kind, this system call will returns the corresponding structure 
 * e32_*_thread_context with * being the system CPU name.
 * 
 * This will throw a kern-panic on invalid handle
 * 
 * \param thread_handle Handle of thread to get context to
 * \param context_des   Descriptor to write the context to.
 * 
*/
SYSCALL_INTERFACE(void, e32_get_thread_context_des, const handle thread_handle, void *context_des);

/**
 * \brief Delay the current thread
 *
 * \param microsecs The time to delay in microseconds
 * \param request_status A request status object that will be notified when the thread is waken up.
*/
SYSCALL_INTERFACE(void, e32_delay, const int microsecs, void *request_status);

/**
 * \brief Get ROM's header address.
 */
SYSCALL_INTERFACE(void*, e32_get_rom_header_address);

/**
 * \brief Get ROM's root directory address
 */
SYSCALL_INTERFACE(void*, e32_get_rom_root_directory_address);

/**
 * \brief Safely ncrease given value by 1 if it's positive.
 *
 * \returns The old value.
 */
SYSCALL_INTERFACE(int32, e32_safe_inc, int32 *org);

/**
 * \brief Lookup for export address of a function at a specific index in a loaded library.
 *
 * \param lib_handle Handle to the library object.
 * \param ord_index The index of the function we want in the library's export directory.
 * 
 * \returns Pointer to the function we are looking for.
 */
SYSCALL_INTERFACE(void*, e32_library_lookup, handle lib_handle, const int ord_index);

/** 
 * \brief Wait for the mutex.
 *
 * If the mutex doesn't have the owner, the current thread will owns it, and any thread that
 * tries to own this mutex later will be lock up, until the mutex is free.
 * 
 * Lock count for this mutex will increase, counting how many times the thread that owns this
 * mutex has call wait() on it. 
 * 
 * \returns E32_ERR_NONE on success.
 */
SYSCALL_INTERFACE(int, e32_mutex_wait, handle mut_handle);

/** 
 * \brief Signal the mutex.
 *
 * Function must be called on the thread that currently owns this mutex.
 * When that condition is met, the lock count will decrease, and if it reachs 0, the highest priority
 * among threads which are waiting for this mutex, will run, but the mutex will not be held by it.
 * 
 * That thread must actually run to acquire the mutex.
 */
SYSCALL_INTERFACE(void, e32_mutex_signal, handle mut_handle);

/** 
 * \brief Get current process's ID
 */
SYSCALL_INTERFACE(uint32, e32_process_get_id, handle process_handle);

/** 
 * \brief Resume a process from pause state
 */
SYSCALL_INTERFACE(void, e32_process_resume, handle process_handle);

/**
 * \brief Signal current's thread request semaphore
 *
 * \param count The number to add to current thread's semaphore
 */
SYSCALL_INTERFACE(void, e32_request_signal, const int32 count);

/**
 * \brief Get a list of entry points from dependencies of current process.
 * 
 * The call will iterate through all dependencies of current process's codeseg, adding
 * the dependency entry point to it, and finally add the entry point address of itself in
 * the end of the list.
 * 
 * \param eps_arr   Pointer to a writeable array of pointer, which will contain entry points.
 * \param total_eps On call, contains total number of entry point the array passed can hold.
 *                  On return, contains total of entry point was written to the list.
 * 
 * \returns E32_ERR_NONE if success, else other system-related errors.
 */
SYSCALL_INTERFACE(int32, e32_static_call_list, int *total_eps, void **eps_arr);

/**
 * \brief Kill a thread.
 * 
 * \param thr_handle     Handle of the thread to kill.
 * \param exit_type      Kill type. See E32_KILL_TYPE* macros.
 * \param reason         Kill reason code.
 * \param kill_category  Pointer to a descriptor, contains the kill category.
 * 
 * \returns E32_ERR_NONE if success, else other system-related codes.
 */
SYSCALL_INTERFACE(int32, e32_thread_kill_des, handle thr_handle, const int32 kill_type,
    const int32 reason, void *kill_category);

/**
 * \brief Get current thread's TLS slot data, given the handle and the dll UID.
 * \returns The TLS slot of the given DLL's data.
 */
SYSCALL_INTERFACE(void*, e32_dll_tls, int handle, int dll_uid);

/**
 * \brief Set current thread's TLS slot data, given the handle and the dll UID.
 * \returns E32_ERR_NONE on success, else other system-related codes.
 */
SYSCALL_INTERFACE(int, e32_dll_set_tls, int handle, int dll_uid, void *data);

#endif
