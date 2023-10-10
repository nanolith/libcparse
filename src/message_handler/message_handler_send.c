/**
 * \file src/message_handler/message_handler_send.c
 *
 * \brief Send a \ref message to this \ref message_handler instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message_handler.h>

/**
 * \brief Send a message to the given message handler.
 *
 * \param mh                    The message handler to receive this message.
 * \param msg                   The message to send.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_handler_send)(
    CPARSE_SYM(message_handler)* mh, const CPARSE_SYM(message)* msg)
{
    return mh->message_callback(mh->context, msg);
}
