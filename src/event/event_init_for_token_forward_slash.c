/**
 * \file src/event/event_init_for_token_forward_slash.c
 *
 * \brief Initialize an event instance for the forward slash token event.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event_type.h>

#include "event_internal.h"

CPARSE_IMPORT_event_internal;

/**
 * \brief Perform an in-place initialization of a forward slash token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_forward_slash)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor)
{
    return
        event_init(
            ev, CPARSE_EVENT_TYPE_TOKEN_FORWARD_SLASH,
            CPARSE_EVENT_CATEGORY_BASE, cursor);
}
