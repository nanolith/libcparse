/**
 * \file preprocessor_scanner/preprocessor_scanner_internal.h
 *
 * \brief Internal declarations and definitions for the preprocessor scanner.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/abstract_parser.h>
#include <libcparse/newline_preserving_whitespace_filter.h>
#include <libcparse/event_reactor_fwd.h>
#include <libcparse/file_position_cache.h>
#include <libcparse/string_builder.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

typedef struct CPARSE_SYM(preprocessor_scanner)
CPARSE_SYM(preprocessor_scanner);

struct CPARSE_SYM(preprocessor_scanner)
{
    CPARSE_SYM(newline_preserving_whitespace_filter)* parent;
    CPARSE_SYM(abstract_parser)* base;
    CPARSE_SYM(event_reactor)* reactor;
    CPARSE_SYM(message_handler) parent_mh;
    CPARSE_SYM(file_position_cache)* cache;
    CPARSE_SYM(string_builder)* builder;
    int state;
};

enum CPARSE_SYM(preprocessor_scanner_state)
{
    CPARSE_PREPROCESSOR_SCANNER_STATE_INIT =                            0,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_IDENTIFIER =                   1,
};

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Message handler callback for
 * \ref preprocessor_scanner_message_callback.
 *
 * \param context           The context for this handler (the
 *                          \ref preprocessor_scanner instance).
 * \param msg               A message for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(preprocessor_scanner_message_callback)(
    void* context, const CPARSE_SYM(message)* msg);

/**
 * \brief Event handler callback for \ref preprocessor_scanner_event_callback.
 *
 * \param context           The context for this handler (the
 *                          \ref preprocessor_scanner instance).
 * \param ev                An event for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(preprocessor_scanner_event_callback)(
    void* context, const CPARSE_SYM(event)* ev);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_preprocessor_scanner_internal_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    static inline int \
    sym ## preprocessor_scanner_message_callback( \
        void* x, const CPARSE_SYM(message)* y) { \
            return CPARSE_SYM(preprocessor_scanner_message_callback)(x,y); } \
    static inline int \
    sym ## preprocessor_scanner_event_callback( \
        void* x, const CPARSE_SYM(event)* y) { \
            return CPARSE_SYM(preprocessor_scanner_event_callback)(x,y); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_preprocessor_scanner_internal_as(sym) \
    __INTERNAL_CPARSE_IMPORT_preprocessor_scanner_internal_sym(sym ## _)
#define CPARSE_IMPORT_preprocessor_scanner_internal \
    __INTERNAL_CPARSE_IMPORT_preprocessor_scanner_internal_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
