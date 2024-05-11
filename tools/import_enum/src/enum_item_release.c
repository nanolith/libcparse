/**
 * \file tools/import_enum/src/enum_item_release.c
 *
 * \brief Release an enum item instance.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stdlib.h>

#include "import_enum_internal.h"

/**
 * \brief Release an enum item.
 *
 * \param item          The enum item to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int enum_item_release(enum_item* item)
{
    /* free the name if set. */
    if (NULL != item->enum_name)
    {
        free(item->enum_name);
    }

    /* free the list. */
    free(item);

    /* success. */
    return STATUS_SUCCESS;
}
