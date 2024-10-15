/**
 * \file event_copy/event_copy_create.c
 *
 * \brief Create an event copy from the given event.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event_copy.h>
#include <libcparse/event/identifier.h>
#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "../event/event_internal.h"
#include "event_copy_internal.h"

CPARSE_IMPORT_cursor;
CPARSE_IMPORT_event;
CPARSE_IMPORT_event_copy;
CPARSE_IMPORT_event_identifier;
CPARSE_IMPORT_event_internal;

static int event_copy_create_base(event_copy** cpy, const event* ev);
static int event_copy_create_identifier(event_copy** cpy, const event* ev);
static int event_copy_create_internal(
    event_copy** cpy, int category, const char* field, const cursor* cursor);

/**
 * \brief Create an event copy from the given event.
 *
 * \param cpy                   Pointer to the \ref event_copy pointer to
 *                              receive this \ref event_copy on success.
 * \param ev                    The event to copy.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_copy_create)(
    CPARSE_SYM(event_copy)** cpy, const CPARSE_SYM(event)* ev)
{
    switch (event_get_category(ev))
    {
        case CPARSE_EVENT_CATEGORY_BASE:
            return event_copy_create_base(cpy, ev);

        case CPARSE_EVENT_CATEGORY_IDENTIFIER:
            return event_copy_create_identifier(cpy, ev);

        default:
            return ERROR_LIBCPARSE_EVENT_COPY_UNSUPPORTED_EVENT_CATEGORY;
    }
}

/**
 * \brief Copy a base event.
 *
 * \param cpy                   Pointer to the \ref event_copy pointer to
 *                              receive this \ref event_copy on success.
 * \param ev                    The event to copy.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int event_copy_create_base(event_copy** cpy, const event* ev)
{
    event_copy* tmp = NULL;
    int retval, release_retval;

    /* create the copy. */
    retval =
        event_copy_create_internal(
            &tmp, CPARSE_EVENT_CATEGORY_BASE, NULL, event_get_cursor(ev));
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* get the event type. */
    int event_type = event_get_type(ev);

    /* initialize the base event. */
    retval =
        event_init(
            &(tmp->detail.event), event_type, tmp->category, &(tmp->cursor));
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tmp;
    }

    /* success. */
    tmp->initialized = true;
    *cpy = tmp;
    retval = STATUS_SUCCESS;
    goto done;

cleanup_tmp:
    release_retval = event_copy_release(tmp);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}

/**
 * \brief Copy an identifier event.
 *
 * \param cpy                   Pointer to the \ref event_copy pointer to
 *                              receive this \ref event_copy on success.
 * \param ev                    The event to copy.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static int event_copy_create_identifier(event_copy** cpy, const event* ev)
{
    event_copy* tmp = NULL;
    event_identifier* iev;
    int retval, release_retval;

    /* downcast the event. */
    retval = event_downcast_to_event_identifier(&iev, (event*)ev);
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* create the copy. */
    retval =
        event_copy_create_internal(
            &tmp, CPARSE_EVENT_CATEGORY_IDENTIFIER, event_identifier_get(iev),
            event_get_cursor(ev));
    if (STATUS_SUCCESS != retval)
    {
        goto done;
    }

    /* initialize the identifier event. */
    retval =
        event_identifier_init(
            &(tmp->detail.event_identifier), &(tmp->cursor), tmp->field1);
    if (STATUS_SUCCESS != retval)
    {
        goto cleanup_tmp;
    }

    /* success. */
    tmp->initialized = true;
    *cpy = tmp;
    retval = STATUS_SUCCESS;
    goto done;

cleanup_tmp:
    release_retval = event_copy_release(tmp);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}

/**
 * \brief Create the event_copy data and copy internal details needed to
 * initialize the event copy.
 *
 * \param cpy       Pointer to the pointer to set to the copy on success.
 * \param category  The event category.
 * \param field     The string field to copy, if any.
 * \param cursor    The cursor for the event, used to copy the file.
 */
static int event_copy_create_internal(
    event_copy** cpy, int category, const char* field, const cursor* cursor)
{
    int retval, release_retval;
    event_copy* tmp;

    /* allocate memory for the event copy. */
    tmp = malloc(sizeof(event_copy));
    if (NULL == tmp)
    {
        retval = ERROR_LIBCPARSE_OUT_OF_MEMORY;
        goto done;
    }

    /* clear memory. */
    memset(tmp, 0, sizeof(*tmp));

    /* set the category. */
    tmp->category = category;

    /* copy the file if set. */
    if (NULL != cursor->file)
    {
        tmp->file = strdup(cursor->file);
        if (NULL == tmp->file)
        {
            retval = ERROR_LIBCPARSE_OUT_OF_MEMORY;
            goto cleanup_tmp;
        }
    }

    /* copy the field if set. */
    if (NULL != field)
    {
        tmp->field1 = strdup(field);
        if (NULL == tmp->field1)
        {
            retval = ERROR_LIBCPARSE_OUT_OF_MEMORY;
            goto cleanup_tmp;
        }
    }

    /* copy the cursor. */
    memcpy(&tmp->cursor, cursor, sizeof(tmp->cursor));

    /* override the file. */
    tmp->cursor.file = tmp->file;

    /* success. */
    *cpy = tmp;
    retval = STATUS_SUCCESS;
    goto done;

cleanup_tmp:
    release_retval = event_copy_release(tmp);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}
