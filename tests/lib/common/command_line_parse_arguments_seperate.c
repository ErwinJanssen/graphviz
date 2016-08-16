/*************************************************************************
 * This program and the accompanying materials are made available under
 * the terms of the Eclipse Public License v1.0 which accompanies this
 * distribution, and is available at:
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors: See version control history
 * Details at https://github.com/ellson/graphviz
 *************************************************************************/

#include "command_line.h"

#include <criterion/criterion.h>

static void compare_gv_config(gv_config* actual, gv_config* expected)
{
	cr_expect_eq(actual->print_version, expected->print_version);
	cr_expect_eq(actual->print_usage, expected->print_usage);
	cr_expect_eq(actual->configure, expected->configure);
	cr_expect_eq(actual->auto_output_filenames, expected->auto_output_filenames);
	cr_expect_eq(actual->reduce, expected->reduce);
}

Test(command_line_parse_arguments, dash_V)
{
	gv_config* expected_config = initialize_gv_config();
	expected_config->print_version = true;

	int argc = 2;
	char* argv[] = {"dot", "-V"};
	gv_config* actual_config = gv_parse_arguments(argc, argv);
	compare_gv_config(expected_config, actual_config);

	free_gv_config(&expected_config);
	free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_questionmark)
{
	gv_config* expected_config = initialize_gv_config();
	expected_config->print_usage = true;

	int argc = 2;
	char* argv[] = {"dot", "-?"};
	gv_config* actual_config = gv_parse_arguments(argc, argv);
	compare_gv_config(expected_config, actual_config);

	free_gv_config(&expected_config);
	free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_c)
{
	gv_config* expected_config = initialize_gv_config();
	expected_config->configure = true;

	int argc = 2;
	char* argv[] = {"dot", "-c"};
	gv_config* actual_config = gv_parse_arguments(argc, argv);
	compare_gv_config(expected_config, actual_config);

	free_gv_config(&expected_config);
	free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_O)
{
	gv_config* expected_config = initialize_gv_config();
	expected_config->auto_output_filenames = true;

	int argc = 2;
	char* argv[] = {"dot", "-O"};
	gv_config* actual_config = gv_parse_arguments(argc, argv);
	compare_gv_config(expected_config, actual_config);

	free_gv_config(&expected_config);
	free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_x)
{
	gv_config* expected_config = initialize_gv_config();
	expected_config->reduce = true;

	int argc = 2;
	char* argv[] = {"dot", "-x"};
	gv_config* actual_config = gv_parse_arguments(argc, argv);
	compare_gv_config(expected_config, actual_config);

	free_gv_config(&expected_config);
	free_gv_config(&actual_config);
}
