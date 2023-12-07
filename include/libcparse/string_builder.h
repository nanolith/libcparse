/**
 * \file libcparse/string_builder.h
 *
 * \brief The \ref string_builder type builds a string in a more efficient and
 * generic way by using internal chunks that can be bucket allocated.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/function_decl.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The string builder type builds strings.
 */
typedef struct CPARSE_SYM(string_builder) CPARSE_SYM(string_builder);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Create a string builder instance.
 *
 * \param builder           Pointer to the string builder pointer to receive
 *                          this instance on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(string_builder_create)(CPARSE_SYM(string_builder)** builder);

/**
 * \brief Release a string builder instance, releasing any internal resources it
 * may own.
 *
 * \param builder           The \ref string_builder instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(string_builder_release)(CPARSE_SYM(string_builder)* builder);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Add a character to the string builder.
 *
 * \param builder           The string builder instance for this operation.
 * \param ch                The character to add.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(string_builder_add_character)(
    CPARSE_SYM(string_builder)* builder, int ch);

/**
 * \brief Add a string to the string builder.
 *
 * \param builder           The string builder instance for this operation.
 * \param str               The string to add.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(string_builder_add_string)(
    CPARSE_SYM(string_builder)* builder, const char* ch);

/**
 * \brief Build a string from the current string builder.
 *
 * \param str               Pointer to the string pointer to receive the string
 *                          on success. On success, this string is owned by the
 *                          caller and must be freed when no longer needed.
 * \param builder           The string builder for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(string_builder_build)(
    char** str, CPARSE_SYM(string_builder)* builder);

/**
 * \brief Clear the current string builder instance, returning its internal
 * state to empty.
 *
 * \param builder           The string builder for this operation.
 */
void CPARSE_SYM(string_builder_clear)(CPARSE_SYM(string_builder)* builder);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_string_builder_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(string_builder) sym ## string_builder; \
    static inline int sym ## string_builder_create( \
        CPARSE_SYM(string_builder)** x) { \
            return CPARSE_SYM(string_builder_create)(x); } \
    static inline int sym ## string_builder_release( \
        CPARSE_SYM(string_builder)* x) { \
            return CPARSE_SYM(string_builder_release)(x); } \
    static inline int sym ## string_builder_add_character( \
        CPARSE_SYM(string_builder)* x, int y) { \
            return CPARSE_SYM(string_builder_add_character)(x,y); } \
    static inline int sym ## string_builder_add_string( \
        CPARSE_SYM(string_builder)* x, const char* y) { \
            return CPARSE_SYM(string_builder_add_string)(x,y); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_string_builder_as(sym) \
    __INTERNAL_CPARSE_IMPORT_string_builder_sym(sym ## _)
#define CPARSE_IMPORT_string_builder \
    __INTERNAL_CPARSE_IMPORT_string_builder_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
