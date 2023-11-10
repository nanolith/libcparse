/**
 * \file libcparse/line_wrap_filter.h
 *
 * \brief The line wrap filter performs line wrapping by removing a newline that
 * occurs after a backslash character in the source file. This allows lines to
 * wrap in the source file while remaining readable to humans by adding natural
 * line breaks.
 *
 * Subscribers to this filter will receive raw character events as with the raw
 * file/line override filter, but any backslash followed by a newline will be
 * automatically filtered out.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/abstract_parser.h>
#include <libcparse/function_decl.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The \ref line_wrap_filter wraps escaped newlines.
 */
typedef struct CPARSE_SYM(line_wrap_filter)
CPARSE_SYM(line_wrap_filter);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Create a line wrap filter.
 *
 * This filter automatically creates a raw file/line override filter and injects
 * itself into the message chain for the parser stack.
 *
 * \param filter            Pointer to the \ref line_wrap_filter pointer to be
 *                          populated with the created line wrap filter instance
 *                          on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(line_wrap_filter_create)(CPARSE_SYM(line_wrap_filter)** filter);

/**
 * \brief Release a line wrap filter instance, releasing any internal resources
 * it may own.
 *
 * \param filter            The \ref line_wrap_filter instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(line_wrap_filter_release)(CPARSE_SYM(line_wrap_filter)* filter);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Get the \ref abstract_parser interface for this filter.
 *
 * \param filter            The \ref line_wrap_filter instance to query.
 *
 * \returns the \ref abstract_parser interface for this filter.
 */
CPARSE_SYM(abstract_parser)* CPARSE_SYM(line_wrap_filter_upcast)(
    CPARSE_SYM(line_wrap_filter)* filter);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_line_wrap_filter_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(line_wrap_filter) sym ## line_wrap_filter; \
    static inline int sym ## line_wrap_filter_create( \
        CPARSE_SYM(line_wrap_filter)** x) { \
            return CPARSE_SYM(line_wrap_filter_create)(x); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_line_wrap_filter_as(sym) \
    __INTERNAL_CPARSE_IMPORT_line_wrap_filter_sym(sym ## _)
#define CPARSE_IMPORT_line_wrap_filter \
    __INTERNAL_CPARSE_IMPORT_line_wrap_filter_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
