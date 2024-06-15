/**
 * \file libcparse/status_codes.h
 *
 * \brief Status codes for the libcparse library.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/function_decl.h>

enum CPARSE_SYM(status_code)
{
    STATUS_SUCCESS =                                                       0,
    ERROR_LIBCPARSE_OUT_OF_MEMORY =                                     1000,
    ERROR_LIBCPARSE_INPUT_STREAM_DESCRIPTOR_CLOSE =                     1001,
    ERROR_LIBCPARSE_INPUT_STREAM_READ_ERROR =                           1002,
    ERROR_LIBCPARSE_INPUT_STREAM_EOF =                                  1003,
    ERROR_LIBCPARSE_RSS_MESSAGE_INPUT_STREAM_NULL =                     1004,
    ERROR_LIBCPARSE_BAD_CAST =                                          1005,
    ERROR_LIBCPARSE_UNHANDLED_MESSAGE =                                 1006,
    ERROR_LIBCPARSE_COMMENT_BAD_STATE =                                 1007,
    ERROR_LIBCPARSE_COMMENT_EXPECTING_SLASH =                           1008,
    ERROR_LIBCPARSE_COMMENT_EXPECTING_STAR_SLASH =                      1009,
    ERROR_LIBCPARSE_COMMENT_EXPECTING_SINGLE_QUOTE =                    1010,
    ERROR_LIBCPARSE_COMMENT_EXPECTING_CHAR_SINGLE_QUOTE =               1011,
    ERROR_LIBCPARSE_COMMENT_EXPECTING_DOUBLE_QUOTE =                    1012,
    ERROR_LIBCPARSE_COMMENT_EXPECTING_CHAR_DOUBLE_QUOTE =               1013,
    ERROR_LIBCPARSE_FILE_POSITION_CACHE_ALREADY_SET =                   1014,
    ERROR_LIBCPARSE_FILE_POSITION_CACHE_NOT_SET =                       1015,
    ERROR_LIBCPARSE_WHITESPACE_BAD_STATE =                              1016,
    ERROR_LIBCPARSE_PP_SCANNER_UNEXPECTED_CHARACTER =                   1017,
    ERROR_LIBCPARSE_PP_SCANNER_BAD_STATE =                              1018,
    ERROR_LIBCPARSE_PP_SCANNER_EXPECTING_CHARACTER =                    1019,
    ERROR_LIBCPARSE_PP_SCANNER_EXPECTING_DIGIT =                        1020,
    ERROR_LIBCPARSE_PP_SCANNER_HEX_FLOAT_EXPECTING_P =                  1021,
    ERROR_LIBCPARSE_BAD_INTEGER_CONVERSION =                            1022,
    ERROR_LIBCPARSE_ENTRY_NOT_FOUND =                                   1023,
    ERROR_LIBCPARSE_FILE_CLOSE_ERROR =                                  1024,
    ERROR_LIBCPARSE_FILE_OPEN_ERROR =                                   1025,
    ERROR_LIBCPARSE_FILE_SEEK =                                         1026,
    ERROR_LIBCPARSE_FILE_TELL =                                         1027,
    ERROR_LIBCPARSE_OUT_OF_BOUNDS =                                     1028,
};
