/**
 * \file libcparse/event/integer.h
 *
 * \brief The \ref event_integer_token type represents integer token events.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/cursor.h>
#include <libcparse/event.h>
#include <libcparse/function_decl.h>
#include <libcparse/integer_type.h>
#include <stdint.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The integer event type represents an integer constant token.
 */
typedef struct CPARSE_SYM(event_integer_token) CPARSE_SYM(event_integer_token);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Perform an in-place initialization of a signed int \ref
 * event_integer_token instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param cursor            The event cursor.
 * \param val               The value of this token
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int FN_DECL_MUST_CHECK CPARSE_SYM(event_integer_token_init_for_signed_int)(
    CPARSE_SYM(event_integer_token)* ev, const CPARSE_SYM(cursor)* cursor,
    int val);

/**
 * \brief Perform an in-place initialization of an unsigned int \ref
 * event_integer_token instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param cursor            The event cursor.
 * \param val               The value of this token
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int FN_DECL_MUST_CHECK CPARSE_SYM(event_integer_token_init_for_unsigned_int)(
    CPARSE_SYM(event_integer_token)* ev, const CPARSE_SYM(cursor)* cursor,
    unsigned int val);

/**
 * \brief Perform an in-place initialization of a signed long \ref
 * event_integer_token instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param cursor            The event cursor.
 * \param val               The value of this token
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int FN_DECL_MUST_CHECK CPARSE_SYM(event_integer_token_init_for_signed_long)(
    CPARSE_SYM(event_integer_token)* ev, const CPARSE_SYM(cursor)* cursor,
    long val);

/**
 * \brief Perform an in-place initialization of an unsigned long \ref
 * event_integer_token instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param cursor            The event cursor.
 * \param val               The value of this token
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int FN_DECL_MUST_CHECK CPARSE_SYM(event_integer_token_init_for_unsigned_long)(
    CPARSE_SYM(event_integer_token)* ev, const CPARSE_SYM(cursor)* cursor,
    unsigned long val);

/**
 * \brief Perform an in-place initialization of a signed long long \ref
 * event_integer_token instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param cursor            The event cursor.
 * \param val               The value of this token
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_integer_token_init_for_signed_long_long)(
    CPARSE_SYM(event_integer_token)* ev, const CPARSE_SYM(cursor)* cursor,
    long long val);

/**
 * \brief Perform an in-place initialization of an unsigned long long \ref
 * event_integer_token instance.
 *
 * \param ev                Pointer to the event to initialize.
 * \param cursor            The event cursor.
 * \param val               The value of this token
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero failure code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_integer_token_init_for_unsigned_long_long)(
    CPARSE_SYM(event_integer_token)* ev, const CPARSE_SYM(cursor)* cursor,
    unsigned long long val);

/**
 * \brief Perform an in-place disposal of an \ref event_integer_token instance.
 *
 * \param ev                Pointer to the event to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK CPARSE_SYM(event_integer_token_dispose)(
    CPARSE_SYM(event_integer_token)* ev);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Attempt to convert this \ref event_integer_token to a char, returning
 * a status indicating whether the conversion was successful.
 *
 * \param val               Pointer to the value to receive this converted value
 *                          on success.
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK CPARSE_SYM(event_integer_token_convert_to_char)(
    char* val, const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Attempt to convert this \ref event_integer_token to an unsigned char,
 * returning a status indicating whether the conversion was successful.
 *
 * \param val               Pointer to the value to receive this converted value
 *                          on success.
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_integer_token_convert_to_unsigned_char)(
    unsigned char* val, const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Attempt to convert this \ref event_integer_token to a short, returning
 * a status indicating whether the conversion was successful.
 *
 * \param val               Pointer to the value to receive this converted value
 *                          on success.
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK CPARSE_SYM(event_integer_token_convert_to_short)(
    short* val, const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Attempt to convert this \ref event_integer_token to an unsigned short,
 * returning a status indicating whether the conversion was successful.
 *
 * \param val               Pointer to the value to receive this converted value
 *                          on success.
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_integer_token_convert_to_unsigned_short)(
    unsigned short* val, const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Attempt to convert this \ref event_integer_token to an int, returning
 * a status indicating whether the conversion was successful.
 *
 * \param val               Pointer to the value to receive this converted value
 *                          on success.
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK CPARSE_SYM(event_integer_token_convert_to_int)(
    int* val, const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Attempt to convert this \ref event_integer_token to an unsigned int,
 * returning a status indicating whether the conversion was successful.
 *
 * \param val               Pointer to the value to receive this converted value
 *                          on success.
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK CPARSE_SYM(event_integer_token_convert_to_unsigned_int)(
    unsigned int* val, const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Attempt to convert this \ref event_integer_token to a long, returning
 * a status indicating whether the conversion was successful.
 *
 * \param val               Pointer to the value to receive this converted value
 *                          on success.
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK CPARSE_SYM(event_integer_token_convert_to_long)(
    long* val, const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Attempt to convert this \ref event_integer_token to an unsigned long,
 * returning a status indicating whether the conversion was successful.
 *
 * \param val               Pointer to the value to receive this converted value
 *                          on success.
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_integer_token_convert_to_unsigned_long)(
    unsigned long* val, const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Attempt to convert this \ref event_integer_token to a long long,
 * returning a status indicating whether the conversion was successful.
 *
 * \param val               Pointer to the value to receive this converted value
 *                          on success.
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK CPARSE_SYM(event_integer_token_convert_to_long_long)(
    long long* val, const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Attempt to convert this \ref event_integer_token to an unsigned long
 * long, returning a status indicating whether the conversion was successful.
 *
 * \param val               Pointer to the value to receive this converted value
 *                          on success.
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK
CPARSE_SYM(event_integer_token_convert_to_unsigned_long_long)(
    unsigned long long* val, const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Attempt to convert this \ref event_integer_token to an int8_t,
 * returning a status indicating whether the conversion was successful.
 *
 * \param val               Pointer to the value to receive this converted value
 *                          on success.
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK CPARSE_SYM(event_integer_token_convert_to_int8)(
    int8_t* val, const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Attempt to convert this \ref event_integer_token to a uint8_t,
 * returning a status indicating whether the conversion was successful.
 *
 * \param val               Pointer to the value to receive this converted value
 *                          on success.
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK CPARSE_SYM(event_integer_token_convert_to_uint8)(
    uint8_t* val, const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Attempt to convert this \ref event_integer_token to an int16_t,
 * returning a status indicating whether the conversion was successful.
 *
 * \param val               Pointer to the value to receive this converted value
 *                          on success.
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK CPARSE_SYM(event_integer_token_convert_to_int16)(
    int16_t* val, const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Attempt to convert this \ref event_integer_token to a uint16_t,
 * returning a status indicating whether the conversion was successful.
 *
 * \param val               Pointer to the value to receive this converted value
 *                          on success.
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK CPARSE_SYM(event_integer_token_convert_to_uint16)(
    uint16_t* val, const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Attempt to convert this \ref event_integer_token to an int32_t,
 * returning a status indicating whether the conversion was successful.
 *
 * \param val               Pointer to the value to receive this converted value
 *                          on success.
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK CPARSE_SYM(event_integer_token_convert_to_int32)(
    int32_t* val, const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Attempt to convert this \ref event_integer_token to a uint32_t,
 * returning a status indicating whether the conversion was successful.
 *
 * \param val               Pointer to the value to receive this converted value
 *                          on success.
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK CPARSE_SYM(event_integer_token_convert_to_uint32)(
    uint32_t* val, const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Attempt to convert this \ref event_integer_token to an int64_t,
 * returning a status indicating whether the conversion was successful.
 *
 * \param val               Pointer to the value to receive this converted value
 *                          on success.
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK CPARSE_SYM(event_integer_token_convert_to_int64)(
    int64_t* val, const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Attempt to convert this \ref event_integer_token to a uint64_t,
 * returning a status indicating whether the conversion was successful.
 *
 * \param val               Pointer to the value to receive this converted value
 *                          on success.
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK CPARSE_SYM(event_integer_token_convert_to_uint64)(
    uint64_t* val, const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Perform a potentially lossy conversion to char.
 *
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
char CPARSE_SYM(event_integer_token_coerce_char)(
    const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Perform a potentially lossy conversion to unsigned char.
 *
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
unsigned char CPARSE_SYM(event_integer_token_coerce_unsigned_char)(
    const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Perform a potentially lossy conversion to short.
 *
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
short CPARSE_SYM(event_integer_token_coerce_short)(
    const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Perform a potentially lossy conversion to unsigned short.
 *
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
unsigned short CPARSE_SYM(event_integer_token_coerce_unsigned_short)(
    const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Perform a potentially lossy conversion to int.
 *
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_integer_token_coerce_int)(
    const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Perform a potentially lossy conversion to unsigned int.
 *
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
unsigned int CPARSE_SYM(event_integer_token_coerce_unsigned_int)(
    const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Perform a potentially lossy conversion to long.
 *
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
long CPARSE_SYM(event_integer_token_coerce_long)(
    const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Perform a potentially lossy conversion to unsigned long.
 *
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
unsigned long CPARSE_SYM(event_integer_token_coerce_unsigned_long)(
    const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Perform a potentially lossy conversion to long long.
 *
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
long long CPARSE_SYM(event_integer_token_coerce_long_long)(
    const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Perform a potentially lossy conversion to unsigned long long.
 *
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
unsigned long long CPARSE_SYM(event_integer_token_coerce_unsigned_long_long)(
    const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Perform a potentially lossy conversion to int8_t.
 *
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int8_t CPARSE_SYM(event_integer_token_coerce_int8)(
    const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Perform a potentially lossy conversion to uint8_t.
 *
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
uint8_t CPARSE_SYM(event_integer_token_coerce_uint8)(
    const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Perform a potentially lossy conversion to int16_t.
 *
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int16_t CPARSE_SYM(event_integer_token_coerce_int16)(
    const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Perform a potentially lossy conversion to uint16_t.
 *
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
uint16_t CPARSE_SYM(event_integer_token_coerce_uint16)(
    const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Perform a potentially lossy conversion to int32_t.
 *
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int32_t CPARSE_SYM(event_integer_token_coerce_int32)(
    const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Perform a potentially lossy conversion to uint32_t.
 *
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
uint32_t CPARSE_SYM(event_integer_token_coerce_uint32)(
    const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Perform a potentially lossy conversion to int64_t.
 *
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int64_t CPARSE_SYM(event_integer_token_coerce_int64)(
    const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Perform a potentially lossy conversion to uint64_t.
 *
 * \param ev                The event for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
uint64_t CPARSE_SYM(event_integer_token_coerce_uint64)(
    const CPARSE_SYM(event_integer_token)* ev);

/**
 * \brief Attempt to downcast an \ref event to an \ref event_integer_token.
 *
 * \param s_ev              Pointer to the event pointer to receive the downcast
 *                          instance on success.
 * \param ev                The \ref event pointer to attempt to downcast to the
 *                          derived type.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int FN_DECL_MUST_CHECK CPARSE_SYM(event_downcast_to_event_integer_token)(
    CPARSE_SYM(event_integer_token)** s_ev, CPARSE_SYM(event)* ev);

/**
 * \brief Upcast an \ref event_integer_token to an \ref event.
 *
 * \param ev                The \ref event_integer_token to upcast.
 *
 * \returns the \ref event instance for this event.
 */
CPARSE_SYM(event)* CPARSE_SYM(event_integer_token_upcast)(
    CPARSE_SYM(event_integer_token)* ev);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_event_integer_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(event_integer_token) sym ## event_integer_token; \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_integer_token_init_for_signed_int( \
        CPARSE_SYM(event_integer_token)* x, const CPARSE_SYM(cursor)* y, \
        int z) { \
            return \
                CPARSE_SYM(event_integer_token_init_for_signed_int)(x,y,z); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_integer_token_init_for_unsigned_int( \
        CPARSE_SYM(event_integer_token)* x, const CPARSE_SYM(cursor)* y, \
        unsigned int z) { \
            return \
                CPARSE_SYM(event_integer_token_init_for_unsigned_int)( \
                    x,y,z); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_integer_token_init_for_signed_long( \
        CPARSE_SYM(event_integer_token)* x, const CPARSE_SYM(cursor)* y, \
        long z) { \
            return \
                CPARSE_SYM(event_integer_token_init_for_signed_long)(x,y,z); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_integer_token_init_for_unsigned_long( \
        CPARSE_SYM(event_integer_token)* x, const CPARSE_SYM(cursor)* y, \
        unsigned long z) { \
            return \
                CPARSE_SYM(event_integer_token_init_for_unsigned_long)( \
                    x,y,z); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_integer_token_init_for_signed_long_long( \
        CPARSE_SYM(event_integer_token)* x, const CPARSE_SYM(cursor)* y, \
        long long z) { \
            return \
                CPARSE_SYM(event_integer_token_init_for_signed_long_long)( \
                    x,y,z); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_integer_token_init_for_unsigned_long_long( \
        CPARSE_SYM(event_integer_token)* x, const CPARSE_SYM(cursor)* y, \
        unsigned long long z) { \
            return \
                CPARSE_SYM(event_integer_token_init_for_unsigned_long_long)( \
                    x,y,z); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_integer_token_dispose( \
        CPARSE_SYM(event_integer_token)* x) { \
            return CPARSE_SYM(event_integer_token_dispose)(x); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_integer_token_convert_to_char( \
        char* x, const CPARSE_SYM(event_integer_token)* y) { \
            return CPARSE_SYM(event_integer_token_convert_to_char)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_integer_token_convert_to_unsigned_char( \
        unsigned char* x, const CPARSE_SYM(event_integer_token)* y) { \
            return \
                CPARSE_SYM(event_integer_token_convert_to_unsigned_char)( \
                    x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_integer_token_convert_to_short( \
        short* x, const CPARSE_SYM(event_integer_token)* y) { \
            return CPARSE_SYM(event_integer_token_convert_to_short)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_integer_token_convert_to_unsigned_short( \
        unsigned short* x, const CPARSE_SYM(event_integer_token)* y) { \
            return \
                CPARSE_SYM(event_integer_token_convert_to_unsigned_short)( \
                    x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_integer_token_convert_to_int( \
        int* x, const CPARSE_SYM(event_integer_token)* y) { \
            return CPARSE_SYM(event_integer_token_convert_to_int)(x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_integer_token_convert_to_unsigned_int( \
        unsigned int* x, const CPARSE_SYM(event_integer_token)* y) { \
            return \
                CPARSE_SYM(event_integer_token_convert_to_unsigned_int)( \
                    x,y); } \
    static inline int FN_DECL_MUST_CHECK \
    sym ## event_integer_token_convert_to_long( \
        long* x, const CPARSE_SYM(event_integer_token)* y) { \
            return CPARSE_SYM(event_integer_token_convert_to_long)(x,y); } \
    static inline int sym ## event_integer_token_convert_to_unsigned_long( \
        unsigned long* x, const CPARSE_SYM(event_integer_token)* y) { \
            return \
                CPARSE_SYM(event_integer_token_convert_to_unsigned_long)( \
                    x,y); } \
    static inline int sym ## event_integer_token_convert_to_long_long( \
        long long* x, const CPARSE_SYM(event_integer_token)* y) { \
            return \
                CPARSE_SYM(event_integer_token_convert_to_long_long)(x,y); } \
    static inline int \
    sym ## event_integer_token_convert_to_unsigned_long_long( \
        unsigned long long* x, const CPARSE_SYM(event_integer_token)* y) { \
            return \
                CPARSE_SYM(event_integer_token_convert_to_unsigned_long_long)( \
                    x,y); } \
    static inline int sym ## event_integer_token_convert_to_int8( \
        int8_t* x, const CPARSE_SYM(event_integer_token)* y) { \
            return CPARSE_SYM(event_integer_token_convert_to_int8)(x,y); } \
    static inline int sym ## event_integer_token_convert_to_uint8( \
        uint8_t* x, const CPARSE_SYM(event_integer_token)* y) { \
            return CPARSE_SYM(event_integer_token_convert_to_uint8)(x,y); } \
    static inline int sym ## event_integer_token_convert_to_int16( \
        int16_t* x, const CPARSE_SYM(event_integer_token)* y) { \
            return CPARSE_SYM(event_integer_token_convert_to_int16)(x,y); } \
    static inline int sym ## event_integer_token_convert_to_uint16( \
        uint16_t* x, const CPARSE_SYM(event_integer_token)* y) { \
            return CPARSE_SYM(event_integer_token_convert_to_uint16)(x,y); } \
    static inline int sym ## event_integer_token_convert_to_int32( \
        int32_t* x, const CPARSE_SYM(event_integer_token)* y) { \
            return CPARSE_SYM(event_integer_token_convert_to_int32)(x,y); } \
    static inline int sym ## event_integer_token_convert_to_uint32( \
        uint32_t* x, const CPARSE_SYM(event_integer_token)* y) { \
            return CPARSE_SYM(event_integer_token_convert_to_uint32)(x,y); } \
    static inline int sym ## event_integer_token_convert_to_int64( \
        int64_t* x, const CPARSE_SYM(event_integer_token)* y) { \
            return CPARSE_SYM(event_integer_token_convert_to_int64)(x,y); } \
    static inline int sym ## event_integer_token_convert_to_uint64( \
        uint64_t* x, const CPARSE_SYM(event_integer_token)* y) { \
            return CPARSE_SYM(event_integer_token_convert_to_uint64)(x,y); } \
    static inline char sym ## event_integer_token_coerce_char( \
        const CPARSE_SYM(event_integer_token)* x) { \
            return CPARSE_SYM(event_integer_token_coerce_char)(x); } \
    static inline unsigned char \
    sym ## event_integer_token_coerce_unsigned_char( \
        const CPARSE_SYM(event_integer_token)* x) { \
            return CPARSE_SYM(event_integer_token_coerce_unsigned_char)(x); } \
    static inline short sym ## event_integer_token_coerce_short( \
        const CPARSE_SYM(event_integer_token)* x) { \
            return CPARSE_SYM(event_integer_token_coerce_short)(x); } \
    static inline unsigned short \
    sym ## event_integer_token_coerce_unsigned_short( \
        const CPARSE_SYM(event_integer_token)* x) { \
            return CPARSE_SYM(event_integer_token_coerce_unsigned_short)(x); } \
    static inline int sym ## event_integer_token_coerce_int( \
        const CPARSE_SYM(event_integer_token)* x) { \
            return CPARSE_SYM(event_integer_token_coerce_int)(x); } \
    static inline unsigned int sym ## event_integer_token_coerce_unsigned_int( \
        const CPARSE_SYM(event_integer_token)* x) { \
            return CPARSE_SYM(event_integer_token_coerce_unsigned_int)(x); } \
    static inline long sym ## event_integer_token_coerce_long( \
        const CPARSE_SYM(event_integer_token)* x) { \
            return CPARSE_SYM(event_integer_token_coerce_long)(x); } \
    static inline unsigned long \
    sym ## event_integer_token_coerce_unsigned_long( \
        const CPARSE_SYM(event_integer_token)* x) { \
            return CPARSE_SYM(event_integer_token_coerce_unsigned_long)(x); } \
    static inline long long sym ## event_integer_token_coerce_long_long( \
        const CPARSE_SYM(event_integer_token)* x) { \
            return CPARSE_SYM(event_integer_token_coerce_long_long)(x); } \
    static inline unsigned long long \
    sym ## event_integer_token_coerce_unsigned_long_long( \
        const CPARSE_SYM(event_integer_token)* x) { \
            return \
                CPARSE_SYM(event_integer_token_coerce_unsigned_long_long)( \
                    x); } \
    static inline int8_t sym ## event_integer_token_coerce_int8( \
        const CPARSE_SYM(event_integer_token)* x) { \
            return CPARSE_SYM(event_integer_token_coerce_int8)(x); } \
    static inline uint8_t sym ## event_integer_token_coerce_uint8( \
        const CPARSE_SYM(event_integer_token)* x) { \
            return CPARSE_SYM(event_integer_token_coerce_uint8)(x); } \
    static inline int16_t sym ## event_integer_token_coerce_int16( \
        const CPARSE_SYM(event_integer_token)* x) { \
            return CPARSE_SYM(event_integer_token_coerce_int16)(x); } \
    static inline uint16_t sym ## event_integer_token_coerce_uint16( \
        const CPARSE_SYM(event_integer_token)* x) { \
            return CPARSE_SYM(event_integer_token_coerce_uint16)(x); } \
    static inline int32_t sym ## event_integer_token_coerce_int32( \
        const CPARSE_SYM(event_integer_token)* x) { \
            return CPARSE_SYM(event_integer_token_coerce_int32)(x); } \
    static inline uint32_t sym ## event_integer_token_coerce_uint32( \
        const CPARSE_SYM(event_integer_token)* x) { \
            return CPARSE_SYM(event_integer_token_coerce_uint32)(x); } \
    static inline int64_t sym ## event_integer_token_coerce_int64( \
        const CPARSE_SYM(event_integer_token)* x) { \
            return CPARSE_SYM(event_integer_token_coerce_int64)(x); } \
    static inline uint64_t sym ## event_integer_token_coerce_uint64( \
        const CPARSE_SYM(event_integer_token)* x) { \
            return CPARSE_SYM(event_integer_token_coerce_uint64)(x); } \
    static inline int sym ## event_downcast_to_event_integer_token( \
        CPARSE_SYM(event_integer_token)** x, CPARSE_SYM(event)* y) { \
            return CPARSE_SYM(event_downcast_to_event_integer_token)(x,y); } \
    static inline CPARSE_SYM(event)* sym ## event_integer_token_upcast( \
        CPARSE_SYM(event_integer_token)* x) { \
            return CPARSE_SYM(event_integer_token_upcast)(x); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_event_integer_as(sym) \
    __INTERNAL_CPARSE_IMPORT_event_integer_sym(sym ## _)
#define CPARSE_IMPORT_event_integer \
    __INTERNAL_CPARSE_IMPORT_event_integer_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
