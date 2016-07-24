/*************************************************************************
 * This program and the accompanying materials are made available under
 * the terms of the Eclipse Public License v1.0 which accompanies this
 * distribution, and is available at:
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors: See version control history
 * Details at https://github.com/ellson/graphviz
 *************************************************************************/

#ifndef LIB_COMMON_COMMAND_LINE_H_
#define LIB_COMMON_COMMAND_LINE_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct
{
	FILE* stderr;
	FILE* stdout;
	void (*exit_function)(int);
} gv_cmdline_handling_info;


typedef struct {
	bool print_version;
	bool print_usage;
} gv_common_argument_options;

typedef enum {
	flag,
	named_value
} gv_cmdline_kind;

typedef struct
{
	char flag;
	gv_cmdline_kind kind;
	char* description;
	size_t data_offset;

} gv_cmdline_argument;

gv_cmdline_argument gv_common_arguments[] =
{
	{
		.flag = 'V',
		.description = "Print version and exit",
		.data_offset = offsetof(gv_common_argument_options, print_version)
	},
	{
		.flag = '?',
		.description = "Print usage and exit"
	}
};

#endif /* LIB_COMMON_COMMAND_LINE_H_ */
