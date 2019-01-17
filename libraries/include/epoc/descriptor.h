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

des_type e32_descriptor_get_type(const descriptor *str);
uint32 e32_descriptor_get_length(const descriptor *str);

void e32_descriptor_set_type(descriptor *str, const des_type type);
void e32_descriptor_set_length(descriptor *str, const uint32 len);

#endif
