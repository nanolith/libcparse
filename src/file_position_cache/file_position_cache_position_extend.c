/**
 * \file file_position_cache/file_position_cache_position_extend.c
 *
 * \brief Extend the cached position.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/cursor.h>
#include <libcparse/event.h>
#include <libcparse/status_codes.h>
#include <stddef.h>

#include "file_position_cache_internal.h"

CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event;

/**
 * \brief Extend the cached position to include this event's position.
 *
 * \param cache             The \ref file_position_cache instance for this
 *                          operation.
 * \param ev                The event to include in this cached position.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(file_position_cache_position_extend)(
    CPARSE_SYM(file_position_cache)* cache, const CPARSE_SYM(event)* ev)
{
    if (NULL == cache->file)
    {
        return ERROR_LIBCPARSE_FILE_POSITION_CACHE_NOT_SET;
    }

    /* get the event position. */
    const cursor* pos = event_get_cursor(ev);

    /* extend the position. */
    cache->pos.end_line = pos->end_line;
    cache->pos.end_col = pos->end_col;

    /* success. */
    return STATUS_SUCCESS;
}
