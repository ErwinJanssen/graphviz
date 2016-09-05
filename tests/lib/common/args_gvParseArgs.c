#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include <stdbool.h>

#include "builddate.h"
#include "cgraph.h"
#include "config.h"
#include "globals.h"
#include "gvc.h"
#include "render.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

lt_symlist_t lt_preloaded_symbols[] = { { 0, 0 } };
extern int GvExitOnUsage;

static char usage_info[] =
        "Usage: dot [-Vv?] [-(GNE)name=val] [-(KTlso)<val>] <dot files>\n"
        "(additional options for neato)    [-x] [-n<v>]\n"
        "(additional options for fdp)      [-L(gO)] [-L(nUCT)<val>]\n"
        "(additional options for memtest)  [-m<v>]\n"
        "(additional options for config)  [-cv]\n"
        "\n"
        " -V          - Print version and exit\n"
        " -v          - Enable verbose mode \n"
        " -Gname=val  - Set graph attribute 'name' to 'val'\n"
        " -Nname=val  - Set node attribute 'name' to 'val'\n"
        " -Ename=val  - Set edge attribute 'name' to 'val'\n"
        " -Tv         - Set output format to 'v'\n"
        " -Kv         - Set layout engine to 'v' (overrides default based on command name)\n"
        " -lv         - Use external library 'v'\n"
        " -ofile      - Write output to 'file'\n"
        " -O          - Automatically generate an output filename based on the input filename with a .'format' appended. (Causes all -ofile options to be ignored.) \n"
        " -P          - Internally generate a graph of the current plugins. \n"
        " -q[l]       - Set level of message suppression (=1)\n"
        " -s[v]       - Scale input by 'v' (=72)\n"
        " -y          - Invert y coordinate in output\n"
        "\n"
        " -n[v]       - No layout mode 'v' (=1)\n"
        " -x          - Reduce graph\n"
        "\n"
        " -Lg         - Don't use grid\n"
        " -LO         - Use old attractive force\n"
        " -Ln<i>      - Set number of iterations to i\n"
        " -LU<i>      - Set unscaled factor to i\n"
        " -LC<v>      - Set overlap expansion factor to v\n"
        " -LT[*]<v>   - Set temperature (temperature factor) to v\n"
        "\n"
        " -m          - Memory test (Observe no growth with top. Kill when done.)\n"
        " -m[v]       - Memory test - v iterations.\n"
        "\n"
        " -c          - Configure plugins (Writes $prefix/lib/graphviz/config \n"
        "               with available plugin information.  Needs write privilege.)\n"
        " -?          - Print usage and exit\n";

/**
 * Exit and output tests for `dot -V`
 */
Test(command_line, dash_V_exit,
        .init = redirect_all_std,
        .exit_code = 0)
{
    GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);
    GvExitOnUsage = 1;
    int argc = 2;
    char* argv[] = { "dot", "-V" };

    gvParseArgs(Gvc, argc, argv);

    // Fail this test if the function above does not call exit.
    cr_assert(false);
}

Test(command_line, dash_V_output,
        .init = redirect_all_std)
{
    GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);
    GvExitOnUsage = 0;
    int argc = 2;
    char* argv[] = { "dot", "-V" };

    gvParseArgs(Gvc, argc, argv);

    char expected_stderr[100];
    sprintf(expected_stderr, "dot - graphviz version %s (%s)\n",
    PACKAGE_VERSION, BUILDDATE);

    cr_assert_stderr_eq_str(expected_stderr);
}

/**
 * Exit and output tests for `dot -Vrandom`
 */
Test(command_line, dash_Vrandom_exit,
        .init = redirect_all_std,
        .exit_code = EXIT_FAILURE)
{
    GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);
    GvExitOnUsage = 1;
    int argc = 2;
    char* argv[] = {"dot", "-Vrandom"};

    gvParseArgs(Gvc, argc, argv);

    // Fail this test if the function above does not call exit.
    cr_assert(false);
}

/**
 * Exit and output tests for `dot -randomV`
 */
Test(command_line, dash_randomV_exit,
        .init = redirect_all_std,
        .exit_code = EXIT_FAILURE)
{
    GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);
    GvExitOnUsage = 1;
    int argc = 2;
    char* argv[] = {"dot", "-randomV"};

    gvParseArgs(Gvc, argc, argv);

    // Fail this test if the function above does not call exit.
    cr_assert(false);
}

/**
 * Exit and output tests for `dot -?V`
 */
Test(command_line, dash_questionmark_V_exit,
        .init = redirect_all_std,
        .exit_code = 0)
{
    GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);
    GvExitOnUsage = 1;
    int argc = 2;
    char* argv[] = {"dot", "-?V"};

    gvParseArgs(Gvc, argc, argv);

    // Fail this test if the function above does not call exit.
    cr_assert(false);
}

Test(command_line, dash_questionmark_V_output,
        .init = redirect_all_std)
{
    GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);
    GvExitOnUsage = 0;
    int argc = 2;
    char* argv[] = {"dot", "-?V"};

    gvParseArgs(Gvc, argc, argv);

    fflush(stdout);
    cr_assert_stdout_eq_str(usage_info);
}

/**
 * Exit and output tests for `dot -V?`
 */
Test(command_line, dash_V_questionmark_exit,
        .init = redirect_all_std,
        .exit_code = 0)
{
    GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);
    GvExitOnUsage = 1;
    int argc = 2;
    char* argv[] = {"dot", "-V?"};

    gvParseArgs(Gvc, argc, argv);

    // Fail this test if the function above does not call exit.
    cr_assert(false);
}

Test(command_line, dash_V_questionmark_output,
        .init = redirect_all_std)
{
    GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);
    GvExitOnUsage = 0;
    int argc = 2;
    char* argv[] = {"dot", "-V?"};

    gvParseArgs(Gvc, argc, argv);

    char expected_stderr[100];
    sprintf(expected_stderr, "dot - graphviz version %s (%s)\n",
                PACKAGE_VERSION, BUILDDATE);

    cr_assert_stderr_eq_str(expected_stderr);
}

Test(command_line, dash_X)
{
    GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);
    GvExitOnUsage = 1;
    int argc = 2;
    char* argv[] = {"dot", "-x"};

    cr_expect_not(Reduce);
    gvParseArgs(Gvc, argc, argv);
    cr_expect(Reduce);
}

Test(command_line, dash_O)
{
    GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);
    GvExitOnUsage = 1;
    int argc = 2;
    char* argv[] = {"dot", "-O"};

    cr_expect_not(Gvc->common.auto_outfile_names);
    gvParseArgs(Gvc, argc, argv);
    cr_expect(Gvc->common.auto_outfile_names);
}

Test(command_line, dash_y)
{
    GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);
    GvExitOnUsage = 1;
    int argc = 2;
    char* argv[] = {"dot", "-y"};

    cr_expect_not(Y_invert);
    gvParseArgs(Gvc, argc, argv);
    cr_expect(Y_invert);
}

Test(command_line, dash_P)
{
    GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);
    GvExitOnUsage = 1;
    int argc = 2;
    char* argv[] = {"dot", "-P"};

    cr_expect_null(P_graph);
    gvParseArgs(Gvc, argc, argv);
    cr_expect_not_null(P_graph);
}

Test(command_line, dash_v)
{
    GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);
    GvExitOnUsage = 1;
    int argc = 2;
    char* argv[] = {"dot", "-v"};

    cr_expect(Gvc->common.verbose == 0);
    cr_expect(Verbose == 0);
    gvParseArgs(Gvc, argc, argv);
    cr_expect(Gvc->common.verbose == 1);
    cr_expect(Verbose == 1);
}

Test(command_line, dash_v3)
{
    GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);
    GvExitOnUsage = 1;
    int argc = 2;
    char* argv[] = {"dot", "-v3"};

    cr_expect(Gvc->common.verbose == 0);
    cr_expect(Verbose == 0);
    gvParseArgs(Gvc, argc, argv);
    cr_expect(Gvc->common.verbose == 3);
    cr_expect(Verbose == 3);
}

Test(command_line, dash_m)
{
    GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);
    GvExitOnUsage = 1;
    int argc = 2;
    char* argv[] = {"dot", "-m"};

    cr_expect(MemTest == 0);
    gvParseArgs(Gvc, argc, argv);
    cr_expect(MemTest == -1);
}

Test(command_line, dash_m5)
{
    GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);
    GvExitOnUsage = 1;
    int argc = 2;
    char* argv[] = {"dot", "-m5"};

    cr_expect(MemTest == 0);
    gvParseArgs(Gvc, argc, argv);
    cr_expect(MemTest == 5);
}

Test(command_line, dash_q)
{
    GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);
    GvExitOnUsage = 1;
    int argc = 2;
    char* argv[] = {"dot", "-q"};

    cr_expect(aggeterr() == AGWARN);
    gvParseArgs(Gvc, argc, argv);
    cr_expect(aggeterr() == AGERR);
}

Test(command_line, dash_q0)
{
    GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);
    GvExitOnUsage = 1;
    int argc = 2;
    char* argv[] = {"dot", "-q0"};

    cr_expect(aggeterr() == AGWARN);
    gvParseArgs(Gvc, argc, argv);
    cr_expect(aggeterr() == AGWARN);
}

Test(command_line, dash_q10)
{
    GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);
    GvExitOnUsage = 1;
    int argc = 2;
    char* argv[] = {"dot", "-q10"};

    cr_expect(aggeterr() == AGWARN);
    gvParseArgs(Gvc, argc, argv);
    cr_expect(aggeterr() == AGMAX);
}

Test(command_line, dash_s)
{
    GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);
    GvExitOnUsage = 1;
    int argc = 2;
    char* argv[] = {"dot", "-s"};

    gvParseArgs(Gvc, argc, argv);
    cr_expect(double_equal(PSinputscale, 72));
}

Test(command_line, dash_s0)
{
    GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);
    GvExitOnUsage = 1;
    int argc = 2;
    char* argv[] = {"dot", "-s0"};

    gvParseArgs(Gvc, argc, argv);
    cr_expect(double_equal(PSinputscale, 72));
}

Test(command_line, dash_s147_dot_234)
{
    GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);
    GvExitOnUsage = 1;
    int argc = 2;
    char* argv[] = {"dot", "-s147.234"};

    gvParseArgs(Gvc, argc, argv);
    cr_expect(double_equal(PSinputscale, 147.234));
}

Test(command_line, dash_X_dash_O)
{
    GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);
    GvExitOnUsage = 1;
    int argc = 3;
    char* argv[] = {"dot", "-x", "-O"};

    cr_expect_not(Reduce);
    cr_expect_not(Gvc->common.auto_outfile_names);
    gvParseArgs(Gvc, argc, argv);
    cr_expect(Reduce);
    cr_expect(Gvc->common.auto_outfile_names);
}

Test(command_line, dash_X_dash_P)
{
    GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);
    GvExitOnUsage = 1;
    int argc = 3;
    char* argv[] = {"dot", "-x", "-P"};

    cr_expect_not(Reduce);
    cr_expect_null(P_graph);
    gvParseArgs(Gvc, argc, argv);
    cr_expect(Reduce);
    cr_expect_not_null(P_graph);
}

Test(command_line, dash_X_dash_y_dash_O)
{
    GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);
    GvExitOnUsage = 1;
    int argc = 4;
    char* argv[] = {"dot", "-x", "-y", "-O"};

    cr_expect_not(Reduce);
    cr_expect_not(Y_invert);
    cr_expect_not(Gvc->common.auto_outfile_names);
    gvParseArgs(Gvc, argc, argv);
    cr_expect(Reduce);
    cr_expect(Y_invert);
    cr_expect(Gvc->common.auto_outfile_names);
}

Test(command_line, dot_dash_xO)
{
    GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);
    GvExitOnUsage = 1;
    int argc = 2;
    char* argv[] = {"dot", "-xO"};

    cr_expect_not(Reduce);
    cr_expect_not(Gvc->common.auto_outfile_names);
    gvParseArgs(Gvc, argc, argv);
    cr_expect(Reduce);
    cr_expect(Gvc->common.auto_outfile_names);
    cr_expect_str_eq(Gvc->common.cmdname, "dot");
    cr_expect_str_eq(CmdName, "dot");
}

Test(command_line, neato_dash_xOs15_dot_76y)
{
    GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);
    GvExitOnUsage = 1;
    int argc = 2;
    char* argv[] = {"neato", "-xOs15.76y"};

    cr_expect_not(Reduce);
    cr_expect_not(Y_invert);
    cr_expect_not(Gvc->common.auto_outfile_names);
    gvParseArgs(Gvc, argc, argv);
    cr_expect(Reduce);
    cr_expect(Y_invert);
    cr_expect(Gvc->common.auto_outfile_names);
    cr_expect_str_eq(Gvc->common.cmdname, "neato");
    cr_expect_str_eq(CmdName, "neato");
    cr_expect(double_equal(PSinputscale, 15.76));
}

Test(command_line, dash_xOP)
{
    GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);
    GvExitOnUsage = 1;
    int argc = 2;
    char* argv[] = {"dot", "-xOP"};

    cr_expect_not(Reduce);
    cr_expect_not(Gvc->common.auto_outfile_names);
    cr_expect_null(P_graph);
    gvParseArgs(Gvc, argc, argv);
    cr_expect(Reduce);
    cr_expect(Gvc->common.auto_outfile_names);
    cr_expect_not_null(P_graph);
}

Test(command_line, dash_xv3OPv2)
{
    GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);
    GvExitOnUsage = 1;
    int argc = 2;
    char* argv[] = {"dot", "-xv3OPv2"};

    cr_expect_not(Reduce);
    cr_expect_not(Gvc->common.auto_outfile_names);
    cr_expect_null(P_graph);
    cr_expect(Gvc->common.verbose == 0);
    cr_expect(Verbose == 0);
    gvParseArgs(Gvc, argc, argv);
    cr_expect(Reduce);
    cr_expect(Gvc->common.auto_outfile_names);
    cr_expect_not_null(P_graph);
    cr_expect(Gvc->common.verbose == 3);
    cr_expect(Verbose == 3);
}

Test(command_line, dash_xm3OPqm2)
{
    GVC_t *Gvc = gvContextPlugins(lt_preloaded_symbols, DEMAND_LOADING);
    GvExitOnUsage = 1;
    int argc = 2;
    char* argv[] = {"dot", "-xm3OPqm2"};

    cr_expect_not(Reduce);
    cr_expect_not(Gvc->common.auto_outfile_names);
    cr_expect_null(P_graph);
    cr_expect(MemTest == 0);
    cr_expect(aggeterr() == AGWARN);
    gvParseArgs(Gvc, argc, argv);
    cr_expect(Reduce);
    cr_expect(Gvc->common.auto_outfile_names);
    cr_expect_not_null(P_graph);
    cr_expect(MemTest == 3);
    cr_expect(aggeterr() == AGERR);
}
