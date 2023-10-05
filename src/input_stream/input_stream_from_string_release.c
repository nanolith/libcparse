/**
 * \file src/input_stream/input_stream_from_string_release.c
 *
 * \brief Release an input stream from string instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "input_stream_internal.h"

CPARSE_IMPORT_input_stream_internal;

/**
 * \brief Release an input stream from string instance.
 *
 * \param stream                The input stream instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(input_stream_from_string_release)(
    CPARSE_SYM(input_stream)* stream)
{
    input_stream_from_string* sstream = (input_stream_from_string*)stream;

    /* clear and free the string memory. */
    if (NULL != sstream->str)
    {
        memset(sstream->str, 0, sstream->max);
        free(sstream->str);
    }

    /* clear the instance. */
    memset(sstream, 0, sizeof(*sstream));

    /* free the instance. */
    free(sstream);

    return STATUS_SUCCESS;
}
