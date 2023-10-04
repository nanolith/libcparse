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

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
