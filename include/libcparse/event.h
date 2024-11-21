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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_eof)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_whitespace_token)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_newline_token)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_comment_block_begin)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_comment_block_end)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_comment_line_begin)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_comment_line_end)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_left_paren)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_right_paren)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_left_brace)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_right_brace)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_left_bracket)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_right_bracket)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_comma)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_colon)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_semicolon)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_dot)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_arrow)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_plus)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_minus)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_star)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_forward_slash)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_percent)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_logical_and)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_logical_or)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_ampersand)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_pipe)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_caret)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_tilde)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_question)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_equal_compare)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_not_equal_compare)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_equal_assign)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_plus_equal)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_minus_equal)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_times_equal)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_div_equal)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_mod_equal)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_and_equal)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_or_equal)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_xor_equal)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_compl_equal)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_left_shift_equal)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_right_shift_equal)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_bitshift_left)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_bitshift_right)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_less_than)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_greater_than)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_less_than_equal)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a greater than equal token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_greater_than_equal)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of an increment token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_increment)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a decrement token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_decrement)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a not token event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_not)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of an ellipsis token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_ellipsis)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a preprocessor id if token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_preprocessor_id_if)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a preprocessor id ifdef token
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_preprocessor_id_ifdef)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a preprocessor id ifndef token
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_preprocessor_id_ifndef)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a preprocessor id elif token
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_preprocessor_id_elif)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a preprocessor id else token
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_preprocessor_id_else)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a preprocessor id endif token
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_preprocessor_id_endif)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a preprocessor id include token
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_preprocessor_id_include)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a preprocessor id define token
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_preprocessor_id_define)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a preprocessor id undef token
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_preprocessor_id_undef)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a preprocessor id line token
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_preprocessor_id_line)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a preprocessor id error token
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_preprocessor_id_error)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a preprocessor id pragma token
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_preprocessor_id_pragma)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a preprocessor string concat
 * token event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_preprocessor_string_concat)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a preprocessor hash token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_preprocessor_hash)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a _Alignas keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword__Alignas)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a _Alignof keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword__Alignof)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a _Atomic keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword__Atomic)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a _Bool keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword__Bool)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a _Complex keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword__Complex)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a _Generic keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword__Generic)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a _Imaginary keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword__Imaginary)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a _Noreturn keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword__Noreturn)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a _Static_assert keyword token
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword__Static_assert)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a _Thread_local keyword token
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword__Thread_local)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of an auto keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_auto)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a break keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_break)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a case keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_case)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a char keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_char)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a const keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_const)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a continue keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_continue)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a default keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_default)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a do keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_do)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a double keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_double)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of an else keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_else)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of an enum keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_enum)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of an extern keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_extern)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a float keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_float)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a for keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_for)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a goto keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_goto)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of an if keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_if)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of an inline keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_inline)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of an int keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_int)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a long keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_long)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a register keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_register)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a restrict keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_restrict)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a return keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_return)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a short keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_short)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a signed keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_signed)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a sizeof keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_sizeof)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a static keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_static)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a struct keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_struct)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a switch keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_switch)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a typedef keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_typedef)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a union keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_union)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a unsigned keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_unsigned)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a void keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_void)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a volatile keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_volatile)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a while keyword token event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_token_keyword_while)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a preprocessor directive end
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_preprocessor_directive_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of an expression begin event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_expression_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of an expression end event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_expression_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a primary expression begin event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_primary_expression_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a primary expression end event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_primary_expression_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of an expression part begin event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_expression_part_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of an expression part end event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_expression_part_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of an array subscript begin
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_array_subscript_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of an array subscript end
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_array_subscript_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a function call begin expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_function_call_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a function call end expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_function_call_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a dot member deref begin
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_dot_member_deref_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a dot member deref end
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_dot_member_deref_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of an arrow member deref begin
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_arrow_member_deref_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of an arrow member deref end
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_arrow_member_deref_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a postfix increment begin
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_postfix_increment_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a postfix increment end
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_postfix_increment_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a postfix decrement begin
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_postfix_decrement_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a postfix decrement end
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_postfix_decrement_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a compound literal begin
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_compound_literal_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a compound literal end
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_compound_literal_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a prefix increment begin
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_prefix_increment_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a prefix increment end
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_prefix_increment_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a prefix decrement begin
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_prefix_decrement_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a prefix decrement end
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_prefix_decrement_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a unary operation begin
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_unary_operation_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a unary operation end
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_unary_operation_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a sizeof expression begin
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_sizeof_exp_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a sizeof expression end
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_sizeof_exp_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a sizeof type begin
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_sizeof_type_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a sizeof type end
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_sizeof_type_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of an _Alignof type begin
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_alignof_type_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of an _Alignof type end
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_alignof_type_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a cast begin expression event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_cast_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a cast end expression event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_cast_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a multiply begin expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_multiply_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a multiply end expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_multiply_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a divide begin expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_divide_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a divide end expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_divide_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a modulo begin expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_modulo_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a modulo end expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_modulo_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of an add begin expression event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_add_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of an add end expression event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_add_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a sub begin expression event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_sub_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a sub end expression event
 * instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_sub_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a bitshift left begin expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_bitshift_left_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a bitshift left end expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_bitshift_left_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a bitshift right begin
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_bitshift_right_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a bitshift right end
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_bitshift_right_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a less-than begin expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_less_than_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a less-than end expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_less_than_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a greater-than begin expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_greater_than_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a greater-than end expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_greater_than_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a less-than equal begin
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_less_than_equal_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a less-than equal end
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_less_than_equal_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a greater-than equal begin
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_greater_than_equal_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a greater-than equal end
 * expression event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_greater_than_equal_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of an equal-to begin expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_equal_to_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of an equal-to end expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_equal_to_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a not equal-to begin expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_not_equal_to_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a not equal-to end expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_not_equal_to_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a bitwise and begin expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_bitwise_and_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a bitwise and end expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_bitwise_and_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a bitwise xor begin expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_bitwise_xor_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a bitwise xor end expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_bitwise_xor_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a bitwise or begin expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_bitwise_or_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a bitwise or end expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_bitwise_or_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a logical and begin expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_logical_and_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a logical and end expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_logical_and_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a logical or begin expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_logical_or_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a logical or end expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_logical_or_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a conditional begin expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_conditional_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a conditional end expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_conditional_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of an assignment begin expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_assignment_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of an assignment end expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_assignment_end)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a comma begin expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_comma_begin)(
    CPARSE_SYM(event)* ev, const CPARSE_SYM(cursor)* cursor);

/**
 * \brief Perform an in-place initialization of a comma end expression
 * event instance.
 *
 * \param ev                    Pointer to the event to initialize.
 * \param cursor                The event cursor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_init_for_exp_comma_end)(
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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_dispose)(CPARSE_SYM(event)* ev);

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
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_get_type)(const CPARSE_SYM(event)* ev);

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
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_eof( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_eof)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_whitespace_token( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_whitespace_token)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_newline_token( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_newline_token)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_comment_block_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_comment_block_begin)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_comment_block_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_comment_block_end)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_comment_line_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_comment_line_begin)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_comment_line_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_comment_line_end)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_left_paren( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_left_paren)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_right_paren( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_right_paren)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_left_brace( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_left_brace)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_right_brace( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_right_brace)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_left_bracket( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_left_bracket)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_right_bracket( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_right_bracket)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_comma( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_comma)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_colon( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_colon)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_semicolon( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_semicolon)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_dot( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_dot)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_arrow( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_arrow)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_plus( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_plus)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_minus( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_minus)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_star( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_star)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_forward_slash( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_forward_slash)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_percent( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_percent)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_logical_and( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_logical_and)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_logical_or( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_logical_or)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_ampersand( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_ampersand)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_pipe( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_pipe)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_caret( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_caret)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_tilde( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_tilde)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_question( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_question)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_equal_compare( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_equal_compare)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_not_equal_compare( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_not_equal_compare)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_equal_assign( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_equal_assign)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_plus_equal( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_plus_equal)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_minus_equal( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_minus_equal)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_times_equal( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_times_equal)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_div_equal( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_div_equal)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_mod_equal( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_mod_equal)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_and_equal( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_and_equal)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_or_equal( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_or_equal)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_xor_equal( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_xor_equal)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_compl_equal( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_compl_equal)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_left_shift_equal( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_left_shift_equal)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_right_shift_equal( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_right_shift_equal)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_bitshift_left( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_bitshift_left)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_bitshift_right( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_bitshift_right)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_less_than( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_less_than)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_greater_than( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_greater_than)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_less_than_equal( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_less_than_equal)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_greater_than_equal( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_greater_than_equal)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_increment( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_increment)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_decrement( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_decrement)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_not( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_not)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_ellipsis( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_ellipsis)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_preprocessor_id_if( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_preprocessor_id_if)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_preprocessor_id_ifdef( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_token_preprocessor_id_ifdef)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_preprocessor_id_ifndef( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_token_preprocessor_id_ifndef)( \
                    x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_preprocessor_id_elif( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_token_preprocessor_id_elif)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_preprocessor_id_else( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_token_preprocessor_id_else)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_preprocessor_id_endif( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_token_preprocessor_id_endif)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_preprocessor_id_include( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_token_preprocessor_id_include)( \
                    x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_init_for_token_preprocessor_id_define( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_token_preprocessor_id_define)( \
                    x,y); } \
    static inline int sym ## event_init_for_token_preprocessor_id_undef( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_token_preprocessor_id_undef)(x,y); } \
    static inline int sym ## event_init_for_token_preprocessor_id_line( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_token_preprocessor_id_line)(x,y); } \
    static inline int sym ## event_init_for_token_preprocessor_id_error( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_token_preprocessor_id_error)(x,y); } \
    static inline int sym ## event_init_for_token_preprocessor_id_pragma( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_token_preprocessor_id_pragma)( \
                    x,y); } \
    static inline int sym ## event_init_for_token_preprocessor_string_concat( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_token_preprocessor_string_concat)( \
                    x,y); } \
    static inline int sym ## event_init_for_token_preprocessor_hash( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_preprocessor_hash)(x,y); } \
    static inline int sym ## event_init_for_token_keyword__Alignas( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword__Alignas)(x,y); } \
    static inline int sym ## event_init_for_token_keyword__Alignof( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword__Alignof)(x,y); } \
    static inline int sym ## event_init_for_token_keyword__Atomic( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword__Atomic)(x,y); } \
    static inline int sym ## event_init_for_token_keyword__Bool( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword__Bool)(x,y); } \
    static inline int sym ## event_init_for_token_keyword__Complex( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword__Complex)(x,y); } \
    static inline int sym ## event_init_for_token_keyword__Generic( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword__Generic)(x,y); } \
    static inline int sym ## event_init_for_token_keyword__Imaginary( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword__Imaginary)(x,y); } \
    static inline int sym ## event_init_for_token_keyword__Noreturn( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword__Noreturn)(x,y); } \
    static inline int sym ## event_init_for_token_keyword__Static_assert( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_token_keyword__Static_assert)( \
                    x,y); } \
    static inline int sym ## event_init_for_token_keyword__Thread_local( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_token_keyword__Thread_local)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_auto( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_auto)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_break( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_break)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_case( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_case)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_char( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_char)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_const( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_const)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_continue( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_continue)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_default( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_default)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_do( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_do)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_double( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_double)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_else( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_else)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_enum( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_enum)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_extern( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_extern)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_float( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_float)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_for( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_for)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_goto( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_goto)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_if( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_if)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_inline( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_inline)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_int( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_int)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_long( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_long)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_register( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_register)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_restrict( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_restrict)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_return( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_return)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_short( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_short)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_signed( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_signed)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_sizeof( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_sizeof)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_static( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_static)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_struct( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_struct)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_switch( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_switch)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_typedef( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_typedef)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_union( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_union)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_unsigned( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_unsigned)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_void( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_void)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_volatile( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_volatile)(x,y); } \
    static inline int sym ## event_init_for_token_keyword_while( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_token_keyword_while)(x,y); } \
    static inline int sym ## event_init_for_preprocessor_directive_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_preprocessor_directive_end)(x,y); } \
    static inline int sym ## event_init_for_expression_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_expression_begin)(x,y); } \
    static inline int sym ## event_init_for_expression_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_expression_end)(x,y); } \
    static inline int sym ## event_init_for_primary_expression_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_primary_expression_begin)(x,y); } \
    static inline int sym ## event_init_for_primary_expression_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_primary_expression_end)(x,y); } \
    static inline int sym ## event_init_for_expression_part_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_expression_part_begin)(x,y); } \
    static inline int sym ## event_init_for_expression_part_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_expression_part_end)(x,y); } \
    static inline int sym ## event_init_for_exp_array_subscript_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_array_subscript_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_array_subscript_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_array_subscript_end)(x,y); } \
    static inline int sym ## event_init_for_exp_function_call_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_function_call_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_function_call_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_function_call_end)(x,y); } \
    static inline int sym ## event_init_for_exp_dot_member_deref_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_dot_member_deref_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_dot_member_deref_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_dot_member_deref_end)(x,y); } \
    static inline int sym ## event_init_for_exp_arrow_member_deref_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_arrow_member_deref_begin)( \
                    x,y); } \
    static inline int sym ## event_init_for_exp_arrow_member_deref_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_arrow_member_deref_end)( \
                    x,y); } \
    static inline int sym ## event_init_for_exp_postfix_increment_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_postfix_increment_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_postfix_increment_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_postfix_increment_end)(x,y); } \
    static inline int sym ## event_init_for_exp_postfix_decrement_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_postfix_decrement_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_postfix_decrement_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_postfix_decrement_end)(x,y); } \
    static inline int sym ## event_init_for_exp_compound_literal_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_compound_literal_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_compound_literal_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_compound_literal_end)(x,y); } \
    static inline int sym ## event_init_for_exp_prefix_increment_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_prefix_increment_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_prefix_increment_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_prefix_increment_end)(x,y); } \
    static inline int sym ## event_init_for_exp_prefix_decrement_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_prefix_decrement_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_prefix_decrement_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_prefix_decrement_end)(x,y); } \
    static inline int sym ## event_init_for_exp_unary_operation_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_unary_operation_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_unary_operation_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_unary_operation_end)(x,y); } \
    static inline int sym ## event_init_for_exp_sizeof_exp_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_sizeof_exp_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_sizeof_exp_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_sizeof_exp_end)(x,y); } \
    static inline int sym ## event_init_for_exp_sizeof_type_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_sizeof_type_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_sizeof_type_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_sizeof_type_end)(x,y); } \
    static inline int sym ## event_init_for_exp_alignof_type_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_alignof_type_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_alignof_type_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_alignof_type_end)(x,y); } \
    static inline int sym ## event_init_for_exp_cast_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_cast_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_cast_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_cast_end)(x,y); } \
    static inline int sym ## event_init_for_exp_multiply_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_multiply_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_multiply_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_multiply_end)(x,y); } \
    static inline int sym ## event_init_for_exp_divide_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_divide_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_divide_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_divide_end)(x,y); } \
    static inline int sym ## event_init_for_exp_modulo_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_modulo_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_modulo_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_modulo_end)(x,y); } \
    static inline int sym ## event_init_for_exp_add_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_add_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_add_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_add_end)(x,y); } \
    static inline int sym ## event_init_for_exp_sub_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_sub_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_sub_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_sub_end)(x,y); } \
    static inline int sym ## event_init_for_exp_bitshift_left_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_bitshift_left_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_bitshift_left_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_bitshift_left_end)(x,y); } \
    static inline int sym ## event_init_for_exp_bitshift_right_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_bitshift_right_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_bitshift_right_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_bitshift_right_end)(x,y); } \
    static inline int sym ## event_init_for_exp_less_than_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_less_than_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_less_than_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_less_than_end)(x,y); } \
    static inline int sym ## event_init_for_exp_greater_than_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_greater_than_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_greater_than_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_greater_than_end)(x,y); } \
    static inline int sym ## event_init_for_exp_less_than_equal_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_less_than_equal_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_less_than_equal_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_less_than_equal_end)(x,y); } \
    static inline int sym ## event_init_for_exp_greater_than_equal_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_greater_than_equal_begin)( \
                    x,y); } \
    static inline int sym ## event_init_for_exp_greater_than_equal_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return \
                CPARSE_SYM(event_init_for_exp_greater_than_equal_end)(x,y); } \
    static inline int sym ## event_init_for_exp_equal_to_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_equal_to_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_equal_to_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_equal_to_end)(x,y); } \
    static inline int sym ## event_init_for_exp_not_equal_to_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_not_equal_to_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_not_equal_to_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_not_equal_to_end)(x,y); } \
    static inline int sym ## event_init_for_exp_bitwise_and_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_bitwise_and_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_bitwise_and_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_bitwise_and_end)(x,y); } \
    static inline int sym ## event_init_for_exp_bitwise_xor_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_bitwise_xor_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_bitwise_xor_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_bitwise_xor_end)(x,y); } \
    static inline int sym ## event_init_for_exp_bitwise_or_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_bitwise_or_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_bitwise_or_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_bitwise_or_end)(x,y); } \
    static inline int sym ## event_init_for_exp_logical_and_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_logical_and_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_logical_and_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_logical_and_end)(x,y); } \
    static inline int sym ## event_init_for_exp_logical_or_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_logical_or_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_logical_or_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_logical_or_end)(x,y); } \
    static inline int sym ## event_init_for_exp_conditional_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_conditional_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_conditional_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_conditional_end)(x,y); } \
    static inline int sym ## event_init_for_exp_assignment_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_assignment_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_assignment_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_assignment_end)(x,y); } \
    static inline int sym ## event_init_for_exp_comma_begin( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_comma_begin)(x,y); } \
    static inline int sym ## event_init_for_exp_comma_end( \
        CPARSE_SYM(event)* x, const CPARSE_SYM(cursor)* y) { \
            return CPARSE_SYM(event_init_for_exp_comma_end)(x,y); } \
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
