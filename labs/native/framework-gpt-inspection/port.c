/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-gpt-inspection/port.c
 *
 * PURPOSE:
 *   Adapt caller-owned bytes to exact Framework reads without opening files or devices.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "lab.h"
#include <string.h>

UmiStatus LabReadAt(void *context, uint64_t offset, void *destination, size_t length)
{
    LabImage *image = context;
    if (image == NULL || image->bytes == NULL || destination == NULL)
        return UMI_STATUS_INVALID_ARGUMENT;
    ++image->reads;
    if (image->reads == image->failRead) return UMI_STATUS_IO_ERROR;
    /* Check offset first. Subtracting it before that check could wrap and make
     * a range outside the allocation appear enormous and therefore acceptable. */
    if (offset > image->length || length > image->length - offset)
        return UMI_STATUS_IO_ERROR;
    memcpy(destination, image->bytes + (size_t)offset, length);
    return UMI_STATUS_OK;
}
