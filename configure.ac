AC_PREREQ([2.69])
AC_INIT([edcount], [1.1.0], [haroldfreeman@protonmail.com])
AC_LANG(C)
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([-Wall -Werror])
LT_INIT

# Add macro directory
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CC
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL

# Checks for header files.
AC_CHECK_HEADERS([stdint.h stdlib.h string.h stdbool.h stdio.h math.h], [], [
                  AC_MSG_ERROR([Missing header file])
                  ])

# Checks for libraries.
AC_SEARCH_LIBS([sqrt], [m], [], [
                  AC_MSG_ERROR([required library math not found])
                  ])

# Checks for library functions.
AC_CHECK_FUNCS([sqrt strchr strtol sqrt log], [] , [
                  AC_MSG_ERROR([Missing function])
                ])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

# Set compile flags
AX_CHECK_COMPILE_FLAG([-Wall], [CFLAGS="$CFLAGS -Wall"], [], [])
AX_CHECK_COMPILE_FLAG([-Werror], [CFLAGS="$CFLAGS -Werror"], [], [])
AX_CHECK_COMPILE_FLAG([-std=c99], [CFLAGS="$CFLAGS -std=c99"], [], [])
AX_CHECK_COMPILE_FLAG([-pedantic], [CFLAGS="$CFLAGS -pedantic"], [], [])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
