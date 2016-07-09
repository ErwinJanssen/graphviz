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

#ifndef LIB_COMMON_PARSE_ARGUMENTS_H_
#define LIB_COMMON_PARSE_ARGUMENTS_H_

#include <stdbool.h>

/**
 * This struct contains the possible options and values that are passed as
 * arguments on the command line. To initialize this struct with the proper
 * default values set, use initialize_argument_options().
 */
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
 *
 * - `print_version` set to `false`
 */
argument_options* initialize_argument_options(void);

/**
 * Reads the input arguments as given by the commandline, parses it
 * and stores the results in an argument_options struct. Values and flags not
 * present in the commandline arguments will keep their default value as given
 * by initialize_argument_options();
 *
 * \pre
 * 		- The length of argv will be equal to the value of argc.
 * 		- No element of argv will be NULL.
 * 		- Every element of argv will be a NUll terminated string.
 */
argument_options* parse_arguments(int argc, char** argv);

/**
 * This functions receives the command line arguments by the `main` function
 * and processes them. They are first parsed by `parse_arguments`. The
 * resulting `argument_options` struct will be used to determine the following
 * actions.
 *
 * \pre
 * 		- The length of argv will be equal to the value of argc.
 * 		- No element of argv will be NULL.
 * 		- Every element of argv will be a NUll terminated string.
 */
void process_arguments(int argc, char** argv);

#endif /* LIB_COMMON_PARSE_ARGUMENTS_H_ */
