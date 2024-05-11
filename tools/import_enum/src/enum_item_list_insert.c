/**
 * \file tools/import_enum/src/enum_item_list_insert.c
 *
 * \brief Insert an item into the enum list.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stdlib.h>
#include <string.h>

#include "import_enum_internal.h"

/**
 * \brief Insert an enum item onto the enum list.
 *
 * \param config        The config instance for this operation.
 * \param name          The name of this enum item.
 * \param value         The value of this enum item.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int enum_item_list_insert(
    import_enum_config* config, const char* name, long value)
{
    int retval, release_retval;
    enum_item* tmp;

    /* allocate memory for this list item. */
    tmp = (enum_item*)malloc(sizeof(*tmp));
    if (NULL == tmp)
    {
        retval = ERROR_LIBCPARSE_OUT_OF_MEMORY;
        goto done;
    }

    /* clear item memory. */
    memset(tmp, 0, sizeof(*tmp));

    /* copy name. */
    tmp->enum_name = strdup(name);
    if (NULL == tmp->enum_name)
    {
        retval = ERROR_LIBCPARSE_OUT_OF_MEMORY;
        goto cleanup_item;
    }

    /* set value. */
    tmp->enum_value = value;

    /* insert item. */
    tmp->next = config->head;
    config->head = tmp->next;

    /* success. */
    retval = STATUS_SUCCESS;
    goto done;

cleanup_item:
    release_retval = enum_item_release(tmp);
    if (STATUS_SUCCESS != release_retval)
    {
        retval = release_retval;
    }

done:
    return retval;
}
