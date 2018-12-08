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
#define LEFT_CHILD(x) (2 * x + 1)
#define RIGHT_CHILD(x) (2 * x + 2)

int main(int argc, char** argv) {
    // Check flags
    if (is_flag_present(argc, argv, "--help")) {
        print_header();
        print_help(argv);
        exit(EXIT_SUCCESS);
    }

    // TODO size from CLI
    int height = 4;
    int occupied_nodes = 0;
	int num_nodes = NUM_NODES(height);
    // Allocate the min-heap
    uint64_t* heap = (uint64_t*) calloc(num_nodes, sizeof(uint64_t));
    if (heap == NULL) {
        exit(EXIT_FAILURE);
    }

//    char buf[BUF_SIZE];
//    uint64_t seed = 0;
//    while (fgets(buf, BUF_SIZE, stdin) != NULL) {
//	    uint64_t hash = fasthash64(buf, strlen(buf), seed);
//        printf("%llu\n", hash);
//        // UINT64_MAX
//    }

    free(heap);

    exit(EXIT_SUCCESS);
}
