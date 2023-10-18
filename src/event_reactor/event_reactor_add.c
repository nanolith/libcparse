/**
 * \file src/event_handler/event_reactor_add.c
 *
 * \brief Add an event_handler to the reactor.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "event_reactor_internal.h"

CPARSE_IMPORT_event_handler;
CPARSE_IMPORT_event_reactor;
CPARSE_IMPORT_event_reactor_internal;

/**
 * \brief Add an \ref event_handler to the event reactor instance.
 *
 * \param er                The event reactor for this operation.
 * \param eh                The event handler to add to this reactor.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_reactor_add)(
    CPARSE_SYM(event_reactor)* er, const CPARSE_SYM(event_handler)* eh)
{
    int retval;
    event_reactor_entry* tmp;

    /* allocate memory for this entry. */
    tmp = (event_reactor_entry*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = ERROR_LIBCPARSE_OUT_OF_MEMORY;
        goto done;
    }

    /* copy the handler. */
    retval = event_handler_init_copy(&tmp->handler, eh);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tmp;
    }

    /* Push the entry onto the list. */
    tmp->next = er->head;
    er->head = tmp;

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

cleanup_tmp:
    memset(tmp, 0, sizeof(*tmp));
    free(tmp);

done:
    return retval;
}
