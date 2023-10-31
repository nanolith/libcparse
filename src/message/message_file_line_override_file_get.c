/**
 * \file src/message/message_file_line_override_file_get.c
 *
 * \brief Getter for file field in \ref message_file_line_override.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message/file_line_override.h>
#include <libcparse/status_codes.h>

/**
 * \brief Get the \ref file associated with a \ref message_file_line_override
 * instance.
 *
 * \param msg               The message to query.
 *
 * \returns the \ref file associated with this message or NULL if unset.
 */
const char*
CPARSE_SYM(message_file_line_override_file_get)(
    const CPARSE_SYM(message_file_line_override)* msg)
{
    return msg->file;
}
