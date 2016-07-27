# $Id$ $Revision$
## Process this file with automake to produce Makefile.in

if HAVE_CRITERION

AM_LDFLAGS = \
	-lcriterion

TESTS = command_line

bin_PROGRAMS = $(TESTS)

command_line_SOURCES = command_line.c
command_line_CPPFLAGS = $(AM_CPPFLAGS) -DDEMAND_LOADING=1

endif
