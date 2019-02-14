/** 
 * Copyright (c) 2019 EKA2L1 Project. All rights reserved.
 * 
 * This work is licensed under the terms of the MIT license.  
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */

#ifndef __EPOC_ERR_H
#define __EPOC_ERR_H

/**  No error, this indicates success */
#define E32_ERR_NONE 0

/**  This error code defined that some operation can't find some items */
#define E32_ERR_NOT_FOUND -1

/**  This error code defined a error that has no specific category */
#define E32_ERR_GENERAL -2

/**  This error code defined that an item is canceled */
#define E32_ERR_CANCEL -3

/**  This error code defined that there is not enough memory left for an operation. */
#define E32_ERR_NO_MEMORY -4

/**  This error code defined that a feature is not supported. */
#define E32_ERR_NOT_SUPPORTED -5

/**  This error code defined that an argument is invalid or out of range. */
#define E32_ERR_ARGUMENT -6

/**  This error code indicates that a calculation has lost precision. */
#define E32_ERR_LOSS_OF_PRECISION -7

/**  This error code indicates that an invalid handle has been passed. */
#define E32_ERR_BAD_HANDLE -8

#define E32_ERR_OVERFLOW -9

#define E32_ERR_UNDERFLOW -10

#define E32_ERR_ALREADY_EXISTS -11

#define E32_ERR_PATH_NOT_FOUND -12

#define E32_ERR_DIED -13

#define E32_ERR_IN_USE -14

#define E32_ERR_SERVER_TERMINATED -15

#define E32_ERR_SERVER_BUSY -16

#define E32_ERR_COMPLETE -17

#define E32_ERR_NOT_READY -18

#define E32_ERR_UNKNOWN -19

#define E32_ERR_CORRUPT -20

#define E32_ERR_ACCESS_DENIED -21

#define E32_ERR_LOCKED -22

/**  This error code indicates that a write operation has not fully write all the provided buffer */
#define E32_ERR_WRITE_NOT_FULL -23

#define E32_ERR_DISMOUNTED -24

#define E32_ERR_EOF -25

#define E32_ERR_DISK_FULL -26

#define E32_ERR_BAD_DRIVER -27

#define E32_ERR_BAD_NAME -28

#define E32_ERR_COMMS_LINE_FAIL -29

#define E32_ERR_COMMS_FRAME -30

#define E32_ERR_COMMS_OVERRUN -31

#define E32_ERR_COMMS_PARITY -32

#define E32_ERR_TIMED_OUT -33

#define E32_ERR_COULD_NOT_CONNECT -34

#define E32_ERR_COULD_NOT_DISCONNECT -35

#define E32_ERR_DISCONNECTED -36

#define E32_ERR_BAD_LIB_ENTRY_POINT -37

#define E32_ERR_BAD_DESCRIPTOR -38

#define E32_ERR_ABORT -39

#define E32_ERR_TOO_BIG -40

#define E32_ERR_DIVIDE_BY_ZERO -41

#define E32_ERR_BAD_POWER -42

#define E32_ERR_DIR_FULL -43

#define E32_ERR_HARDWARE_NOT_AVAIL -44

#define E32_ERR_SESSION_CLOSED -45

#define E32_ERR_PERMISSON_DENIED -46

#define E32_ERR_EXTENSION_NOT_SUPPORTED -47

#define E32_ERR_COMMS_BREAK -48

#define E32_ERR_NO_SECURE -49

#define E32_ERR_CORRUPT_SURROTAGE_FOUND -50

#endif
