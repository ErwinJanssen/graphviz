/* $Id$ $Revision$ */

/*************************************************************************
 * Copyright (c) 2011 AT&T Intellectual Property
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors: See CVS logs. Details at http://www.graphviz.org/
 *************************************************************************/

/*
 * Written by Erwin Janssen
 */

#include "usage.h"

#include "arguments.h"

static char *usageFmt =
		"Usage: %s [-Vv?] [-(GNE)name=val] [-(KTlso)<val>] <dot files>\n";

static char *genericItems =
		"\n\
 -V          - Print version and exit\n\
 -v          - Enable verbose mode \n\
 -Gname=val  - Set graph attribute 'name' to 'val'\n\
 -Nname=val  - Set node attribute 'name' to 'val'\n\
 -Ename=val  - Set edge attribute 'name' to 'val'\n\
 -Tv         - Set output format to 'v'\n\
 -Kv         - Set layout engine to 'v' (overrides default based on command name)\n\
 -lv         - Use external library 'v'\n\
 -ofile      - Write output to 'file'\n\
 -O          - Automatically generate an output filename based on the input filename with a .'format' appended. (Causes all -ofile options to be ignored.) \n\
 -P          - Internally generate a graph of the current plugins. \n\
 -q[l]       - Set level of message suppression (=1)\n\
 -s[v]       - Scale input by 'v' (=72)\n\
 -y          - Invert y coordinate in output\n";

static char *neatoFlags = "(additional options for neato)    [-x] [-n<v>]\n";
static char *neatoItems =
		"\n\
 -n[v]       - No layout mode 'v' (=1)\n\
 -x          - Reduce graph\n";

static char *fdpFlags =
		"(additional options for fdp)      [-L(gO)] [-L(nUCT)<val>]\n";
static char *fdpItems =
		"\n\
 -Lg         - Don't use grid\n\
 -LO         - Use old attractive force\n\
 -Ln<i>      - Set number of iterations to i\n\
 -LU<i>      - Set unscaled factor to i\n\
 -LC<v>      - Set overlap expansion factor to v\n\
 -LT[*]<v>   - Set temperature (temperature factor) to v\n";

static char *memtestFlags = "(additional options for memtest)  [-m<v>]\n";
static char *memtestItems =
		"\n\
 -m          - Memory test (Observe no growth with top. Kill when done.)\n\
 -m[v]       - Memory test - v iterations.\n";

static char *configFlags = "(additional options for config)  [-cv]\n";
static char *configItems =
		"\n\
 -c          - Configure plugins (Writes $prefix/lib/graphviz/config \n\
               with available plugin information.  Needs write privilege.)\n\
 -?          - Print usage and exit\n";

void print_graphviz_usage(void)
{
	print_graphviz_usage_to_stream(stdout);
}

void print_graphviz_usage_to_stream(FILE* stream)
{
	print_graphviz_version_to_stream(stream);
	fprintf(stream, usageFmt, "dot");
	fputs(neatoFlags, stream);
	fputs(fdpFlags, stream);
	fputs(memtestFlags, stream);
	fputs(configFlags, stream);
	fputs(genericItems, stream);
	fputs(neatoItems, stream);
	fputs(fdpItems, stream);
	fputs(memtestItems, stream);
	fputs(configItems, stream);
}
