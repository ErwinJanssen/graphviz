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
void print_graphviz_usage(void);

/**
 * Print usage of the command line program and the current Graphviz version to
 * the specified output stream, then exit.
 */
void print_graphviz_usage_to_stream(FILE* stream);

#endif /* LIB_COMMON_USAGE_H_ */
