/**
 * \file libcparse/event_internal.h
 *
 * \brief Internal declarations for \ref event.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/event.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The event category is used for determining the structural data found
 * in an event.
 */
enum CPARSE_SYM(event_category)
{
    CPARSE_EVENT_CATEGORY_EVENT =                                       0x0000,
};

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Perform an in-place initialization of an event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param event_type            The type of the event.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init)(
    CPARSE_SYM(event)* ev, int event_type, const CPARSE_SYM(cursor)* cursor);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_event_internal_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    static inline int sym ## event_init( \
        CPARSE_SYM(event)* x, int y, const CPARSE_SYM(cursor)* z) { \
            return CPARSE_SYM(event_init)(x,y,z); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_event_internal_as(sym) \
    __INTERNAL_CPARSE_IMPORT_event_internal_sym(sym ## _)
#define CPARSE_IMPORT_event_internal \
    __INTERNAL_CPARSE_IMPORT_event_internal_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
