#include <epoc/common.h>

#ifdef __GCC32__
typedef void (*PFV)();
extern PFV __CTOR_LIST__[];
extern PFV __DTOR_LIST__[];

void e32_global_destructor_func() {
    uint32 i = 1;
    
    while (__DTOR_LIST__[i]) {
        (*__DTOR_LIST__[i++])();
    }
}

void e32_global_constructor_func() {
    uint32 i = 1;

    while (__CTOR_LIST__[i]) {
        (*__CTOR_LIST__[i++])();
    }
}
#endif

void e32_run_thread(bool is_not_first_thread_created, void *thread_info)
{
    if (!is_not_first_thread_created)
    {
        // This is the first thread in the process, setup some stuffs
    }
}
