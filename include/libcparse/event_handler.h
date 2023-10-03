/**
 * \file libcparse/event_handler.h
 *
 * \brief The \ref event_handler reacts to an event.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/event.h>
#include <libcparse/function_decl.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief An event callback function responds to an event.
 *
 * \param context               A user-supplied context pointer given to the
 *                              callback.
 * \param ev                    An event to which this callback is subscribed.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
typedef int (*CPARSE_SYM(event_callback_fn))(
    void* context, const CPARSE_SYM(event)* ev);

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/
#define __INTERNAL_CPARSE_IMPORT_event_handler_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(event_handler) sym ## event_handler; \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_event_handler_as(sym) \
    __INTERNAL_CPARSE_IMPORT_event_handler_sym(sym ## _)
#define CPARSE_IMPORT_event_handler \
    __INTERNAL_CPARSE_IMPORT_event_handler_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
