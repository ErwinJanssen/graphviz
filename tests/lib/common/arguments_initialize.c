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

#include <criterion/criterion.h>
#include "arguments.h"

Test(initialize_argument_options, print_version_default)
{
	argument_options* default_options = initialize_argument_options();
	cr_assert(!default_options->print_version);
	free_argument_options(&default_options);
}

Test(initialize_argument_options, print_usage_default)
{
	argument_options* default_options = initialize_argument_options();
	cr_assert(!default_options->print_usage);
	free_argument_options(&default_options);
}
