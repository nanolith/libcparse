/**
 * \file src/message/message_rss_add_input_stream_filename_get.c
 *
 * \brief Get the filename associated with the given message.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message/raw_stack_scanner.h>

/**
 * \brief Get the filename associated with a \ref message_rss_add_input_stream
 * instance.
 *
 * \param msg               The message to query.
 *
 * \returns the filename associated with this message.
 */
const char* CPARSE_SYM(message_rss_add_input_stream_filename_get)(
    const CPARSE_SYM(message_rss_add_input_stream)* msg)
{
    return msg->name;
}
