#include <stdbool.h>
#include <stdint.h>

#ifndef _DYNAMIC_MEM_H
#define _DYNAMIC_MEM_H

typedef struct dynamic_mem_node
{
    uint32_t size;
    bool used;
    struct dynamic_mem_node* prev;
    struct dynamic_mem_node* next;
} dynamic_mem_node_t;

#define DYNAMIC_MEM_TOTAL_SIZE (20 * 1024)
#define DYNAMIC_MEM_NODE_SIZE sizeof(dynamic_mem_node_t)  // 16

// Initialize dynamic memory
dynamic_mem_node_t* find_best_mem_block(dynamic_mem_node_t* dynamic_mem, size_t size);
dynamic_mem_node_t* merge_next_node_into_current(dynamic_mem_node_t* current_mem_node);
void merge_current_node_into_previous(dynamic_mem_node_t* current_mem_node);

#endif