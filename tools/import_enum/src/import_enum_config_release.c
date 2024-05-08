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
    if (NULL != config->input)
    {
        free(config->input);
    }

    if (NULL != config->output)
    {
        free(config->output);
    }

    if (NULL != config->enumeration)
    {
        free(config->enumeration);
    }

    free(config);

    return STATUS_SUCCESS;
}
