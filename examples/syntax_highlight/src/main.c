/**
 * \file examples/syntax_highlight/src/main.c
 *
 * \brief Main entry point for the syntax_highlight example command.
 *
 * syntax_highlight transforms an input file into an HTML output file that
 * includes CSS markup for syntax highlighting.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stdio.h>

#include "syntax_highlight_internal.h"

static void log_config(const syntax_highlight_config* config);

/**
 * \brief Main entry point for comment_strip.
 *
 * \param argc              The argument count.
 * \param argv              The argument vector.
 *
 * \returns 0 on success and non-zero on failure.
 */
int main(int argc, char* argv[])
{
    int retval, release_retval;
    syntax_highlight_config* config = NULL;

    /* read command-line options. */
    retval = syntax_highlight_config_create(&config, &argc, &argv);
    if (STATUS_SUCCESS != retval)
    {
        retval = 1;
        goto done;
    }

    log_config(config);

    fprintf(stderr, "Not yet implemented.\n");
    retval = 1;
    goto cleanup;

cleanup:
    release_retval = syntax_highlight_config_release(config);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}

/**
 * \brief Log config values to stderr.
 *
 * \params config       The config to log.
 */
static void log_config(const syntax_highlight_config* config)
{
    fprintf(stderr, "Input file: %s\n", config->input);
    fprintf(stderr, "Output file: %s\n", config->output);

    if (0 != config->snip_begin)
    {
        fprintf(stderr, "Snip begin: %ld\n", config->snip_begin);
        fprintf(stderr, "Snip end: %ld\n", config->snip_end);
    }
}
