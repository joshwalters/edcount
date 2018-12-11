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

#include "kmv.h"

/**
 * Swap two nodes in the heap.
 */
void swap(uint64_t* a, uint64_t* b) {
    uint64_t tmp = *a;
    *a = *b;
    *b = tmp;
}

bool kmv_init(struct KMV *kmv, uint8_t height) {
    kmv->height = height;
    kmv->num_nodes = NUM_NODES(height);
    kmv->occupied_nodes = 0;
    kmv->cell_size = 64;
    kmv->total_inserts = 0;
    kmv->data = NULL;
    kmv->data = calloc(kmv->num_nodes, sizeof(uint64_t));
    if (kmv->data == NULL) {
        return false;
    }
    return true;
}

void kmv_free(struct KMV *kmv) {
    if (kmv->data == NULL) {
        return;
    }
    free(kmv->data);
    kmv->data = NULL;
}

void kmv_insert(struct KMV *kmv, uint64_t value) {
    // Increment total inserts
    kmv->total_inserts += 1;
    if (kmv->occupied_nodes < kmv->num_nodes) {
        // Heap is not full, insert at end and buble up
        uint64_t node_pos = kmv->occupied_nodes;
        kmv->data[node_pos] = value;
        kmv->occupied_nodes += 1;
        // Now bubble up
        while (node_pos != 0 && (kmv->data[node_pos] > kmv->data[PARENT(node_pos)])) {
            swap(&kmv->data[node_pos], &kmv->data[PARENT(node_pos)]);
            node_pos = PARENT(node_pos);
        }
    } else {
        // Heap is full. If value less than root, replace root and bubble down.
        if (value < kmv->data[0]) {
            kmv->data[0] = value;
            uint64_t node_pos = 0;
            // Keep moving node down as long as the position is valid
            while (node_pos < kmv->occupied_nodes) {
                uint64_t left = LEFT_CHILD(node_pos);
                uint64_t right = RIGHT_CHILD(node_pos);
                if (left >= kmv->num_nodes || right >= kmv->num_nodes) {
                    // Done inserting
                    return;
                }
                // Assume left is largest
                uint64_t largest_child = left;
                if (kmv->data[LEFT_CHILD(node_pos)] < kmv->data[RIGHT_CHILD(node_pos)]) {
                    largest_child = RIGHT_CHILD(node_pos);
                }
                // Check if current node is smaller than child, if so, swap
                if (kmv->data[node_pos] < kmv->data[largest_child]) {
                    swap(&kmv->data[node_pos], &kmv->data[largest_child]);
                    node_pos = largest_child;
                } else {
                    // Node is in valid position
                    return;
                }
            }
        }
    }
}

/**
 * Helper function, remove root, replace with furthest node, and bubble down.
 */
bool remove_root(struct KMV *kmv) {
    if (kmv->occupied_nodes > 1) {
        kmv->data[0] = kmv->data[kmv->occupied_nodes - 1];
        kmv->occupied_nodes -= 1;
        uint64_t node_pos = 0;
        // Keep moving node down as long as the position is valid
        while (node_pos < kmv->occupied_nodes) {
            uint64_t left = LEFT_CHILD(node_pos);
            uint64_t right = RIGHT_CHILD(node_pos);
            if (left >= kmv->num_nodes || right >= kmv->num_nodes) {
                // Done inserting
                return true;
            }
            // Assume left is largest
            uint64_t largest_child = left;
            if (kmv->data[LEFT_CHILD(node_pos)] < kmv->data[RIGHT_CHILD(node_pos)]) {
                largest_child = RIGHT_CHILD(node_pos);
            }
            // Check if current node is smaller than child, if so, swap
            if (kmv->data[node_pos] < kmv->data[largest_child]) {
                swap(&kmv->data[node_pos], &kmv->data[largest_child]);
                node_pos = largest_child;
            } else {
                // Node is in valid position
                return true;
            }
        }
        return true;
    }
    return false;
}

uint64_t kmv_estimate_whm(struct KMV *kmv) {
    // Special single record case
    if (kmv->occupied_nodes <= 1) {
        return 1;
    }
    double running_total;
    double weight = 1.0;
    double weight_total = 0.0;
    do {
        double estimate = (double)(kmv->occupied_nodes - 1) / ((double)kmv->data[0] / (double)UINT64_MAX);
        running_total += weight / estimate;
        weight_total += weight;
        weight = (double)(kmv->occupied_nodes) / (double)(kmv->num_nodes);
    } while(remove_root(kmv) == false);
    return (uint64_t)(weight_total / running_total);
}

uint64_t kmv_estimate_hm(struct KMV *kmv) {
    // Special single record case
    if (kmv->occupied_nodes <= 1) {
        return 1;
    }
    double running_total = 0;
    uint64_t count = 0;
    do {
        double estimate = (double)(kmv->occupied_nodes - 1) / ((double)kmv->data[0] / (double)UINT64_MAX);
        running_total += 1 / estimate;
        count += 1;
    } while(remove_root(kmv) == false);
    return (uint64_t)(count / running_total);
}
