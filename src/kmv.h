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

#ifndef EDCOUNT_KMV_H
#define EDCOUNT_KMV_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define NUM_NODES(height) ((1 << (height + 1)) - 1)
#define PARENT(x) ((x - 1) / 2)
#define LEFT_CHILD(x) (2 * x + 1)
#define RIGHT_CHILD(x) (2 * x + 2)

/**
 * Store the K-Min Values (max heap).
 */
struct KMV {
    uint8_t height;
    uint8_t cell_size;
    uint64_t total_inserts;
    uint64_t num_nodes;
    uint64_t occupied_nodes;
    uint64_t* data;
};

/**
 * Setup the KMV.
 */
bool kmv_init(struct KMV *kmv, uint8_t height);

/**
 * Free KMV.
 */
void kmv_free(struct KMV *kmv);

/**
 * Insert into the KMV.
 */
void kmv_insert(struct KMV *kmv, uint64_t value);

/**
 * Estimate cardinality. Weighted harmonic mean.
 */
uint64_t kmv_estimate_whm(struct KMV *kmv);

/**
 * Estimate cardinality. Harmonic mean.
 */
uint64_t kmv_estimate_hm(struct KMV *kmv);

#endif
