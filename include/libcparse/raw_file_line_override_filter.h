/**
 * \file libcparse/raw_file_line_override_filter.h
 *
 * \brief The raw file / line override filter performs file and line override
 * filtration for raw character events.
 *
 * Subscribers to this filter will receive raw character events as with the raw
 * stack scanner, but the cursor for these events will be updated to reflect
 * file and line overrides.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <libcparse/function_decl.h>

/* C++ compatibility. */
# ifdef   __cplusplus
extern "C" {
# endif /*__cplusplus*/

/**
 * \brief The \ref raw_stack_scanner reacts to a stack of input streams.
 */
typedef struct CPARSE_SYM(raw_file_line_override_filter)
CPARSE_SYM(raw_file_line_override_filter);

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Create a raw file/line override filter.
 *
 * This filter automatically creates a raw stack scanner and injects itself into
 * the message chain for that scanner.
 *
 * \param filter            Pointer to the \ref raw_file_line_override_filter
 *                          pointer to be populated with the created raw
 *                          file/line override filter instance on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(raw_file_line_override_filter_create)(
    CPARSE_SYM(raw_file_line_override_filter)** filter);

/**
 * \brief Release a raw file/line override filter, instance, releasing any
 * internal resources it may own.
 *
 * \param filter            The \ref raw_file_line_override_filter instance to
 *                          release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(raw_file_line_override_filter_release)(
    CPARSE_SYM(raw_file_line_override_filter)* filter);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
