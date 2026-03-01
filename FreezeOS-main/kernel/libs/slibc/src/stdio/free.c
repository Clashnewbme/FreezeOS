#include <stddef.h>
#include "dynamic_mem.h"

// Make free the dynamically allocated memory space
void free(void* ptr)
{
    if (ptr == NULL)
    {
        return;
    }

    dynamic_mem_node_t* current_mem_node =
        (dynamic_mem_node_t*)((uint8_t*)ptr - DYNAMIC_MEM_NODE_SIZE);

    if (current_mem_node == NULL)
    {
        return;
    }

    current_mem_node->used = false;

    current_mem_node = merge_next_node_into_current(current_mem_node);
    merge_current_node_into_previous(current_mem_node);
}