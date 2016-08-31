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

#include "globals.h"
#include "render.h"

gv_config* initialize_gv_config(void)
{
	gv_config* default_gv_config = safe_malloc(sizeof(gv_config), __FUNCTION__);
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
	default_gv_config->invalid_flags_without_value = NULL;
	return default_gv_config;
}

void free_gv_config(gv_config** config)
{
	free((*config)->invalid_flags_without_value);
	free(*config);
	*config = NULL;
}

gv_config* gv_parse_arguments(int argc, char** argv)
{
	gv_config* config = initialize_gv_config();
	// Skip argv[0] because this doesn't contain reliable data.
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

		if (gv_parse_argument_with_value(config, argv, &i))
		{
			// TODO add arguments to gv_parse_argument_with_value function
			continue;
		}
		gv_parse_flags_without_value(config, argument);
	}
	return config;
}

bool gv_parse_argument_with_value(gv_config* config, char** argv,
		int* argv_position)
{
	char* argument = argv[*argv_position];
	for (size_t i = 0; i < gv_common_arguments_length(); i++)
	{
		if ((gv_common_arguments[i].argument_type == ARGUMENT_WITH_MULTIPLE_VALUES
				|| gv_common_arguments[i].argument_type == ARGUMENT_WITH_SINGLE_VALUE)
				&& argument[1] == gv_common_arguments[i].flag)
		{
			return true;
		}
	}
	return false;
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
				*field_value = true;
				if (argument->argument_type == ARGUMENT_WITH_OPTIONAL_VALUE
						&& flags[i + 1] && isdigit(flags[i + 1]))
				{
					uint32_t* optional_value = (uint32_t*) get_struct_field(
							config, argument->field_offset_optional_value);
					uint32_t new_value = gv_read_optional_flag_value(&flags[i + 1]);
					if (new_value > *optional_value)
					{
						*optional_value = new_value;
					}
					i += number_of_digits(new_value);
					valid_flag = true;
					continue;
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

uint32_t gv_read_optional_flag_value(char* partial_argument)
{
	const uint8_t max_integer_length = 8;
	uint8_t digits_read = 0;
	uint32_t optional_value = 0;
	while (partial_argument[digits_read] && digits_read <= max_integer_length
			&& isdigit(partial_argument[digits_read]))
	{
		optional_value *= 10;
		optional_value += char_to_int(partial_argument[digits_read]);
		digits_read++;
	}
	return optional_value;
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
			if(config->memory_test_iterations > INT_MAX)
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
	if (config->verbose)
	{
		unsigned char verbosity_level = 0;
		if(config->verbosity_level > UCHAR_MAX)
		{
			verbosity_level = UCHAR_MAX;
		}
		else
		{
			verbosity_level = (unsigned char) config->verbosity_level;
		}
		gvc->common.verbose = verbosity_level;
		Verbose = verbosity_level;
	}
}

void gv_initialize_empty_string(char** target_address)
{
	(*target_address) = safe_malloc(sizeof(char), __FUNCTION__);
	(*target_address)[0] = '\0';
}

void gv_print_version(FILE* stream, GVC_t* gvc)
{
	fprintf(stream, "%s - %s version %s (%s)\n",
		    gvc->common.cmdname, gvc->common.info[0],
		    gvc->common.info[1], gvc->common.info[2]);
}
