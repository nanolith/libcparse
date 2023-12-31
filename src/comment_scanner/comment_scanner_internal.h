/**
 * \file comment_scanner/comment_scanner_internal.h
 *
 * \brief Internal declarations for \ref comment_scanner.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/abstract_parser_fwd.h>
#include <libcparse/event_reactor_fwd.h>
#include <libcparse/file_position_cache.h>
#include <libcparse/line_wrap_filter.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

typedef struct CPARSE_SYM(comment_scanner)
CPARSE_SYM(comment_scanner);

struct CPARSE_SYM(comment_scanner)
{
    CPARSE_SYM(line_wrap_filter)* parent;
    CPARSE_SYM(abstract_parser)* base;
    CPARSE_SYM(event_reactor)* reactor;
    CPARSE_SYM(message_handler) parent_mh;
    CPARSE_SYM(file_position_cache)* cache;
    int state;
};

enum CPARSE_SYM(comment_scanner_state)
{
    CPARSE_COMMENT_SCANNER_STATE_INIT =                          0,
    CPARSE_COMMENT_SCANNER_STATE_SLASH =                         1,
    CPARSE_COMMENT_SCANNER_STATE_IN_BLOCK_COMMENT =              2,
    CPARSE_COMMENT_SCANNER_STATE_IN_BLOCK_COMMENT_STAR =         3,
    CPARSE_COMMENT_SCANNER_STATE_IN_LINE_COMMENT =               4,
    CPARSE_COMMENT_SCANNER_STATE_IN_CHAR_SEQUENCE =              5,
    CPARSE_COMMENT_SCANNER_STATE_IN_CHAR_SEQUENCE_BACKSLASH =    6,
    CPARSE_COMMENT_SCANNER_STATE_IN_STRING =                     7,
    CPARSE_COMMENT_SCANNER_STATE_IN_STRING_BACKSLASH =           8,
};

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Message handler callback for \ref comment_scanner.
 *
 * \param context           The context for this handler (the
 *                          \ref comment_scanner instance).
 * \param msg               A message for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(comment_scanner_message_callback)(
    void* context, const CPARSE_SYM(message)* msg);

/**
 * \brief Event handler callback for \ref comment_scanner.
 *
 * \param context           The context for this handler (the
 *                          \ref commant_scanner instance).
 * \param ev                An event for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(comment_scanner_event_callback)(
    void* context, const CPARSE_SYM(event)* ev);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_comment_scanner_internal_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    static inline int sym ## comment_scanner_message_callback( \
        void* x, const CPARSE_SYM(message)* y) { \
            return CPARSE_SYM(comment_scanner_message_callback)(x,y); } \
    static inline int sym ## comment_scanner_event_callback( \
        void* x, const CPARSE_SYM(event)* y) { \
            return CPARSE_SYM(comment_scanner_event_callback)(x,y); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_comment_scanner_internal_as(sym) \
    __INTERNAL_CPARSE_IMPORT_comment_scanner_internal_sym(sym ## _)
#define CPARSE_IMPORT_comment_scanner_internal \
    __INTERNAL_CPARSE_IMPORT_comment_scanner_internal_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
