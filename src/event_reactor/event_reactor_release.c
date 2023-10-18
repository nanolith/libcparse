/**
 * \file src/event_handler/event_reactor_release.c
 *
 * \brief Release an \ref event_reactor instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "event_reactor_internal.h"

CPARSE_IMPORT_event_reactor;
CPARSE_IMPORT_event_reactor_internal;

/**
 * \brief Release an \ref event_reactor instance.
 *
 * \param er                The event reactor instance to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_reactor_release)(CPARSE_SYM(event_reactor)* er)
{
    event_reactor_entry* ent = er->head;

    /* reclaim all entries. */
    while (NULL != ent)
    {
        event_reactor_entry* tmp = ent;
        ent = ent->next;

        /* clear entry memory. */
        memset(tmp, 0, sizeof(*tmp));

        /* reclaim entry memory. */
        free(tmp);
    }

    /* clear instance memory. */
    memset(er, 0, sizeof(*er));

    /* reclaim instance memory. */
    free(er);

    /* success. */
    return STATUS_SUCCESS;
}
