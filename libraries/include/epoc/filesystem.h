#ifndef __EPOC_FILESYSTEM_H
#define __EPOC_FILESYSTEM_H

#include <epoc/common.h>

#ifdef __EKA2__
#define E32_FILE_SERVER_NAME "!FileServer"
#else
#define E32_FILE_SERVER_NAME "!FileServer"
#endif

typedef handle e32file;

#define E32_FS_MSG_FILE_OPEN 30

E32_API handle e32_create_file_session(const int32 max_msg_slots);

/*! \brief Set the current's thread file session.
 *
 * By default, file session will be used from its parent session.
 * If the session is not available when calling first file operation, a new session will be created
*/
E32_API handle e32_set_current_thread_file_session(const handle h);
E32_API handle e32_get_current_thread_file_session();

e32file e32_open_file(const ucs2 *path, const int flags, const int mode);
void e32_close_file(e32file file);

#endif
