/**
 * \file src/event/event_init_for_exp_less_than_equal_end.c
 *
 * \brief Initialize an event instance for a less than equal end event.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event_type.h>

#include "event_internal.h"

CPARSE_IMPORT_event_internal;

/**
 * \brief Perform an in-place initialization of a less-than equal end
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_exp_less_than_equal_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor)
{
    return
        event_init(
            ev, CPARSE_EVENT_TYPE_EXP_LESS_THAN_EQUAL_END,
            CPARSE_EVENT_CATEGORY_BASE, cursor);
}
