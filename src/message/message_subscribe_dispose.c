/**
 * \file src/message/message_subscribe_dispose.c
 *
 * \brief Dispose method for the \ref message_subscribe type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message/subscription.h>
#include <libcparse/status_codes.h>
#include <string.h>

CPARSE_IMPORT_event_handler;
CPARSE_IMPORT_message;

/**
 * \brief Dispose of a \ref message_subscribe instance.
 *
 * \param msg               The message to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_subscribe_dispose)(CPARSE_SYM(message_subscribe)* msg)
{
    int message_dispose_retval = STATUS_SUCCESS;
    int event_handler_dispose_retval = STATUS_SUCCESS;

    /* dispose the base message. */
    message_dispose_retval = message_dispose(&msg->hdr);

    /* dispose the event handler. */
    event_handler_dispose_retval = event_handler_dispose(&msg->handler);

    /* clear instance data. */
    memset(msg, 0, sizeof(*msg));

    /* decode return value. */
    if (STATUS_SUCCESS != message_dispose_retval)
    {
        return message_dispose_retval;
    }
    else
    {
        return event_handler_dispose_retval;
    }
}
