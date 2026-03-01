#include <stdbool.h>
#include <stdint.h>
#include "dynamic_mem.h"

// Dynamically allocate memory space
void* malloc(size_t size)
{
    dynamic_mem_node_t* best_mem_block = find_best_mem_block(NULL, size);

    if (best_mem_block != NULL)
    {
        best_mem_block->size = best_mem_block->size - size - DYNAMIC_MEM_NODE_SIZE;

        dynamic_mem_node_t* mem_node_allocate =
            (dynamic_mem_node_t*)(((uint8_t*)best_mem_block) + DYNAMIC_MEM_NODE_SIZE +
                                  best_mem_block->size);
        mem_node_allocate->size = size;
        mem_node_allocate->used = true;
        mem_node_allocate->prev = best_mem_block;
        mem_node_allocate->next = best_mem_block->next;

        if (best_mem_block->next != NULL)
        {
            best_mem_block->next->prev = mem_node_allocate;
        }
        best_mem_block->next = mem_node_allocate;

        return (void*)((uint8_t*)mem_node_allocate + DYNAMIC_MEM_NODE_SIZE);
    }

    return NULL;
}
