/** 
 * Copyright (c) 2019 EKA2L1 Project. All rights reserved.
 * 
 * This work is licensed under the terms of the MIT license.  
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */

#ifndef __EPOC_FILESYSTEM_COMMON_H
#define __EPOC_FILESYSTEM_COMMON_H

#include <epoc/common.h>

#ifdef __EKA2__
#define E32_FILE_SERVER_NAME "!FileServer"
#else
#define E32_FILE_SERVER_NAME "!FileServer"
#endif

typedef handle e32file;

#define E32_FS_MSG_FILE_CLOSE 28
#define E32_FS_MSG_FILE_OPEN 30
#define E32_FS_MSG_FILE_CREATE 31
#define E32_FS_MSG_FILE_REPLACE 32
#define E32_FS_MSG_FILE_TEMP 33

/** 
 * Indicates that the file can be open and use by current process, any other
 * process try to open this will fail.
 * 
 * If other process already opens your file with this mode, you can't open it.
 */
#define E32_FS_FILE_SHARE_EXCLUSIVE 0

/**
 * When you open your file with this share mode, all file access operation forwards
 * can only open this file in read mode.
 * 
 * Opening this share mode along with write mode will not work.
*/
#define E32_FS_FILE_SHARE_READ_ONLY 1

/**
 * Open your file with this mode allows unlimited access to the file when opening in
 * the future.
 * 
 * This mode is not compatible with read only share mode, since it gurantees the file 
 * to be writeable.
 */
#define E32_FS_FILE_SHARE_ANY 2

/**
 * Open your file with this mode allows unlimited access to the file when opening in the
 * future.
 * 
 * This mode is compatible with read only share mode
 */
#define E32_FS_FILE_SHARE_READ_WRITE 3

/**
 * Open your file in binary mode.
 */
#define E32_FS_FILE_BIN_MODE 0

/**
 * Open your file in text mode.
 */
#define E32_FS_FILE_TEXT_MODE 0x100

/**
 * Open the file for reading.
*/
#define E32_FS_FILE_READ 0

/**
 * Open the file for writing.
*/
#define E32_FS_FILE_WRITE 0x200

/**
 * Specifies that an asynchronous read request should not be completed 
 * until all requested data becomes available.
 *
 * Cannot be combined with the E32_FS_FILE_SHARE_EXCLUSIVE or E32_FS_FILE_SHARE_READ_ONLY
 * as this will prohibit a writer from updating the file.
 */
#define E32_FS_FILE_READ_ASYNC_ALL 0x400

/**
 * Open a file in big mode, allowing file larger than 4GB
 */
#define E32_FS_FILE_BIG 0x00040000

#endif
