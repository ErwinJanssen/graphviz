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

#include <stdlib.h>
#include <stdio.h>

size_t gv_common_arguments_length(void)
{
	return sizeof(gv_common_arguments) / sizeof(gv_cmdline_argument);
}

gv_config* initialize_gv_config(void)
{
	gv_config* default_gv_config = safe_malloc(sizeof(gv_config), __FUNCTION__);
	default_gv_config->print_version = false;
	default_gv_config->print_usage = false;
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
		// For now, assume that an argument must start with a
		// ARGUMENT_WITHOUT_VALUE type flag before we process it.
		// These are some simple and dirty check that will be replaced
		// when more arguments are added to the new code.
		// Also require that it starts with a dash.
		if (argument[0] != '-')
		{
			continue;
		}
		bool no_value_argument = false;
		for (size_t j = 0; j < gv_common_arguments_length(); j++)
		{
			if (gv_common_arguments[j].argument_type == ARGUMENT_WITHOUT_VALUE
					&& argument[1] == gv_common_arguments[j].flag)
			{
				no_value_argument = true;
			}
		}
		if (!no_value_argument)
		{
			continue;
		}
		gv_parse_flags_without_value(config, argument);
	}
	return config;
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
			if (gv_common_arguments[j].argument_type == ARGUMENT_WITHOUT_VALUE
					&& flag == gv_common_arguments[j].flag)
			{
				bool* field_value = (((bool*) config)
						+ gv_common_arguments[j].field_offset);
				*field_value = true;
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

void gv_process_arguments(gv_config* config)
{

}

void* safe_malloc(size_t size, const char* calling_function)
{
	void* memory = malloc(size);
	if (!memory)
	{
		fprintf(stderr, "Error: not enough memory for malloc in function: %s",
				calling_function);
		exit(EXIT_FAILURE);
	}
	return memory;
}

void gv_initialize_empty_string(char** target_address)
{
	(*target_address) = safe_malloc(sizeof(char), __FUNCTION__);
	(*target_address)[0] = '\0';
}
