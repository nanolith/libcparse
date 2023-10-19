/**
 * \file src/raw_stack_scanner/raw_stack_entry_create.c
 *
 * \brief Create a \ref raw_stack_entry given a stream and a name.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "raw_stack_scanner_internal.h"

CPARSE_IMPORT_raw_stack_scanner_internal;

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
    const char* name)
{
    int retval;
    raw_stack_entry* tmp;

    /* allocate instance memory. */
    tmp = (raw_stack_entry*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = ERROR_LIBCPARSE_OUT_OF_MEMORY;
        goto done;
    }

    /* clear instance memory. */
    memset(tmp, 0, sizeof(*tmp));

    /* duplicate name. */
    tmp->name = strdup(name);
    if (NULL == tmp->name)
    {
        retval = ERROR_LIBCPARSE_OUT_OF_MEMORY;
        goto cleanup_tmp;
    }

    /* initialize instance. */
    tmp->next = NULL;
    tmp->stream = stream;
    tmp->pos.file = tmp->name;
    tmp->pos.begin_line = 1;
    tmp->pos.begin_col = 1;
    tmp->pos.end_line = 1;
    tmp->pos.end_col = 1;

    /* success. */
    retval = STATUS_SUCCESS;
    *ent = tmp;
    goto done;

cleanup_tmp:
    free(tmp);

done:
    return retval;
}
