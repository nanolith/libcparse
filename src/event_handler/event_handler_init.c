/**
 * \file src/event_handler/event_handler_init.c
 *
 * \brief Init method for the \ref event_handler type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event_handler.h>
#include <libcparse/status_codes.h>
#include <string.h>

/**
 * \brief Initialize an \ref event_handler from a callback function and
 * context.
 *
 * \param eh                    The event handler instance to initialize.
 * \param ecb                   The event callback function.
 * \param ectx                  The event handler user context.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_handler_init)(
    CPARSE_SYM(event_handler)* eh, CPARSE_SYM(event_callback_fn) ecb,
    void* ectx)
{
    /* clear instance. */
    memset(eh, 0, sizeof(*eh));

    /* set values. */
    eh->event_callback = ecb;
    eh->context = ectx;

    /* success. */
    return STATUS_SUCCESS;
}
