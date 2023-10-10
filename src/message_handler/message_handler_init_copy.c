/**
 * \file src/message_handler/message_handler_init_copy.c
 *
 * \brief Initialize a \ref message_handler as a copy of another
 * \ref message_handler.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message_handler.h>
#include <libcparse/status_codes.h>
#include <string.h>

/**
 * \brief Initialize a \ref message_handler by copying another
 * \ref message_handler.
 *
 * \param mh                    The message handler instance to initialize.
 * \param mhc                   The message handler to copy.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_handler_init_copy)(
    CPARSE_SYM(message_handler)* mh, const CPARSE_SYM(message_handler)* mhc)
{
    /* copy the instance data. */
    memcpy(mh, mhc, sizeof(*mh));

    /* success. */
    return STATUS_SUCCESS;
}
