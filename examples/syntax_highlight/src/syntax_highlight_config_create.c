/**
 * \file exmaples/syntax_highlight/src/syntax_highlight_config_create.c
 *
 * \brief Create a \ref syntax_highlight_config instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "syntax_highlight_internal.h"

/**
 * \brief Read command-line options, creating a syntax_highlight_config instance
 * on success.
 *
 * \param config        Pointer to the config pointer to populate with the
 *                      created config on success.
 * \param argc          Pointer to argc, to be updated on success.
 * \param argv          Pointer to argv, to be updated on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int syntax_highlight_config_create(
    syntax_highlight_config** config, int* argc, char*** argv)
{
    int retval, release_retval, ch;
    syntax_highlight_config* tmp = NULL;
    char* invalid_char = NULL;
    bool snip_begin_populated = false;
    bool snip_end_populated = false;

    /* allocate memory for this instance. */
    tmp = (syntax_highlight_config*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = ERROR_LIBCPARSE_OUT_OF_MEMORY;
        goto done;
    }

    /* clear this memory. */
    memset(tmp, 0, sizeof(*tmp));

    /* read options. */
    while ((ch = getopt(*argc, *argv, "i:o:b:e:d")) != -1)
    {
        switch (ch)
        {
            case 'i':
                if (NULL != tmp->input)
                    free(tmp->input);

                tmp->input = strdup(optarg);
                break;

            case 'o':
                if (NULL != tmp->output)
                    free(tmp->output);

                tmp->output = strdup(optarg);
                break;

            case 'b':
                tmp->snip_begin = strtol(optarg, &invalid_char, 10);
                if (invalid_char == optarg || 0 != *invalid_char)
                {
                    fprintf(stderr, "invalid number %s\n", optarg);
                    retval = 1;
                    goto cleanup;
                }
                snip_begin_populated = true;
                break;

            case 'e':
                tmp->snip_end = strtol(optarg, &invalid_char, 10);
                if (invalid_char == optarg || 0 != *invalid_char)
                {
                    fprintf(stderr, "invalid number %s\n", optarg);
                    retval = 1;
                    goto cleanup;
                }
                snip_end_populated = true;
                break;

            case 'd':
                tmp->debug = true;
                break;
        }
    }

    /* verify that we have an input file. */
    if (NULL == tmp->input)
    {
        fprintf(stderr, "input file required.\n");
        retval = 1;
        goto cleanup;
    }

    /* verify that we have an output file. */
    if (NULL == tmp->output)
    {
        fprintf(stderr, "output file required.\n");
        retval = 1;
        goto cleanup;
    }

    /* if a snip has been set, verify that both snips are set. */
    if (
            (snip_begin_populated | snip_end_populated)
         && (snip_begin_populated ^ snip_end_populated))
    {
        fprintf(stderr, "both -b and -e must be present if one is.\n");
        retval = 1;
        goto cleanup;
    }

    /* if both snips have been set, verify that begin <= end. */
    if (
            snip_begin_populated && snip_end_populated
         && tmp->snip_begin > tmp->snip_end)
    {
        fprintf(stderr, "-b must be less than or equal to -e.\n");
        retval = 1;
        goto cleanup;
    }

    /* update argc / argv. */
    *argc -= optind;
    *argv += optind;

    /* success. */
    *config = tmp;
    retval = STATUS_SUCCESS;
    goto done;

cleanup:
    release_retval = syntax_highlight_config_release(tmp);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}
