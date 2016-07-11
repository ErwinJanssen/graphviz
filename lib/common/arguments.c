/* $Id$ $Revision$ */

/*************************************************************************
 * Copyright (c) 2011 AT&T Intellectual Property
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors: See CVS logs. Details at http://www.graphviz.org/
 *************************************************************************/

/*
 * Written by Erwin Janssen
 */

#include "arguments.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

argument_options* initialize_argument_options(void)
{
	argument_options* options = (argument_options*) malloc(
			sizeof(argument_options));
	options->print_version = false;
	options->print_usage = false;
	return options;
}

void free_argument_options(argument_options** options)
{
	free(*options);
	*options = NULL;
}

argument_options* parse_arguments(int argc, char** argv)
{
	argument_options* options = initialize_argument_options();

	// Value at argv[0] is the name of the calling program, so for parsing the
	// options we start at 1.
	for (unsigned long i = 1; i < argc; i++)
	{
		if ((strcmp(argv[i], "-V") == 0) || strcmp(argv[i], "--version") == 0)
		{
			options->print_version = true;
		}
		else if ((strcmp(argv[i], "-?") == 0) || (strcmp(argv[i], "-h") == 0)
				|| (strcmp(argv[i], "--help") == 0))
		{
			options->print_usage = true;
		}
	}
	return options;
}

void process_arguments_options(argument_options* options)
{
	if (options->print_version)
	{
		print_graphviz_version();
		exit(0);
	}
	else if (options->print_usage)
	{
		print_graphviz_usage();
		exit(0);
	}
}

void print_graphviz_version(void)
{
	print_graphviz_version_to_stream(stdout);
}

void print_graphviz_version_to_stream(FILE* stream)
{
	fprintf(stream, "Graphviz - version %s\n", PACKAGE_VERSION);
}

void print_graphviz_usage(void)
{
	print_graphviz_usage_to_stream(stdout);
}

void print_graphviz_usage_to_stream(FILE* stream)
{
	print_graphviz_version_to_stream(stream);
	fprintf(stream, "Print usage.\n");
}
