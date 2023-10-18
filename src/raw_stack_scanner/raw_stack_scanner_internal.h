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
    char* name;
    CPARSE_SYM(cursor) pos;
};

struct CPARSE_SYM(raw_stack_scanner)
{
    CPARSE_SYM(abstract_parser) hdr;
    CPARSE_SYM(raw_stack_entry)* head;
};

/******************************************************************************/
/* Start of constructors.                                                     */
/******************************************************************************/

/**
 * \brief Create a \ref raw_stack_entry instance with the given stream and
 * name.
 *
 * \note Ownership of \p stream passes to this instance on success. The stream
 * will be released when this instance is released.
 *
 * \param ent               Pointer to the \ref raw_stack_entry pointer to
 *                          receive this instance on success.
 * \param stream            The input stream for this instance.
 * \param name              The name of this stream.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(raw_stack_entry_create)(
    CPARSE_SYM(raw_stack_entry)** ent, CPARSE_SYM(input_stream)* stream,
    const char* name);

/**
 * \brief Release a \ref raw_stack_entry instance.
 *
 * \param ent               The instance to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(raw_stack_entry_release)(CPARSE_SYM(raw_stack_entry)* ent);

/******************************************************************************/
/* Start of public methods.                                                   */
/******************************************************************************/

/**
 * \brief Message handler callback for \ref raw_stack_scanner.
 *
 * \param context           The context for this handler (the
 *                          \ref raw_stack_scanner instance).
 * \param msg               A message for this handler.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(raw_stack_scanner_message_callback)(
    void* context, const CPARSE_SYM(message)* msg);

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
