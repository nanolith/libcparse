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
#include <libcparse/event/identifier.h>
#include <libcparse/event/include.h>
#include <libcparse/event/integer.h>
#include <libcparse/event/raw_character.h>
#include <libcparse/event/raw_character_literal.h>
#include <libcparse/event/raw_integer.h>
#include <libcparse/event/raw_string.h>
#include <libcparse/event/raw_float.h>
#include <libcparse/event/string.h>
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
        CPARSE_SYM(event_string) event_string;
        CPARSE_SYM(event_raw_string_token) event_raw_string_token;
        CPARSE_SYM(event_raw_character_literal) event_raw_character_literal;
        CPARSE_SYM(event_identifier) event_identifier;
        CPARSE_SYM(event_integer_token) event_integer_token;
        CPARSE_SYM(event_raw_integer_token) event_raw_integer_token;
        CPARSE_SYM(event_raw_float_token) event_raw_float_token;
    } detail;
};
