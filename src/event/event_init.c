/**
 * \file src/event/event_init.c
 *
 * \brief Initialize an event instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <string.h>

#include "event_internal.h"

/**
 * \brief Perform an in-place initialization of an event_type instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param event_type            The type of the event.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_init)(
    CPARSE_SYM(event)* ev, int event_type, const CPARSE_SYM(cursor)* cursor)
{
    /* clear event structure. */
    memset(ev, 0, sizeof(*ev));

    /* initialize structure members. */
    ev->event_type = event_type;
    memcpy(&ev->event_cursor, cursor, sizeof(ev->event_cursor));

    /* success. */
    return STATUS_SUCCESS;
}
