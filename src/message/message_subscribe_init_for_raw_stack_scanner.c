/**
 * \file src/message/message_subscribe_init_for_raw_stack_scanner.c
 *
 * \brief \ref message_subscribe type init method for raw stack scanner
 * subscriptions.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message/subscription.h>

CPARSE_IMPORT_message_subscription;

/**
 * \brief Initialize a \ref message_subscribe instance for subscribing to the
 * raw stack scanner.
 *
 * \param msg               The message to initialize.
 * \param handler           The \ref event_handler to add to this endpoint.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_subscribe_init_for_raw_stack_scanner)(
    CPARSE_SYM(message_subscribe)* msg, CPARSE_SYM(event_handler)* handler)
{
    return
        message_subscribe_init(msg, CPARSE_MESSAGE_TYPE_RSS_SUBSCRIBE, handler);
}
