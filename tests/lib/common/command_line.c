#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdbool.h>
#include <stdio.h>



#include "command_line.h"
#include "gvc.h"
#include "gvplugin.h"

bool function_called;

void exit_function(int exit_value)
{
	function_called = true;
}

lt_symlist_t lt_preloaded_symbols[] = { { 0, 0 } };

GvExitOnUsage = 1;

Test(test, success, .exit_code = 0)
{
	GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);

	gv_stream_and_exit_info stream_and_exit_info = {
		.output_stream = stdout,
		.error_stream = stderr,
		.exit_function = &exit_function
	};

	int argc = 2;
	char* argv[] = {"dot", "-V"};
	printf("Before call to dotneato_args_initialize\n");
	fflush(stdout);
	dotneato_args_initialize(Gvc, argc, argv, stream_and_exit_info);
	printf("After call to dotneato_args_initialize\n");
	fflush(stdout);
    cr_assert(1);
}
