/**
 * \file libcparse/comment_filter.h
 *
 * \brief The comment filter consumes events from the comment scanner and
 * replaces comments with a single whitespace character.
 *
 * Subscribers to this scanner will receive raw character events as from the
 * comment scanner, except that both line comments and block comments will be
 * replaced with a single space.
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
 * \brief The \ref comment_filter filters comments out of an input stream.
 */
typedef struct CPARSE_SYM(comment_filter)
CPARSE_SYM(comment_filter);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Create a comment filter.
 *
 * This filter automatically creates a comment scanner and injects itself into
 * the message chain for the parser stack.
 *
 * \param scanner           Pointer to the \ref comment_filter pointer to be
 *                          populated with the created comment filter instance
 *                          on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(comment_filter_create)(CPARSE_SYM(comment_filter)** filter);

/**
 * \brief Release a comment filter instance, releasing any internal resources
 * it may own.
 *
 * \param filter            The \ref comment_filter instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(comment_filter_release)(CPARSE_SYM(comment_filter)* filter);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Get the \ref abstract_parser interface for this filter.
 *
 * \param filter            The \ref comment_filter instance to query.
 *
 * \returns the \ref abstract_parser interface for this filter.
 */
CPARSE_SYM(abstract_parser)* CPARSE_SYM(comment_filter_upcast)(
    CPARSE_SYM(comment_filter)* filter);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_comment_filter_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(comment_filter) sym ## comment_filter; \
    static inline int sym ## comment_filter_create( \
        CPARSE_SYM(comment_filter)** x) { \
            return CPARSE_SYM(comment_filter_create)(x); } \
    static inline int sym ## comment_filter_release( \
        CPARSE_SYM(comment_filter)* x) { \
            return CPARSE_SYM(comment_filter_release)(x); } \
    static inline CPARSE_SYM(abstract_parser)* sym ## comment_filter_upcast( \
        CPARSE_SYM(comment_filter)* x) { \
            return CPARSE_SYM(comment_filter_upcast)(x); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_comment_filter_as(sym) \
    __INTERNAL_CPARSE_IMPORT_comment_filter_sym(sym ## _)
#define CPARSE_IMPORT_comment_filter \
    __INTERNAL_CPARSE_IMPORT_comment_filter_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
