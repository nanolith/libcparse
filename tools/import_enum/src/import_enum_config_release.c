/**
 * \file tools/import_enum/src/import_enum_config_release.c
 *
 * \brief Release an \ref import_enum_config instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "import_enum_internal.h"

CPARSE_IMPORT_preprocessor_scanner;

/**
 * \brief Release an import_enum_config instance.
 *
 * \param config        The instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int import_enum_config_release(import_enum_config* config)
{
    int retval = STATUS_SUCCESS;
    int release_retval;

    /* free input filename if set. */
    if (NULL != config->input)
    {
        free(config->input);
    }

    /* free output filename if set. */
    if (NULL != config->output)
    {
        free(config->output);
    }

    /* free enumeration name if set. */
    if (NULL != config->enumeration)
    {
        free(config->enumeration);
    }

    /* close output file if open. */
    if (NULL != config->out)
    {
        release_retval = fclose(config->out);
        if (0 != release_retval)
        {
            retval = ERROR_LIBCPARSE_FILE_CLOSE_ERROR;
        }
    }

    /* Release scanner if created. */
    if (NULL != config->scanner)
    {
        release_retval = preprocessor_scanner_release(config->scanner);
        if (STATUS_SUCCESS != release_retval)
        {
            retval = release_retval;
        }
    }

    /* release enum list if set. */
    if (NULL != config->head)
    {
        release_retval = enum_item_list_release(config->head);
        if (STATUS_SUCCESS != release_retval)
        {
            retval = release_retval;
        }
    }

    /* release the enum name if set. */
    if (NULL != config->enum_name)
    {
        free(config->enum_name);
    }

    free(config);

    return retval;
}
