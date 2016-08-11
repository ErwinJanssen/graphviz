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
	args_gvParseArgs \
	command_line_initialize \
	command_line_free \
	command_line_parse_arguments_seperate \
	command_line_parse_arguments_mixed 

bin_PROGRAMS = $(TESTS)

args_gvParseArgs_SOURCES = args_gvParseArgs.c
args_gvParseArgs_LDADD = \
	$(top_builddir)/lib/gvc/libgvc.la

command_line_initialize_SOURCES = command_line_initialize.c
command_line_initialize_LDADD = \
	$(top_builddir)/lib/gvc/libgvc.la

command_line_free_SOURCES = command_line_free.c
command_line_free_LDADD = \
	$(top_builddir)/lib/gvc/libgvc.la

command_line_parse_arguments_seperate_SOURCES = command_line_parse_arguments_seperate.c
command_line_parse_arguments_seperate_LDADD = \
	$(top_builddir)/lib/gvc/libgvc.la

command_line_parse_arguments_mixed_SOURCES = command_line_parse_arguments_mixed.c
command_line_parse_arguments_mixed_LDADD = \
	$(top_builddir)/lib/gvc/libgvc.la

endif
