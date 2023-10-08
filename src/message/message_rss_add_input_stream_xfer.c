/**
 * \file src/message/message_rss_add_input_stream_xfer.c
 *
 * \brief Transfer ownership of the \ref input_stream from the message to
 * caller.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message/raw_stack_scanner.h>
#include <libcparse/status_codes.h>
#include <stddef.h>

/**
 * \brief Transfer the \ref input_stream associated with this message to the
 * caller, transferring ownership of this stream to the caller as well.
 *
 * \param stream            Pointer to the \ref input_stream pointer to hold
 *                          this stream on success.
 * \param msg               The message for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_rss_add_input_stream_xfer)(
    CPARSE_SYM(input_stream)** stream,
    CPARSE_SYM(message_rss_add_input_stream)* msg)
{
    int retval;

    /* verify that the stream is valid. */
    if (NULL == msg->stream)
    {
        retval = ERROR_LIBCPARSE_RSS_MESSAGE_INPUT_STREAM_NULL;
        goto done;
    }

    /* transfer the stream. */
    *stream = msg->stream;
    msg->stream = NULL;
    retval = STATUS_SUCCESS;
    goto done;

done:
    return retval;
}
