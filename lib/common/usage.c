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

#include "usage.h"

#include "arguments.h"

void print_graphviz_usage(void)
{
	print_graphviz_usage_to_stream(stdout);
}

void print_graphviz_usage_to_stream(FILE* stream)
{
	print_graphviz_version_to_stream(stream);
	fprintf(stream, "Print usage.\n");
}
