/**
 * \file src/event/event_init_for_comment_block_begin.c
 *
 * \brief Initialize an event instance for the comment block begin event.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event.h>
#include <libcparse/event_type.h>

CPARSE_IMPORT_event;

/**
 * \brief Perform an in-place initialization of a comment block begin event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_comment_block_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor)
{
    return event_init(ev, CPARSE_EVENT_TYPE_COMMENT_BLOCK_BEGIN, cursor);
}
