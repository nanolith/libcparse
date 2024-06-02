/**
 * \file exmaples/syntax_highlight/src/syntax_highlight_config_release.c
 *
 * \brief Release a \ref syntax_highlight_config instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/preprocessor_scanner.h>
#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <stdio.h>

#include "syntax_highlight_internal.h"

CPARSE_IMPORT_preprocessor_scanner;

/**
 * \brief Release a syntax_highlight_config instance.
 *
 * \param config        The instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int syntax_highlight_config_release(syntax_highlight_config* config)
{
    int retval = STATUS_SUCCESS;
    int release_retval;

    /* free input if set. */
    if (NULL != config->input)
    {
        free(config->input);
    }

    /* free output if set. */
    if (NULL != config->output)
    {
        free(config->output);
    }

    /* release scanner if set. */
    if (NULL != config->scanner)
    {
        release_retval = preprocessor_scanner_release(config->scanner);
        if (STATUS_SUCCESS != release_retval)
        {
            retval = release_retval;
        }
    }

    /* free input_string if set. */
    if (NULL != config->input_string)
    {
        free(config->input_string);
    }

    /* close out if open. */
    if (NULL != config->out)
    {
        fclose(config->out);
    }

    /* release the list if set. */
    if (NULL != config->head)
    {
        release_retval = source_list_release(config->head);
        if (STATUS_SUCCESS != release_retval)
        {
            retval = release_retval;
        }
    }

    /* release the lines array if set. */
    if (NULL != config->lines)
    {
        free(config->lines);
    }

    /* free the config. */
    free(config);

    /* return the decoded status. */
    return retval;
}
