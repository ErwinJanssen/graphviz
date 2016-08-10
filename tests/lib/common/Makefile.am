# $Id$ $Revision$
## Process this file with automake to produce Makefile.in

if HAVE_CRITERION

AM_CPPFLAGS = \
	-I$(top_srcdir) \
    -I$(top_srcdir)/lib/common \
    -I$(top_srcdir)/lib/gvc \
	-I$(top_srcdir)/lib/pathplan \
	-I$(top_srcdir)/lib/cgraph \
	-I$(top_srcdir)/lib/cdt \
    -DDEMAND_LOADING=1

AM_LDFLAGS = \
	-lcriterion

TESTS = \
	command_line \
	command_line_initialize \
	command_line_free

bin_PROGRAMS = $(TESTS)

command_line_SOURCES = command_line.c
command_line_LDADD = \
	$(top_builddir)/lib/gvc/libgvc.la

command_line_initialize_SOURCES = command_line_initialize.c
command_line_initialize_LDADD = \
	$(top_builddir)/lib/gvc/libgvc.la

command_line_free_SOURCES = command_line_free.c
command_line_free_LDADD = \
	$(top_builddir)/lib/gvc/libgvc.la

endif
