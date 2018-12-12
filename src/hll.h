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

#ifndef HLL_H
#define HLL_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "fasthash.h"

struct HLL {
    uint8_t size;
    uint8_t *counter;
    uint64_t num_counters;
    uint64_t num_inserts;
};

bool hll_init(struct HLL *hll, uint8_t size);
void hll_free(struct HLL *hll);
void hll_insert(struct HLL *hll, uint64_t hash);
uint64_t hll_estimate(struct HLL *hll);
bool hll_union(struct HLL *dest, struct HLL *first, struct HLL *second);

#endif
