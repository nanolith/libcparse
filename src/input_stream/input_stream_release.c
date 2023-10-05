/**
 * \file src/input_stream/input_stream_release.c
 *
 * \brief Release an \ref input_stream instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "input_stream_internal.h"

/**
 * \brief Release an input stream instance, releasing any internal resources it
 * may own.
 *
 * \param stream                The input stream instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(input_stream_release)(CPARSE_SYM(input_stream)* stream)
{
    return stream->input_stream_release_fn(stream);
}
