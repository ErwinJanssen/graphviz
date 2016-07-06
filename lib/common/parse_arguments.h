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

#include <stdbool.h>

#ifndef LIB_COMMON_PARSE_ARGUMENTS_H_
#define LIB_COMMON_PARSE_ARGUMENTS_H_

typedef struct argument_options
{
	bool print_version;
	bool print_usage;
	bool configure_plugins;
	char** input_files;
	char** output_files;
} argument_options;

/**
 * This function returns an argument_options struct with all values
 * set to their default value.
 */
argument_options* initialize_argument_options(void);

/**
 * Reads the input arguments as given by the commandline, parses it
 * and stored the results in a argument_options struct. Values not
 * present in the commandline arguments are flags unset will remain
 * their default value.
 */
argument_options* parse_arguments(int argc, char** argv);

#endif /* LIB_COMMON_PARSE_ARGUMENTS_H_ */
