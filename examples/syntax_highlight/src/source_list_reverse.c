/**
 * \file exmaples/syntax_highlight/src/source_list_reverse.c
 *
 * \brief Reverse a source list.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/status_codes.h>
#include <stdlib.h>

#include "syntax_highlight_internal.h"

/**
 * \brief Reverse the source list.
 *
 * \param config        The config instance for this operation.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int source_list_reverse(syntax_highlight_config* config)
{
    source_line* list = config->head;
    source_line* tmp = NULL;
    source_line* tmp2 = NULL;

    /* set tmp to the next line if the list is not NULL. */
    if (NULL != list)
    {
        tmp = list->next;

        /* the current list is now the tail of the list. */
        list->next = NULL;
    }

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
