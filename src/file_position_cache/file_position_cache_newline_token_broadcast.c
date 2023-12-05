/**
 * \file file_position_cache/file_position_cache_newline_token_broadcast.c
 *
 * \brief Broadcast a newline token event using the cached file and position.
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
 * \brief Given a cache and event reactor, send a cached newline token event to
 * the event reactor subscribers.
 *
 * \param cache             The \ref file_position_cache instance for this
 *                          operation.
 * \param reactor           The \ref event_reactor for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(file_position_cache_newline_token_broadcast)(
    CPARSE_SYM(file_position_cache)* cache, CPARSE_SYM(event_reactor)* reactor)
{
    int retval, release_retval;
    event ev;

    /* initialize the event. */
    retval = event_init(&ev, CPARSE_EVENT_TYPE_TOKEN_NEWLINE, &cache->pos);
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
