/**
 * \file libcparse/event/string.h
 *
 * \brief The \ref event_string type represents string token events.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/cursor.h>
#include <libcparse/event.h>
#include <libcparse/function_decl.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The raw line event type indicates the scan of a single raw
 * preprocessor control line.
 */
typedef struct CPARSE_SYM(event_identifier) CPARSE_SYM(event_identifier);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Perform an in-place initialization of an \ref event_identifier
 * instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param cursor            The event cursor.
 * \param id                The identifier value for this event.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_identifier_init)(
    CPARSE_SYM(event_identifier)* ev, const CPARSE_SYM(cursor)* cursor,
    const char* id);

/**
 * \brief Perform an in-place disposal of an \ref event_identifier instance.
 *
 * \param ev                Pointer to the event to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_identifier_dispose)(CPARSE_SYM(event_identifier)* ev);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Get the identifier value for this event.
 *
 * \param ev                The event instance to query.
 *
 * \returns the line value for this event.
 */
const char* CPARSE_SYM(event_identifier_get)(
    const CPARSE_SYM(event_identifier)* ev);

/**
 * \brief Attempt to downcast an \ref event to an \ref event_identifier.
 *
 * \param i_ev              Pointer to the event pointer to receive the downcast
 *                          instance on success.
 * \param ev                The \ref event pointer to attempt to downcast to the
 *                          derived type.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_downcast_to_event_identifier)(
    CPARSE_SYM(event_identifier)** i_ev, CPARSE_SYM(event)* ev);

/**
 * \brief Upcast an \ref event_identifier to an \ref event.
 *
 * \param ev                The \ref event_identifier to upcast.
 *
 * \returns the \ref event instance for this event.
 */
CPARSE_SYM(event)* CPARSE_SYM(event_identifier_upcast)(
    CPARSE_SYM(event_identifier)* ev);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
