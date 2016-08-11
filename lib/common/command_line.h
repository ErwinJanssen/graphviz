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
#include <stdint.h>
#include <string.h>

#include "gvc.h"

/**
 * This struct contains the possible options and values that are passed as
 * arguments on the command line. To initialize this struct with the proper
 * default values set, use initialize_gv_config().
 */
typedef struct
{
	bool print_version;
	bool print_usage;
	char* invalid_flags_without_value;
} gv_config;

/**
 * Enum for the different types of flags supported by the command line
 */
typedef enum
{
	ARGUMENT_WITH_VALUE, ARGUMENT_WITHOUT_VALUE,
} gv_argument_type;

/**
 * This struct describes a command line arguments accepted by Graphviz.
 * The field offset is the position of the variable in the gv_config that is
 * affected by this argument.
 */
typedef struct
{
	char flag;
	gv_argument_type argument_type;
	char* description;
	size_t field_offset;
} gv_cmdline_argument;

/**
 * A list containing information about the common command line arguments.
 * Its length is computed by gv_common_arguments_length().
 */
extern gv_cmdline_argument gv_common_arguments[];

/**
 * Get the length of the gv_common_arguments array.
 */
size_t gv_common_arguments_length(void);

/**
 * This function returns an initialized gv_config struct with all values
 * set to their default value. This function will exit if no memory can be
 * allocated for the struct.
 *
 * - `print_version` set to `false`
 */
gv_config* initialize_gv_config(void);

/**
 * Properly frees the gv_config struct.
 */
void free_gv_config(gv_config** config);

/**
 * Parses the command line arguments and creates a gv_config struct based on
 * the contents of the given arguments. This function will not perform any
 * other action based on the contents of the arguments, this is done by the
 * `gv_process_arguments` function.
 */
gv_config* gv_parse_arguments(int argc, char** argv);

/**
 * Called by `gv_parse_arguments` to parse the flags that do not have
 * a separate value.
 * This function assumes that `flags` starts with a dash and that it is a
 * null terminated string.
 */
void gv_parse_flags_without_value(gv_config* config, char* flags);

/**
 * Processes a gv_config struct and acts upon its contents. If gv_config has
 * `print_version` set, the version will be printed and this function will
 * call exit.
 */
void gv_process_arguments(gv_config* config, GVC_t* gvc);

/**
 * Performs like an ordinary malloc, but perform error handling on the returned
 * pointer. If the pointer is NULL, then exit is called.
 */
void* safe_malloc(size_t size, const char* calling_function);

/**
 * Takes the address to a char*, allocates enough memory for one character
 * and sets this character to '\0'.
 */
void gv_initialize_empty_string(char** target_address);

#endif /* LIB_COMMON_COMMAND_LINE_H_ */
