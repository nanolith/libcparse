/**
 * \file tools/import_enum/src/enum_item_list_reverse.c
 *
 * \brief Reverse an enum list to make it ready for output.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>

#include "import_enum_internal.h"

/**
 * \brief Reverse the enum item list, so it is ready for output.
 *
 * \param config        The config instance for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int enum_item_list_reverse(import_enum_config* config)
{
    enum_item* list = config->head;
    enum_item* tmp = NULL;
    enum_item* tmp2 = NULL;

    /* set tmp to the next item if list is not NULL. */
    if (NULL != list)
    {
        tmp = list->next;
    }

    /* the current list is now the tail of the list. */
    list->next = NULL;

    while (NULL != list)
    {
        if (NULL != tmp)
        {
            tmp2 = tmp->next;
            tmp->next = list;
            list = tmp;
            tmp = tmp2;
        }
        else
        {
            config->head = list;
            break;
        }
    }

    return STATUS_SUCCESS;
}
