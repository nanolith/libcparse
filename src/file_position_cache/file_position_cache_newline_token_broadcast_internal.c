/**
 * \file
 * file_position_cache/file_position_cache_newline_token_broadcast_internal.c
 *
 * \brief Internal newline token broadcast method.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event.h>
#include <libcparse/event_reactor.h>
#include <libcparse/status_codes.h>

#include "file_position_cache_internal.h"

CPARSE_IMPORT_event;
CPARSE_IMPORT_event_reactor;

/**
 * \brief Given a cache and event reactor, send the final cached newline token
 * event to the event reactor subscribers.
 *
 * This event is triggered by an EOF event, so this function will automatically
 * adjust the end line and column to reflect one line "past" the EOF in the
 * position to assist with newline positioning logic in downstream event
 * handlers that care about token position.
 *
 * \param reactor           The \ref event_reactor for this operation.
 * \param pos               The position to use for this token.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(file_position_cache_newline_token_broadcast_internal)(
    CPARSE_SYM(event_reactor)* reactor, const CPARSE_SYM(cursor)* pos)
{
    int retval, release_retval;
    event ev;

    /* initialize the event. */
    retval = event_init_for_newline_token(&ev, pos);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this message. */
    retval = event_reactor_broadcast(reactor, &ev);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_ev;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto cleanup_ev;

cleanup_ev:
    release_retval = event_dispose(&ev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}
