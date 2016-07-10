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

Test(arguments_parse_version, dash_V_true)
{
	int argc = 2;
	char* argv[] = {"dot", "-V"};
	argument_options* options = parse_arguments(argc, argv);
	cr_assert(options->print_version);
	free_argument_options(&options);
}

Test(arguments_parse_version, dash_v_false)
{
	int argc = 2;
	char* argv[] = {"dot", "-v"};
	argument_options* options = parse_arguments(argc, argv);
	cr_assert(!options->print_version);
	free_argument_options(&options);
}

Test(arguments_parse_version, dash_dash_V_false)
{
	int argc = 2;
	char* argv[] = {"dot", "--V"};
	argument_options* options = parse_arguments(argc, argv);
	cr_assert(!options->print_version);
	free_argument_options(&options);
}

Test(arguments_parse_version, dash_VX_false)
{
	int argc = 2;
	char* argv[] = {"dot", "-VX"};
	argument_options* options = parse_arguments(argc, argv);
	cr_assert(!options->print_version);
	free_argument_options(&options);
}

Test(arguments_parse_version, dash_dash_version_true)
{
	int argc = 2;
	char* argv[] = {"dot", "--version"};
	argument_options* options = parse_arguments(argc, argv);
	cr_assert(options->print_version);
	free_argument_options(&options);
}

Test(arguments_parse_version, dash_version_false)
{
	int argc = 2;
	char* argv[] = {"dot", "-version"};
	argument_options* options = parse_arguments(argc, argv);
	cr_assert(!options->print_version);
	free_argument_options(&options);
}

Test(arguments_parse_version, dash_dash_version_random_false)
{
	int argc = 2;
	char* argv[] = {"dot", "--version-random"};
	argument_options* options = parse_arguments(argc, argv);
	cr_assert(!options->print_version);
	free_argument_options(&options);
}
