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

/**
 * This struct contains the possible options and values that are passed as
 * arguments on the command line. To initialize this struct with the proper
 * default values set, use initialize_gv_config().
 */
typedef struct {
	bool print_version;
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


#endif /* LIB_COMMON_COMMAND_LINE_H_ */
