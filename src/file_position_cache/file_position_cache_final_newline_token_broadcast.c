/**
 * \file file_position_cache/file_position_cache_final_newline_token_broadcast.c
 *
 * \brief Broadcast the final newline in a source file.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event.h>
#include <libcparse/event_reactor.h>
#include <libcparse/status_codes.h>
#include <string.h>

#include "file_position_cache_internal.h"

CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_reactor;
CPARSE_IMPORT_file_position_cache_internal;

/**
 * \brief Given a cache and event reactor, send the final cached newline token
 * event to the event reactor subscribers.
 *
 * This event is triggered by an EOF event, so this function will automatically
 * adjust the end line and column to reflect one line "past" the EOF in the
 * position to assist with newline positioning logic in downstream event
 * handlers that care about token position.
 *
 * \param cache             The \ref file_position_cache instance for this
 *                          operation.
 * \param reactor           The \ref event_reactor for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(file_position_cache_final_newline_token_broadcast)(
    CPARSE_SYM(file_position_cache)* cache, CPARSE_SYM(event_reactor)* reactor)
{
    cursor nlpos;

    /* extend the position for this broadcast token past the EOF. */
    memcpy(&nlpos, &cache->pos, sizeof(nlpos));
    ++nlpos.end_line;
    nlpos.end_col = 1;

    return
        file_position_cache_newline_token_broadcast_internal(reactor, &nlpos);
}
