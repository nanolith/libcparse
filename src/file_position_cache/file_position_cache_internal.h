/**
 * \file file_position_cache/file_position_cache_internal.h
 *
 * \brief Internal declarations for \ref file_position_cache.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

typedef struct CPARSE_SYM(file_position_cache) CPARSE_SYM(file_position_cache);

struct CPARSE_SYM(file_position_cache)
{
    char* file;
    CPARSE_SYM(cursor) pos;
};

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
