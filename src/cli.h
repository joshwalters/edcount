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

#ifndef EDCOUNT_CLI_H
#define EDCOUNT_CLI_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define CLI_PARAM_SIZE 64

/**
 * Store CLI arguments.
 */
struct CLIArgs {
    // Accuracy to use
    uint8_t accuracy
    // Weather to print verbose information
    bool verbose;
};

/**
 * Print CLI help information.
 * @param argv Argument strings
 */
void print_help(char **argv);

/**
 * Check if a flag is present in the args.
 * @param argc Number of arguments.
 * @param argv Argument strings.
 * @param short_flag Search argv for this string.
 * @param long_flag Search argv for this string.
 * @return True if flag present, false otherwise
 */
bool is_flag_present(int argc, char **argv, char *short_flag, char *long_flag);

/**
 * Get value for a flag.
 * @param argc Number of arguments.
 * @param argv Argument strings.
 * @param short_flag Search argv for this string.
 * @param long_flag Search argv for this string.
 * @param data Used to store the flag value.
 * @param size Max values to copy to data.
 * @return True if flag and value present, false otherwise.
 */
bool get_flag_value(int argc, char **argv, char *short_flag,
                    char *long_flag, char *data, size_t size);

/**
 * Parse CLI arguments into CLIArg struct.
 * @param argc Number of arguments.
 * @param argv Argument strings.
 * @param cli_args Used to store arguments.
 */
void parse_args(int argc, char **argv, struct CLIArgs *cli_args);

#endif
