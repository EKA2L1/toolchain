/** 
 * Copyright (c) 2019 EKA2L1 Project. All rights reserved.
 * 
 * This work is licensed under the terms of the MIT license.  
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */

#ifndef __EPOC_DESCRIPTOR_H
#define __EPOC_DESCRIPTOR_H

#include <epoc/common.h>

typedef enum des_type 
{
    des_buf_c,
    des_ptr_c,
    des_ptr,
    des_buf,
    des_buf_ptr
} des_type;

typedef struct descriptor
{
    uint32 info;
} descriptor;

/**
 * \brief A descriptor that contains pointer to actual string data.
 *
 * This descriptor is not mean to be modifiable or expandable
 */
typedef struct ptrc_descriptor
{
    uint32 info;
    void *data;
} ptrc_descriptor;

/**
 * \brief A descriptor that contains pointer to actual string data.
 *
 * This descriptor is mean to be modifiable or expandable
 */
typedef struct ptr_descriptor
{
    uint32 info;
    uint32 max_length;
    void *data;
} ptr_descriptor;

des_type e32_descriptor_get_type(const descriptor *str);
uint32 e32_descriptor_get_length(const descriptor *str);

void e32_descriptor_set_type(descriptor *str, const des_type type);
void e32_descriptor_set_length(descriptor *str, const uint32 len);

/**
 * brief Construct a 16-bit not modifiable descriptor from an UCS-2 string
 *
 * \param des Pointer to the ptrc descriptor variant
 * \param str Pointer to the string
 * \param len The length of the string. If this is -1, the function will strlen.
 * 
 * \returns E32_ERR_NONE if success
 */
int32 e32_create_descriptor_const_16(ptrc_descriptor *des, const ucs2str str, const int32 len);

/**
 * \brief Construct a 16-bit modifiable descriptor from an UCS-2 string
 *
 * \param des Pointer to the ptrc descriptor variant
 * \param str Pointer to the string
 * \param len The length of the string. If this is -1, the function will strlen.
 * \param ini_max_length Initial max length the string can reach
 * 
 * \returns E32_ERR_NONE if success
 */
int32 e32_create_descriptor_16(ptr_descriptor *des, const ucs2str str, const int32 len, const int32 ini_max_length);

/**
 * \brief Construct an 8-bit not modifiable descriptor from an UCS-2 string
 *
 * \param des Pointer to the ptrc descriptor variant
 * \param str Pointer to the string
 * \param len The length of the string. If this is -1, the function will strlen.
 * 
 * \returns E32_ERR_NONE if success
 */
int32 e32_create_descriptor_const(ptrc_descriptor *des, const char *str, const int32 len);

/**
 * \brief Construct an 8-bit modifiable descriptor from an UCS-2 string
 *
 * \param des Pointer to the ptrc descriptor variant
 * \param str Pointer to the string
 * \param len The length of the string. If this is -1, the function will strlen.
 * \param ini_max_length Initial max length the string can reach
 * 
 * \returns E32_ERR_NONE if success
 */
int32 e32_create_descriptor(ptr_descriptor *des, const char *str, const int32 len, const int32 ini_max_length);

#endif
