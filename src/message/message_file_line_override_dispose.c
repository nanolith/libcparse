/**
 * \file src/message/message_file_line_override_dispose.c
 *
 * \brief Dispose method for the \ref message_file_line_override type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message/file_line_override.h>
#include <libcparse/status_codes.h>
#include <libcparse/string_utils.h>
#include <stdlib.h>
#include <string.h>

#include "message_internal.h"

CPARSE_IMPORT_message_internal;
CPARSE_IMPORT_string_utils;

/**
 * \brief Dispose of a \ref message_file_line_override instance.
 *
 * \param msg               The message to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_file_line_override_dispose)(
    CPARSE_SYM(message_file_line_override)* msg)
{
    int message_dispose_retval = STATUS_SUCCESS;

    /* clean up the file if set. */
    if (NULL != msg->file)
    {
        string_utils_string_release(msg->file);
    }

    /* dispose the message header. */
    message_dispose_retval = message_dispose(&msg->hdr);

    /* clear structure. */
    memset(msg, 0, sizeof(*msg));

    /* decode return value. */
    return message_dispose_retval;
}
