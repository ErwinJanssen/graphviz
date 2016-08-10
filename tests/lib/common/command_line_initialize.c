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
