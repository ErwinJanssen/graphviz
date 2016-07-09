## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = \
        -I$(top_srcdir)/lib/common

AM_LDFLAGS = \
	-lcriterion

TESTS = arguments_parse_test

bin_PROGRAMS = arguments_parse_test

arguments_parse_test_SOURCES = arguments_parse_test.c
arguments_parse_test_CPPFLAGS = $(AM_CPPFLAGS) -DDEMAND_LOADING=1
arguments_parse_test_LDADD = \
	$(top_builddir)/lib/gvc/libgvc.la
