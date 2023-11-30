/**
 * \file raw_stack_scanner/raw_file_line_override_filter_internal.h
 *
 * \brief Internal declarations for \ref raw_file_line_override_filter.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/abstract_parser_fwd.h>
#include <libcparse/event_handler.h>
#include <libcparse/raw_stack_scanner.h>
#include <libcparse/cursor.h>
#include <libcparse/event_reactor_fwd.h>
#include <libcparse/function_decl.h>
#include <stdbool.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

typedef struct CPARSE_SYM(raw_file_line_override_filter)
CPARSE_SYM(raw_file_line_override_filter);

struct CPARSE_SYM(raw_file_line_override_filter)
{
    CPARSE_SYM(raw_stack_scanner)* parent;
    CPARSE_SYM(abstract_parser)* base;
    CPARSE_SYM(event_reactor)* reactor;
    CPARSE_SYM(message_handler) parent_mh;
    bool use_pos;
    CPARSE_SYM(cursor) pos;
    char* file;
};

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Message handler callback for \ref raw_file_line_override_filter.
 *
 * \param context           The context for this handler (the
 *                          \ref raw_file_line_override_filter instance).
 * \param msg               A message for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(raw_file_line_override_filter_message_callback)(
    void* context, const CPARSE_SYM(message)* msg);

/**
 * \brief Event handler callback for \ref raw_file_line_override_filter.
 *
 * \param context           The context for this handler (the
 *                          \ref raw_file_line_override_filter instance).
 * \param ev                An event for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(raw_file_line_override_filter_event_callback)(
    void* context, const CPARSE_SYM(event)* ev);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/
#define __INTERNAL_CPARSE_IMPORT_raw_file_line_override_filter_internal_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    static inline int sym ## raw_file_line_override_filter_message_callback( \
        void* x, const CPARSE_SYM(message)* y) { \
            return \
                CPARSE_SYM(raw_file_line_override_filter_message_callback)( \
                    x,y); } \
    static inline int sym ## raw_file_line_override_filter_event_callback( \
        void* x, const CPARSE_SYM(event)* y) { \
            return \
                CPARSE_SYM(raw_file_line_override_filter_event_callback)( \
                    x,y); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_raw_file_line_override_filter_internal_as(sym) \
    __INTERNAL_CPARSE_IMPORT_raw_file_line_override_filter_internal_sym(sym ## _)
#define CPARSE_IMPORT_raw_file_line_override_filter_internal \
    __INTERNAL_CPARSE_IMPORT_raw_file_line_override_filter_internal_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
