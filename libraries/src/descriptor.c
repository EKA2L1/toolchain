#include <epoc/descriptor.h>
#include <epoc/err.h>

des_type e32_descriptor_get_type(const descriptor *str)
{
    return (des_type)str->info >> 28;
}

uint32 e32_descriptor_get_length(const descriptor *str)
{
    return str->info & 0x0FFFFFFF;
}

void e32_descriptor_set_type(descriptor *str, const des_type type)
{
    str->info &= ~0xF0000000;
    str->info |= (int32)type << 28;
}

void e32_descriptor_set_length(descriptor *str, const uint32 len)
{
    str->info &= ~0x0FFFFFFF;
    str->info |= (len & (0x0FFFFFFF));
}

int32 e32_create_descriptor_const(ptrc_descriptor *des, const char *str, const int32 len)
{
    if (!str)
    {
        return E32_ERR_ARGUMENT;
    }

    int32 deslen = len;

    if (len == -1)
    {
        deslen = e32_get_str_length(str);
    }

    if (deslen < 0)
    {
        return E32_ERR_ARGUMENT;
    }

    e32_descriptor_set_type((descriptor*)des, des_ptr_c);
    e32_descriptor_set_length((descriptor*)des, deslen);

    des->data = (void*)str;

    return E32_ERR_NONE;
}

int32 e32_create_descriptor(ptr_descriptor *des, const char *str, const int32 len, const int32 ini_max_length) 
{
    int32 error_code = e32_create_descriptor_const((ptrc_descriptor*)(des), str, len);

    if (error_code != E32_ERR_NONE) 
    {
        return error_code;
    }

    des->max_length = ini_max_length;
    return E32_ERR_NONE;
}

int32 e32_create_descriptor_const_16(ptrc_descriptor *des, const ucs2 *str, const int32 len) 
{
    int32 deslen = len;

    if (len == -1)
    {
        deslen = e32_get_str16_length(str);
    }

    return e32_create_descriptor_const(des, (const char*)str, deslen);
}

int32 e32_create_descriptor_16(ptr_descriptor *des, const ucs2 *str, const int32 len, const int32 ini_max_length)
{
    int32 error_code = e32_create_descriptor_const_16((ptrc_descriptor*)(des), str, len);

    if (error_code != E32_ERR_NONE) 
    {
        return error_code;
    }

    des->max_length = ini_max_length;
    return E32_ERR_NONE;
}
