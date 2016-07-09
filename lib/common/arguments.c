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
	argument_options* options = (argument_options*) malloc(sizeof(argument_options));
	options->print_version = false;
	return options;
}

argument_options* parse_arguments(int argc, char** argv)
{
	argument_options* options = initialize_argument_options();

	// Value at argv[0] is the name of the calling program, so for parsing the
	// options we start at 1.
	for(unsigned long i = 1; i < argc; i++)
	{
		if((strcmp(argv[i], "-V") == 0) || strcmp(argv[i], "--version") == 0)
		{
			options->print_version = true;
		}
	}
	return options;
}

void process_arguments(int argc, char** argv)
{
	argument_options* options = parse_arguments(argc, argv);
	if(options->print_version)
	{
		print_graphviz_version();
		exit(0);
	}
}

void print_graphviz_version(void)
{
	printf("Graphviz version %s\n", PACKAGE_VERSION);
}
