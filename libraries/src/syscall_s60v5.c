#include <epoc/common.h>
#include <epoc/syscall_s60v5.h>

SYSCALL_V1(0x00800000, void, e32_wait_for_any_request);
SYSCALL_V1(0x00800001, void*, e32_get_thread_heap_allocator);
SYSCALL_V1(0x00800002, void*, e32_set_thread_allocator, const void *new_allocator);
SYSCALL_V1(0x0000006A, uint32, e32_close_handle, handle target_handle);
