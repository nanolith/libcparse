/**
 * \file src/event/event_dispose.c
 *
 * \brief Dispose an event instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <string.h>

#include "event_internal.h"

/**
 * \brief Perform an in-place disposable of an event instance.
 *
 * \param ev                    Pointer to the event to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_dispose)(CPARSE_SYM(event)* ev)
{
    memset(ev, 0, sizeof(*ev));

    return STATUS_SUCCESS;
}
