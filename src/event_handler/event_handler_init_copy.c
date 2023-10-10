/**
 * \file src/event_handler/event_handler_init_copy.c
 *
 * \brief Initialize a copy of the given \ref event_handler instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event_handler.h>
#include <libcparse/status_codes.h>
#include <string.h>

/**
 * \brief Initialize a \ref event_handler by copying another
 * \ref event_handler.
 *
 * \param eh                    The event handler instance to initialize.
 * \param ehc                   The event handler to copy.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_handler_init_copy)(
    CPARSE_SYM(event_handler)* eh, const CPARSE_SYM(event_handler)* ehc)
{
    /* copy instance data. */
    memcpy(eh, ehc, sizeof(*eh));

    /* success. */
    return STATUS_SUCCESS;
}
