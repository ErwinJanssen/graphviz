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

gv_config* initialize_gv_config(void)
{
	gv_config* default_gv_config = malloc(sizeof(gv_config));
	if(!default_gv_config)
	{
		fprintf(stderr, "Error: Not enough memory could be allocated for "
				"gv_config in function '%s'.\n", __FUNCTION__);
		exit(EXIT_FAILURE);
	}
	default_gv_config->print_version = false;
	return default_gv_config;
}

void free_gv_config(gv_config** config)
{
	free(*config);
	*config = NULL;
}
