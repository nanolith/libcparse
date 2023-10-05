/**
 * \file src/input_stream/input_stream_from_string_read.c
 *
 * \brief Read a character from a string input stream.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>

#include "input_stream_internal.h"

CPARSE_IMPORT_input_stream_internal;

/**
 * \brief Read a character from the input stream from string instance.
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
int CPARSE_SYM(input_stream_from_string_read)(
    CPARSE_SYM(input_stream)* stream, int* ch)
{
    input_stream_from_string* sstream = (input_stream_from_string*)stream;

    /* can we read a character? */
    if (sstream->curr < sstream->max)
    {
        *ch = sstream->str[sstream->curr];
        sstream->curr += 1;
        return STATUS_SUCCESS;
    }
    else
    {
        return ERROR_LIBCPARSE_INPUT_STREAM_EOF;
    }
}
