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
 
#ifndef MAL_HEAP_H
#define MAL_HEAP_H

#include <stddef.h>
#include <stdbool.h>

// Memory heap configuration
#define MAL_HEAP_SIZE  10 * 1024        // Heap size in kilobytes
#define MAL_BLOCK_SIZE 32               // Minimum block size in bytes
#define MAL_ALIGNMENT  sizeof(char*)    // Memory alignment in bytes

// Memory heap structure
typedef struct MAL_block {
    struct MAL_block* next;  // Pointer to the next block
    size_t size;             // Block size in bytes
    bool is_free;            // Block free status
} MAL_block_t;

typedef struct {
    unsigned char pool[MAL_HEAP_SIZE];           // Memory pool
    MAL_block_t* free_list;                      // Linked list of free blocks
    size_t total_allocated;                      // Memory allocated
    size_t max_contiguous;
} MAL_heap_t;

// Initialize the memory heap
void MAL_heap_init(MAL_heap_t* heap);

// Allocate a chunk of memory
void* MAL_malloc(MAL_heap_t* heap, size_t size);

// Free a chunck of memory
void MAL_free(MAL_heap_t* heap, void* ptr);

// Get the current memory usage
size_t MAL_heap_get_used(const MAL_heap_t* heap);
size_t MAL_heap_get_free(const MAL_heap_t* heap);
bool MAL_heap_check_integrity(const MAL_heap_t* heap);

#endif // MAL_HEAP_H