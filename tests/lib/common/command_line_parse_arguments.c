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

Test(command_line_parse_arguments, dash_V)
{
	int argc = 2;
	char* argv[] = {"dot", "-V"};
	gv_config* config = gv_parse_arguments(argc, argv);
	cr_assert(config->print_version);
	cr_assert(!config->print_usage);
	free_gv_config(&config);
}

Test(command_line_parse_arguments, dash_questionmark)
{
	int argc = 2;
	char* argv[] = {"dot", "-?"};
	gv_config* config = gv_parse_arguments(argc, argv);
	cr_assert(!config->print_version);
	cr_assert(config->print_usage);
	free_gv_config(&config);
}

Test(command_line_parse_arguments, dash_V_questionmark)
{
	int argc = 2;
	char* argv[] = {"dot", "-V?"};
	gv_config* config = gv_parse_arguments(argc, argv);
	cr_assert(config->print_version);
	cr_assert(config->print_usage);
	free_gv_config(&config);
}

Test(command_line_parse_arguments, dash_questionmark_V)
{
	int argc = 2;
	char* argv[] = {"dot", "-?V"};
	gv_config* config = gv_parse_arguments(argc, argv);
	cr_assert(config->print_version);
	cr_assert(config->print_usage);
	free_gv_config(&config);
}
