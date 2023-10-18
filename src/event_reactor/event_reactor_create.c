/**
 * \file src/event_handler/event_reactor_create.c
 *
 * \brief Create an \ref event_reactor instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "event_reactor_internal.h"

CPARSE_IMPORT_event_reactor;

/**
 * \brief Create an \ref event_reactor instance.
 *
 * \param er                Pointer to the event reactor pointer to receive the
 *                          created instance on success.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_reactor_create)(CPARSE_SYM(event_reactor)** er)
{
    event_reactor* tmp;

    /* allocate memory for this instance. */
    tmp = (event_reactor*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        return ERROR_LIBCPARSE_OUT_OF_MEMORY;
    }

    /* clear instance memory. */
    memset(tmp, 0, sizeof(*tmp));

    /* success. */
    *er = tmp;
    tmp = NULL;
    return STATUS_SUCCESS;
}
