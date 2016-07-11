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

Test(arguments_parse_usage, dash_questionmark_true)
{
	int argc = 2;
	char* argv[] = {"dot", "-?"};
	argument_options* options = parse_arguments(argc, argv);
	cr_assert(options->print_usage);
	free_argument_options(&options);
}

Test(arguments_parse_usage, dash_h_true)
{
	int argc = 2;
	char* argv[] = {"dot", "-h"};
	argument_options* options = parse_arguments(argc, argv);
	cr_assert(options->print_usage);
	free_argument_options(&options);
}

Test(arguments_parse_usage, dash_H_false)
{
	int argc = 2;
	char* argv[] = {"dot", "-H"};
	argument_options* options = parse_arguments(argc, argv);
	cr_assert(!options->print_usage);
	free_argument_options(&options);
}

Test(arguments_parse_usage, dash_dash_questionmark_false)
{
	int argc = 2;
	char* argv[] = {"dot", "--?"};
	argument_options* options = parse_arguments(argc, argv);
	cr_assert(!options->print_usage);
	free_argument_options(&options);
}

Test(arguments_parse_usage, dash_dash_h_false)
{
	int argc = 2;
	char* argv[] = {"dot", "--h"};
	argument_options* options = parse_arguments(argc, argv);
	cr_assert(!options->print_usage);
	free_argument_options(&options);
}

Test(arguments_parse_usage, dash_questionmarkX_false)
{
	int argc = 2;
	char* argv[] = {"dot", "-?X"};
	argument_options* options = parse_arguments(argc, argv);
	cr_assert(!options->print_usage);
	free_argument_options(&options);
}

Test(arguments_parse_usage, dash_hX_false)
{
	int argc = 2;
	char* argv[] = {"dot", "-hX"};
	argument_options* options = parse_arguments(argc, argv);
	cr_assert(!options->print_usage);
	free_argument_options(&options);
}

Test(arguments_parse_usage, dash_dash_help_true)
{
	int argc = 2;
	char* argv[] = {"dot", "--help"};
	argument_options* options = parse_arguments(argc, argv);
	cr_assert(options->print_usage);
	free_argument_options(&options);
}

Test(arguments_parse_usage, dash_help_false)
{
	int argc = 2;
	char* argv[] = {"dot", "-help"};
	argument_options* options = parse_arguments(argc, argv);
	cr_assert(!options->print_usage);
	free_argument_options(&options);
}

Test(arguments_parse_usage, dash_dash_help_random_false)
{
	int argc = 2;
	char* argv[] = {"dot", "--help-random"};
	argument_options* options = parse_arguments(argc, argv);
	cr_assert(!options->print_usage);
	free_argument_options(&options);
}
