#include "dynamic_mem.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static uint8_t dynamic_mem_area[DYNAMIC_MEM_TOTAL_SIZE];
static dynamic_mem_node_t* dynamic_mem_start;

// Initialize dynamic memory
void init_dynamic_mem()
{
    dynamic_mem_start = (dynamic_mem_node_t*)dynamic_mem_area;
    dynamic_mem_start->size = DYNAMIC_MEM_TOTAL_SIZE - DYNAMIC_MEM_NODE_SIZE;
    dynamic_mem_start->prev = NULL;
    dynamic_mem_start->next = NULL;
    dynamic_mem_start->used = false;  // Initialize the used member
}

dynamic_mem_node_t* find_best_mem_block(dynamic_mem_node_t* dynamic_mem, size_t size)
{
    if (dynamic_mem == NULL)
        dynamic_mem = dynamic_mem_start;

    dynamic_mem_node_t* best_mem_block = (dynamic_mem_node_t*)NULL;
    uint32_t best_mem_block_size = DYNAMIC_MEM_TOTAL_SIZE + 1;

    dynamic_mem_node_t* current_mem_block = dynamic_mem;
    while (current_mem_block)
    {
        if ((!current_mem_block->used) &&
            (current_mem_block->size >= (size + DYNAMIC_MEM_NODE_SIZE)) &&
            (current_mem_block->size <= best_mem_block_size))
        {
            best_mem_block = current_mem_block;
            best_mem_block_size = current_mem_block->size;
        }
        current_mem_block = current_mem_block->next;
    }
    return best_mem_block;
}

dynamic_mem_node_t* merge_next_node_into_current(dynamic_mem_node_t* current_mem_node)
{
    dynamic_mem_node_t* next_mem_node = current_mem_node->next;
    if (next_mem_node != NULL && !next_mem_node->used)
    {
        current_mem_node->size += next_mem_node->size;
        current_mem_node->size += DYNAMIC_MEM_NODE_SIZE;

        current_mem_node->next = next_mem_node->next;
        if (current_mem_node->next != NULL)
        {
            current_mem_node->next->prev = current_mem_node;
        }
    }

    return current_mem_node;
}

void merge_current_node_into_previous(dynamic_mem_node_t* current_mem_node)
{
    dynamic_mem_node_t* prev_mem_node = current_mem_node->prev;

    if (prev_mem_node != NULL && !prev_mem_node->used)
    {
        prev_mem_node->size += current_mem_node->size;
        prev_mem_node->size += DYNAMIC_MEM_NODE_SIZE;

        prev_mem_node->next = current_mem_node->next;
        if (prev_mem_node->next != NULL)
        {
            prev_mem_node->next->prev = prev_mem_node;
        }
    }
}