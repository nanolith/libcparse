/**
 * \file src/message/message_subscribe_event_handler_get.c
 *
 * \brief Get the \ref event_handler for a \ref message_subscribe instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message/subscription.h>

/**
 * \brief Get the \ref event_handler associated with a \ref message_subscribe
 * instance.
 *
 * \param msg               The message to query.
 *
 * \returns the \ref event_handler associated with this message.
 */
const CPARSE_SYM(event_handler)*
CPARSE_SYM(message_subscribe_event_handler_get)(
    const CPARSE_SYM(message_subscribe)* msg)
{
    return &msg->handler;
}
