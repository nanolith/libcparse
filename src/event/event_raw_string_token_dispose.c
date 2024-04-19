/**
 * \file src/event/event_raw_string_token_dispose.c
 *
 * \brief Dispose method for the \ref event_raw_string_token type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event.h>
#include <libcparse/event/raw_string.h>
#include <libcparse/status_codes.h>
#include <string.h>

CPARSE_IMPORT_event;

/**
 * \brief Perform an in-place disposal of an \ref event_raw_string_token
 * instance.
 *
 * \param ev                Pointer to the event to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_raw_string_token_dispose)(
    CPARSE_SYM(event_raw_string_token)* ev)
{
    int event_dispose_retval = STATUS_SUCCESS;

    /* dispose base type. */
    event_dispose_retval = event_dispose(&ev->hdr);

    /* clear instance memory. */
    memset(ev, 0, sizeof(*ev));

    /* return base type dispose result. */
    return event_dispose_retval;
}
