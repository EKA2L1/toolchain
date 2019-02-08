#include <epoc/filesystem.h>
#include <epoc/kernel.h>

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
