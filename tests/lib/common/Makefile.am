## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = \
        -I$(top_srcdir)/lib/common

AM_LDFLAGS = \
	-lcriterion

TESTS = parse_arguments_test

bin_PROGRAMS = parse_arguments_test

parse_arguments_test_SOURCES = parse_arguments_test.c
parse_arguments_test_CPPFLAGS = $(AM_CPPFLAGS) -DDEMAND_LOADING=1
parse_arguments_test_LDADD = \
	$(top_builddir)/lib/gvc/libgvc.la
