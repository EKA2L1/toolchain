#ifndef __EPOC_FILESYSTEM
#define __EPOC_FILESYSTEM

#include <epoc/common.h>

typedef handle e32file;

handle e32_create_file_session(const int32 max_msg_slots);
void e32_close_file_session(const handle h);

/*! \brief Set the current's thread file session.
 *
 * By default, file session will be used from its parent session.
 * If the session is not available when calling first file operation, a new session will be created
*/
handle e32_set_current_thread_file_session(const handle h);

e32file e32_open_file(const ucs2_str path, const int flags, const int mode);
void e32_close_file(e32file file);

#endif