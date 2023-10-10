/**
 * \file src/message/message_handler_init.c
 *
 * \brief Init method for the \ref message_handler type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/message_handler.h>
#include <libcparse/status_codes.h>
#include <string.h>

/**
 * \brief Initialize a \ref message_handler from a callback function and
 * context.
 *
 * \param mh                    The message handler instance to initialize.
 * \param mcb                   The message callback function.
 * \param mctx                  The message handler user context.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_handler_init)(
    CPARSE_SYM(message_handler)* mh, CPARSE_SYM(message_callback_fn) mcb,
    void* mctx)
{
    /* clear instance. */
    memset(mh, 0, sizeof(*mh));

    /* set values. */
    mh->message_callback = mcb;
    mh->context = mctx;

    /* success. */
    return STATUS_SUCCESS;
}
