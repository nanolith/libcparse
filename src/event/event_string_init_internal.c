/**
 * \file src/event/event_string_init_internal.c
 *
 * \brief Init method for the \ref event_string type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event/string.h>
#include <libcparse/status_codes.h>
#include <string.h>

#include "event_internal.h"

CPARSE_IMPORT_event_internal;

/**
 * \brief Perform an in-place initialization of an \ref event_string instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param event_type        The type of the string event to initialize.
 * \param cursor            The event cursor.
 * \param str               The string value for this event.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_string_init_internal)(
    CPARSE_SYM(event_string)* ev, int event_type,
    const CPARSE_SYM(cursor)* cursor, const char* str)
{
    int retval;

    /* clear event memory. */
    memset(ev, 0, sizeof(*ev));

    /* initialize base type. */
    retval = event_init(&ev->hdr, event_type, cursor);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize instance variables. */
    ev->str = str;

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

done:
    return retval;
}
