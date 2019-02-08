#include <epoc/filesystem.h>
#include <epoc/kernel.h>
#include <epoc/descriptor.h>
#include <epoc/err.h>

E32_API handle e32_set_current_thread_file_session(const handle h) {
    e32_thread_global_storage *storage = e32_get_global_storage();
    const handle old_handle = storage->fs_session;
    storage->fs_session = h;

    return old_handle;
}

E32_API handle e32_get_current_thread_file_session() {
    e32_thread_global_storage *storage = e32_get_global_storage();
    return storage->fs_session;
}

E32_API handle e32_create_file_session(const int32 max_msg_slots) {
    return e32_session_create(E32_FILE_SERVER_NAME, max_msg_slots,
        E32_NULL, E32_IPC_SERVER_ROLE_DEFAULT);
}

E32_API e32file e32_open_file(const ucs2 *path, const int flags, const int mode) {
    e32file file_handle = 0;

    // Create file name descriptor
    ptrc_descriptor file_name_des;
    e32_create_descriptor_const_16(&file_name_des, path, -1);

    // Create a modifable descriptor for server to store handle
    ptr_descriptor file_handle_des;
    e32_create_descriptor(&file_handle_des, (uint8*)(&file_handle), 0, sizeof(file_handle));

    e32_ipc_args args;
    e32_set_ipc_arg_string(&args, 0, (void*)(&file_name_des), E32_FALSE, E32_TRUE);
    e32_set_ipc_arg(&args, 1, mode);
    e32_set_ipc_arg_string(&args, 3, (void*)(&file_handle_des), E32_TRUE, E32_FALSE);

    e32_request_status status;
    e32_initialize_request_status(&status);

    // Finish packing, now we should send and wait
    const uint32 err = e32_session_send_sync(e32_get_current_thread_file_session(), E32_FS_MSG_FILE_OPEN,
        &args, &status);

    if (err != E32_ERR_NONE) {
        return err;
    }

    e32_wait_for_request(&status);
    if (status.code != E32_ERR_NONE) {
        return status.code;
    }

    return file_handle;
}

E32_API void e32_close_file(e32file file) {
    
}
