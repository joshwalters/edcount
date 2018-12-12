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

#include "hll.h"

uint8_t count_trailing_zeros(uint64_t x) {
    if (x == 0) {
        return 64;
    }
    #if __GNUC__
        return __builtin_ctzll(x);
    #else
        uint8_t count = 0;
        while ((x & 1) == 0) {
            count++;
            x = x >> 1;
        }
        return count;
    #endif
}

bool hll_init(struct HLL *hll, uint8_t size) {
    if (size < 4 || size > 20) {
        return false;
    }
    hll->size = size;
    hll->num_counters = 1 << size;
    hll->counter = calloc(hll->num_counters, sizeof(uint8_t));
    if (hll->counter == NULL) {
        return false;
    }
    return true;
}

void hll_free(struct HLL *hll) {
    if (hll->counter != NULL) {
        free(hll->counter);
    }
    hll->counter = NULL;
    return;
}

void hll_insert(struct HLL *hll, uint64_t hash) {
    hll->num_inserts += 1;
    uint8_t zeros = count_trailing_zeros(hash) + 1;
    uint64_t index = (hash >> 44) & ((1 << hll->size) - 1);
    if (zeros > hll->counter[index]) {
        hll->counter[index] = zeros;
    }
}

uint64_t hll_estimate(struct HLL *hll) {
    double alpha;
    switch (hll->num_counters) {
        case 16:
            alpha = 0.673;
            break;
        case 32:
            alpha = 0.697;
            break;
        case 64:
            alpha = 0.709;
            break;
        default:
            alpha = 0.7213 / (1.0 + (1.079 / (double)hll->num_counters));
            break;
    }
    double z = 0;
    uint64_t counters_with_zero = 0;
    for (uint64_t i = 0; i < hll->num_counters; i++) {
        if (hll->counter[i] == 0) {
            counters_with_zero++;
            z++;
        } else {
            z += 1 / (double)((uint64_t)1 << hll->counter[i]);
        }
    }
	double estimate = (alpha * hll->num_counters * hll->num_counters) / z;
    if (estimate < ((5.0/2.0) * hll->num_counters)) {
        estimate = hll->num_counters * log(hll->num_counters / (double)counters_with_zero);
    }
    return (uint64_t)estimate;
}

void hll_copy_and_wrap(struct HLL *dest, struct HLL *src) {
    uint64_t dest_i = 0;
    for (uint64_t src_i = 0; src_i < src->num_counters; src_i++, dest_i++) {
        if (dest_i >= dest->num_counters) {
            dest_i = 0;
        }
        if (dest->counter[dest_i] < src->counter[src_i]) {
            dest->counter[dest_i] = src->counter[src_i];
        }
    }
}

bool hll_union(struct HLL *dest, struct HLL *first, struct HLL *second) {
    if (first->counter == NULL || second->counter == NULL) {
        return false;
    }
    uint8_t min_size = first->size;
    if (second->size < min_size) {
        min_size = second->size;
    }
    if (hll_init(dest, min_size) == false) {
        return false;
    }
    hll_copy_and_wrap(dest, first);
    hll_copy_and_wrap(dest, second);
    return true;
}
