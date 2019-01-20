#include <epoc/common.h>
#include <epoc/syscall_s60v5.h>

SYSCALL_V1(0x00800000, void, e32_wait_for_any_request);
SYSCALL_V1(0x00800001, void*, e32_get_thread_heap_allocator);
SYSCALL_V1(0x00800002, void*, e32_set_thread_heap_allocator, const void *new_allocator);
SYSCALL_V1(0x00800005, void*, e32_get_active_scheduler);
SYSCALL_V1(0x00800006, void, e32_set_active_scheduler, void* new_scheduler);
SYSCALL_V1(0x00800008, void*, e32_get_thread_trap_handler);
SYSCALL_V1(0x00800009, void*, e32_set_thread_trap_handler, const void *new_trap);
SYSCALL_V1(0x00000001, void*, e32_get_chunk_base, const handle chunk_handle);
SYSCALL_V1(0x0000000C, void, e32_imb_range, const void *start, const int32 size);
SYSCALL_V1(0x00000003, int32, e32_get_chunk_max_size, const handle chunk_handle);
SYSCALL_V1(0x00000056, void, e32_debug_print_des, descriptor *des, const int mode);
SYSCALL_V1(0x0000006A, uint32, e32_close_handle, const handle target_handle);
