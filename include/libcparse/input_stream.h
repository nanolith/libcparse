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
