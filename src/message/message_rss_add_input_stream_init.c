/**
 * \file src/message/message_rss_add_input_stream_init.c
 *
 * \brief Init method for the \ref message_rss_add_input_stream_init type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message/raw_stack_scanner.h>
#include <libcparse/status_codes.h>
#include <string.h>

#include "message_internal.h"

CPARSE_IMPORT_message_internal;

/**
 * \brief Initialize a \ref message_rss_add_input_stream.
 *
 * \note On a successful send of this message, ownership of this input stream is
 * transferred to the accepting message handler.
 *
 * \param msg               The message to initialize.
 * \param name              The name of the stream, used for cursor reporting.
 * \param stream            The input stream to send to the
 *                          \ref raw_stack_scanner.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_rss_add_input_stream_init)(
    CPARSE_SYM(message_rss_add_input_stream)* msg, const char* name,
    CPARSE_SYM(input_stream)* stream)
{
    int retval;

    /* clear the message buffer. */
    memset(msg, 0, sizeof(*msg));

    /* initialize the base message. */
    retval = message_init(&msg->hdr, CPARSE_MESSAGE_TYPE_RSS_ADD_INPUT_STREAM);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* copy the name. */
    msg->name = strdup(name);
    if (NULL == msg->name)
    {
        retval = ERROR_LIBCPARSE_OUT_OF_MEMORY;
        goto done;
    }

    /* success: take ownership of the stream. */
    retval = STATUS_SUCCESS;
    msg->stream = stream;
    goto done;

done:
    return retval;
}
