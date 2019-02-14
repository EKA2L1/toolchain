/** 
 * Copyright (c) 2019 EKA2L1 Project. All rights reserved.
 * 
 * This work is licensed under the terms of the MIT license.  
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */

#include <epoc/std.h>
#include <epoc/kernel.h>

E32_API void e32_wait_for_request(e32_request_status *status) {
    int32 i = -1;

    do {
        i++;
        e32_wait_for_any_request();
    } while (status->code == E32_REQUEST_PENDING);

    if (i) {
        e32_request_signal(i);
    }
}

E32_API void e32_initialize_request_status(e32_request_status *status) {
    status->code = E32_REQUEST_PENDING;
}

