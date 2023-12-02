/**
 * \file src/event/event_include_init_for_system_include.c
 *
 * \brief System include init method for the \ref event_include type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event.h>
#include <libcparse/event/include.h>
#include <libcparse/status_codes.h>
#include <string.h>

#include "event_include_internal.h"

CPARSE_IMPORT_event;
CPARSE_IMPORT_event_include;
CPARSE_IMPORT_event_include_internal;

/**
 * \brief Perform an in-place initialization of an \ref event_include instance
 * for a system include.
 *
 * \param ev                Pointer to the event to initialize.
 * \param cursor            The event cursor.
 * \param file              The file to include for this event.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_include_init_for_system_include)(
    CPARSE_SYM(event_include)* ev, const CPARSE_SYM(cursor)* cursor,
    const char* file)
{
    return
        event_include_init(
            ev, CPARSE_EVENT_TYPE_PREPROCESSOR_SYSTEM_INCLUDE, cursor, file);
}
