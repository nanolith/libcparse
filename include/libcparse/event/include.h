/**
 * \file libcparse/event/include.h
 *
 * \brief The \ref event_include type indicates the scan of a system
 * or local include preprocessor control line.
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
 * \brief The include event type indicates the scan of a single include
 * preprocessor control line.
 */
typedef struct CPARSE_SYM(event_include)
CPARSE_SYM(event_include);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Perform an in-place initialization of an \ref event_include instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param event_type        The type of the event.
 * \param cursor            The event cursor.
 * \param file              The file to include for this event.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_include_init)(
    CPARSE_SYM(event_include)* ev, int event_type,
    const CPARSE_SYM(cursor)* cursor, const char* file);

/**
 * \brief Perform an in-place disposal of an \ref event_include instance.
 *
 * \param ev                Pointer to the event to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_include_dispose)(CPARSE_SYM(event_include)* ev);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Get the file value for this event.
 *
 * \param ev                The event instance to query.
 *
 * \returns the line value for this event.
 */
const char* CPARSE_SYM(event_include_file_get)(
    const CPARSE_SYM(event_include)* ev);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
