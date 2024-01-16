/**
 * \file src/event/event_identifier_init_internal.c
 *
 * \brief Init method for the \ref event_identifier type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event/identifier.h>
#include <libcparse/status_codes.h>
#include <string.h>

#include "event_internal.h"

CPARSE_IMPORT_event_internal;

/**
 * \brief Perform an in-place initialization of an \ref event_identifier
 * instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param cursor            The event cursor.
 * \param id                The identifier value for this event.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_identifier_init)(
    CPARSE_SYM(event_identifier)* ev, const CPARSE_SYM(cursor)* cursor,
    const char* id)
{
    int retval;

    /* clear event memory. */
    memset(ev, 0, sizeof(*ev));

    /* initialize base type. */
    retval = event_init(&ev->hdr, CPARSE_EVENT_TYPE_TOKEN_IDENTIFIER, cursor);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize instance variables. */
    ev->id = id;

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

done:
    return retval;
}
