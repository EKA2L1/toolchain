/** 
 * Copyright (c) 2019 EKA2L1 Project. All rights reserved.
 * 
 * This work is licensed under the terms of the MIT license.  
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */

#include <epoc/common.h>
#include <epoc/kernel.h>

#ifdef __GNUC__
typedef void (*PFV)();
extern PFV __CTOR_LIST__[];
extern PFV __DTOR_LIST__[];

void e32_global_destructor_func() {
    uint32 i = 1;
    
    while (__DTOR_LIST__[i]) {
        (*__DTOR_LIST__[i++])();
    }
}

void e32_global_constructor_func() {
    uint32 i = 1;

    while (__CTOR_LIST__[i]) {
        (*__CTOR_LIST__[i++])();
    }
}
#endif

#define E32_GLOBAL_DESTRUCTOR_KEY 0x80001010
#define E32_SPECIAL_DLL_UID       -1

#define E32_PANIC_REASON_NKERN_ALLOC_GLOBAL_STORAGE_FAIL 1
#define E32_PANIC_REASON_NKERN_CATEGORY "NKERN32"

#define E32_GLOBAL_STORAGE_CHUNK_MAX 0x1000

void e32_create_global_storage_chunk(void *thread_info, const bool first)
{
    e32_new_standard_thread_create_info *thread_create_info = (e32_new_standard_thread_create_info*)thread_info;
    e32_thread_global_storage *storage;

    if (!thread_create_info->last_global_storage || first) {
        e32_chunk_create_info storage_create_info;
        storage_create_info.attrib = E32_CHUNK_ATTRIB_LOCAL | E32_CHUNK_ATTRIB_READ_WRITE | E32_CHUNK_ATTRIB_DISCONNECTED;
        storage_create_info.force_fixed = E32_TRUE;
        storage_create_info.initial_bottom = 0;
        storage_create_info.initial_top = E32_GLOBAL_STORAGE_CHUNK_MAX;
        storage_create_info.max_size = E32_GLOBAL_STORAGE_CHUNK_MAX;
        storage_create_info.clear_byte = 0xCC;  // Use 0xCC as clear byte

        const int32 result = e32_chunk_create("GlobalStorageChunks", E32_HANDLE_OWNER_PROCESS, 
            &storage_create_info);

        if (result < 0) {
            e32_panic(E32_PANIC_REASON_NKERN_ALLOC_GLOBAL_STORAGE_FAIL, E32_PANIC_REASON_NKERN_CATEGORY);
        }

        // Get the base address right away
        storage = e32_get_chunk_base(result);
        storage->global_storage_chunk = result;
        storage->fs_session = 0;
    } else {
        storage = (e32_thread_global_storage*)(thread_create_info->last_global_storage + 
            sizeof(e32_thread_global_storage));
        // Simple allocation
        *storage = *(e32_thread_global_storage*)(thread_create_info->last_global_storage);
    }

    // Switch the storage
    e32_set_thread_heap_allocator(storage);
}

void e32_run_thread(bool is_not_first_thread_created, void *thread_info)
{
    if (!is_not_first_thread_created)
    {
        // This is the first thread in the process, setup some stuffs
        int32 err = e32_set_dll_tls(E32_GLOBAL_DESTRUCTOR_KEY, E32_SPECIAL_DLL_UID, (void*)e32_global_constructor_func);
    }

    // Create global storage for this thread
    e32_create_global_storage_chunk(thread_info, !is_not_first_thread_created);
}
