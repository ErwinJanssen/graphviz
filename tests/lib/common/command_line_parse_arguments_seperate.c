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
    cr_expect_str_eq(actual->command_name, expected->command_name);
    cr_expect_eq(actual->print_version, expected->print_version);
    cr_expect_eq(actual->print_usage, expected->print_usage);
    cr_expect_eq(actual->configure, expected->configure);
    cr_expect_eq(actual->auto_output_filenames, expected->auto_output_filenames);
    cr_expect_eq(actual->reduce, expected->reduce);
    cr_expect_eq(actual->invert_y, expected->invert_y);
    cr_expect_eq(actual->generate_plugin_graph, expected->generate_plugin_graph);
    cr_expect_eq(actual->verbose, expected->verbose);
    cr_expect_eq(actual->verbosity_level, expected->verbosity_level);
    cr_expect_eq(actual->memory_test, expected->memory_test);
    cr_expect_eq(actual->message_suppression, expected->message_suppression);
    cr_expect_eq(actual->message_suppression_level, expected->message_suppression_level);
    cr_expect_eq(actual->memory_test_iterations, expected->memory_test_iterations);

    if (!actual->invalid_flags_without_value)
    {
        cr_expect_null(expected->invalid_flags_without_value);
    }
    else
    {
        cr_expect_str_eq(actual->invalid_flags_without_value, expected->invalid_flags_without_value);
    }
}

Test(command_line_parse_arguments, command_name_dot)
{
    gv_config* expected_config = initialize_gv_config();
    safe_strcpy(expected_config->command_name, "dot");

    int argc = 1;
    char* argv[] = {"dot"};
    gv_config* actual_config = gv_parse_arguments(argc, argv);
    compare_gv_config(expected_config, actual_config);

    free_gv_config(&expected_config);
    free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, command_name_neato)
{
    gv_config* expected_config = initialize_gv_config();
    safe_strcpy(expected_config->command_name, "neato");

    int argc = 1;
    char* argv[] = {"neato"};
    gv_config* actual_config = gv_parse_arguments(argc, argv);
    compare_gv_config(expected_config, actual_config);

    free_gv_config(&expected_config);
    free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, command_name_twopi)
{
    gv_config* expected_config = initialize_gv_config();
    safe_strcpy(expected_config->command_name, "twopi");

    int argc = 1;
    char* argv[] = {"twopi"};
    gv_config* actual_config = gv_parse_arguments(argc, argv);
    compare_gv_config(expected_config, actual_config);

    free_gv_config(&expected_config);
    free_gv_config(&actual_config);
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

Test(command_line_parse_arguments, dash_y)
{
    gv_config* expected_config = initialize_gv_config();
    expected_config->invert_y = true;

    int argc = 2;
    char* argv[] = {"dot", "-y"};
    gv_config* actual_config = gv_parse_arguments(argc, argv);
    compare_gv_config(expected_config, actual_config);

    free_gv_config(&expected_config);
    free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_P)
{
    gv_config* expected_config = initialize_gv_config();
    expected_config->generate_plugin_graph = true;

    int argc = 2;
    char* argv[] = {"dot", "-P"};
    gv_config* actual_config = gv_parse_arguments(argc, argv);
    compare_gv_config(expected_config, actual_config);

    free_gv_config(&expected_config);
    free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_v)
{
    gv_config* expected_config = initialize_gv_config();
    expected_config->verbose = true;
    expected_config->verbosity_level = 1;

    int argc = 2;
    char* argv[] = {"dot", "-v"};
    gv_config* actual_config = gv_parse_arguments(argc, argv);
    compare_gv_config(expected_config, actual_config);

    free_gv_config(&expected_config);
    free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_v2)
{
    gv_config* expected_config = initialize_gv_config();
    expected_config->verbose = true;
    expected_config->verbosity_level = 2;

    int argc = 2;
    char* argv[] = {"dot", "-v2"};
    gv_config* actual_config = gv_parse_arguments(argc, argv);
    compare_gv_config(expected_config, actual_config);

    free_gv_config(&expected_config);
    free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_v9)
{
    gv_config* expected_config = initialize_gv_config();
    expected_config->verbose = true;
    expected_config->verbosity_level = 9;

    int argc = 2;
    char* argv[] = {"dot", "-v9"};
    gv_config* actual_config = gv_parse_arguments(argc, argv);
    compare_gv_config(expected_config, actual_config);

    free_gv_config(&expected_config);
    free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_v10)
{
    gv_config* expected_config = initialize_gv_config();
    expected_config->verbose = true;
    expected_config->verbosity_level = 10;

    int argc = 2;
    char* argv[] = {"dot", "-v10"};
    gv_config* actual_config = gv_parse_arguments(argc, argv);
    compare_gv_config(expected_config, actual_config);

    free_gv_config(&expected_config);
    free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_v254643)
{
    gv_config* expected_config = initialize_gv_config();
    expected_config->verbose = true;
    expected_config->verbosity_level = 254643;

    int argc = 2;
    char* argv[] = {"dot", "-v254643"};
    gv_config* actual_config = gv_parse_arguments(argc, argv);
    compare_gv_config(expected_config, actual_config);

    free_gv_config(&expected_config);
    free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_v_dash_v9)
{
    gv_config* expected_config = initialize_gv_config();
    expected_config->verbose = true;
    expected_config->verbosity_level = 9;

    int argc = 3;
    char* argv[] = {"dot", "-v", "-v9"};
    gv_config* actual_config = gv_parse_arguments(argc, argv);
    compare_gv_config(expected_config, actual_config);

    free_gv_config(&expected_config);
    free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_v9_dash_v)
{
    gv_config* expected_config = initialize_gv_config();
    expected_config->verbose = true;
    expected_config->verbosity_level = 9;

    int argc = 3;
    char* argv[] = {"dot", "-v9", "-v"};
    gv_config* actual_config = gv_parse_arguments(argc, argv);
    compare_gv_config(expected_config, actual_config);

    free_gv_config(&expected_config);
    free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_m)
{
    gv_config* expected_config = initialize_gv_config();
    expected_config->memory_test = true;
    expected_config->memory_test_iterations = 0;

    int argc = 2;
    char* argv[] = {"dot", "-m"};
    gv_config* actual_config = gv_parse_arguments(argc, argv);
    compare_gv_config(expected_config, actual_config);

    free_gv_config(&expected_config);
    free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_m9_dash_m)
{
    gv_config* expected_config = initialize_gv_config();
    expected_config->memory_test = true;
    expected_config->memory_test_iterations = 9;

    int argc = 3;
    char* argv[] = {"dot", "-m9", "-m"};
    gv_config* actual_config = gv_parse_arguments(argc, argv);
    compare_gv_config(expected_config, actual_config);

    free_gv_config(&expected_config);
    free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_q)
{
    gv_config* expected_config = initialize_gv_config();
    expected_config->message_suppression = true;
    expected_config->message_suppression_level = 1;

    int argc = 2;
    char* argv[] = {"dot", "-q"};
    gv_config* actual_config = gv_parse_arguments(argc, argv);
    compare_gv_config(expected_config, actual_config);

    free_gv_config(&expected_config);
    free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_q9_dash_q)
{
    gv_config* expected_config = initialize_gv_config();
    expected_config->message_suppression = true;
    expected_config->message_suppression_level = 9;

    int argc = 3;
    char* argv[] = {"dot", "-q9", "-q"};
    gv_config* actual_config = gv_parse_arguments(argc, argv);
    compare_gv_config(expected_config, actual_config);

    free_gv_config(&expected_config);
    free_gv_config(&actual_config);
}
