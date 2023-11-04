/**
 * \file libcparse/comment_scanner.h
 *
 * \brief The comment scanner consumes events from the file / line override
 * filter, detecting comments and sending comment related events.
 *
 * Subscribers to this scanner will receive raw character events as from the
 * file / line override filter, except that both line comments and block
 * comments will be denoted with start and end events. All of the characters
 * inside and outside of comments will still be available, but the subscriber
 * can choose to ignore characters within comments. Actual comment start
 * characters will be consumed by this scanner, and instead, subscribers will
 * get comment start and end events.
 *
 * The comment block begin event will correspond to the slash star of a start
 * block comment, and the comment block end event will correspond to the star
 * slash of an end block comment. These characters will not be rebroadcast from
 * this scanner. Likewise, the comment line begin event will correspond to the
 * double slash of a line comment, and the comment line end event will
 * come before a newline character. Unlike the block begin and end events, the
 * newline character will NOT be consumed, as it is needed by downstream
 * parsers.
 *
 * The comment filter consumes events from the comment scanner in order to
 * transform comments into whitespace. The reason for splitting these parsers
 * into separate pieces is so that user code can subscribe to the comment
 * scanner in order to receive verbatim comments. This is useful for
 * documentation generation and comment related code markup in static analysis.
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
 * \brief The \ref comment_scanner detects comments in an input stream.
 */
typedef struct CPARSE_SYM(comment_scanner)
CPARSE_SYM(comment_scanner);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Create a comment scanner.
 *
 * This filter automatically creates a file / line override filter and injects
 * itself into the message chain for the parser stack.
 *
 * \param scanner           Pointer to the \ref comment_scanner pointer to be
 *                          populated with the created comment scanner instance
 *                          on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(comment_scanner_create)(CPARSE_SYM(comment_scanner)** scanner);

/**
 * \brief Release a comment scanner instance, releasing any internal resources
 * it may own.
 *
 * \param scanner           The \ref comment_scanner instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(comment_scanner_release)(CPARSE_SYM(comment_scanner)* scanner);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Get the \ref abstract_parser interface for this scanner.
 *
 * \param scanner           The \ref comment_scanner instance to query.
 *
 * \returns the \ref abstract_parser interface for this scanner.
 */
CPARSE_SYM(abstract_parser)* CPARSE_SYM(comment_scanner_upcast)(
    CPARSE_SYM(comment_scanner)* scanner);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_comment_scanner_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(comment_scanner) sym ## comment_scanner; \
    static inline int sym ## comment_scanner_create( \
        CPARSE_SYM(comment_scanner)** x) { \
            return CPARSE_SYM(comment_scanner_create)(x); } \
    static inline int sym ## comment_scanner_release( \
        CPARSE_SYM(comment_scanner)* x) { \
            return CPARSE_SYM(comment_scanner_release)(x); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_comment_scanner_as(sym) \
    __INTERNAL_CPARSE_IMPORT_comment_scanner_sym(sym ## _)
#define CPARSE_IMPORT_comment_scanner \
    __INTERNAL_CPARSE_IMPORT_comment_scanner_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
