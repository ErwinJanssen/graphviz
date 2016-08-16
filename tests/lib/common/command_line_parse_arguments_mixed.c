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
	cr_expect_eq(actual->invert_y, expected->invert_y);
	cr_expect_eq(actual->generate_plugin_graph, expected->generate_plugin_graph);
}

Test(command_line_parse_arguments, dash_V_questionmark)
{
	gv_config* expected_config = initialize_gv_config();
	expected_config->print_version = true;
	expected_config->print_usage = true;

	int argc = 2;
	char* argv[] = {"dot", "-V?"};
	gv_config* actual_config = gv_parse_arguments(argc, argv);
	compare_gv_config(expected_config, actual_config);

	free_gv_config(&expected_config);
	free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_questionmark_V)
{
	gv_config* expected_config = initialize_gv_config();
	expected_config->print_version = true;
	expected_config->print_usage = true;

	int argc = 2;
	char* argv[] = {"dot", "-?V"};
	gv_config* actual_config = gv_parse_arguments(argc, argv);
	compare_gv_config(expected_config, actual_config);

	free_gv_config(&expected_config);
	free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_questionmark_BV)
{
	gv_config* expected_config = initialize_gv_config();
	expected_config->print_version = true;
	expected_config->print_usage = true;

	int argc = 2;
	char* argv[] = {"dot", "-?BV"};
	gv_config* actual_config = gv_parse_arguments(argc, argv);
	compare_gv_config(expected_config, actual_config);
	cr_assert_str_eq(actual_config->invalid_flags_without_value, "B");

	free_gv_config(&expected_config);
	free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_questionmark_BAV)
{
	gv_config* expected_config = initialize_gv_config();
	expected_config->print_version = true;
	expected_config->print_usage = true;

	int argc = 2;
	char* argv[] = {"dot", "-?BAV"};
	gv_config* actual_config = gv_parse_arguments(argc, argv);
	compare_gv_config(expected_config, actual_config);
	cr_assert_str_eq(actual_config->invalid_flags_without_value, "BA");

	free_gv_config(&expected_config);
	free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_questionmark_dash_x)
{
	gv_config* expected_config = initialize_gv_config();
	expected_config->print_usage = true;
	expected_config->reduce = true;

	int argc = 3;
	char* argv[] = {"dot", "-?", "-x"};
	gv_config* actual_config = gv_parse_arguments(argc, argv);
	compare_gv_config(expected_config, actual_config);

	free_gv_config(&expected_config);
	free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_questionmark_dash_x_dash_O)
{
	gv_config* expected_config = initialize_gv_config();
	expected_config->print_usage = true;
	expected_config->auto_output_filenames = true;
	expected_config->reduce = true;

	int argc = 4;
	char* argv[] = {"dot", "-?", "-x", "-O"};
	gv_config* actual_config = gv_parse_arguments(argc, argv);
	compare_gv_config(expected_config, actual_config);

	free_gv_config(&expected_config);
	free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_questionmark_dash_x_dash_O_dash_y)
{
	gv_config* expected_config = initialize_gv_config();
	expected_config->print_usage = true;
	expected_config->auto_output_filenames = true;
	expected_config->reduce = true;
	expected_config->invert_y = true;

	int argc = 5;
	char* argv[] = {"dot", "-?", "-x", "-O", "-y"};
	gv_config* actual_config = gv_parse_arguments(argc, argv);
	compare_gv_config(expected_config, actual_config);

	free_gv_config(&expected_config);
	free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_questionmark_dash_x_dash_O_dash_P)
{
	gv_config* expected_config = initialize_gv_config();
	expected_config->print_usage = true;
	expected_config->auto_output_filenames = true;
	expected_config->reduce = true;
	expected_config->invert_y = true;
	expected_config->generate_plugin_graph = true;

	int argc = 6;
	char* argv[] = {"dot", "-?", "-x", "-O", "-y", "-P"};
	gv_config* actual_config = gv_parse_arguments(argc, argv);
	compare_gv_config(expected_config, actual_config);

	free_gv_config(&expected_config);
	free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_questionmark_dash_c_dash_x)
{
	gv_config* expected_config = initialize_gv_config();
	expected_config->print_usage = true;
	expected_config->configure = true;
	expected_config->reduce = true;

	int argc = 4;
	char* argv[] = {"dot", "-?", "-c", "-x"};
	gv_config* actual_config = gv_parse_arguments(argc, argv);
	compare_gv_config(expected_config, actual_config);

	free_gv_config(&expected_config);
	free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_Vx)
{
	gv_config* expected_config = initialize_gv_config();
	expected_config->print_version = true;
	expected_config->reduce = true;

	int argc = 2;
	char* argv[] = {"dot", "-Vx"};
	gv_config* actual_config = gv_parse_arguments(argc, argv);
	compare_gv_config(expected_config, actual_config);

	free_gv_config(&expected_config);
	free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_Vcx)
{
	gv_config* expected_config = initialize_gv_config();
	expected_config->print_version = true;
	expected_config->configure = true;
	expected_config->reduce = true;

	int argc = 2;
	char* argv[] = {"dot", "-Vcx"};
	gv_config* actual_config = gv_parse_arguments(argc, argv);
	compare_gv_config(expected_config, actual_config);

	free_gv_config(&expected_config);
	free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_Ox)
{
	gv_config* expected_config = initialize_gv_config();
	expected_config->auto_output_filenames = true;
	expected_config->reduce = true;

	int argc = 2;
	char* argv[] = {"dot", "-Ox"};
	gv_config* actual_config = gv_parse_arguments(argc, argv);
	compare_gv_config(expected_config, actual_config);

	free_gv_config(&expected_config);
	free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_Oyx)
{
	gv_config* expected_config = initialize_gv_config();
	expected_config->auto_output_filenames = true;
	expected_config->reduce = true;
	expected_config->invert_y = true;

	int argc = 2;
	char* argv[] = {"dot", "-Oyx"};
	gv_config* actual_config = gv_parse_arguments(argc, argv);
	compare_gv_config(expected_config, actual_config);

	free_gv_config(&expected_config);
	free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_OPx)
{
	gv_config* expected_config = initialize_gv_config();
	expected_config->auto_output_filenames = true;
	expected_config->reduce = true;
	expected_config->generate_plugin_graph = true;

	int argc = 2;
	char* argv[] = {"dot", "-OPx"};
	gv_config* actual_config = gv_parse_arguments(argc, argv);
	compare_gv_config(expected_config, actual_config);

	free_gv_config(&expected_config);
	free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_Ox_dash_OP)
{
	gv_config* expected_config = initialize_gv_config();
	expected_config->auto_output_filenames = true;
	expected_config->reduce = true;
	expected_config->generate_plugin_graph = true;

	int argc = 3;
	char* argv[] = {"dot", "-Ox", "-OP"};
	gv_config* actual_config = gv_parse_arguments(argc, argv);
	compare_gv_config(expected_config, actual_config);

	free_gv_config(&expected_config);
	free_gv_config(&actual_config);
}
