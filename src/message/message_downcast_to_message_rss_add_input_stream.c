/**
 * \file src/message/message_downcast_to_message_rss_add_input_stream.c
 *
 * \brief Attempt to downcast the message instance to the derived type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message/raw_stack_scanner.h>
#include <libcparse/status_codes.h>

CPARSE_IMPORT_message;
CPARSE_IMPORT_message_raw_stack_scanner;

/**
 * \brief Attempt to downcast a \ref message to a
 * \ref message_rss_add_input_stream.
 *
 * \param rss_msg           Pointer to the message pointer to receive the
 *                          downcast instance on success.
 * \param msg               The \ref message pointer to attempt to downcast to
 *                          the derived type.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_downcast_to_message_rss_add_input_stream)(
    CPARSE_SYM(message_rss_add_input_stream)** rss_msg,
    CPARSE_SYM(message)* msg)
{
    /* verify that the message type matches the derived type. */
    if (CPARSE_MESSAGE_TYPE_RSS_ADD_INPUT_STREAM != message_get_type(msg))
    {
        return ERROR_LIBCPARSE_BAD_CAST;
    }

    /* reinterpret cast the message. */
    *rss_msg = (message_rss_add_input_stream*)msg;
    return STATUS_SUCCESS;
}
