/**
 * \file src/message/message_subscribe_upcast.c
 *
 * \brief Upcast derived type to base type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message/subscription.h>

/**
 * \brief Upcast a \ref message_subscribe to a \ref message.
 *
 * \param msg               The \ref message_subscribe to upcast.
 *
 * \returns the \ref message instance for this message.
 */
CPARSE_SYM(message)* CPARSE_SYM(message_subscribe_upcast)(
    CPARSE_SYM(message_subscribe)* msg)
{
    return &msg->hdr;
}
