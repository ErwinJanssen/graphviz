/*************************************************************************
 * This program and the accompanying materials are made available under
 * the terms of the Eclipse Public License v1.0 which accompanies this
 * distribution, and is available at:
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors: See version control history
 * Details at https://github.com/ellson/graphviz
 *************************************************************************/

#include "command_line_arguments.h"

gv_cmdline_argument gv_common_arguments[] =
{
	{
		.flag = 'V',
		.argument_type = ARGUMENT_WITHOUT_VALUE,
		.description = "Print the version and exit",
		.field_offset = offsetof(gv_config, print_version)
	},
	{
		.flag = '?',
		.argument_type = ARGUMENT_WITHOUT_VALUE,
		.description = "Print the usage and exit",
		.field_offset = offsetof(gv_config, print_usage)
	},
	{
		.flag = 'x',
		.argument_type = ARGUMENT_WITHOUT_VALUE,
		.description = "Reduce graph",
		.field_offset = offsetof(gv_config, reduce)
	},
	{
		.flag = 'y',
		.argument_type = ARGUMENT_WITHOUT_VALUE,
		.description = "Invert y coordinate in output",
		//.field_offset =
	},
	{
		.flag = 'P',
		.argument_type = ARGUMENT_WITHOUT_VALUE,
		.description = "Internally generate a graph of the current plugins",
		//.field_offset =
	},
	{
		.flag = 'q',
		.argument_type = ARGUMENT_WITH_OPTIONAL_VALUE,
		.description = "Set level of message suppression default=1)",
		//.field_offset =
	},
	{
		.flag = 's',
		.argument_type = ARGUMENT_WITH_OPTIONAL_VALUE,
		.description = "Scale input by this value, default=72",
		//.field_offset =
	},
	{
		.flag = 'G',
		.argument_type = ARGUMENT_WITH_MULTIPLE_VALUES,
		.description = "Set additional graph attribute in the form of name=val",
		//.field_offset =
	},
	{
		.flag = 'N',
		.argument_type = ARGUMENT_WITH_MULTIPLE_VALUES,
		.description = "Set additional node attribute in the form of name=val",
		//.field_offset =
	},
	{
		.flag = 'E',
		.argument_type = ARGUMENT_WITH_MULTIPLE_VALUES,
		.description = "Set additional edge attribute in the form of name=val",
		//.field_offset =
	},
	{
		.flag = 'T',
		.argument_type = ARGUMENT_WITH_MULTIPLE_VALUES,
		.description = "Set output format",
		//.field_offset =
	},
	{
		.flag = 'K',
		.argument_type = ARGUMENT_WITH_MULTIPLE_VALUES,
		.description = "Set layout engine",
		//.field_offset =
	},
	{
		.flag = 'l',
		.argument_type = ARGUMENT_WITH_MULTIPLE_VALUES,
		.description = "Use external library",
		//.field_offset =
	},
	{
		.flag = 'o',
		.argument_type = ARGUMENT_WITH_MULTIPLE_VALUES,
		.description = "Specify output file",
		//.field_offset =
	}
};

size_t gv_common_arguments_length(void)
{
	return sizeof(gv_common_arguments) / sizeof(gv_cmdline_argument);
}
