/**
 * \file src/message/message_init.c
 *
 * \brief Init method for the \ref message type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message.h>
#include <libcparse/status_codes.h>
#include <string.h>

/**
 * \brief Initialize a \ref message.
 *
 * \param msg                   The message to initialize.
 * \param msg_type              The message type.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_init)(CPARSE_SYM(message)* msg, int msg_type)
{
    /* clear and initialize message. */
    memset(msg, 0, sizeof(*msg));
    msg->msg_type = msg_type;

    return STATUS_SUCCESS;
}
