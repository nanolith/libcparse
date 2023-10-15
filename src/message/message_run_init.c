/**
 * \file src/message/message_run_init.c
 *
 * \brief Init method for the \ref message_run type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message/run.h>
#include <libcparse/status_codes.h>
#include <string.h>

CPARSE_IMPORT_message;

/**
 * \brief Initialize a \ref message_run instance.
 *
 * \param msg               The message to initialize.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_run_init)(CPARSE_SYM(message_run)* msg)
{
    /* clear the message instance. */
    memset(msg, 0, sizeof(*msg));

    /* initialize the base message. */
    return
        message_init(&msg->hdr, CPARSE_MESSAGE_TYPE_RUN);
}
