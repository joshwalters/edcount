/*
    edcount - estimate distinct count utility tool.
    Copyright (C) 2018 Harold Freeman

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "fasthash.h"
#include "cli.h"

#define BUF_SIZE 1024*10

#define NUM_NODES(height) ((1 << (height + 1)) - 1)
#define PARENT(x) ((x - 1) / 2)
#define LEFT_CHILD(x) (2 * x + 1)
#define RIGHT_CHILD(x) (2 * x + 2)

/**
 * Store the heap.
 */
typedef struct {
    uint8_t height;
    uint32_t num_nodes;
    uint32_t occupied_nodes;
    uint64_t* data;
} Heap;

/**
 * Swap two nodes in the heap.
 */
void swap(uint64_t* a, uint64_t* b) {
    uint64_t tmp = *a;
    *a = *b;
    *b = tmp;
}

/**
 * Insert into the heap.
 */
void insert(Heap *heap, uint64_t value) {
    if (heap->occupied_nodes < heap->num_nodes) {
        // Heap is not full, insert at end and buble up
        int node_pos = heap->occupied_nodes;
        heap->data[node_pos] = value;
        heap->occupied_nodes += 1;
        // Now bubble up
        while (node_pos != 0 && (heap->data[node_pos] > heap->data[PARENT(node_pos)])) {
            swap(&heap->data[node_pos], &heap->data[PARENT(node_pos)]);
            node_pos = PARENT(node_pos);
        }
        return;
    } else {
        // Heap is full. If value less than root, replace root and bubble down.
    }
}

int main(int argc, char** argv) {
    // Check flags
    if (is_flag_present(argc, argv, "--help")) {
        print_header();
        print_help(argv);
        exit(EXIT_SUCCESS);
    }

    // TODO size from CLI
    Heap heap;
    heap.height = 2;
    heap.occupied_nodes = 0;
	heap.num_nodes = NUM_NODES(heap.height);
    // Allocate the min-heap
    heap.data = (uint64_t*) calloc(heap.num_nodes, sizeof(uint64_t));
    if (heap.data == NULL) {
        exit(EXIT_FAILURE);
    }

    // Use heap
    insert(&heap, 42);
    insert(&heap, 5);
    insert(&heap, 60);
    insert(&heap, 80);
    insert(&heap, 90);
    insert(&heap, 99);
    insert(&heap, 100);
    insert(&heap, 101);

    //Print heap
    int i = 0;
    for (i = 0; i < heap.num_nodes; i++) {
        printf("%llu ", heap.data[i]);
    }
    printf("\n");

//    char buf[BUF_SIZE];
//    uint64_t seed = 0;
//    while (fgets(buf, BUF_SIZE, stdin) != NULL) {
//	    uint64_t hash = fasthash64(buf, strlen(buf), seed);
//        printf("%llu\n", hash);
//        // UINT64_MAX
//    }

    free(heap.data);

    exit(EXIT_SUCCESS);
}
