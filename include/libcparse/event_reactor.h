/**
 * \file libcparse/event_reactor.h
 *
 * \brief The \ref event_reactor registers event handlers and broadcasts events
 * to them.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The event reactor provides event management support for a parser.
 */
typedef struct CPARSE_SYM(event_reactor) CPARSE_SYM(event_reactor);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Create an \ref event_reactor instance.
 *
 * \param er                Pointer to the event reactor pointer to receive the
 *                          created instance on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_reactor_create)(CPARSE_SYM(event_reactor)** er);

/**
 * \brief Release an \ref event_reactor instance.
 *
 * \param er                The event reactor instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_reactor_release)(CPARSE_SYM(event_reactor)* er);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
