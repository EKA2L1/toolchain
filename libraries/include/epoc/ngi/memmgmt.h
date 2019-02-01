#ifndef __EPOC_NGI_MEM_MGMT_H
#define __EPOC_NGI_MEM_MGMT_H

#include <epoc/common.h>

typedef struct ngi_heap_base {
    void *vtable;
    uint8 gaps[0x7C];
    void *allocator;        ////< RHeap*. This will not be used, as this manager will provided function to do allocate itself.
    uint8 gaps2[0x38];
    handle cs_lock;         ///< A critical section responds for gurantees thread-safe allocating
    uint32 gaps3[4];
} ngi_heap_base;

/*! \brief Create a heap memory region.
 *
 * This new memory can be used with the returned memory manager. 200 bytes of the new memory chunk are used
 * for storing this memory manager.
 * 
 * This is actually ngi::CHeap::NewL() method in a vtable. We still needs to find where the export
 * is.
 * 
 * \param max_mem_size Maximum size of this new memory chunk
 * 
 * \returns nullptr if max_mem_size is negative, or memory chunk can't be created.
*/
ngi_heap_base *ngi_new_memory_chunk(const int max_mem_size, const int unk1, const int unk2, 
    const int unk3);

#endif