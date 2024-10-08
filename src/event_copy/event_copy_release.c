/**
 * \file event_copy/event_copy_release.c
 *
 * \brief Release an event copy instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event.h>
#include <libcparse/status_codes.h>
#include <stdlib.h>

#include "../event/event_internal.h"
#include "event_copy_internal.h"

CPARSE_IMPORT_event;
CPARSE_IMPORT_event_copy;

static int event_copy_dispose_base(event_copy* cpy);

/**
 * \brief Release an \ref event_copy instance.
 *
 * \param cpy                   Pointer to the \ref event_copy to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_copy_release)(CPARSE_SYM(event_copy)* cpy)
{
    int retval = STATUS_SUCCESS;
    int release_retval;

    /* release the event instance if initialized. */
    if (cpy->initialized)
    {
        switch (cpy->category)
        {
            case CPARSE_EVENT_CATEGORY_BASE:
                release_retval = event_copy_dispose_base(cpy);
                break;
            default:
                release_retval =
                    ERROR_LIBCPARSE_EVENT_COPY_UNSUPPORTED_EVENT_CATEGORY;
                break;
        }

        if (STATUS_SUCCESS != release_retval)
        {
            retval = release_retval;
        }
    }

    /* release file if initialized. */
    if (NULL != cpy->file)
    {
        free(cpy->file);
    }

    /* release field1 if initialized. */
    if (NULL != cpy->field1)
    {
        free(cpy->field1);
    }

    /* release event copy instance. */
    free(cpy);

    /* return the decoded status. */
    return retval;
}

/**
 * \brief Dispose a base event from this event copy.
 *
 * \param cpy                   Pointer to the \ref event_copy to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int event_copy_dispose_base(event_copy* cpy)
{
    return event_dispose(&cpy->detail.event);
}
