/**
 * \file libcparse/status_codes.h
 *
 * \brief Status codes for the libcparse library.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#define STATUS_SUCCESS                                             0
#define ERROR_LIBCPARSE_OUT_OF_MEMORY                           1000
#define ERROR_LIBCPARSE_INPUT_STREAM_DESCRIPTOR_CLOSE           1001
#define ERROR_LIBCPARSE_INPUT_STREAM_READ_ERROR                 1002
#define ERROR_LIBCPARSE_INPUT_STREAM_EOF                        1003
#define ERROR_LIBCPARSE_RSS_MESSAGE_INPUT_STREAM_NULL           1004
#define ERROR_LIBCPARSE_BAD_CAST                                1005
#define ERROR_LIBCPARSE_UNHANDLED_MESSAGE                       1006
#define ERROR_LIBCPARSE_COMMENT_BAD_STATE                       1007
#define ERROR_LIBCPARSE_COMMENT_EXPECTING_SLASH                 1008
#define ERROR_LIBCPARSE_COMMENT_EXPECTING_STAR_SLASH            1009
#define ERROR_LIBCPARSE_COMMENT_EXPECTING_SINGLE_QUOTE          1010
#define ERROR_LIBCPARSE_COMMENT_EXPECTING_CHAR_SINGLE_QUOTE     1011
#define ERROR_LIBCPARSE_COMMENT_EXPECTING_DOUBLE_QUOTE          1012
#define ERROR_LIBCPARSE_COMMENT_EXPECTING_CHAR_DOUBLE_QUOTE     1013
