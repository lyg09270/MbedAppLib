/*
 * Copyright 2024 Civic_Crab
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * File: MAL_Kalman_Filter.h
 * Author: Civic_Crab
 * Version: 0.0.1
 * Created on: 2025-3-22
 *
 * Description:
 * This file contains the heap management functions.
 */
 
#include "mal_heap.h"
#include <string.h>

// Metadata for each block
#define METADATA_SIZE ((sizeof(MAL_block_t) + (MAL_ALIGNMENT-1)) & ~(MAL_ALIGNMENT-1))

// transfer size to block size
static size_t size_to_blocks(size_t size) {
    size_t total = (size + METADATA_SIZE + MAL_BLOCK_SIZE - 1) / MAL_BLOCK_SIZE;
    return (total == 0) ? 1 : total; // Ensure at least one block
}

// combine adjacent free blocks
static void coalesce_blocks(MAL_block_t* block) {
    while (block->next && block->next->is_free) {
        block->size += block->next->size + 
                      (block->next - block - block->size);
        block->next = block->next->next;
    }
}

void mal_heap_init(MAL_heap_t* heap) {
    // Initialize heap
    MAL_block_t* first = (MAL_block_t*)heap->pool;
    first->next = NULL;
    first->size = (MAL_HEAP_SIZE - METADATA_SIZE) / MAL_BLOCK_SIZE;
    first->is_free = true;
    
    heap->free_list = first;
    heap->total_allocated = 0;
    heap->max_contiguous = first->size;
}

void* mal_malloc(MAL_heap_t* heap, size_t size) {
    if (size == 0 || size > MAL_HEAP_SIZE - METADATA_SIZE) 
        return NULL;

    // find suitable block
    size_t required = size_to_blocks(size);
    MAL_block_t **prev = &heap->free_list, *curr = heap->free_list;
    
    while (curr) {
        if (curr->is_free && curr->size >= required) {
            // find big enough block
            if (curr->size > required) {
                // split block
                MAL_block_t* new_block = curr + required + 1;
                new_block->next = curr->next;
                new_block->size = curr->size - required - 1;
                new_block->is_free = true;
                
                curr->size = required;
                curr->next = new_block;
            }
            curr->is_free = false;
            *prev = curr->next; // remove from free list
            
            // update the memory allocated
            heap->total_allocated += curr->size * MAL_BLOCK_SIZE;
            size_t contiguous = curr->size * MAL_BLOCK_SIZE;
            if (contiguous > heap->max_contiguous)
                heap->max_contiguous = contiguous;
            
            // return pointer to the allocated memory
            return (void*)((char*)curr + METADATA_SIZE);
        }
        prev = &curr->next;
        curr = curr->next;
    }
    return NULL; // No suitable block found
}

void mal_free(MAL_heap_t* heap, void* ptr) {
    if (!ptr || ptr < (void*)heap->pool || 
        ptr >= (void*)(heap->pool + MAL_HEAP_SIZE))
        return;

    MAL_block_t* block = (MAL_block_t*)((char*)ptr - METADATA_SIZE);
    block->is_free = true;
    
    // Insert into free list
    block->next = heap->free_list;
    heap->free_list = block;
    
    // combine adjacent free blocks
    coalesce_blocks(block);
    
    // Update memory allocated
    heap->total_allocated -= block->size * MAL_BLOCK_SIZE;
}

size_t mal_heap_get_used(const MAL_heap_t* heap) {
    return heap->total_allocated;
}

size_t mal_heap_get_free(const MAL_heap_t* heap) {
    size_t free = 0;
    MAL_block_t* curr = heap->free_list;
    while (curr) {
        free += curr->size * MAL_BLOCK_SIZE;
        curr = curr->next;
    }
    return free;
}

bool mal_heap_check_integrity(const MAL_heap_t* heap) {
    MAL_block_t* curr = (MAL_block_t*)heap->pool;
    while (curr < (MAL_block_t*)(heap->pool + MAL_HEAP_SIZE)) {
        if (curr->next && curr->next <= curr) 
            return false;
        if (curr->size == 0 || (unsigned char*)curr + METADATA_SIZE + curr->size*MAL_BLOCK_SIZE > heap->pool + MAL_HEAP_SIZE)
            return false;
        curr = curr + curr->size + 1;
    }
    return true;
}