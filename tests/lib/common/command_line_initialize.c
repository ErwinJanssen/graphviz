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

Test(command_line_initialze, not_null)
{
	gv_config* config = initialize_gv_config();
	cr_assert_not_null(config);
	free_gv_config(&config);
}

Test(command_line_initialze, print_version)
{
	gv_config* config = initialize_gv_config();
	cr_assert_not(config->print_version);
	free_gv_config(&config);
}

Test(command_line_initialze, configure)
{
	gv_config* config = initialize_gv_config();
	cr_assert_not(config->configure);
	free_gv_config(&config);
}

Test(command_line_initialze, auto_output_filenames)
{
	gv_config* config = initialize_gv_config();
	cr_assert_not(config->auto_output_filenames);
	free_gv_config(&config);
}

Test(command_line_initialze, reduce)
{
	gv_config* config = initialize_gv_config();
	cr_assert_not(config->reduce);
	free_gv_config(&config);
}

Test(command_line_initialze, invert_y)
{
	gv_config* config = initialize_gv_config();
	cr_assert_not(config->invert_y);
	free_gv_config(&config);
}

Test(command_line_initialze, generate_plugin_graph)
{
	gv_config* config = initialize_gv_config();
	cr_assert_not(config->generate_plugin_graph);
	free_gv_config(&config);
}

Test(command_line_initialze, verbose)
{
	gv_config* config = initialize_gv_config();
	cr_assert_not(config->verbose);
	free_gv_config(&config);
}

Test(command_line_initialze, verbosity_level)
{
	gv_config* config = initialize_gv_config();
	cr_assert(config->verbosity_level == 1);
	free_gv_config(&config);
}

Test(command_line_initialze, memory_test)
{
	gv_config* config = initialize_gv_config();
	cr_assert_not(config->memory_test);
	free_gv_config(&config);
}

Test(command_line_initialze, memory_test_iterations)
{
	gv_config* config = initialize_gv_config();
	cr_assert(config->memory_test_iterations == 0);
	free_gv_config(&config);
}

Test(command_line_initialze, invalid_flags_without_value)
{
	gv_config* config = initialize_gv_config();
	cr_assert_null(config->invalid_flags_without_value);
	free_gv_config(&config);
}

