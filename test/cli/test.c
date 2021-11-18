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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "src/cli.h"

int test_verbose()
{
    // Setup arguments
    int arg_count = 2;
    char *arg_values[2];
    arg_values[0] = "PROG_NAME";
    arg_values[1] = "--verbose";
    // Parse the CLI arguments
    struct CLIArgs cli_args;
    parse_args(arg_count, arg_values, &cli_args);
    // Verify that using verbose
    if (cli_args.verbose == false) {
        fprintf(stderr, "Verbose == false, should be true.\n");
        return 1;
    }
    return 0;
}

int test_not_verbose()
{
    // Setup arguments
    int arg_count = 1;
    char *arg_values[1];
    arg_values[0] = "PROG_NAME";
    // Parse the CLI arguments
    struct CLIArgs cli_args;
    parse_args(arg_count, arg_values, &cli_args);
    // Verify that not verbose
    if (cli_args.verbose == true) {
        fprintf(stderr, "Verbose == true, should default to false.\n");
        return 1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    int errors = 0;
    errors += test_verbose();
    errors += test_not_verbose();
    if (errors > 0) {
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
