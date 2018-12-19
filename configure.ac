AC_PREREQ([2.69])
AC_INIT([edcount], [1.1.0], [haroldfreeman@protonmail.com])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([-Wall -Werror])

# Add macro directory
AC_CONFIG_MACRO_DIR([m4])

# Check compile flags
AX_CHECK_COMPILE_FLAG([-Wall], [CFLAGS="$CFLAGS -Wall"], [], [])
AX_CHECK_COMPILE_FLAG([-Werror], [CFLAGS="$CFLAGS -Werror"], [], [])
AX_CHECK_COMPILE_FLAG([-std=c99], [CFLAGS="$CFLAGS -std=c99"], [], [])
AX_CHECK_COMPILE_FLAG([-pedantic], [CFLAGS="$CFLAGS -pedantic"], [], [])

# Checks for programs.
AC_PROG_CC
AC_PROG_MAKE_SET

# Checks for libraries.
AC_SEARCH_LIBS([sqrt], [m])

# Checks for header files.
AC_CHECK_HEADERS([stdint.h stdlib.h string.h stdbool.h stdio.h math.h])

# Check for programs used during development
AM_MISSING_PROG(HELP2MAN, help2man, $missing_dir)
AM_MISSING_PROG(INDENT, indent, $missing_dir)

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_CHECK_FUNCS([sqrt strchr strtol])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
