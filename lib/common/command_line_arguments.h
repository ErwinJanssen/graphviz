/*************************************************************************
 * This program and the accompanying materials are made available under
 * the terms of the Eclipse Public License v1.0 which accompanies this
 * distribution, and is available at:
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors: See version control history
 * Details at https://github.com/ellson/graphviz
 *************************************************************************/

#ifndef LIB_COMMON_COMMAND_LINE_ARGUMENTS_H_
#define LIB_COMMON_COMMAND_LINE_ARGUMENTS_H_

#include "command_line.h"

/**
 * Enum for the different types of flags supported by the command line
 */
typedef enum
{
    ARGUMENT_WITHOUT_VALUE,
    ARGUMENT_WITH_OPTIONAL_VALUE,
    ARGUMENT_WITH_SINGLE_VALUE,
    ARGUMENT_WITH_MULTIPLE_VALUES
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
    size_t field_offset_optional_value;
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

#endif /* LIB_COMMON_COMMAND_LINE_ARGUMENTS_H_ */
