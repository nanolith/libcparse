/**
 * \file event_copy/event_copy_get_event.c
 *
 * \brief Get the event associated with an event copy.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include "event_copy_internal.h"

/**
 * \brief Get a pointer to the \ref event for this \ref event_copy.
 *
 * \param cpy                   The \ref event_copy to query.
 *
 * \returns the \ref event for this copy.
 */
const CPARSE_SYM(event)*  CPARSE_SYM(event_copy_get_event)(
    const CPARSE_SYM(event_copy)* cpy)
{
    return &cpy->detail.event;
}
