/**
 * \file examples/slowcat/src/main.c
 *
 * \brief Main entry point for the slowcat example command.
 *
 * slowcat works just like Unix cat, except using the raw_stack_scanner. It's
 * much slower than cat.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <stdio.h>

/**
 * \brief Main entry point for slowcat.
 *
 * \param argc              The argument count.
 * \param argv              The argument vector.
 *
 * \returns 0 on success and non-zero on failure.
 */
int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    printf("Not yet implemented.\n");

    return 0;
}
