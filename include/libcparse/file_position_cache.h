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

#include <libcparse/cursor.h>
#include <libcparse/event_fwd.h>
#include <libcparse/event_reactor_fwd.h>
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
    CPARSE_SYM(file_position_cache)** cache);

/**
 * \brief Release a file position cache instance, releasing any internal
 * resources it may own.
 *
 * \param cache             The \ref line_wrap_filter instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(file_position_cache_release)(
    CPARSE_SYM(file_position_cache)* cache);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Set the \ref file_position_cache file and position.
 *
 * \param cache             The \ref file_position_cache instance for this
 *                          operation.
 * \param file              The file to cache.
 * \param position          The position to cache.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(file_position_cache_set)(
    CPARSE_SYM(file_position_cache)* cache, const char* file,
    const CPARSE_SYM(cursor)* position);

/**
 * \brief Clear the \ref file_position_cache.
 *
 * \param cache             The \ref file_position_cache instance for this
 *                          operation.
 */
void CPARSE_SYM(file_position_cache_clear)(
    CPARSE_SYM(file_position_cache)* cache);

/**
 * \brief Get the cached file.
 *
 * \param cache             The \ref file_position_cache instance for this
 *                          operation.
 * \param file              The file pointer pointer to receive this file on
 *                          success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(file_position_cache_file_get)(
    CPARSE_SYM(file_position_cache)* cache, const char** file);

/**
 * \brief Get the cached position.
 *
 * \param cache             The \ref file_position_cache instance for this
 *                          operation.
 * \param pos               The cursor pointer pointer to receive this position
 *                          on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(file_position_cache_position_get)(
    CPARSE_SYM(file_position_cache)* cache,
    const CPARSE_SYM(cursor)** position);

/**
 * \brief Extend the cached position to include this event's position.
 *
 * \param cache             The \ref file_position_cache instance for this
 *                          operation.
 * \param ev                The event to include in this cached position.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(file_position_cache_position_extend)(
    CPARSE_SYM(file_position_cache)* cache, const CPARSE_SYM(event)* ev);

/**
 * \brief Given a cache, event reactor, and character, send a cached raw
 * character event to the event reactor subscribers.
 *
 * \param cache             The \ref file_position_cache instance for this
 *                          operation.
 * \param reactor           The \ref event_reactor for this operation.
 * \param ch                The raw character to send.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(file_position_cache_raw_character_broadcast)(
    CPARSE_SYM(file_position_cache)* cache, CPARSE_SYM(event_reactor)* reactor,
    int ch);

/**
 * \brief Given a cache and event reactor, send a cached whitespace token event
 * to the event reactor subscribers.
 *
 * \param cache             The \ref file_position_cache instance for this
 *                          operation.
 * \param reactor           The \ref event_reactor for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(file_position_cache_whitespace_token_broadcast)(
    CPARSE_SYM(file_position_cache)* cache, CPARSE_SYM(event_reactor)* reactor);

/**
 * \brief Given a cache, event reactor, and event type, send a cached generic
 * event to the event reactor subscribers.
 *
 * \param cache             The \ref file_position_cache instance for this
 *                          operation.
 * \param reactor           The \ref event_reactor for this operation.
 * \param type              The event type.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(file_position_cache_generic_event_broadcast)(
    CPARSE_SYM(file_position_cache)* cache, CPARSE_SYM(event_reactor)* reactor,
    int type);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_file_position_cache_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(file_position_cache) sym ## file_position_cache; \
    static inline int sym ## file_position_cache_create( \
        CPARSE_SYM(file_position_cache)** x) { \
            return CPARSE_SYM(file_position_cache_create)(x); } \
    static inline int sym ## file_position_cache_release( \
        CPARSE_SYM(file_position_cache)* x) { \
            return CPARSE_SYM(file_position_cache_release)(x); } \
    static inline int sym ## file_position_cache_set( \
        CPARSE_SYM(file_position_cache)* x, const char* y, \
        const CPARSE_SYM(cursor)* z) { \
            return CPARSE_SYM(file_position_cache_set)(x,y,z); } \
    static inline void sym ## file_position_cache_clear( \
        CPARSE_SYM(file_position_cache)* x) { \
            CPARSE_SYM(file_position_cache_clear)(x); } \
    static inline int sym ## file_position_cache_file_get( \
        CPARSE_SYM(file_position_cache)* x, const char** y) { \
            return CPARSE_SYM(file_position_cache_file_get)(x,y); } \
    static inline int sym ## file_position_cache_position_get( \
        CPARSE_SYM(file_position_cache)* x, const CPARSE_SYM(cursor)** y) { \
            return CPARSE_SYM(file_position_cache_position_get)(x,y); } \
    static inline int sym ## file_position_cache_position_extend( \
        CPARSE_SYM(file_position_cache)* x, const CPARSE_SYM(event)* y) { \
            return CPARSE_SYM(file_position_cache_position_extend)(x,y); } \
    static inline int sym ## file_position_cache_raw_character_broadcast( \
        CPARSE_SYM(file_position_cache)* x, CPARSE_SYM(event_reactor)* y, \
        int z) { \
            return \
                CPARSE_SYM(file_position_cache_raw_character_broadcast)( \
                    x,y,z); } \
    static inline int sym ## file_position_cache_generic_event_broadcast( \
        CPARSE_SYM(file_position_cache)* x, CPARSE_SYM(event_reactor)* y, \
        int z) { \
            return \
                CPARSE_SYM(file_position_cache_generic_event_broadcast)( \
                    x,y,z); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_file_position_cache_as(sym) \
    __INTERNAL_CPARSE_IMPORT_file_position_cache_sym(sym ## _)
#define CPARSE_IMPORT_file_position_cache \
    __INTERNAL_CPARSE_IMPORT_file_position_cache_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
