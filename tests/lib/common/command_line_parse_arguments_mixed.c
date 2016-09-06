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
    cr_expect_eq(actual->scale_input, expected->scale_input);
    cr_expect(double_equal(actual->scale_input_value, expected->scale_input_value));
    cr_expect_eq(actual->graph_attributes_count, expected->graph_attributes_count);
    if (actual->graph_attributes_count == expected->graph_attributes_count)
    {
        for (size_t i = 0; i < actual->graph_attributes_count; i++)
        {
            cr_expect_str_eq(actual->graph_attributes[i], expected->graph_attributes[i]);
        }
    }

    if (!actual->invalid_flags_without_value)
    {
        cr_expect_null(expected->invalid_flags_without_value);
    }
    else
    {
        cr_expect_str_eq(actual->invalid_flags_without_value, expected->invalid_flags_without_value);
    }
}

Test(command_line_parse_arguments, dot_dash_V_questionmark)
{
    gv_config* expected_config = initialize_gv_config();
    safe_strcpy(expected_config->command_name, "dot");
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
    safe_strcpy(expected_config->invalid_flags_without_value, "B");

    int argc = 2;
    char* argv[] = {"dot", "-?BV"};
    gv_config* actual_config = gv_parse_arguments(argc, argv);
    compare_gv_config(expected_config, actual_config);

    free_gv_config(&expected_config);
    free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_questionmark_BAV)
{
    gv_config* expected_config = initialize_gv_config();
    expected_config->print_version = true;
    expected_config->print_usage = true;
    safe_strcpy(expected_config->invalid_flags_without_value, "BA");

    int argc = 2;
    char* argv[] = {"dot", "-?BAV"};
    gv_config* actual_config = gv_parse_arguments(argc, argv);
    compare_gv_config(expected_config, actual_config);

    free_gv_config(&expected_config);
    free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, neato_dash_questionmark_dash_x)
{
    gv_config* expected_config = initialize_gv_config();
    safe_strcpy(expected_config->command_name, "neato");
    expected_config->print_usage = true;
    expected_config->reduce = true;

    int argc = 3;
    char* argv[] = {"neato", "-?", "-x"};
    gv_config* actual_config = gv_parse_arguments(argc, argv);
    compare_gv_config(expected_config, actual_config);

    free_gv_config(&expected_config);
    free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_questionmark_dash_x_dash_v)
{
    gv_config* expected_config = initialize_gv_config();
    expected_config->print_usage = true;
    expected_config->reduce = true;
    expected_config->verbose = true;
    expected_config->verbosity_level = 1;

    int argc = 4;
    char* argv[] = {"dot", "-?", "-x", "-v"};
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

Test(command_line_parse_arguments, dash_questionmark_dash_x_dash_O_dash_m5_dash_y)
{
    gv_config* expected_config = initialize_gv_config();
    expected_config->print_usage = true;
    expected_config->auto_output_filenames = true;
    expected_config->reduce = true;
    expected_config->invert_y = true;
    expected_config->memory_test = true;
    expected_config->memory_test_iterations = 5;

    int argc = 6;
    char* argv[] = {"dot", "-?", "-x", "-O", "-m5", "-y"};
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

Test(command_line_parse_arguments, dash_OPsx)
{
    gv_config* expected_config = initialize_gv_config();
    expected_config->auto_output_filenames = true;
    expected_config->reduce = true;
    expected_config->generate_plugin_graph = true;
    expected_config->scale_input = true;
    expected_config->scale_input_value = 72;

    int argc = 2;
    char* argv[] = {"dot", "-OPsx"};
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

Test(command_line_parse_arguments, dash_Ovx_dash_OP)
{
    gv_config* expected_config = initialize_gv_config();
    expected_config->auto_output_filenames = true;
    expected_config->reduce = true;
    expected_config->generate_plugin_graph = true;
    expected_config->verbose = true;
    expected_config->verbosity_level = 1;
    expected_config->scale_input = true;
    expected_config->scale_input_value = 100.42;

    int argc = 3;
    char* argv[] = {"dot", "-Ovx", "-Os100.42P"};
    gv_config* actual_config = gv_parse_arguments(argc, argv);
    compare_gv_config(expected_config, actual_config);

    free_gv_config(&expected_config);
    free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_Ov7x_dash_v2OP_dash_q60)
{
    gv_config* expected_config = initialize_gv_config();
    expected_config->auto_output_filenames = true;
    expected_config->reduce = true;
    expected_config->generate_plugin_graph = true;
    expected_config->verbose = true;
    expected_config->verbosity_level = 7;
    expected_config->message_suppression = true;
    expected_config->message_suppression_level = 60;

    int argc = 4;
    char* argv[] = {"dot", "-Ov7x", "-Ov2P", "-q60"};
    gv_config* actual_config = gv_parse_arguments(argc, argv);
    compare_gv_config(expected_config, actual_config);

    free_gv_config(&expected_config);
    free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_Ov7235435m3x_dash_v2OP)
{
    gv_config* expected_config = initialize_gv_config();
    expected_config->auto_output_filenames = true;
    expected_config->reduce = true;
    expected_config->generate_plugin_graph = true;
    expected_config->verbose = true;
    expected_config->verbosity_level = 7235435;
    expected_config->memory_test = true;
    expected_config->memory_test_iterations = 3;

    int argc = 3;
    char* argv[] = {"dot", "-Ov7235435m3x", "-Ov2P"};
    gv_config* actual_config = gv_parse_arguments(argc, argv);
    compare_gv_config(expected_config, actual_config);

    free_gv_config(&expected_config);
    free_gv_config(&actual_config);
}

Test(command_line_parse_arguments, dash_G_dirLR_dash_Ov6_Gdpi300)
{
    gv_config* expected_config = initialize_gv_config();
    expected_config->verbose = true;
    expected_config->verbosity_level = 6;
    expected_config->auto_output_filenames = true;
    expected_config->graph_attributes_count = 2;
    char* graph_attributes[] = {"dir=LR", "dpi=300"};
    expected_config->graph_attributes = graph_attributes;

    int argc = 5;
    char* argv[] = {"dot", "-G", "dir=LR", "-Ov6", "-Gdpi=300"};
    gv_config* actual_config = gv_parse_arguments(argc, argv);
    compare_gv_config(expected_config, actual_config);

    free_gv_config(&expected_config);
    free_gv_config(&actual_config);
}
