/*
    edcount - estimate distinct count utility tool.
    Copyright (C) 2018 Josh Walters (joshwalters@protonmail.com)

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

#ifndef HLL_H
#define HLL_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

/**
 * Store the HLL.
 */
struct HLL {
    uint8_t size;
    uint8_t *counter;
    uint64_t num_counters;
    uint64_t num_inserts;
};

/**
 * Initialize the HLL struct.
 * @param hll HLL instance to use.
 * @param size Size of the HLL. Between range 4 to 20.
 * @return 0 on success, 1 on failure.
 */
int hll_init(struct HLL *hll, uint8_t size);

/**
 * Free HLL memory.
 * @param hll HLL instance to use.
 */
void hll_free(struct HLL *hll);

/**
 * Insert hash into HLL.
 * @param hll HLL instance to use.
 * @param hash Hash to insert.
 */
void hll_insert(struct HLL *hll, uint64_t hash);

/**
 * Estimate cardinality stored in the HLL.
 * @param hll HLL instance to use.
 */
uint64_t hll_estimate(struct HLL *hll);

/**
 * Compute sigma for the HLL.
 * @param hll HLL instance to use.
 * @return Sigma value.
 */
double hll_sigma(struct HLL *hll);

#endif
