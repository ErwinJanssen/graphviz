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

#include "command_line_arguments.h"
#include "gvc.h"
#include "utils.h"

/**
 * This struct contains the possible options and values that are passed as
 * arguments on the command line. To initialize this struct with the proper
 * default values set, use initialize_gv_config().
 */
typedef struct
{
    char* command_name;
    bool print_version;
    bool print_usage;
    bool configure;
    bool auto_output_filenames;
    bool reduce;
    bool invert_y;
    bool generate_plugin_graph;
    bool verbose;
    uint32_t verbosity_level;
    bool memory_test;
    uint32_t memory_test_iterations;
    bool message_suppression;
    uint32_t message_suppression_level;
    bool scale_input;
    double scale_input_value;
    char* invalid_flags_without_value;
} gv_config;

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
 * Called by `gv_parse_arguments` to parse an argument that takes a value.
 * Returns true if an argument with a value is found, returns false otherwise.
 */
bool gv_parse_argument_with_value(gv_config* config, int argc, char** argv,
        int* argv_position);

/**
 * Read the value attached to an argument. If the value is in the next argument,
 * increment arg_position by one. If no value is present, return NULL;
 */
char* gv_get_argument_value(int argc, char** argv, int* argv_position);

/**
 * Called by `gv_parse_arguments` to parse the flags that do not have
 * a separate value.
 * This function assumes that `flags` starts with a dash and that it is a
 * null terminated string.
 */
void gv_parse_flags_without_value(gv_config* config, char* flags);

/**
 * This function is called by `gv_parse_flags_without_value` to read the
 * optional integer value attached to flag.
 */
uint32_t gv_read_optional_int_value(char* partial_argument, size_t* i);

/**
 * This function is called by `gv_parse_flags_without_value` to read the
 * optional floating point value attached to flag.
 */
double gv_read_optional_float_value(char* partial_argument, size_t* i);

/**
 * This functions counts the number of digits that make up an unsigned integer.
 */
uint8_t number_of_digits(uint32_t integer);

/**
 * Processes a gv_config struct and acts upon its contents. If gv_config has
 * `print_version` set, the version will be printed and this function will
 * call exit.
 */
void gv_process_arguments(gv_config* config, GVC_t* gvc);

/**
 * Takes the address to a char*, allocates enough memory for one character
 * and sets this character to '\0'.
 */
void gv_initialize_empty_string(char** target_address);

/**
 * Prints the version number of Graphviz to the specified FILE* stream, using
 * the information in gvc.
 */
void gv_print_version(FILE* stream, GVC_t* gvc);

#endif /* LIB_COMMON_COMMAND_LINE_H_ */
