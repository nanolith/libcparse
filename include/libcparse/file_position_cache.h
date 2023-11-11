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

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Create a file position cache instance.
 *
 * \param cache             Pointer to the \ref file_position_cache pointer to
 *                          be populated with the created file position cache
 *                          instance on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(file_position_cache_create)(
    CPARSE_SYM(file_position_cache)** filter);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
