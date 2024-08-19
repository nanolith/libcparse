/**
 * \file libcparse/event_copy.h
 *
 * \brief The event copy type allows an event to be cloned so that its lifetime
 * exceeds the lifetime of the original event on which it was based.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/event_fwd.h>
#include <libcparse/function_decl.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The event copy type abstracts cloned events.
 */
typedef struct CPARSE_SYM(event_copy) CPARSE_SYM(event_copy);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Create an event copy from the given event.
 *
 * \param cpy                   Pointer to the \ref event_copy pointer to
 *                              receive this \ref event_copy on success.
 * \param ev                    The event to copy.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_copy_create)(
    CPARSE_SYM(event_copy)** cpy, const CPARSE_SYM(event)* ev);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
