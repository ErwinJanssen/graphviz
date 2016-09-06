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

#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

#include "geom.h"
#include "globals.h"
#include "memory.h"
#include "render.h"

gv_config* initialize_gv_config(void)
{
    gv_config* default_gv_config = safe_malloc(sizeof(gv_config));
    safe_strcpy(default_gv_config->command_name, "dot");
    default_gv_config->print_version = false;
    default_gv_config->print_usage = false;
    default_gv_config->configure = false;
    default_gv_config->auto_output_filenames = false;
    default_gv_config->reduce = false;
    default_gv_config->invert_y = false;
    default_gv_config->generate_plugin_graph = false;
    default_gv_config->verbose = false;
    default_gv_config->verbosity_level = 1;
    default_gv_config->memory_test = false;
    default_gv_config->memory_test_iterations = 0;
    default_gv_config->message_suppression = false;
    default_gv_config->message_suppression_level = 1;
    default_gv_config->invalid_flags_without_value = NULL;
    default_gv_config->scale_input = false;
    default_gv_config->scale_input_value = POINTS_PER_INCH;
    return default_gv_config;
}

void free_gv_config(gv_config** config)
{
    safe_free((*config)->command_name);
    safe_free((*config)->invalid_flags_without_value);
    safe_free(*config);
}

gv_config* gv_parse_arguments(int argc, char** argv)
{
    gv_config* config = initialize_gv_config();
    // FIXME determining the command name based the argv[0] is hacky, there is
    // no way to know if argv[0] contains any reliable information.
    safe_strcpy(config->command_name, dotneato_basename(argv[0]));
    for (int i = 1; i < argc; i++)
    {
        char* argument = argv[i];
        if (!argument)
        {
            // TODO The other parsing functions set an arguments to 0 when
            // they are parsed. This check must be removed when the other
            // parsing functions are removed.
            continue;
        }

        if (argument[0] != '-')
        {
            // TODO add argument to input file list
            continue;
        }

        if (gv_parse_argument_with_value(config, argc, argv, &i))
        {
            // TODO add arguments to gv_parse_argument_with_value function
            continue;
        }
        gv_parse_flags_without_value(config, argument);
    }
    return config;
}

bool gv_parse_argument_with_value(gv_config* config, int argc, char** argv,
        int* argv_position)
{
    char* argument = argv[*argv_position];
    for (size_t i = 0; i < gv_common_arguments_length(); i++)
    {
        gv_cmdline_argument argument_type = gv_common_arguments[i];
        if (argument[1] == argument_type.flag)
        {
            if (argument_type.argument_type == ARGUMENT_WITH_SINGLE_VALUE)
            {
                return true;
            }
            else if (argument_type.argument_type == ARGUMENT_WITH_MULTIPLE_VALUES)
            {
                char* value = gv_get_argument_value(argc, argv, argv_position);
                if (!value)
                {
                    fprintf(stderr, "Encountered -%c without value, ignoring.\n", argument[1]);
                    return true;
                }
                char*** value_field = (char***) get_struct_field(config,
                        argument_type.field_offset);
                size_t* counter_field = (size_t*) get_struct_field(config,
                        argument_type.additional_field_offset);
                (*counter_field)++;
                (*value_field) = realloc(*value_field, (*counter_field) * sizeof(char**));
                (*value_field)[(*counter_field) - 1] = NULL;
                safe_strcpy((*value_field)[(*counter_field) - 1], value);
                return true;
            }
        }
    }
    return false;
}

char* gv_get_argument_value(int argc, char** argv, int* argv_position)
{
    if (strlen(argv[*argv_position]) <= 2)
    {
        if ((*argv_position) + 1 == argc || argv[(*argv_position) + 1][0] == '-')
        {
            return NULL;
        }
        else
        {
            (*argv_position)++;
            return argv[(*argv_position)];
        }
    }
    else
    {
        char* value = NULL;
        return safe_strcpy(value, &(argv[*argv_position][2]));
    }
}

void gv_parse_flags_without_value(gv_config* config, char* flags)
{
    // Start at 1 to skip the dash.
    for (size_t i = 1; i < strlen(flags); i++)
    {
        char flag = flags[i];
        bool valid_flag = false;
        for (size_t j = 0; j < gv_common_arguments_length(); j++)
        {
            if (flag == gv_common_arguments[j].flag)
            {
                gv_cmdline_argument* argument = &gv_common_arguments[j];
                bool* field_value = (bool*) get_struct_field(config,
                        argument->field_offset);
                bool first_encounter = false;
                if(!*field_value)
                {
                    first_encounter = true;
                }
                *field_value = true;
                if (flags[i + 1] && isdigit(flags[i + 1]))
                {
                    if (argument->argument_type == ARGUMENT_WITH_OPTIONAL_INT)
                    {
                        uint32_t* optional_value = (uint32_t*) get_struct_field(
                                config, argument->additional_field_offset);
                        uint32_t new_value = gv_read_optional_int_value(
                                &flags[i + 1], &i);
                        if (first_encounter || new_value > *optional_value)
                        {
                            *optional_value = new_value;
                        }
                    }
                    else if (argument->argument_type == ARGUMENT_WITH_OPTIONAL_FLOAT)
                    {
                        double* optional_value = (double*) get_struct_field(
                                config, argument->additional_field_offset);
                        double new_value = gv_read_optional_float_value(
                                &flags[i + 1], &i);
                        if (first_encounter || new_value > *optional_value)
                        {
                            *optional_value = new_value;
                        }
                    }
                }
                valid_flag = true;
                continue;
            }
        }
        if (!valid_flag)
        {
            if (!config->invalid_flags_without_value)
            {
                gv_initialize_empty_string(
                        &config->invalid_flags_without_value);
            }
            sprintf(config->invalid_flags_without_value, "%s%c",
                    config->invalid_flags_without_value, flag);
        }
    }
}

uint32_t gv_read_optional_int_value(char* partial_argument, size_t* i)
{
    const uint8_t max_digits = 8;
    uint8_t digits_read = 0;
    uint32_t optional_value = 0;
    while (partial_argument[digits_read] && digits_read <= max_digits
            && isdigit(partial_argument[digits_read]))
    {
        optional_value *= 10;
        optional_value += char_to_int(partial_argument[digits_read]);
        digits_read++;
        (*i)++;
    }
    return optional_value;
}

double gv_read_optional_float_value(char* partial_argument, size_t* i)
{
    const uint8_t max_digits = 8;
    uint8_t digits_read = 0;
    bool decimal_point_found = false;
    while (partial_argument[digits_read] && digits_read <= max_digits
            && (isdigit(partial_argument[digits_read])
                    || partial_argument[digits_read] == '.'))
    {
        if (partial_argument[digits_read] == '.')
        {
            if(!decimal_point_found)
            {
                decimal_point_found = true;
            }
            else
            {
                break;
            }
        }
        digits_read++;
        (*i)++;
    }
    char* optional_value_string = NULL;
    optional_value_string = safe_strncpy(optional_value_string, partial_argument, digits_read);
    return atof(optional_value_string);
}

uint8_t number_of_digits(uint32_t integer)
{
    if (integer < 10)
    {
        return 1;
    }
    else
    {
        return (uint8_t) (1 + number_of_digits(integer / 10));
    }
}

void gv_process_arguments(gv_config* config, GVC_t* gvc)
{
    safe_strcpy(gvc->common.cmdname, config->command_name);
    safe_strcpy(CmdName, config->command_name);
    if (config->invalid_flags_without_value)
    {
        fprintf(stderr, "Error: encountered the following invalid flags: ");
        for (size_t i = 0; i < strlen(config->invalid_flags_without_value); i++)
        {
            if (i < strlen(config->invalid_flags_without_value) - 1)
            {
                fprintf(stderr, "'%c', ",
                        config->invalid_flags_without_value[i]);
            }
            else
            {
                fprintf(stderr, "'%c'.\n",
                        config->invalid_flags_without_value[i]);
            }
        }
        fprintf(stderr, "Use the -? flag for information about the usage.\n");
        exit(EXIT_FAILURE);
    }
    if (config->print_usage)
    {
        dotneato_usage(0);
        exit(EXIT_SUCCESS);
    }
    if (config->print_version)
    {
        gv_print_version(stderr, gvc);
        exit(EXIT_SUCCESS);
    }
    if (config->verbose)
    {
        unsigned char verbosity_level = 0;
        if (config->verbosity_level > UCHAR_MAX)
        {
            verbosity_level = UCHAR_MAX;
        }
        else
        {
            verbosity_level = (unsigned char) config->verbosity_level;
        }
        gvc->common.verbose = verbosity_level;
        Verbose = verbosity_level;
        gv_print_version(stderr, gvc);
    }
    if (config->configure)
    {
        gvconfig(gvc, true);
        exit(EXIT_SUCCESS);
    }
    if (config->memory_test)
    {
        if (config->memory_test_iterations == 0)
        {
            MemTest = -1;
        }
        else
        {
            if (config->memory_test_iterations > INT_MAX)
            {
                MemTest = INT_MAX;
            }
            else
            {
                MemTest = (int) config->memory_test_iterations;
            }
        }
    }
    if (config->generate_plugin_graph)
    {
        P_graph = gvplugin_graph(gvc);
    }
    if (config->auto_output_filenames)
    {
        gvc->common.auto_outfile_names = true;
    }
    if (config->reduce)
    {
        Reduce = true;
    }
    if (config->invert_y)
    {
        Y_invert = true;
    }
    if (config->message_suppression)
    {
        if (config->message_suppression_level == 0)
        {
            agseterr(AGWARN);
        }
        else if (config->message_suppression_level == 1)
        {
            agseterr(AGERR);
        }
        else
        {
            agseterr(AGMAX);
        }
    }
    if (config->scale_input)
    {
        if (config->scale_input_value <= 0)
        {
            PSinputscale = POINTS_PER_INCH;
        }
        else
        {
            PSinputscale = config->scale_input_value;
        }
    }
}

void gv_initialize_empty_string(char** target_address)
{
    (*target_address) = safe_malloc(sizeof(char));
    (*target_address)[0] = '\0';
}

void gv_print_version(FILE* stream, GVC_t* gvc)
{
    fprintf(stream, "%s - %s version %s (%s)\n",
            gvc->common.cmdname, gvc->common.info[0],
            gvc->common.info[1], gvc->common.info[2]);
}
