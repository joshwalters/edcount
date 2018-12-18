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

TESTS = check_edcount
check_PROGRAMS = check_edcount
check_edcount_SOURCES = src/test.c
