/**
 * \file src/message_type/message_type_valid_subscription_type.c
 *
 * \brief Determine whether a given message type is a subscription message type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message_type.h>

/**
 * \brief Verify that a message type is a valid subscription type.
 *
 * \param msg_type                  The message type to check.
 *
 * \returns true if this is a subscription message type, or false otherwise.
 */
bool CPARSE_SYM(message_type_valid_subscription_type)(int msg_type)
{
    switch (msg_type)
    {
        /* valid message types. */
        case CPARSE_MESSAGE_TYPE_RSS_SUBSCRIBE:
        case CPARSE_MESSAGE_TYPE_RFLO_SUBSCRIBE:
        case CPARSE_MESSAGE_TYPE_COMMENT_SCANNER_SUBSCRIBE:
        case CPARSE_MESSAGE_TYPE_COMMENT_FILTER_SUBSCRIBE:
        case CPARSE_MESSAGE_TYPE_LINE_WRAP_FILTER_SUBSCRIBE:
        case CPARSE_MESSAGE_TYPE_NEWLINE_PRESERVING_WHITESPACE_FILTER_SUBSCRIBE:
            return true;

        default:
            return false;
    }
}
