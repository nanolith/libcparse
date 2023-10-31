/**
 * \file src/message/message_file_line_override_file_get.c
 *
 * \brief Getter for line field in \ref message_file_line_override.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message/file_line_override.h>

/**
 * \brief Get the \ref line associated with a \ref message_file_line_override
 * instance.
 *
 * \param msg               The message to query.
 *
 * \returns the \ref line associated with this message.
 */
unsigned int
CPARSE_SYM(message_file_line_override_line_get)(
    const CPARSE_SYM(message_file_line_override)* msg)
{
    return msg->line;
}
