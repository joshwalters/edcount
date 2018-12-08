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

void print_help(char** argv) {
    printf("Usage: %s [FLAGS]...\n", argv[0]);
    printf("\n");
    printf("--help: Print this help message.\n");
    printf("--size S: Set size of heap.\n");
    printf("\tWill increase accuracy at the price of memory.\n");
    printf("\tCreates 2^(s+1)-1 64 bit values.\n");
}

bool is_flag_present(int argc, char** argv, char* flag) {
    for(int i = 0; i < argc; i++) {
        if (strcmp(argv[i], flag) == 0) {
            return true;
        }
    }
    return false;
}

bool get_flag_value(int argc, char** argv, char* flag, char* data, size_t size) {
    for(int i = 0; i < argc; i++) {
        if (strcmp(argv[i], flag) == 0) {
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
