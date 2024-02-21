/**
 * \file event/event_integer_internal.h
 *
 * \brief Internal declarations for the \ref event_integer_token type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/event/integer.h>
#include <libcparse/function_decl.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/******************************************************************************/
/* Start of private constructors.                                             */
/******************************************************************************/

/**
 * \brief Perform an in-place initialization of a signed \ref
 * event_integer_token instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param cursor            The event cursor.
 * \param integer_type      The integer type.
 * \param val               The integer value.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_integer_init_for_signed_internal)(
    CPARSE_SYM(event_integer_token)* ev, int event_type,
    const CPARSE_SYM(cursor)* cursor, long long val);

/**
 * \brief Perform an in-place initialization of an unsigned \ref
 * event_integer_token instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param cursor            The event cursor.
 * \param integer_type      The integer type.
 * \param val               The integer value.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int CPARSE_SYM(event_integer_init_for_unsigned_internal)(
    CPARSE_SYM(event_integer_token)* ev, int event_type,
    const CPARSE_SYM(cursor)* cursor, unsigned long long val);

/******************************************************************************/
/* Start of private exports.                                                  */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_event_integer_internal_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    static inline int sym ## event_integer_init_for_signed_internal( \
        CPARSE_SYM(event_integer_token)* w, int x, \
        const CPARSE_SYM(cursor)* y, long long z) { \
            return \
                CPARSE_SYM(event_integer_init_for_signed_internal)(w,x,y,z); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_event_integer_internal_as(sym) \
    __INTERNAL_CPARSE_IMPORT_event_integer_internal_sym(sym ## _)
#define CPARSE_IMPORT_event_integer_internal \
    __INTERNAL_CPARSE_IMPORT_event_integer_internal_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
