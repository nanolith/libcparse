/**
 * \file preprocessor_scanner/preprocessor_scanner_internal.h
 *
 * \brief Internal declarations and definitions for the preprocessor scanner.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/abstract_parser.h>
#include <libcparse/newline_preserving_whitespace_filter.h>
#include <libcparse/event_reactor_fwd.h>
#include <libcparse/file_position_cache.h>
#include <libcparse/string_builder.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

typedef struct CPARSE_SYM(preprocessor_scanner)
CPARSE_SYM(preprocessor_scanner);

struct CPARSE_SYM(preprocessor_scanner)
{
    CPARSE_SYM(newline_preserving_whitespace_filter)* parent;
    CPARSE_SYM(abstract_parser)* base;
    CPARSE_SYM(event_reactor)* reactor;
    CPARSE_SYM(message_handler) parent_mh;
    CPARSE_SYM(file_position_cache)* cache;
    CPARSE_SYM(file_position_cache)* newline_cache;
    CPARSE_SYM(file_position_cache)* hash_cache;
    CPARSE_SYM(string_builder)* builder;
    int state;
    int preprocessor_state;
    bool state_reset;
    bool has_hex_digit;
};

enum CPARSE_SYM(preprocessor_scanner_state)
{
    CPARSE_PREPROCESSOR_SCANNER_STATE_INIT =                            0,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_IDENTIFIER =                   1,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DASH =                         2,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_PLUS =                         3,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STAR =                         4,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_SLASH =                        5,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_PERCENT =                      6,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_PERCENT_COLON =                7,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_PERCENT_COLON_PERCENT =        8,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_AMPERSAND =                    9,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_PIPE =                        10,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CARET =                       11,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_TILDE =                       12,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_EQUAL =                       13,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_NOT =                         14,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_LT =                          15,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_LT_LT =                       16,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_GT =                          17,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_GT_GT =                       18,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER =             19,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_OCTAL_INTEGER =               20,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_0_INTEGER =                   21,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_HEX_INTEGER =                 22,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_U =           23,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_UL =          24,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_L =           25,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_LL =          26,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DECIMAL_INTEGER_END =         27,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING =                      28,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_SLASH =                29,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_OCTAL_1 =              30,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_OCTAL_2 =              31,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_HEX =                  32,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_HEX_OPT =              33,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_LITTLE_U =             34,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_LITTLE_U1 =            35,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_LITTLE_U2 =            36,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_LITTLE_U3 =            37,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U =                38,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U1 =               39,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U2 =               40,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U3 =               41,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U4 =               42,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U5 =               43,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U6 =               44,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_STRING_BIG_U7 =               45,
    CPARSE_PREPROCESSOR_SCANNER_STATE_BEGIN_LINE =                     46,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_HASH =                        47,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_SINGLE_HASH =                 48,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CHAR =                        49,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CHAR_SLASH =                  50,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CHAR_OCTAL_1 =                51,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CHAR_OCTAL_2 =                52,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CHAR_HEX =                    53,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CHAR_HEX_OPT =                54,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CHAR_LITTLE_U =               55,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CHAR_LITTLE_U1 =              56,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CHAR_LITTLE_U2 =              57,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CHAR_LITTLE_U3 =              58,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CHAR_BIG_U =                  59,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CHAR_BIG_U1 =                 60,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CHAR_BIG_U2 =                 61,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CHAR_BIG_U3 =                 62,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CHAR_BIG_U4 =                 63,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CHAR_BIG_U5 =                 64,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CHAR_BIG_U6 =                 65,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_CHAR_BIG_U7 =                 66,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DOT =                         67,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_DOT_DOT =                     68,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_COLON =                       69,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_FLOAT =                       70,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_FLOAT_E_EXPECT_DIGIT =        71,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_FLOAT_E_SIGN_EXPECT_DIGIT =   72,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_FLOAT_E_WITH_DIGIT =          73,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_FLOAT_SUFFIX =                74,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_HEX_FLOAT =                   75,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_HEX_FLOAT_P_EXPECT_DIGIT =    76,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_HEX_FLOAT_P_S_EXPECT_DIGIT =  77,
    CPARSE_PREPROCESSOR_SCANNER_STATE_IN_HEX_FLOAT_P_WITH_DIGIT =      78,
};

enum CPARSE_SYM(preprocessor_directive_state)
{
    CPARSE_PREPROCESSOR_DIRECTIVE_STATE_INIT =                          0,
    CPARSE_PREPROCESSOR_DIRECTIVE_STATE_MAYBE =                         1,
    CPARSE_PREPROCESSOR_DIRECTIVE_STATE_ENABLED =                       2,
    CPARSE_PREPROCESSOR_DIRECTIVE_STATE_ENABLED_INCLUDE =               3,
    CPARSE_PREPROCESSOR_DIRECTIVE_STATE_ENABLED_INCLUDE_SYSTEM_STRING = 4,
    CPARSE_PREPROCESSOR_DIRECTIVE_STATE_DISABLED =                      5,
};

/******************************************************************************/
/* Start of private methods.                                                  */
/******************************************************************************/

/**
 * \brief Message handler callback for
 * \ref preprocessor_scanner_message_callback.
 *
 * \param context           The context for this handler (the
 *                          \ref preprocessor_scanner instance).
 * \param msg               A message for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(preprocessor_scanner_message_callback)(
    void* context, const CPARSE_SYM(message)* msg);

/**
 * \brief Event handler callback for \ref preprocessor_scanner_event_callback.
 *
 * \param context           The context for this handler (the
 *                          \ref preprocessor_scanner instance).
 * \param ev                An event for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(preprocessor_scanner_event_callback)(
    void* context, const CPARSE_SYM(event)* ev);

/******************************************************************************/
/* Start of privote exports.                                                  */
/******************************************************************************/

#define __INTERNAL_CPARSE_IMPORT_preprocessor_scanner_internal_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    static inline int \
    sym ## preprocessor_scanner_message_callback( \
        void* x, const CPARSE_SYM(message)* y) { \
            return CPARSE_SYM(preprocessor_scanner_message_callback)(x,y); } \
    static inline int \
    sym ## preprocessor_scanner_event_callback( \
        void* x, const CPARSE_SYM(event)* y) { \
            return CPARSE_SYM(preprocessor_scanner_event_callback)(x,y); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_preprocessor_scanner_internal_as(sym) \
    __INTERNAL_CPARSE_IMPORT_preprocessor_scanner_internal_sym(sym ## _)
#define CPARSE_IMPORT_preprocessor_scanner_internal \
    __INTERNAL_CPARSE_IMPORT_preprocessor_scanner_internal_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
