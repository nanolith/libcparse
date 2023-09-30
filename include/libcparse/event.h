/**
 * \file libcparse/event.h
 *
 * \brief The event type represents an individual lexer or parser event.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/function_decl.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The event type abstracts individual lexer or parser events.
 */
typedef struct CPARSE_SYM(event) CPARSE_SYM(event);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Release an event instance.
 *
 * \param ev                    The event instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_release)(CPARSE_SYM(event)* ev);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/
#define __INTERNAL_CPARSE_IMPORT_event_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(event) sym ## event; \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_event_as(sym) \
    __INTERNAL_CPARSE_IMPORT_event_sym(sym ## _)
#define CPARSE_IMPORT_event \
    __INTERNAL_CPARSE_IMPORT_event_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
