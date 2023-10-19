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
#include <libcparse/event_reactor_fwd.h>
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

typedef struct CPARSE_SYM(raw_stack_scanner) CPARSE_SYM(raw_stack_scanner);

struct CPARSE_SYM(raw_stack_scanner)
{
    CPARSE_SYM(abstract_parser) hdr;
    CPARSE_SYM(event_reactor)* reactor;
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

/******************************************************************************/
/* Start of public exports.                                                   */
/******************************************************************************/
#define __INTERNAL_CPARSE_IMPORT_raw_stack_scanner_internal_sym(sym) \
    CPARSE_BEGIN_EXPORT \
    typedef CPARSE_SYM(raw_stack_entry) sym ## raw_stack_entry; \
    static inline int sym ## raw_stack_entry_create( \
        CPARSE_SYM(raw_stack_entry)** x, CPARSE_SYM(input_stream)* y, \
        const char* z) { \
            return CPARSE_SYM(raw_stack_entry_create)(x,y,z); } \
    static inline int sym ## raw_stack_entry_release( \
        CPARSE_SYM(raw_stack_entry)* x) { \
            return CPARSE_SYM(raw_stack_entry_release)(x); } \
    static inline int sym ## raw_stack_scanner_message_callback( \
        void* x, const CPARSE_SYM(message)* y) { \
            return CPARSE_SYM(raw_stack_scanner_message_callback)(x,y); } \
    CPARSE_END_EXPORT \
    REQUIRE_SEMICOLON_HERE
#define CPARSE_IMPORT_raw_stack_scanner_internal_as(sym) \
    __INTERNAL_CPARSE_IMPORT_raw_stack_scanner_internal_sym(sym ## _)
#define CPARSE_IMPORT_raw_stack_scanner_internal \
    __INTERNAL_CPARSE_IMPORT_raw_stack_scanner_internal_sym()

/* C++ compatibility. */
# ifdef   __cplusplus
}
# endif /*__cplusplus*/
