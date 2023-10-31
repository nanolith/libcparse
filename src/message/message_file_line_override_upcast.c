/**
 * \file src/message/message_file_line_override_upcast.c
 *
 * \brief Upcast a \ref message_file_line_override to a \ref message.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message/file_line_override.h>

/**
 * \brief Upcast a \ref message_file_line_override to a \ref message.
 *
 * \param msg               The \ref message_file_line_override to upcast.
 *
 * \returns the \ref message instance for this message.
 */
CPARSE_SYM(message)* CPARSE_SYM(message_file_line_override_upcast)(
    CPARSE_SYM(message_file_line_override)* msg)
{
    return &msg->hdr;
}
