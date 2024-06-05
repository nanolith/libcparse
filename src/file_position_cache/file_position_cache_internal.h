/**
 * \file file_position_cache/file_position_cache_internal.h
 *
 * \brief Internal declarations for \ref file_position_cache.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/cursor.h>
#include <libcparse/event_reactor.h>
#include <libcparse/function_decl.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

typedef struct CPARSE_SYM(file_position_cache) CPARSE_SYM(file_position_cache);

struct CPARSE_SYM(file_position_cache)
{
    char* file;
    CPARSE_SYM(cursor) pos;
};

/******************************************************************************/
/* Start of private methods.                                                  */
/******************************************************************************/

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
 * \param pos               The position to use for this token.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(file_position_cache_newline_token_broadcast_internal)(
    CPARSE_SYM(file_position_cache)* cache, CPARSE_SYM(event_reactor)* reactor,
    const CPARSE_SYM(cursor)* pos);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
