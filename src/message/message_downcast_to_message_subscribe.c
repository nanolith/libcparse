/**
 * \file src/message/message_downcast_to_message_subscribe.c
 *
 * \brief Attempt to downcast the message instance to the derived type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message/subscription.h>
#include <libcparse/status_codes.h>

CPARSE_IMPORT_message;
CPARSE_IMPORT_message_subscription;
CPARSE_IMPORT_message_type;

/**
 * \brief Attempt to downcast a \ref message to a
 * \ref message_subscribe.
 *
 * \param sub_msg           Pointer to the message pointer to receive the
 *                          downcast instance on success.
 * \param msg               The \ref message pointer to attempt to downcast to
 *                          the derived type.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_downcast_to_message_subscribe)(
    CPARSE_SYM(message_subscribe)** sub_msg, CPARSE_SYM(message)* msg)
{
    /* verify that message type matches a valid subscription message type. */
    if (!message_type_valid_subscription_type(message_get_type(msg)))
    {
        return ERROR_LIBCPARSE_BAD_CAST;
    }

    /* reinterpret cast the message. */
    *sub_msg = (message_subscribe*)msg;
    return STATUS_SUCCESS;
}
