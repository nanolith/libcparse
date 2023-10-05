/**
 * \file src/input_stream/input_stream_create_from_string.c
 *
 * \brief Create an input stream instance from a string.
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
 * \brief Create an input stream instance from a string.
 *
 * \note This allocates the instance, storing the result in \p stream. This is a
 * resource that must be released by calling \ref input_stream_release when it
 * is no longer needed. This stream copies the given string internally; the
 * string parameter remains owned by the caller.
 *
 * \param stream                Pointer to the \ref input_stream pointer to be
 *                              populated with the created input stream on
 *                              success.
 * \param str                   The string to copy for use as input.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(input_stream_create_from_string)(
    CPARSE_SYM(input_stream)** stream, const char* str)
{
    int retval, release_retval;
    input_stream_from_string* tmp = NULL;

    /* allocate memory for this stream instance. */
    tmp = (input_stream_from_string*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = ERROR_LIBCPARSE_OUT_OF_MEMORY;
        goto done;
    }

    /* clear instance. */
    memset(tmp, 0, sizeof(*tmp));

    /* set instance data. */
    tmp->hdr.input_stream_release_fn = &input_stream_from_string_release;
    tmp->hdr.input_stream_read_fn = &input_stream_from_string_read;
    tmp->curr = 0;
    tmp->max = strlen(str);

    /* duplicate string. */
    tmp->str = strdup(str);
    if (NULL == tmp->str)
    {
        retval = ERROR_LIBCPARSE_OUT_OF_MEMORY;
        goto cleanup_tmp;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    *stream = &tmp->hdr;
    goto done;

cleanup_tmp:
    release_retval = input_stream_from_string_release(&tmp->hdr);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}
