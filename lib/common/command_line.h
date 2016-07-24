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

#include <stdio.h>

/**
 * This struct can be used to pass information about which stream to use for
 * output and error reporting and which function to call when the program needs
 * to exit.
 */
typedef struct gv_stream_and_exit_info {
	/** The stream to use for default output and printing, often stdout. */
	FILE* output_stream;
	/** The stream to use for error reporting, often stderr. */
	FILE* error_stream;
	/** The address of the function to call when requesting the exit of the
	 *  program, often the address of exit(). */
	void (*exit_function)(int);
} gv_stream_and_exit_info;

#endif /* LIB_COMMON_COMMAND_LINE_H_ */
