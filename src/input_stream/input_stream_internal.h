/**
 * \file src/input_stream/input_stream_internal.h
 *
 * \brief The internal input_stream header.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/input_stream.h>
#include <stddef.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

struct CPARSE_SYM(input_stream)
{
    int (*input_stream_release_fn)(CPARSE_SYM(input_stream)* stream);
    int (*input_stream_read_fn)(CPARSE_SYM(input_stream)* stream, int* ch);
};

/**
 * \brief input stream from descriptor derived type.
 */
typedef struct CPARSE_SYM(input_stream_from_descriptor)
CPARSE_SYM(input_stream_from_descriptor);

struct CPARSE_SYM(input_stream_from_descriptor)
{
    CPARSE_SYM(input_stream) hdr;
    int desc;
};

/**
 * \brief input stream from string derived type.
 */
typedef struct CPARSE_SYM(input_stream_from_string)
CPARSE_SYM(input_stream_from_string);

struct CPARSE_SYM(input_stream_from_string)
{
    CPARSE_SYM(input_stream) hdr;
    char* str;
    size_t curr;
    size_t max;
};

/**
 * \brief Release an input stream from descriptor instance.
 *
 * \param stream                The input stream instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(input_stream_from_descriptor_release)(
    CPARSE_SYM(input_stream)* stream);

/**
 * \brief Read a character from the input stream from descriptor instance.
 *
 * \param stream                The input stream from which this character is
 *                              read.
 * \param ch                    Pointer to be populated with the character read
 *                              on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - ERROR_LIBCPARSE_INPUT_STREAM_EOF on EOF.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(input_stream_from_descriptor_read)(
    CPARSE_SYM(input_stream)* stream, int* ch);

/**
 * \brief Release an input stream from string instance.
 *
 * \param stream                The input stream instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(input_stream_from_string_release)(
    CPARSE_SYM(input_stream)* stream);

/**
 * \brief Read a character from the input stream from string instance.
 *
 * \param stream                The input stream from which this character is
 *                              read.
 * \param ch                    Pointer to be populated with the character read
 *                              on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - ERROR_LIBCPARSE_INPUT_STREAM_EOF on EOF.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(input_stream_from_string_read)(
    CPARSE_SYM(input_stream)* stream, int* ch);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/
#define __INTERNAL_CPARSE_IMPORT_input_stream_internal_sym(sym) \
    CPARSE_BEGIN_EXPORT \
        typedef CPARSE_SYM(input_stream_from_descriptor) \
        sym ## input_stream_from_descriptor; \
        typedef CPARSE_SYM(input_stream_from_string) \
        sym ## input_stream_from_string; \
        static inline int sym ## input_stream_from_descriptor_release ( \
            CPARSE_SYM(input_stream)* x) { \
                return CPARSE_SYM(input_stream_from_descriptor_release)(x); } \
        static inline int sym ## input_stream_from_descriptor_read( \
            CPARSE_SYM(input_stream)* x, int* y) { \
                return CPARSE_SYM(input_stream_from_descriptor_read)(x,y); } \
        static inline int sym ## input_stream_from_string_release( \
            CPARSE_SYM(input_stream)* x) { \
                return CPARSE_SYM(input_stream_from_string_release)(x); } \
        static inline int sym ## input_stream_from_string_read( \
            CPARSE_SYM(input_stream)* x, int* y) { \
                return CPARSE_SYM(input_stream_from_string_read)(x,y); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_input_stream_internal_as(sym) \
    __INTERNAL_CPARSE_IMPORT_input_stream_internal_sym(sym ## _)
#define CPARSE_IMPORT_input_stream_internal \
    __INTERNAL_CPARSE_IMPORT_input_stream_internal_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
