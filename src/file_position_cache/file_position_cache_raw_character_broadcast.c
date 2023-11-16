/**
 * \file file_position_cache/raw_character_broadcast.c
 *
 * \brief Broadcast a raw character using the cached file and position.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event_reactor.h>
#include <libcparse/event/raw_character.h>
#include <libcparse/status_codes.h>

#include "file_position_cache_internal.h"

CPARSE_IMPORT_event_raw_character;
CPARSE_IMPORT_event_reactor;

/**
 * \brief Given a cache, event reactor, and character, send a cached raw
 * character event to the event reactor subscribers.
 *
 * \param cache             The \ref file_position_cache instance for this
 *                          operation.
 * \param reactor           The \ref event_reactor for this operation.
 * \param ch                The raw character to send.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(file_position_cache_raw_character_broadcast)(
    CPARSE_SYM(file_position_cache)* cache, CPARSE_SYM(event_reactor)* reactor,
    int ch)
{
    int retval, release_retval;
    event_raw_character rev;

    /* initialize the raw character event. */
    retval =
        event_raw_character_init(
            &rev, CPARSE_EVENT_TYPE_RAW_CHARACTER, &cache->pos, ch);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* broadcast this message. */
    retval = event_reactor_broadcast(reactor, event_raw_character_upcast(&rev));
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_rev;
    }

    /* success. */
    retval = STATUS_SUCCESS;
    goto cleanup_rev;

cleanup_rev:
    release_retval = event_raw_character_dispose(&rev);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}
