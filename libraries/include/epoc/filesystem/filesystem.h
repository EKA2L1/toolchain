/** 
 * Copyright (c) 2019 EKA2L1 Project. All rights reserved.
 * 
 * This work is licensed under the terms of the MIT license.  
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */

#ifndef __EPOC_FILESYSTEM_FILESYSTEM_H
#define __EPOC_FILESYSTEM_FILESYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <epoc/filesystem/common.h>

/*
 * \brief Create a new file session.
 * 
 * This create a new session to !FileServer, allows you to send messages to it, including
 * important function like open or close files.
 * 
 * \param    max_msg_slots Total async message slots
 * 
 * \returns  0 for failure, else handle to the new file session.
*/
E32_API handle e32_create_file_session(const int32 max_msg_slots);

/**
 * \brief Set current thread's file session.
 *
 * By default, file session will be used from its parent session.
 * If the session is not available when calling first file operation, a new session will be created
 */
E32_API handle e32_set_current_thread_file_session(const handle h);

/**
 * \brief Get current thread's file session.
 */
E32_API handle e32_get_current_thread_file_session();

/**
 * \brief Open a file.
 * 
 * Using current thread's file session, the function sends an open/create/temporary/replace
 * file message to the server, depends on the given flag.
 * 
 * \param path  File path in UCS2
 * \param mode  File open mode.
 *    
 * First 20 bits are used to store the read/write/share mode.
 * Next  8  bits are used to store the open kind.   
 *        
 * The file open kind can be a normal open, create new, temporary or replace.
 * - "Open" will make the function returns error if the file doesn't exist yet.
 * - "Create" flag will create a new file and returns error if the file already exists.
 * - "Temporary" flag will make a temporary file and open it.
 * - "Replace" flag will replace the file with new one if it already exists, or create if it doesn't exist.
 * 
 * If those 8 bits are cleared, the function will determine which kind will suit best with given read/write/share mode.
 * 
 * \returns A handle to file in current thread's file session if successful, else error codes.
 */
e32file e32_open_file(const ucs2str path, const int mode);

/**
 * \brief Close a file subsession in current thread's file session.
 */
void e32_close_file(e32file file);

#ifdef __cplusplus
}
#endif

#endif
