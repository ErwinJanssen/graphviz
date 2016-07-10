## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = \
        -I$(top_srcdir) \
        -I$(top_srcdir)/lib/common

AM_LDFLAGS = \
	-lcriterion

TESTS = arguments_initialize arguments_free arguments_parse_version

bin_PROGRAMS = arguments_initialize arguments_free arguments_parse_version

arguments_initialize_SOURCES = arguments_initialize.c
arguments_initialize_CPPFLAGS = $(AM_CPPFLAGS) -DDEMAND_LOADING=1
arguments_initialize_LDADD = \
	$(top_builddir)/lib/gvc/libgvc.la

arguments_free_SOURCES = arguments_free.c
arguments_free_CPPFLAGS = $(AM_CPPFLAGS) -DDEMAND_LOADING=1
arguments_free_LDADD = \
	$(top_builddir)/lib/gvc/libgvc.la

arguments_parse_version_SOURCES = arguments_parse_version.c
arguments_parse_version_CPPFLAGS = $(AM_CPPFLAGS) -DDEMAND_LOADING=1
arguments_parse_version_LDADD = \
	$(top_builddir)/lib/gvc/libgvc.la