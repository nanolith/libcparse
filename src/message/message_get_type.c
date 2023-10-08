/**
 * \file src/message/message_get_type.c
 *
 * \brief Message type getter.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message.h>

/**
 * \brief Get the message type for the given message.
 *
 * \param msg                   The message to query.
 *
 * \returns the \ref event_type for this event.
 */
int CPARSE_SYM(message_get_type)(const CPARSE_SYM(message)* msg)
{
    return msg->msg_type;
}
