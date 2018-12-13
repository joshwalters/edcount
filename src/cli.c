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

#include "cli.h"

void print_help(char **argv) {
    printf("Usage: %s [OPTION]...\n", argv[0]);
    printf("Estimate distinct count of values from standard input.\n");
    printf("Value is considered terminated with a newline.\n");
    printf("\n");
    printf("-h, --help            Print this help message.\n");
    printf("-v, --verbose         Print additional information.\n");
    printf("-a, --accuracy SIZE   Higher value increases accuracy at\n");
    printf("                      the cost of memory usage.\n");
    printf("                      Must be value in range [4, 20].\n");
    printf("                      Default value is 20.\n");
    printf("                      SIZE   Error   Bytes Used\n");
    printf("                         4   26.0%%           16\n");
    printf("                        10    3.2%%         1024\n");
    printf("                        15    0.6%%        32768\n");
    printf("                        20    0.1%%      1048576\n");
}

bool is_flag_present(int argc, char **argv, char *short_flag, char *long_flag) {
    for(int i = 0; i < argc; i++) {
        if (strcmp(argv[i], short_flag) == 0 ||
            strcmp(argv[i], long_flag) == 0) {
            return true;
        }
    }
    return false;
}

bool get_flag_value(int argc, char **argv, char *short_flag, char *long_flag, char *data, size_t size) {
    for(int i = 0; i < argc; i++) {
        if (strcmp(argv[i], short_flag) == 0 ||
            strcmp(argv[i], long_flag) == 0) {
            // Check if flag is last argument
            if ((i + 1) >= argc) {
                return false;
            }
            // Copy flag value
            strncpy(data, argv[i + 1], size);
            // Manually null character to be safe
            data[size - 1] = '\0';
            return true;
        }
    }
    return false;
}

void parse_args(int argc, char **argv, struct CLIArgs *cli_args) {
    char cli_buf[CLI_PARAM_SIZE];
    // Default values
    cli_args->accuracy = 20;
    cli_args->verbose = false;
    // Help
    if (is_flag_present(argc, argv, "-h", "--help")) {
        print_help(argv);
        exit(EXIT_SUCCESS);
    }
    // Accuracy.
    if (get_flag_value(argc, argv, "-a", "--accuracy", cli_buf, CLI_PARAM_SIZE)) {
        char* end;
        cli_args->accuracy = (uint8_t)strtol(cli_buf, &end, 10);
        if (*end != '\0' || cli_args->accuracy > 20 || cli_args->accuracy < 4) {
            fprintf(stderr, "Invalid accuracy '%s'. "
                            "Should be between '4' and '20'.\n\n", cli_buf);
            print_help(argv);
            exit(EXIT_FAILURE);
        }
    }
    // Verbose.
    if (is_flag_present(argc, argv, "-v", "--verbose")) {
        cli_args->verbose = true;
    }
}
