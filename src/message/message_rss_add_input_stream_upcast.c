/**
 * \file src/message/message_rss_add_input_stream_upcast.c
 *
 * \brief Upcast derived type to base type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message/raw_stack_scanner.h>

/**
 * \brief Upcast a \ref message_rss_add_input_stream to a \ref message.
 *
 * \param msg               The \ref message_rss_add_input_stream to upcast.
 *
 * \returns the \ref message instance for this message.
 */
CPARSE_SYM(message)* CPARSE_SYM(message_rss_add_input_stream_upcast)(
    CPARSE_SYM(message_rss_add_input_stream)* msg)
{
    return &msg->hdr;
}
