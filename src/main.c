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

#include "fasthash.h"
#include "cli.h"
#include "hll.h"

#define BUF_SIZE 128
#define STARTING_SEED 19721127

int main(int argc, char **argv)
{
    // Parse the CLI arguments
    struct CLIArgs cli_args;
    parse_args(argc, argv, &cli_args);
    // Create the HLL
    struct HLL hll;
    if (hll_init(&hll, cli_args.accuracy) != 0) {
        fprintf(stderr, "Error allocating memory.\n");
        exit(EXIT_FAILURE);
    }
    // Read STDIN
    char buf[BUF_SIZE];
    // Used for accumulating hashes when line is longer than BUF_SIZE
    uint64_t seed = STARTING_SEED;
    while (fgets(buf, BUF_SIZE, stdin) != NULL) {
        uint64_t hash = fasthash64(buf, strlen(buf), seed);
        // Check if fgets read whole string
        if (strchr(buf, '\n') != NULL) {
            hll_insert(&hll, hash);
            seed = STARTING_SEED;
        } else {
            // Did not contain newline, need to continue hashing this line
            seed = hash;
        }
    }
    // Compute estimate distinct count
    uint64_t estimate = hll_estimate(&hll);
    fprintf(stdout, "%lu\n", estimate);
    // Print verbose information
    if (cli_args.verbose) {
        fprintf(stderr, "Number of total inserts: %lu\n", hll.num_inserts);
        double sigma = hll_sigma(&hll);
        fprintf(stderr, "Sigma: %f%%\n", sigma * 100);
        fprintf(stderr, "65%% confidence interval: %lu to %lu\n",
                estimate - (uint64_t) (estimate * sigma),
                estimate + (uint64_t) (estimate * sigma));
        fprintf(stderr, "95%% confidence interval: %lu to %lu\n",
                estimate - (uint64_t) (estimate * 2 * sigma),
                estimate + (uint64_t) (estimate * 2 * sigma));
        fprintf(stderr, "99%% confidence interval: %lu to %lu\n",
                estimate - (uint64_t) (estimate * 3 * sigma),
                estimate + (uint64_t) (estimate * 3 * sigma));
    }
    // Free memory
    hll_free(&hll);
    exit(EXIT_SUCCESS);
}
