ACLOCAL_AMFLAGS = -I m4
AUTOMAKE_OPTIONS = subdir-objects
bin_PROGRAMS = edcount
edcount_SOURCES = \
	src/main.c \
	src/cli.c \
	src/cli.h \
	src/hll.c \
	src/hll.h \
	src/fasthash.c \
	src/fasthash.h

# Setup tests
TESTS = \
		test_hll \
		test_cli
check_PROGRAMS = $(TESTS)

# Test HLL
test_hll_SOURCES = \
	test/hll/test.c \
	src/fasthash.c \
	src/fasthash.h \
	src/hll.c \
	src/hll.h

# Test CLI
test_cli_SOURCES = \
	test/cli/test.c \
	src/cli.c \
	src/cli.h

# Manual file
man_MANS = doc/edcount.1
EXTRA_DIST = doc/edcount.1

# Format code
.PHONY: format
format:
	find ./ -type f -name '*.[ch]' -exec $(INDENT) '{}' \
		-kr -ci4 -cli4 -i4 -l79 -nut \;
