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
#include "kmv.h"

#define BUF_SIZE 1024*10

int main(int argc, char **argv) {
    // Parse the CLI arguments
    struct CLIArgs cli_args;
    parse_args(argc, argv, &cli_args);
    // Create the KMV
    struct KMV kmv;
    if(kmv_init(&kmv, cli_args.accuracy) == false) {
        fprintf(stderr, "Error allocating memory.\n");
        exit(EXIT_FAILURE);
    }
    // Read STDIN
    char buf[BUF_SIZE];
    uint64_t seed = 0;
    while (fgets(buf, BUF_SIZE, stdin) != NULL) {
        uint64_t hash = fasthash64(buf, strlen(buf), seed);
        kmv_insert(&kmv, hash);
    }
    // Compute estimate distinct count
    fprintf(stdout, "Estimate: %lu\n", kmv_estimate(&kmv));
    // Print verbose information
    if (cli_args.verbose) {
        if (kmv.num_nodes > kmv.occupied_nodes) {
            fprintf(stdout, "Mode: Exact\n");
        } else {
            fprintf(stdout, "Mode: Estimate\n");
        }
        fprintf(stdout, "Total bytes used: %lu\n", kmv.num_nodes * kmv.cell_size);
        fprintf(stdout, "Total inserts: %lu\n", kmv.total_inserts);
    }
    // Free memory
    kmv_free(&kmv);
    exit(EXIT_SUCCESS);
}
