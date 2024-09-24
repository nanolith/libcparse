/**
 * \file event_copy/event_copy_internal.h
 *
 * \brief Internal definitions for the \ref event_copy interface.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/event/detail.h>
#include <libcparse/event/include.h>
#include <libcparse/event/raw_character.h>
#include <libcparse/event_copy.h>

/**
 * \brief The event copy type abstracts cloned events.
 */
struct CPARSE_SYM(event_copy)
{
    union
    {
        CPARSE_SYM(event) event;
        CPARSE_SYM(event_raw_character) event_raw_character;
        CPARSE_SYM(event_include) event_include;
    } detail;
};
