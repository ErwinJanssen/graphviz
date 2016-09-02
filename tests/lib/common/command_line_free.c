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

Test(command_line_free, config)
{
    gv_config* config = initialize_gv_config();
    free_gv_config(&config);
    cr_assert_null(config);
}

Test(command_line_free, command_name)
{
    gv_config* config = initialize_gv_config();
    char** command_name = &config->command_name;
    free_gv_config(&config);
    cr_assert_null(*command_name);
}

Test(command_line_free, invalid_flags_without_value)
{
    gv_config* config = initialize_gv_config();
    char** invalid_flags_without_value = &config->invalid_flags_without_value;
    safe_strcpy(*invalid_flags_without_value, "random");
    free_gv_config(&config);
    cr_assert_null(*invalid_flags_without_value);
}
