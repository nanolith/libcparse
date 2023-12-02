/**
 * \file src/event/event_raw_character_init.c
 *
 * \brief Init method for the \ref event_raw_character type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event.h>
#include <libcparse/event/raw_character.h>
#include <libcparse/status_codes.h>
#include <string.h>

CPARSE_IMPORT_event;

/**
 * \brief Perform an in-place initialization of an \ref event_raw_character
 * instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param cursor            The event cursor.
 * \param ch                The raw character for this event.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_raw_character_init)(
    CPARSE_SYM(event_raw_character)* ev, const CPARSE_SYM(cursor)* cursor,
    int ch)
{
    int retval;

    /* clear event memory. */
    memset(ev, 0, sizeof(*ev));

    /* initialize base type. */
    retval = event_init(&ev->hdr, CPARSE_EVENT_TYPE_RAW_CHARACTER, cursor);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize instance variables. */
    ev->raw_character = ch;

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

done:
    return retval;
}
