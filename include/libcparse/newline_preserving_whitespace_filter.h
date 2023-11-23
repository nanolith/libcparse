/**
 * \file libcparse/newline_preserving_whitespace_filter.h
 *
 * \brief The newline preserving whitespace filter merges all non-newline
 * whitespace characters into single whitespace tokens. Newline characters are
 * turned into newline tokens.
 *
 * Subscribers to this scanner will receive whitespace token, newline token, and
 * raw character events as from the comment filter. Runs of raw whitespace will
 * be replaced with either a single whitespace token, or a newline token,
 * depending upon whether the runs contain a newline.
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
 * \brief The \ref newline_preserving_whitespace_filter replaces runs of
 * whitespace with a single whitespace token, and preserves newlines as a
 * newline token.
 */
typedef struct CPARSE_SYM(newline_preserving_whitespace_filter)
CPARSE_SYM(newline_preserving_whitespace_filter);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Create a newline preserving whitespace filter.
 *
 * This filter automatically creates a comment filter and injects itself into
 * the message chain for the parser stack.
 *
 * \param filter            Pointer to the
 *                          \ref newline_preserving_whitespace_filter pointer to
 *                          be populated with the filter instance on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(newline_preserving_whitespace_filter_create)(
    CPARSE_SYM(newline_preserving_whitespace_filter)** filter);

/**
 * \brief Release a newline preserving whitespace filter instance, releasing any
 * internal resources it may own.
 *
 * \param filter            The\ref newline_preserving_whitespace_filter to
 *                          release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(newline_preserving_whitespace_filter_release)(
    CPARSE_SYM(newline_preserving_whitespace_filter)* filter);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Get the \ref abstract_parser interface for this filter.
 *
 * \param filter            The \ref newline_preserving_whitespace_filter
 *                          instance to query.
 *
 * \returns the \ref abstract_parser interface for this filter.
 */
CPARSE_SYM(abstract_parser)*
CPARSE_SYM(newline_preserving_whitespace_filter_upcast)(
    CPARSE_SYM(newline_preserving_whitespace_filter)* filter);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_newline_preserving_whitespace_filter_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(newline_preserving_whitespace_filter) \
    sym ## newline_preserving_whitespace_filter; \
    static inline int sym ## newline_preserving_whitespace_filter_create( \
        CPARSE_SYM(newline_preserving_whitespace_filter)** x) { \
            return \
                CPARSE_SYM(newline_preserving_whitespace_filter_create)(x); } \
    static inline int sym ## newline_preserving_whitespace_filter_release( \
        CPARSE_SYM(newline_preserving_whitespace_filter)* x) { \
            return \
                CPARSE_SYM(newline_preserving_whitespace_filter_release)(x); } \
    static inline CPARSE_SYM(abstract_parser)* \
    sym ## newline_preserving_whitespace_filter_upcast( \
        CPARSE_SYM(newline_preserving_whitespace_filter)* x) { \
            return \
                CPARSE_SYM(newline_preserving_whitespace_filter_upcast)(x); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_newline_preserving_whitespace_filter_as(sym) \
    __INTERNAL_CPARSE_IMPORT_newline_preserving_whitespace_filter_sym(sym ## _)
#define CPARSE_IMPORT_newline_preserving_whitespace_filter \
    __INTERNAL_CPARSE_IMPORT_newline_preserving_whitespace_filter_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
