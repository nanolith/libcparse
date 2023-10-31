/**
 * \file src/message/message_downcast_to_message_file_line_override.c
 *
 * \brief Downcast a \ref message to a \ref message_file_line_override.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message/file_line_override.h>
#include <libcparse/status_codes.h>

CPARSE_IMPORT_message;
CPARSE_IMPORT_message_file_line_override;

/**
 * \brief Attempt to downcast a \ref message to a
 * \ref message_file_line_override.
 *
 * \param flo_msg           Pointer to the message pointer to receive the
 *                          downcast instance on success.
 * \param msg               The \ref message pointer to attempt to downcast to
 *                          the derived type.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_downcast_to_message_file_line_override)(
    CPARSE_SYM(message_file_line_override)** flo_msg, CPARSE_SYM(message)* msg)
{
    /* verify that this message is the correct type. */
    if (CPARSE_MESSAGE_TYPE_RFLO_FILE_LINE_OVERRIDE != message_get_type(msg))
    {
        return ERROR_LIBCPARSE_BAD_CAST;
    }

    /* reinterpret cast this message. */
    *flo_msg = (message_file_line_override*)msg;
    return STATUS_SUCCESS;
}
