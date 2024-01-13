/**
 * \file event/event_string_internal.h
 *
 * \brief Internal declarations for the \ref event_string type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/event/string.h>
#include <libcparse/function_decl.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/******************************************************************************/
/* Start of private constructors.                                             */
/******************************************************************************/

/**
 * \brief Perform an in-place initialization of an \ref event_string instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param event_type        The type of the string event to initialize.
 * \param cursor            The event cursor.
 * \param str               The string value for this event.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_string_init_internal)(
    CPARSE_SYM(event_string)* ev, int event_type,
    const CPARSE_SYM(cursor)* cursor, const char* line);

/******************************************************************************/
/* Start of private exports.                                                  */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_event_string_internal_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    static inline int sym ## event_string_init_internal( \
        CPARSE_SYM(event_string)* w, int x, const CPARSE_SYM(cursor)* y, \
        const char* z) { \
            return CPARSE_SYM(event_string_init_internal)(w,x,y,z); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_event_string_internal_as(sym) \
    __INTERNAL_CPARSE_IMPORT_event_string_internal_sym(sym ## _)
#define CPARSE_IMPORT_event_string_internal \
    __INTERNAL_CPARSE_IMPORT_event_string_internal_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
