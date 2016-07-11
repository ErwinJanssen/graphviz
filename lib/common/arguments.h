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

#ifndef LIB_COMMON_ARGUMENTS_H_
#define LIB_COMMON_ARGUMENTS_H_

#include <stdbool.h>
#include <stdio.h>

/**
 * This struct contains the possible options and values that are passed as
 * arguments on the command line. To initialize this struct with the proper
 * default values set, use initialize_argument_options().
 */
typedef struct argument_options
{
	bool print_version;
	bool print_usage;
} argument_options;

/**
 * This function returns an argument_options struct with all values
 * set to their default value.
 *
 * - `print_version` set to `false`
 * - `print_usage` set to `false`
 */
argument_options* initialize_argument_options(void);

/**
 * Properly frees the argument_options struct and all it's children.
 * Takes a pointer to an argument_options pointer, frees it and sets its value
 * to NULL.
 */
void free_argument_options(argument_options** options);

/**
 * Reads the input arguments as given by the command line, parses it
 * and stores the results in an argument_options struct. Values and flags not
 * present in argv will keep their default value as given
 * by `initialize_argument_options()`.
 *
 * \pre
 * 		- The length of argv will be equal to the value of argc.
 * 		- No element of argv will be NULL.
 * 		- Every element of argv will be a NUll terminated string.
 *
 * \post
 * 		Flags and values will have the following effects
 * 		- `-V` and `--version` will set `print_version` to true.
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
void process_arguments_options(argument_options* options);

/**
 * Print the version number to stdout, then exit. The name of the program will
 * be a hard coded string, not the name of the executed program (argv[0]).
 * This value is not guaranteed to be set or contain the actual program name,
 * for example when the executable has been renamed.
 *
 * \pre
 * 		`PACKAGE_VERSION` should be defined and contain the current version,
 * 		it usually defined in config.h.
 */
void print_graphviz_version(void);

/**
 * Print the version number to the specified output stream.
 */
void print_graphviz_version_to_stream(FILE* stream);

#endif /* LIB_COMMON_PARSE_ARGUMENTS_H_ */
