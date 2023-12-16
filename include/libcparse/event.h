/**
 * \file libcparse/event.h
 *
 * \brief The event type represents an individual lexer or parser event.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/cursor.h>
#include <libcparse/event/detail.h>
#include <libcparse/event_type.h>
#include <libcparse/function_decl.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The event type abstracts individual lexer or parser events.
 */
typedef struct CPARSE_SYM(event) CPARSE_SYM(event);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Perform an in-place initialization of an EOF event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_eof)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a whitespace token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_whitespace_token)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a newline token event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_newline_token)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a comment block begin event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_comment_block_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a comment block end event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_comment_block_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a comment line begin event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_comment_line_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a comment line end event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_comment_line_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a left paren token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_left_paren)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a right paren token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_right_paren)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a left brace token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_left_brace)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a right brace token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_right_brace)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a left bracket token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_left_bracket)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a right bracket token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_right_bracket)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a comma token event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_comma)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a colon token event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_colon)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a semicolon token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_semicolon)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a dot token event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_dot)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place disposal of an event instance.
 *
 * \param ev                    Pointer to the event to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_dispose)(CPARSE_SYM(event)* ev);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Get the event type for the given event.
 *
 * \param ev                    The event to query.
 *
 * \returns the \ref event_type for this event.
 */
int CPARSE_SYM(event_get_type)(const CPARSE_SYM(event)* ev);

/**
 * \brief Get the cursor for the given event.
 *
 * \param ev                    The event to query.
 *
 * \returns the \ref cursor for this event.
 */
const CPARSE_SYM(cursor)*
CPARSE_SYM(event_get_cursor)(const CPARSE_SYM(event)* ev);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/
#define __INTERNAL_CPARSE_IMPORT_event_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(event) sym ## event; \
    static inline int sym ## event_init_for_eof( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_eof)(x,y); } \
    static inline int sym ## event_init_for_whitespace_token( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_whitespace_token)(x,y); } \
    static inline int sym ## event_init_for_newline_token( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_newline_token)(x,y); } \
    static inline int sym ## event_init_for_comment_block_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_comment_block_begin)(x,y); } \
    static inline int sym ## event_init_for_comment_block_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_comment_block_end)(x,y); } \
    static inline int sym ## event_init_for_comment_line_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_comment_line_begin)(x,y); } \
    static inline int sym ## event_init_for_comment_line_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_comment_line_end)(x,y); } \
    static inline int sym ## event_init_for_token_left_paren( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_left_paren)(x,y); } \
    static inline int sym ## event_init_for_token_right_paren( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_right_paren)(x,y); } \
    static inline int sym ## event_init_for_token_left_brace( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_left_brace)(x,y); } \
    static inline int sym ## event_init_for_token_right_brace( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_right_brace)(x,y); } \
    static inline int sym ## event_init_for_token_left_bracket( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_left_bracket)(x,y); } \
    static inline int sym ## event_init_for_token_right_bracket( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_right_bracket)(x,y); } \
    static inline int sym ## event_init_for_token_comma( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_comma)(x,y); } \
    static inline int sym ## event_init_for_token_colon( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_colon)(x,y); } \
    static inline int sym ## event_init_for_token_semicolon( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_semicolon)(x,y); } \
    static inline int sym ## event_init_for_token_dot( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_dot)(x,y); } \
    static inline int sym ## event_dispose( \
        CPARSE_SYM(event)* x) { \
            return CPARSE_SYM(event_dispose)(x); } \
    static inline int sym ## event_get_type(const CPARSE_SYM(event)* x) { \
        return CPARSE_SYM(event_get_type)(x); } \
    static inline const CPARSE_SYM(cursor)* \
    sym ## event_get_cursor(const CPARSE_SYM(event)* x) { \
        return CPARSE_SYM(event_get_cursor)(x); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_event_as(sym) \
    __INTERNAL_CPARSE_IMPORT_event_sym(sym ## _)
#define CPARSE_IMPORT_event \
    __INTERNAL_CPARSE_IMPORT_event_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
