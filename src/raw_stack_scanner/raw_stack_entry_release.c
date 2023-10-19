/**
 * \file src/raw_stack_scanner/raw_stack_entry_release.c
 *
 * \brief Release a \ref raw_stack_entry instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "raw_stack_scanner_internal.h"

CPARSE_IMPORT_input_stream;
CPARSE_IMPORT_raw_stack_scanner_internal;

/**
 * \brief Release a \ref raw_stack_entry instance.
 *
 * \param ent               The instance to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(raw_stack_entry_release)(CPARSE_SYM(raw_stack_entry)* ent)
{
    int stream_release_retval = STATUS_SUCCESS;

    /* free name if set. */
    if (NULL != ent->name)
    {
        free(ent->name);
    }

    /* release stream if set. */
    if (NULL != ent->stream)
    {
        stream_release_retval = input_stream_release(ent->stream);
    }

    /* clear instance memory. */
    memset(ent, 0, sizeof(*ent));

    /* free instance memory. */
    free(ent);

    /* decode return code. */
    return stream_release_retval;
}
