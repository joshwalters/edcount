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

#include "cli.h"

void
print_help (char **argv)
{
  fprintf (stdout, "%s\n", PACKAGE_STRING);
  fprintf (stdout, "Estimate distinct count of values from standard "
	   "input.\n");
  fprintf (stdout, "Value is considered terminated with a newline.\n");
  fprintf (stdout, "\n");
  fprintf (stdout, "Usage: %s [OPTION]...\n", argv[0]);
  fprintf (stdout, "\n");
  fprintf (stdout, "-h, --help       Print this help message.\n");
  fprintf (stdout,
	   "    --version    Print version and copyright information.\n");
  fprintf (stdout,
	   "-v, --verbose    Print additional information about the "
	   "data.\n");
  fprintf (stdout,
	   "                 Error bounds, number of input records, "
	   "etc.\n");
  fprintf (stdout, "\n");
  fprintf (stdout, "Report bugs to: haroldfreeman@protonmail.com\n");
  fprintf (stdout, "pkg home page: "
	   "<https://github.com/haroldfreeman/edcount>\n");
}

void
print_version ()
{
  fprintf (stdout, "%s\n", PACKAGE_STRING);
  fprintf (stdout, "Copyright (C) 2018 Harold Freeman\n");
  fprintf (stdout, "License GPLv3+: GNU GPL version 3 or "
	   "later <https://gnu.org/licenses/gpl.html>\n");
  fprintf (stdout, "This is free software: you are free to change and "
	   "redistribute it.\n");
  fprintf (stdout, "There is NO WARRANTY, to the extent permitted by law.\n");
}

bool
is_flag_present (int argc, char **argv, char *short_flag, char *long_flag)
{
  for (int i = 0; i < argc; i++)
    {
      // Skip nulled (already processed) args
      if (argv[i] == NULL)
	{
	  continue;
	}
      // Check if flag matches
      if (strcmp (argv[i], short_flag) == 0 ||
	  strcmp (argv[i], long_flag) == 0)
	{
	  // Null out the value, for enforcement of unknown flags
	  argv[i] = NULL;
	  return true;
	}
    }
  return false;
}

void
parse_args (int argc, char **argv, struct CLIArgs *cli_args)
{
  // Default values
  cli_args->accuracy = 20;
  cli_args->verbose = false;
  // Help flag
  if (is_flag_present (argc, argv, "-h", "--help"))
    {
      print_help (argv);
      exit (EXIT_SUCCESS);
    }
  // Verbose flag
  if (is_flag_present (argc, argv, "-v", "--verbose"))
    {
      cli_args->verbose = true;
    }
  // Version flag
  if (is_flag_present (argc, argv, "--version", "--version"))
    {
      print_version (argv);
      exit (EXIT_SUCCESS);
    }
  // Super secret flag
  if (is_flag_present (argc, argv, "--voncount", "--voncount"))
    {
      fprintf (stdout, "Seven! Seven bats! Ah, Ah, Ah!\n");
      exit (EXIT_SUCCESS);
    }
  // Check for unknown flags, report to user and fail if found
  int i;
  for (i = 1; i < argc; i++)
    {
      if (argv[i] != NULL)
	{
	  fprintf (stderr, "Invalid argument '%s'\n\n", argv[i]);
	  print_help (argv);
	  exit (EXIT_FAILURE);
	}
    }
}
