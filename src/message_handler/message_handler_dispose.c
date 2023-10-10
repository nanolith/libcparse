/**
 * \file src/message_handler/message_handler_dispose.c
 *
 * \brief Dispose of a \ref message_handler instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message_handler.h>
#include <libcparse/status_codes.h>
#include <string.h>

/**
 * \brief Dispose a \ref message_handler instance.
 *
 * \param mh                    The message handler instance to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_handler_dispose)(CPARSE_SYM(message_handler)* mh)
{
    /* clear instance data. */
    memset(mh, 0, sizeof(*mh));

    /* success. */
    return STATUS_SUCCESS;
}
