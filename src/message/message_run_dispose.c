/**
 * \file src/message/message_run_dispose.c
 *
 * \brief Dispose method for the \ref message_run type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message/run.h>
#include <string.h>

CPARSE_IMPORT_message;

/**
 * \brief Dispose of a \ref message_run instance.
 *
 * \param msg               The message to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_run_dispose)(CPARSE_SYM(message_run)* msg)
{
    int message_dispose_retval;

    /* dispose the base message type. */
    message_dispose_retval = message_dispose(&msg->hdr);

    /* clear this instance. */
    memset(msg, 0, sizeof(*msg));

    /* return the result of disposing the base message. */
    return message_dispose_retval;
}
