/**
 * \file libcparse/message/file_line_override.h
 *
 * \brief Message to override the file and line position in the file/line
 * filter.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/function_decl.h>
#include <libcparse/message.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The file/line override message allows a user to override the file and
 * line position of the file/line override filter.
 */
typedef struct CPARSE_SYM(message_file_line_override)
CPARSE_SYM(message_file_line_override);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
