/**
 * \file src/message/message_rss_add_input_stream_dispose.c
 *
 * \brief Dispose method for the \ref message_rss_add_input_stream_init type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/input_stream.h>
#include <libcparse/message/raw_stack_scanner.h>
#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

CPARSE_IMPORT_input_stream;
CPARSE_IMPORT_message;

/**
 * \brief Dispose of a \ref message_rss_add_input_stream message.
 *
 * \param msg               The message to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_rss_add_input_stream_dispose)(
    CPARSE_SYM(message_rss_add_input_stream)* msg)
{
    int base_dispose_retval = STATUS_SUCCESS;
    int input_stream_release_retval = STATUS_SUCCESS;

    /* release the input stream if set. */
    if (NULL != msg->stream)
    {
        input_stream_release_retval = input_stream_release(msg->stream);
    }

    /* free the name if set. */
    if (NULL != msg->name)
    {
        memset(msg->name, 0, strlen(msg->name));
        free(msg->name);
    }

    /* dispose base structure. */
    base_dispose_retval = message_dispose(&msg->hdr);

    /* clear structure. */
    memset(msg, 0, sizeof(*msg));

    /* decode return value. */
    if (STATUS_SUCCESS != input_stream_release_retval)
    {
        return input_stream_release_retval;
    }
    else
    {
        return base_dispose_retval;
    }
}
