/**
 * \file libcparse/message/file_line_override.h
 *
 * \brief Message to override the file and line position in the file/line
 * filter.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/function_decl.h>
#include <libcparse/message.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The file/line override message allows a user to override the file and
 * line position of the file/line override filter.
 */
typedef struct CPARSE_SYM(message_file_line_override)
CPARSE_SYM(message_file_line_override);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Initialize a \ref message_file_line_override instance.
 *
 * \param msg               The message to initialize.
 * \param msg_type          The type of file/line override message.
 * \param file              The new name of the file, which is optional and can
 *                          be NULL if unchanged.
 * \param line              The line to override.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_file_line_override_init)(
    CPARSE_SYM(message_file_line_override)* msg, int msg_type,
    const char* file, unsigned int line);

/**
 * \brief Dispose of a \ref message_file_line_override instance.
 *
 * \param msg               The message to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_file_line_override_dispose)(
    CPARSE_SYM(message_file_line_override)* msg);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Get the \ref file associated with a \ref message_file_line_override
 * instance.
 *
 * \param msg               The message to query.
 *
 * \returns the \ref file associated with this message or NULL if unset.
 */
const char*
CPARSE_SYM(message_file_line_override_file_get)(
    const CPARSE_SYM(message_file_line_override)* msg);

/**
 * \brief Get the \ref line associated with a \ref message_file_line_override
 * instance.
 *
 * \param msg               The message to query.
 *
 * \returns the \ref line associated with this message.
 */
unsigned int
CPARSE_SYM(message_file_line_override_line_get)(
    const CPARSE_SYM(message_file_line_override)* msg);

/**
 * \brief Attempt to downcast a \ref message to a
 * \ref message_file_line_override.
 *
 * \param flo_msg           Pointer to the message pointer to receive the
 *                          downcast instance on success.
 * \param msg               The \ref message pointer to attempt to downcast to
 *                          the derived type.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(message_downcast_to_message_file_line_override)(
    CPARSE_SYM(message_file_line_override)** flo_msg, CPARSE_SYM(message)* msg);

/**
 * \brief Upcast a \ref message_file_line_override to a \ref message.
 *
 * \param msg               The \ref message_file_line_override to upcast.
 *
 * \returns the \ref message instance for this message.
 */
CPARSE_SYM(message)* CPARSE_SYM(message_file_line_override_upcast)(
    CPARSE_SYM(message_file_line_override)* msg);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_message_file_line_override_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(message_file_line_override) \
    sym ## message_file_line_override; \
    static inline int sym ## message_file_line_override_init( \
        CPARSE_SYM(message_file_line_override)* w, int x, const char* y, \
        unsigned int z) { \
            return CPARSE_SYM(message_file_line_override_init)(w,x,y,z); } \
    static inline int sym ## message_file_line_override_dispose( \
        CPARSE_SYM(message_file_line_override)* x) { \
            return CPARSE_SYM(message_file_line_override_dispose)(x); } \
    static inline const char* sym ## message_file_line_override_file_get( \
        const CPARSE_SYM(message_file_line_override)* x) { \
            return CPARSE_SYM(message_file_line_override_file_get)(x); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_message_file_line_override_as(sym) \
    __INTERNAL_CPARSE_IMPORT_message_file_line_override_sym(sym ## _)
#define CPARSE_IMPORT_message_file_line_override \
    __INTERNAL_CPARSE_IMPORT_message_file_line_override_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
