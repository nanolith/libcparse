/**
 * \file src/message/message_subscribe_init_for_line_wrap_filter.c
 *
 * \brief \ref message_subscribe type init method for line wrap filter
 * subscriptions.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "message_subscription_internal.h"

CPARSE_IMPORT_message_subscription_internal;

/**
 * \brief Initialize a \ref message_subscribe instance for subscribing to the
 * line wrap filter.
 *
 * \param msg               The message to initialize.
 * \param handler           The \ref event_handler to add to this endpoint.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_subscribe_init_for_line_wrap_filter)(
    CPARSE_SYM(message_subscribe)* msg, CPARSE_SYM(event_handler)* handler)
{
    return
        message_subscribe_init(
            msg, CPARSE_MESSAGE_TYPE_LINE_WRAP_FILTER_SUBSCRIBE, handler);
}
