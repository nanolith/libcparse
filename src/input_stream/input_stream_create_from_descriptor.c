/**
 * \file src/input_stream/input_stream_create_from_descriptor.c
 *
 * \brief Create an input stream from a descriptor.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "input_stream_internal.h"

CPARSE_IMPORT_input_stream;
CPARSE_IMPORT_input_stream_internal;

/**
 * \brief Create an input stream instance from a Unix file descriptor.
 *
 * \note This allocates the instance, storing the result in \p stream. This is a
 * resource that must be released by calling \ref input_stream_release when it
 * is no longer needed. This stream takes ownership of the Unix file descriptor
 * provided in \p desc and will close it when it is released.
 *
 * \param stream                Pointer to the \ref input_stream pointer to be
 *                              populated with the created input stream on
 *                              success.
 * \param desc                  The Unix file descriptor for this stream.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(input_stream_create_from_descriptor)(
    CPARSE_SYM(input_stream)** stream, int desc)
{
    int retval;
    input_stream_from_descriptor* tmp = NULL;

    /* allocate memory for the input stream. */
    tmp = (input_stream_from_descriptor*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = ERROR_LIBCPARSE_OUT_OF_MEMORY;
        goto done;
    }

    /* clear instance. */
    memset(tmp, 0, sizeof(*tmp));

    /* set instance data. */
    tmp->hdr.input_stream_release_fn = &input_stream_from_descriptor_release;
    tmp->hdr.input_stream_read_fn = &input_stream_from_descriptor_read;
    tmp->desc = desc;

    /* success. */
    retval = STATUS_SUCCESS;
    *stream = &tmp->hdr;
    goto done;

done:
    return retval;
}
