/**
 * \file libcparse/event/detail.h
 *
 * \brief Details for the event type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/cursor.h>
#include <libcparse/event_fwd.h>
#include <stdbool.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

struct CPARSE_SYM(event)
{
    int event_type;
    CPARSE_SYM(cursor) event_cursor;
};

struct CPARSE_SYM(event_raw_character)
{
    CPARSE_SYM(event) hdr;
    int raw_character;
};

struct CPARSE_SYM(event_include)
{
    CPARSE_SYM(event) hdr;
    const char* file;
};

struct CPARSE_SYM(event_string)
{
    CPARSE_SYM(event) hdr;
    const char* str;
};

struct CPARSE_SYM(event_identifier)
{
    CPARSE_SYM(event) hdr;
    const char* id;
};

struct CPARSE_SYM(event_integer_token)
{
    CPARSE_SYM(event) hdr;
    int integer_type;
    union
    {
        long long signed_val;
        unsigned long long unsigned_val;
    } val;
};

struct CPARSE_SYM(event_raw_integer)
{
    CPARSE_SYM(event) hdr;
    int integer_type;
    bool has_sign;
    const char* digits;
};

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
