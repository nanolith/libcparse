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
