AUTOMAKE_OPTIONS = subdir-objects
bin_PROGRAMS = edcount
edcount_CFLAGS = -lm
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
test_hll_CFLAGS = -lm
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
