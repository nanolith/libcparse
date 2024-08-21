/**
 * \file src/event/event_raw_character_literal_init.c
 *
 * \brief Init method for the \ref event_raw_character_literal type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event/raw_character_literal.h>
#include <libcparse/status_codes.h>
#include <string.h>

#include "event_internal.h"

CPARSE_IMPORT_event_internal;

/**
 * \brief Perform an in-place initialization of an
 * \ref event_raw_character_literal instance.
 * instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param cursor            The event cursor.
 * \param val               The raw string representation of this token.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_raw_character_literal_init)(
    CPARSE_SYM(event_raw_character_literal)* ev,
    const CPARSE_SYM(cursor)* cursor, const char* val)
{
    int retval;

    /* clear event memory. */
    memset(ev, 0, sizeof(*ev));

    /* initialize base type. */
    retval =
        event_init(
            &ev->hdr, CPARSE_EVENT_TYPE_TOKEN_VALUE_RAW_CHARACTER,
            CPARSE_EVENT_CATEGORY_RAW_CHARACTER_LITERAL, cursor);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize instance variables. */
    ev->val = val;

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

done:
    return retval;
}
