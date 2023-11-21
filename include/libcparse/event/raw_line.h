/**
 * \file libcparse/event/raw_line.h
 *
 * \brief The \ref event_raw_line type indicates the scan of a raw preprocessor
 * control line.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/cursor.h>
#include <libcparse/function_decl.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The raw line event type indicates the scan of a single raw
 * preprocessor control line.
 */
typedef struct CPARSE_SYM(event_raw_line) CPARSE_SYM(event_raw_line);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Perform an in-place initialization of an \ref event_raw_line instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param event_type        The type of the event.
 * \param cursor            The event cursor.
 * \param line              The raw line for this event.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_raw_line_init)(
    CPARSE_SYM(event_raw_line)* ev, int event_type,
    const CPARSE_SYM(cursor)* cursor, const char* line);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
