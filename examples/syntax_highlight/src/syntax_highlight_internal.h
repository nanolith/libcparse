/**
 * \file examples/syntaxn_highlight/src/syntax_highlight_internal.h
 *
 * \brief Internal data structures and functions for the syntax_highlight
 * utility.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/abstract_parser.h>
#include <libcparse/preprocessor_scanner.h>
#include <libcparse/preprocessor_scanner.h>
#include <stdio.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

typedef struct syntax_highlight_config syntax_highlight_config;

struct syntax_highlight_config
{
    char* input;
    char* output;
    int state;
    CPARSE_SYM(preprocessor_scanner)* scanner;
    CPARSE_SYM(abstract_parser)* ap;
    FILE* out;
    long count;
};

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
