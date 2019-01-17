#include <epoc/descriptor.h>

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
