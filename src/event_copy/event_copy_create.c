/**
 * \file event_copy/event_copy_create.c
 *
 * \brief Create an event copy from the given event.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event_copy.h>
#include <libcparse/status_codes.h>

/**
 * \brief Create an event copy from the given event.
 *
 * \param cpy                   Pointer to the \ref event_copy pointer to
 *                              receive this \ref event_copy on success.
 * \param ev                    The event to copy.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_copy_create)(
    CPARSE_SYM(event_copy)** cpy, const CPARSE_SYM(event)* ev)
{
    (void)cpy;
    (void)ev;

    return ERROR_LIBCPARSE_EVENT_COPY_UNSUPPORTED_EVENT_CATEGORY;
}
