/**
 * \file raw_stack_scanner/raw_stack_scanner_internal.h
 *
 * \brief Internal declarations for \ref raw_stack_scanner.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/abstract_parser.h>
#include <libcparse/cursor.h>
#include <libcparse/function_decl.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

typedef struct CPARSE_SYM(raw_stack_entry) CPARSE_SYM(raw_stack_entry);

struct CPARSE_SYM(raw_stack_entry)
{
    CPARSE_SYM(raw_stack_entry)* next;
    CPARSE_SYM(input_stream)* stream;
    CPARSE_SYM(cursor) pos;
};

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
