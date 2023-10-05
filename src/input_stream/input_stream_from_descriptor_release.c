/**
 * \file src/input_stream/input_stream_from_descriptor_release.c
 *
 * \brief Release an input stream from descriptor instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "input_stream_internal.h"

CPARSE_IMPORT_input_stream_internal;

/**
 * \brief Release an input stream from descriptor instance.
 *
 * \param stream                The input stream instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(input_stream_from_descriptor_release)(
    CPARSE_SYM(input_stream)* stream)
{
    int descriptor_close_retval = STATUS_SUCCESS;
    input_stream_from_descriptor* dstream =
        (input_stream_from_descriptor*)stream;

    /* close the file descriptor. */
    if (dstream->desc >= 0)
    {
        descriptor_close_retval = close(dstream->desc);
        if (descriptor_close_retval < 0)
        {
            descriptor_close_retval =
                ERROR_LIBCPARSE_INPUT_STREAM_DESCRIPTOR_CLOSE;
        }
    }

    /* clear the structure. */
    memset(dstream, 0, sizeof(*dstream));

    /* release the structure. */
    free(dstream);

    return descriptor_close_retval;
}
