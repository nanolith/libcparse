/**
 * \file libcparse/message/detail.h
 *
 * \brief Private \ref message interface details.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/event_handler.h>
#include <libcparse/function_decl.h>
#include <libcparse/input_stream.h>
#include <libcparse/message.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

struct CPARSE_SYM(message)
{
    int msg_type;
};

typedef struct CPARSE_SYM(message) CPARSE_SYM(message);

struct CPARSE_SYM(message_rss_add_input_stream)
{
    CPARSE_SYM(message) hdr;
    CPARSE_SYM(input_stream)* stream;
    char* name;
};

struct CPARSE_SYM(message_subscribe)
{
    CPARSE_SYM(message) hdr;
    CPARSE_SYM(event_handler) handler;
};

struct CPARSE_SYM(message_run)
{
    CPARSE_SYM(message) hdr;
};

struct CPARSE_SYM(message_file_line_override)
{
    CPARSE_SYM(message) hdr;
    char* file;
    unsigned int line;
};

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
