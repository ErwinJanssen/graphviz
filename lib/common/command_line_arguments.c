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
	}
};

size_t gv_common_arguments_length(void)
{
	return sizeof(gv_common_arguments) / sizeof(gv_cmdline_argument);
}
