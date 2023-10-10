/**
 * \file src/event_handler/event_handler_send.c
 *
 * \brief Send method for the \ref event_handler type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event_handler.h>

/**
 * \brief Send an event to the given event handler.
 *
 * \param eh                    The event handler to receive this event.
 * \param ev                    The event to send.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_handler_send)(
    CPARSE_SYM(event_handler)* eh, const CPARSE_SYM(event)* ev)
{
    return eh->event_callback(eh->context, ev);
}
