/**
 * \file src/event_handler/event_handler_dispose.c
 *
 * \brief Dispose method for the \ref event_handler type.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <libcparse/event_handler.h>
#include <libcparse/status_codes.h>
#include <string.h>

/**
 * \brief Dispose a \ref event_handler instance.
 *
 * \param eh                    The event handler instance to dispose.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int CPARSE_SYM(event_handler_dispose)(CPARSE_SYM(event_handler)* eh)
{
    /* clear instance data. */
    memset(eh, 0, sizeof(*eh));

    /* success. */
    return STATUS_SUCCESS;
}
