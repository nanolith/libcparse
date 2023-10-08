/**
 * \file src/message/message_dispose.c
 *
 * \brief Disposer for the \ref message type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <string.h>

#include "message_internal.h"

/**
 * \brief Dispose a \ref message.
 *
 * \param msg                   The message to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_dispose)(CPARSE_SYM(message)* msg)
{
    memset(msg, 0, sizeof(*msg));

    return STATUS_SUCCESS;
}
