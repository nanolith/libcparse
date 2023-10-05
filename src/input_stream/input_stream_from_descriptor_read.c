/**
 * \file src/input_stream/input_stream_from_descriptor_read.c
 *
 * \brief Read a character from a descriptor input stream.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <unistd.h>

#include "input_stream_internal.h"

CPARSE_IMPORT_input_stream_internal;

/**
 * \brief Read a character from the input stream from descriptor instance.
 *
 * \param stream                The input stream from which this character is
 *                              read.
 * \param ch                    Pointer to be populated with the character read
 *                              on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - ERROR_LIBCPARSE_INPUT_STREAM_EOF on EOF.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(input_stream_from_descriptor_read)(
    CPARSE_SYM(input_stream)* stream, int* ch)
{
    char buf;
    int retval;
    input_stream_from_descriptor* dstream =
        (input_stream_from_descriptor*)stream;

    /* attempt to read a character. */
    retval = read(dstream->desc, &buf, sizeof(buf));
    if (retval < 0)
    {
        retval = ERROR_LIBCPARSE_INPUT_STREAM_READ_ERROR;
        goto done;
    }
    else if (0 == retval)
    {
        retval = ERROR_LIBCPARSE_INPUT_STREAM_EOF;
        goto done;
    }

    /* success. */
    *ch = buf;
    retval = STATUS_SUCCESS;
    goto done;

done:
    return retval;
}
