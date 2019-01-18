#include <epoc/common.h>
#include <epoc/err.h>

int32 e32_get_str16_length(const ucs2str *str)
{
    if (str == E32_NULL)
    {
        return E32_ERR_ARGUMENT;
    }

    int32 deslen = 0;

    // Run until we got \0
    deslen = 0;

    while (*str++ != 0)
    {
        deslen++;
    }
    
    return deslen;
}

int32 e32_get_str_length(const char *str)
{
    if (str == E32_NULL)
    {
        return E32_ERR_ARGUMENT;
    }

    int32 deslen = 0;

    // Run until we got \0
    deslen = 0;

    while (*str++ != 0)
    {
        deslen++;
    }
    
    return deslen;
}
