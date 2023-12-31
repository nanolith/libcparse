/**
 * \file libcparse/newline_preserving_whitespace_filter_internal.h
 *
 * \brief Internal declarations and definitions for the newline preserving
 * whitespace filter.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/abstract_parser.h>
#include <libcparse/comment_filter.h>
#include <libcparse/event_reactor_fwd.h>
#include <libcparse/file_position_cache.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

typedef struct CPARSE_SYM(newline_preserving_whitespace_filter)
CPARSE_SYM(newline_preserving_whitespace_filter);

struct CPARSE_SYM(newline_preserving_whitespace_filter)
{
    CPARSE_SYM(comment_filter)* parent;
    CPARSE_SYM(abstract_parser)* base;
    CPARSE_SYM(event_reactor)* reactor;
    CPARSE_SYM(message_handler) parent_mh;
    CPARSE_SYM(file_position_cache)* cache;
    int state;
};

enum CPARSE_SYM(newline_preserving_whitespace_filter_state)
{
    CPARSE_NL_WHITESPACE_FILTER_STATE_INIT =                        0,
    CPARSE_NL_WHITESPACE_FILTER_STATE_IN_NEWLINE =                  1,
    CPARSE_NL_WHITESPACE_FILTER_STATE_IN_STRING =                   2,
    CPARSE_NL_WHITESPACE_FILTER_STATE_IN_STRING_SLASH =             3,
    CPARSE_NL_WHITESPACE_FILTER_STATE_IN_CHARACTER_SEQUENCE =       4,
    CPARSE_NL_WHITESPACE_FILTER_STATE_IN_CHARACTER_SEQUENCE_SLASH = 5,
    CPARSE_NL_WHITESPACE_FILTER_STATE_IN_WHITESPACE =               6,
};

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Message handler callback for
 * \ref newline_preserving_whitespace_filter.
 *
 * \param context           The context for this handler (the
 *                          \ref newline_preserving_whitespace_filter instance).
 * \param msg               A message for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(newline_preserving_whitespace_filter_message_callback)(
    void* context, const CPARSE_SYM(message)* msg);

/**
 * \brief Event handler callback for
 * \ref newline_preserving_whitespace_filter.
 *
 * \param context           The context for this handler (the
 *                          \ref newline_preserving_whitespace_filter instance).
 * \param ev                An event for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(newline_preserving_whitespace_filter_event_callback)(
    void* context, const CPARSE_SYM(event)* ev);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_newline_preserving_whitespace_filter_internal_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    static inline int \
    sym ## newline_preserving_whitespace_filter_message_callback( \
        void* x, const CPARSE_SYM(message)* y) { \
            return \
                CPARSE_SYM(newline_preserving_whitespace_filter_message_callback)( \
                    x,y); } \
    static inline int \
    sym ## newline_preserving_whitespace_filter_event_callback( \
        void* x, const CPARSE_SYM(event)* y) { \
            return \
                CPARSE_SYM(newline_preserving_whitespace_filter_event_callback)( \
                    x,y); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_newline_preserving_whitespace_filter_internal_as(sym) \
    __INTERNAL_CPARSE_IMPORT_newline_preserving_whitespace_filter_internal_sym(sym ## _)
#define CPARSE_IMPORT_newline_preserving_whitespace_filter_internal \
    __INTERNAL_CPARSE_IMPORT_newline_preserving_whitespace_filter_internal_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
