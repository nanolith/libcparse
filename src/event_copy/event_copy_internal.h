/**
 * \file event_copy/event_copy_internal.h
 *
 * \brief Internal definitions for the \ref event_copy interface.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/event_copy.h>
#include <libcparse/event/detail.h>

/**
 * \brief The event copy type abstracts cloned events.
 */
struct CPARSE_SYM(event_copy)
{
    union
    {
        CPARSE_SYM(event) event;
    } detail;
};
