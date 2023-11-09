/**
 * \file comment_filter/comment_filter_internal.h
 *
 * \brief Internal declarations for \ref comment_filter.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/comment_scanner.h>
#include <libcparse/event_reactor_fwd.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

typedef struct CPARSE_SYM(comment_filter)
CPARSE_SYM(comment_filter);

struct CPARSE_SYM(comment_filter)
{
    CPARSE_SYM(comment_scanner)* parent;
    CPARSE_SYM(event_reactor)* reactor;
    CPARSE_SYM(message_handler) parent_mh;
    char* file;
    CPARSE_SYM(cursor) pos1;
    int state;
};

enum CPARSE_SYM(comment_filter_state)
{
    CPARSE_COMMENT_FILTER_STATE_INIT =                           0,
    CPARSE_COMMENT_FILTER_STATE_IN_COMMENT =                     1,
};

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Message handler callback for \ref comment_filter.
 *
 * \param context           The context for this handler (the
 *                          \ref comment_filter instance).
 * \param msg               A message for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(comment_filter_message_callback)(
    void* context, const CPARSE_SYM(message)* msg);

/**
 * \brief Event handler callback for \ref comment_filter.
 *
 * \param context           The context for this handler (the
 *                          \ref commant_filter instance).
 * \param ev                An event for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(comment_filter_event_callback)(
    void* context, const CPARSE_SYM(event)* ev);

/**
 * \brief Clear and free cached file.
 *
 * \param filter            The filter for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(comment_filter_cached_file_clear)(
    CPARSE_SYM(comment_filter)* filter);

/**
 * \brief Set the cached file and position, clearing the previous cached file if
 * necessary.
 *
 * \param filter            The filter for this operation.
 * \param pos               The position to use for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(comment_filter_cached_file_position_set)(
    CPARSE_SYM(comment_filter)* filter, const CPARSE_SYM(cursor)* pos);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_comment_filter_internal_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    static inline int sym ## comment_filter_message_callback( \
        void* x, const CPARSE_SYM(message)* y) { \
            return CPARSE_SYM(comment_filter_message_callback)(x,y); } \
    static inline int sym ## comment_filter_event_callback( \
        void* x, const CPARSE_SYM(event)* y) { \
            return CPARSE_SYM(comment_filter_event_callback)(x,y); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_comment_filter_internal_as(sym) \
    __INTERNAL_CPARSE_IMPORT_comment_filter_internal_sym(sym ## _)
#define CPARSE_IMPORT_comment_filter_internal \
    __INTERNAL_CPARSE_IMPORT_comment_filter_internal_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
