/**
 * \file tools/import_enum/src/enum_item_list_release.c
 *
 * \brief Release an enum item list.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stdlib.h>

#include "import_enum_internal.h"

/**
 * \brief Release an enum item list.
 *
 * \param list          The enum item list to release.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int enum_item_list_release(enum_item* list)
{
    int retval = STATUS_SUCCESS;
    int release_retval;
    enum_item* tmp = list;

    while (NULL != list)
    {
        list = list->next;

        release_retval = enum_item_release(tmp);
        if (STATUS_SUCCESS != release_retval)
        {
            retval = release_retval;
        }

        tmp = list;
    }

    return retval;
}
