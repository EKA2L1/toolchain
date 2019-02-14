/** 
 * Copyright (c) 2019 EKA2L1 Project. All rights reserved.
 * 
 * This work is licensed under the terms of the MIT license.  
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */

#ifndef __EPOC_STD_H
#define __EPOC_STD_H

#include <epoc/common.h>

typedef struct e32_request_status 
{
    int32 code;
    int32 flags;
} e32_request_status;

E32_API void e32_initialize_request_status(e32_request_status *status);

#define E32_REQUEST_PENDING -0x7fffffff

#define E32_POLICY_TYPE_ALWAYS_FAIL 0
#define E32_POLICY_TYPE_ALWAYS_PASS 1

// This policy has up to 3 capabilities
#define E32_POLICY_TYPE_C3 2

// This policy has up to 7 capabilities
// Normaly, it only has max of 3, but more needed, so 4 more fields got added
#define E32_POLICY_TYPE_C7 3

// Secure ID + 3 capabilities
#define E32_POLICY_TYPE_S3 4

// Vendor ID + 3 capabilities
#define E32_POLICY_TYPE_V3 5

typedef union e32_extended_security_policy
{
    uint32 secure_id;
    uint32 vendor_id;
    uint8  extra_caps[4];
} e32_extended_security_policy;

typedef struct e32_security_policy 
{
    uint8 type;
    uint8 caps[3];

    e32_extended_security_policy extended_policy;
} e32_security_policy;

E32_API void e32_wait_for_request(e32_request_status *status);

#endif
