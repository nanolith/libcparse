/**
 * \file src/event/event_include_init.c
 *
 * \brief Init method for the \ref event_include type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event/include.h>
#include <libcparse/status_codes.h>
#include <string.h>

#include "event_internal.h"

CPARSE_IMPORT_event_internal;

/**
 * \brief Perform an in-place initialization of an \ref event_include instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param event_type        The type of the event.
 * \param cursor            The event cursor.
 * \param file              The file to include for this event.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_include_init)(
    CPARSE_SYM(event_include)* ev, int event_type,
    const CPARSE_SYM(cursor)* cursor, const char* file)
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
    ev->file = file;

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

done:
    return retval;
}
