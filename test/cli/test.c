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

#include "src/cli.h"

int main(int argc, char **argv)
{
	// Setup arguments
	int arg_count = 2;
	char *arg_values[2];
	arg_values[0] = "PROG_NAME";
	arg_values[1] = "--verbose";
	// Parse the CLI arguments
	struct CLIArgs cli_args;
	parse_args (arg_count, arg_values, &cli_args);
	// Verify that using verbose
  	if (cli_args.verbose == false) {
		fprintf(stderr, "Verbose mode not set.\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
