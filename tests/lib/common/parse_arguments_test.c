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
#include "parse_arguments.h"

Test(initialize_argument_options, print_version_default)
{
	argument_options* default_options = initialize_argument_options();
	cr_assert(!default_options->print_version);
}

Test(parse_arguments, dash_V_true)
{
	int argc = 2;
	char* argv[] = {"dot", "-V"};
	argument_options* options = parse_arguments(argc, argv);
	cr_assert(options->print_version);
}

Test(parse_arguments, dash_v_false)
{
	int argc = 2;
	char* argv[] = {"dot", "-v"};
	argument_options* options = parse_arguments(argc, argv);
	cr_assert(!options->print_version);
}

Test(parse_arguments, dash_dash_V_false)
{
	int argc = 2;
	char* argv[] = {"dot", "--V"};
	argument_options* options = parse_arguments(argc, argv);
	cr_assert(!options->print_version);
}

Test(parse_arguments, dash_dash_version_true)
{
	int argc = 2;
	char* argv[] = {"dot", "--version"};
	argument_options* options = parse_arguments(argc, argv);
	cr_assert(options->print_version);
}

Test(parse_arguments, dash_version_false)
{
	int argc = 2;
	char* argv[] = {"dot", "-version"};
	argument_options* options = parse_arguments(argc, argv);
	cr_assert(!options->print_version);
}
