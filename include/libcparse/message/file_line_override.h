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

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
