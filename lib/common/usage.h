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

#ifndef LIB_COMMON_USAGE_H_
#define LIB_COMMON_USAGE_H_

#include <stdio.h>

/**
 * Print usage of the command line program and the current Graphviz version to
 * stdout, then exit.
 */
void print_graphviz_usage(char* layout_engine);

/**
 * Print usage of the command line program and the current Graphviz version to
 * the specified output stream.
 */
void print_graphviz_usage_to_stream(FILE* stream, char* layout_engine);

/**
 * Prints the generic usage of the command line programs. Requires the name
 * of the layout engine as input.
 */
void print_generic_usage(FILE* stream, char* layout_engine);

/**
 * Prints the generic options that are used by all Graphviz command line
 * programs and layout engines.
 */
void print_generic_options(FILE* stream);

#endif /* LIB_COMMON_USAGE_H_ */
