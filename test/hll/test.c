/*
    edcount - estimate distinct count utility tool.
    Copyright (C) 2018 Harold Freeman (haroldfreeman@protonmail.com)

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

#include "src/hll.h"
#include "src/fasthash.h"

int main(int argc, char **argv)
{
    struct HLL hll;
    if (hll_init(&hll, 20) != 0) {
        fprintf(stderr, "Error allocating memory.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 100000; i++) {
        uint64_t hash = fasthash64(&i, sizeof(int), 42);
        hll_insert(&hll, hash);
    }
    // Compute estimate distinct count
    uint64_t estimate = hll_estimate(&hll);
    if (estimate < 98000 || estimate > 102000) {
        fprintf(stderr, "Estimate outside expected range: %lu\n", estimate);
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
