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

void print_header() {
    printf("TODO\n");
    printf("\n");
}

void print_help(char **argv) {
    printf("Usage: %s [ARGS]...\n", argv[0]);
    printf("\n");
    printf("-h, --help\n");
    printf("\tPrint this help message.\n\n");
    printf("-v, --verbose\n");
    printf("\tPrint additional information.\n\n");
    printf("-a, --accuracy SIZE\n");
    printf("\tWill increase accuracy at the cost of more memory.\n");
    printf("\tNeeds to be in range [4, 20].\n");
    printf("\tDefault is 10.\n\n");
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
    cli_args->accuracy = 10;
    cli_args->verbose = false;
    // Help
    if (is_flag_present(argc, argv, "-h", "--help")) {
        print_header();
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
            print_header();
            print_help(argv);
            exit(EXIT_FAILURE);
        }
    }
    // Verbose.
    if (is_flag_present(argc, argv, "-v", "--verbose")) {
        cli_args->verbose = true;
    }
}
