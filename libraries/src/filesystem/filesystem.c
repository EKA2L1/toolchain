/** 
 * Copyright (c) 2019 EKA2L1 Project. All rights reserved.
 * 
 * This work is licensed under the terms of the MIT license.  
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */

#include <epoc/filesystem/filesystem.h>
#include <epoc/kernel.h>
#include <epoc/descriptor.h>
#include <epoc/err.h>

/**
 * \brief Choose best open kind given open mode.
 */
int e32_choose_best_open_kind(const int mode) 
{
    if (mode & E32_FS_FILE_WRITE) {
        return E32_FS_MSG_FILE_REPLACE;
    }
    
    return E32_FS_MSG_FILE_OPEN;
}

E32_API handle e32_set_current_thread_file_session(const handle h)
{
    e32_thread_global_storage *storage = e32_get_global_storage();
    const handle old_handle = storage->fs_session;
    storage->fs_session = h;

    return old_handle;
}

E32_API handle e32_get_current_thread_file_session() 
{
    e32_thread_global_storage *storage = e32_get_global_storage();

    // If the file session hasn't been opened yet, open it.
    if (storage->fs_session == 0) {
        storage->fs_session = e32_create_file_session(-1);
    }

    return storage->fs_session;
}

E32_API handle e32_create_file_session(const int32 max_msg_slots)
{
    return e32_session_create(E32_FILE_SERVER_NAME, max_msg_slots,
        E32_NULL, E32_IPC_SERVER_ROLE_DEFAULT);
}

E32_API e32file e32_open_file(const ucs2str path, const int mode) 
{
    e32file file_handle = 0;

    // Try to get the open kind
    int msg = mode & 0x0FF00000;

    // No kind provided
    if (msg == 0) {
        msg = e32_choose_best_open_kind(mode & 0x000FFFFF);
    }

    // Create file name descriptor
    ptrc_descriptor file_name_des;
    e32_create_descriptor_const_16(&file_name_des, path, -1);

    // Create a modifable descriptor for server to store handle
    ptr_descriptor file_handle_des;
    e32_create_descriptor(&file_handle_des, (uint8*)(&file_handle), 0, sizeof(file_handle));

    e32_ipc_args args;
    e32_set_ipc_arg_string(&args, 0, (void*)(&file_name_des), E32_FALSE, E32_TRUE);
    e32_set_ipc_arg(&args, 1, mode & 0x000FFFFF);
    e32_set_ipc_arg_string(&args, 3, (void*)(&file_handle_des), E32_TRUE, E32_FALSE);

    // Finish packing, now we should send and wait
    const uint32 handle = e32_session_send_and_wait(e32_get_current_thread_file_session(), msg,
        &args);

    return handle;
}

E32_API void e32_close_file(e32file file) 
{
    e32_ipc_args args;
    e32_set_ipc_arg(&args, 3, file);

    e32_session_send_and_wait(e32_get_current_thread_file_session(), E32_FS_MSG_FILE_OPEN, &args);
}
