/**
 * \file comment_scanner/comment_scanner_internal.h
 *
 * \brief Internal declarations for \ref comment_scanner.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/event_reactor_fwd.h>
#include <libcparse/raw_file_line_override_filter.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

typedef struct CPARSE_SYM(comment_scanner)
CPARSE_SYM(comment_scanner);

struct CPARSE_SYM(comment_scanner)
{
    CPARSE_SYM(raw_file_line_override_filter)* parent;
    CPARSE_SYM(event_reactor)* reactor;
    CPARSE_SYM(message_handler) parent_mh;
    int state;
};

enum CPARSE_SYM(comment_scanner_state)
{
    CPARSE_COMMENT_SCANNER_STATE_INIT =                          0,
    CPARSE_COMMENT_SCANNER_SLASH =                               1,
    CPARSE_COMMENT_SCANNER_IN_BLOCK_COMMENT =                    2,
    CPARSE_COMMENT_SCANNER_IN_BLOCK_COMMENT_STAR =               3,
    CPARSE_COMMENT_SCANNER_IN_LINE_COMMENT =                     4,
    CPARSE_COMMENT_SCANNER_IN_CHAR_SEQUENCE =                    5,
    CPARSE_COMMENT_SCANNER_IN_CHAR_SEQUENCE_BACKSLASH =          6,
    CPARSE_COMMENT_SCANNER_IN_STRING =                           7,
    CPARSE_COMMENT_SCANNER_IN_STRING_BACKSLASH =                 8,
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

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
