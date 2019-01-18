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
SYSCALL_INTERFACE(void*, e32_set_thread_allocator, const void *new_allocator);

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

#endif
