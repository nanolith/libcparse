/**
 * \file libcparse/file_position_cache.h
 *
 * \brief The file position cache caches the file and position of an event and
 * rebroadcasts a future event, overwriting its postion with  the cached
 * position and an optional end position.
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
 * \brief This type caches file and position data from an event.
 */
typedef struct CPARSE_SYM(file_position_cache) CPARSE_SYM(file_position_cache);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
