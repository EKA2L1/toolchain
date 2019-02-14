/** 
 * Copyright (c) 2019 EKA2L1 Project. All rights reserved.
 * 
 * This work is licensed under the terms of the MIT license.  
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */

#include <epoc/common.h>
#include <epoc/syscall_s60v5.h>

SYSCALL_V1(0x00800000, void, e32_wait_for_any_request);
SYSCALL_V1(0x00800001, void*, e32_get_thread_heap_allocator);
SYSCALL_V1(0x00800002, void*, e32_set_thread_heap_allocator, const void *new_allocator);
SYSCALL_V1(0x00800005, void*, e32_get_active_scheduler);
SYSCALL_V1(0x00800006, void, e32_set_active_scheduler, void* new_scheduler);
SYSCALL_V1(0x00800008, void*, e32_get_thread_trap_handler);
SYSCALL_V1(0x00800009, void*, e32_set_thread_trap_handler, const void *new_trap);
SYSCALL_V1(0x00800013, void*, e32_get_rom_header_address);
SYSCALL_V1(0x00800014, void*, e32_get_rom_root_directory_address);
SYSCALL_V1(0x00800015, int32, e32_safe_inc, int32 *org);
SYSCALL_V1(0x00000001, void*, e32_get_chunk_base, const handle chunk_handle);
SYSCALL_V1(0x0000000C, void, e32_imb_range, const void *start, const int32 size);
SYSCALL_V1(0x0000000E, void*, e32_library_lookup, handle lib_handle, const int ord_index);
SYSCALL_V1(0x00000011, int, e32_mutex_wait, handle mut_handle);
SYSCALL_V1(0x00000012, void, e32_mutex_signal, handle mut_handle);
SYSCALL_V1(0x00000013, uint32, e32_process_get_id, handle process_handle);
SYSCALL_V1(0x00000015, void, e32_process_resume, handle process_handle);
SYSCALL_V1(0x00000003, int32, e32_get_chunk_max_size, const handle chunk_handle);
SYSCALL_V1(0x00000025, int32, e32_session_send, handle sesion_handle, const int32 opcode, 
    const void *ipc_args, const void *req_sts);
SYSCALL_V1(0x0000003B, void, e32_request_signal, const int32 count);
SYSCALL_V1(0x00000040, void, e32_delay, const int microsecs, void *request_status);
SYSCALL_V1(0x0000004D, int32, e32_session_send_sync, handle sesion_handle, const int32 opcode, 
    const void *ipc_args, const void *req_sts);
SYSCALL_V1(0x00000056, void, e32_debug_print_des, void *des, const int mode);
SYSCALL_V1(0x0000005E, void, e32_get_thread_context_des, const handle thread_handle, void *context_des);
SYSCALL_V1(0x0000006A, uint32, e32_close_handle, const handle target_handle);
SYSCALL_V1(0x0000006B, int32, e32_chunk_create_des, const int owner_type, void *name,
    const void *chunk_create_info);
SYSCALL_V1(0x0000006C, int32, e32_chunk_adjust, handle chunk_handle, const int adjust_type, const int a1,
    const int a2);
SYSCALL_V1(0x0000007F, int32, e32_session_create_des, void *server_name, const int32 async_msg_slot_count,
    const void *sec_policy, const int32 type);
