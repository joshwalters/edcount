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

#include "hll.h"

uint8_t count_trailing_zeros(uint64_t x)
{
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

int hll_init(struct HLL *hll, uint8_t size)
{
    if (size < 4 || size > 20) {
        return 1;
    }
    hll->size = size;
    hll->num_counters = 1 << size;
    hll->num_inserts = 0;
    hll->counter = calloc(hll->num_counters, sizeof(uint8_t));
    if (hll->counter == NULL) {
        return 1;
    }
    return 0;
}

void hll_free(struct HLL *hll)
{
    if (hll->counter != NULL) {
        free(hll->counter);
    }
    hll->counter = NULL;
    return;
}

void hll_insert(struct HLL *hll, uint64_t hash)
{
    hll->num_inserts += 1;
    uint8_t zeros = count_trailing_zeros(hash) + 1;
    uint64_t index = (hash >> 44) & ((1 << hll->size) - 1);
    if (zeros > hll->counter[index]) {
        hll->counter[index] = zeros;
    }
}

uint64_t hll_estimate(struct HLL *hll)
{
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
            alpha = 0.7213 / (1.0 + (1.079 / (double) hll->num_counters));
            break;
    }
    double z = 0;
    uint64_t counters_with_zero = 0;
    for (uint64_t i = 0; i < hll->num_counters; i++) {
        if (hll->counter[i] == 0) {
            counters_with_zero++;
            z++;
        } else {
            z += 1 / (double) ((uint64_t) 1 << hll->counter[i]);
        }
    }
    double estimate = (alpha * hll->num_counters * hll->num_counters) / z;
    if (estimate < ((5.0 / 2.0) * hll->num_counters)) {
        estimate =
            hll->num_counters * log(hll->num_counters /
                                    (double) counters_with_zero);
    }
    return (uint64_t) estimate;
}

double hll_sigma(struct HLL *hll)
{
    return 1.04 / sqrt((double) hll->num_counters);
}
