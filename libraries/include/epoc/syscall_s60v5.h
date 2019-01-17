#ifndef __EPOC_SYSCALL_S60V5
#define __EPOC_SYSCALL_S60V5

#include <epoc/common.h>
#include <epoc/syscall_common.h>

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
SYSCALL_INTERFACE(uint32, e32_close_handle, handle target_handle);

#endif
