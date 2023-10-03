/**
 * \file libcparse/input_stream.h
 *
 * \brief The input stream abstracts input, which can be from a file, a memory
 * buffer, or from a mock.
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
 * \brief The input stream abstracts input for the parser.
 */
typedef struct CPARSE_SYM(input_stream) CPARSE_SYM(input_stream);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Create an input stream instance from a Unix file descriptor.
 *
 * \note This allocates the instance, storing the result in \p stream. This is a
 * resource that must be released by calling \ref input_stream_release when it
 * is no longer needed. This stream takes ownership of the Unix file descriptor
 * provided in \p desc and will close it when it is released.
 *
 * \param stream                Pointer to the \ref input_stream pointer to be
 *                              populated with the created input stream on
 *                              success.
 * \param desc                  The Unix file descriptor for this stream.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(input_stream_create_from_descriptor)(
    CPARSE_SYM(input_stream)** stream, int desc);

/**
 * \brief Create an input stream instance from a string.
 *
 * \note This allocates the instance, storing the result in \p stream. This is a
 * resource that must be released by calling \ref input_stream_release when it
 * is no longer needed. This stream copies the given string internally; the
 * string parameter remains owned by the caller.
 *
 * \param stream                Pointer to the \ref input_stream pointer to be
 *                              populated with the created input stream on
 *                              success.
 * \param str                   The string to copy for use as input.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(input_stream_create_from_strting)(
    CPARSE_SYM(input_stream)** stream, const char* str);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Read a character from the input stream.
 *
 * \param stream                    The input stream from which this character
 *                                  is read.
 * \param ch                        Pointer to be populated with the character
 *                                  read on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - ERROR_LIBCPARSE_INPUT_STREAM_EOF on EOF.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(input_stream_read)(CPARSE_SYM(input_stream)* stream, int* ch);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
