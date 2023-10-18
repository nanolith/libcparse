/**
 * \file src/event_handler/event_reactor_broadcast.c
 *
 * \brief Broadcast an event to all event handlers added to this reactor.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stddef.h>

#include "event_reactor_internal.h"

CPARSE_IMPORT_event_handler;
CPARSE_IMPORT_event_reactor_internal;

/**
 * \brief Broadcast an event to all event handlers in this event reactor.
 *
 * \param er                The event reactor for this operation.
 * \param ev                The event to broadcast.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_reactor_broadcast)(
    CPARSE_SYM(event_reactor)* er, const CPARSE_SYM(event)* ev)
{
    int retval;
    event_reactor_entry* ent = er->head;

    /* iterate through all entries. */
    while (NULL != ent)
    {
        /* broadcast to an assigned handler. */
        retval = event_handler_send(&ent->handler, ev);
        if (STATUS_SUCCESS != retval)
        {
            return retval;
        }

        /* go to the next entry. */
        ent = ent->next;
    }

    /* success. */
    return STATUS_SUCCESS;
}
