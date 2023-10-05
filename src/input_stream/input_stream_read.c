/**
 * \file src/input_stream/input_stream_read.c
 *
 * \brief Read a character from the \ref input_stream instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "input_stream_internal.h"

/**
 * \brief Read a character from the input stream.
 *
 * \param stream                    The input stream from which this character
 *                                  is read.
 * \param ch                        Pointer to be populated with the character
 *                                  read on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - ERROR_LIBCPARSE_INPUT_STREAM_EOF on EOF.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(input_stream_read)(CPARSE_SYM(input_stream)* stream, int* ch)
{
    return stream->input_stream_read_fn(stream, ch);
}
