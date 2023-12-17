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
 * \brief Perform an in-place initialization of an arrow token event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_arrow)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a plus token event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_plus)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a minus token event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_minus)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a star token event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_star)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a forward slash token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_forward_slash)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a percent token event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_percent)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a logical and token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_logical_and)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a logical or token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_logical_or)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a ampersand token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_ampersand)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a pipe token event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_pipe)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a caret token event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_caret)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a tilde token event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_tilde)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a question token event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_question)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of an equal compare token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_equal_compare)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a not equal compare token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_not_equal_compare)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of an equal assign token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_equal_assign)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a plus equal token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_plus_equal)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a minus equal token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_minus_equal)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a times equal token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_times_equal)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a div equal token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_div_equal)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a mod equal token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_mod_equal)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of an and equal token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_and_equal)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of an or equal token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_or_equal)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of an xor equal token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_xor_equal)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a compl equal token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_compl_equal)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a left shift equal token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_left_shift_equal)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a right shift equal token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_right_shift_equal)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a bitshift left token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_bitshift_left)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a bitshift right token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_bitshift_right)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a less than token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_less_than)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a greater than token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_greater_than)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a less than equal token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_init_for_token_less_than_equal)(
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
    static inline int sym ## event_init_for_token_arrow( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_arrow)(x,y); } \
    static inline int sym ## event_init_for_token_plus( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_plus)(x,y); } \
    static inline int sym ## event_init_for_token_minus( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_minus)(x,y); } \
    static inline int sym ## event_init_for_token_star( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_star)(x,y); } \
    static inline int sym ## event_init_for_token_forward_slash( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_forward_slash)(x,y); } \
    static inline int sym ## event_init_for_token_percent( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_percent)(x,y); } \
    static inline int sym ## event_init_for_token_logical_and( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_logical_and)(x,y); } \
    static inline int sym ## event_init_for_token_logical_or( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_logical_or)(x,y); } \
    static inline int sym ## event_init_for_token_ampersand( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_ampersand)(x,y); } \
    static inline int sym ## event_init_for_token_pipe( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_pipe)(x,y); } \
    static inline int sym ## event_init_for_token_caret( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_caret)(x,y); } \
    static inline int sym ## event_init_for_token_tilde( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_tilde)(x,y); } \
    static inline int sym ## event_init_for_token_question( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_question)(x,y); } \
    static inline int sym ## event_init_for_token_equal_compare( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_equal_compare)(x,y); } \
    static inline int sym ## event_init_for_token_not_equal_compare( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_not_equal_compare)(x,y); } \
    static inline int sym ## event_init_for_token_equal_assign( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_equal_assign)(x,y); } \
    static inline int sym ## event_init_for_token_plus_equal( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_plus_equal)(x,y); } \
    static inline int sym ## event_init_for_token_minus_equal( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_minus_equal)(x,y); } \
    static inline int sym ## event_init_for_token_times_equal( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_times_equal)(x,y); } \
    static inline int sym ## event_init_for_token_div_equal( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_div_equal)(x,y); } \
    static inline int sym ## event_init_for_token_mod_equal( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_mod_equal)(x,y); } \
    static inline int sym ## event_init_for_token_and_equal( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_and_equal)(x,y); } \
    static inline int sym ## event_init_for_token_or_equal( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_or_equal)(x,y); } \
    static inline int sym ## event_init_for_token_xor_equal( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_xor_equal)(x,y); } \
    static inline int sym ## event_init_for_token_compl_equal( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_compl_equal)(x,y); } \
    static inline int sym ## event_init_for_token_left_shift_equal( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_left_shift_equal)(x,y); } \
    static inline int sym ## event_init_for_token_right_shift_equal( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_right_shift_equal)(x,y); } \
    static inline int sym ## event_init_for_token_bitshift_left( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_bitshift_left)(x,y); } \
    static inline int sym ## event_init_for_token_bitshift_right( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_bitshift_right)(x,y); } \
    static inline int sym ## event_init_for_token_less_than( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_less_than)(x,y); } \
    static inline int sym ## event_init_for_token_greater_than( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_greater_than)(x,y); } \
    static inline int sym ## event_init_for_token_less_than_equal( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_less_than_equal)(x,y); } \
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
