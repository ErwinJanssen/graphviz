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

#include "parse_arguments.h"

#include <stdlib.h>

argument_options* initialize_argument_options(void)
{
	argument_options* options = (argument_options*) malloc(sizeof(argument_options));
	return options;
}

argument_options* parse_arguments(int argc, char** argv)
{
	argument_options* options = initialize_argument_options();
	return 0;
}
