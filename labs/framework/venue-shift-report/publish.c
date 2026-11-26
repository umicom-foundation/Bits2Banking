/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/framework/venue-shift-report/publish.c
 *
 * PURPOSE:
 *   Use Framework exclusive file creation and keep the first I/O failure.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "venue_report.h"

#include "umicom/platform/output_file.h"

UmiStatus BtbVenuePublish(const char *path, const char *output, size_t length)
{
    if (!path || !output || length == 0) {
        return UMI_STATUS_INVALID_ARGUMENT;
    }
    UmiOutputFile *file = NULL;
    UmiStatus status = UmiOutputFileCreate(path, &file);
    if (status != UMI_STATUS_OK) {
        return status;
    }

    /* Always close once ownership was acquired. Report a failed write even
     * when closing the file succeeds.
     */
    status = UmiOutputFileWrite(file, output, length);
    UmiStatus close_status = UmiOutputFileClose(file);
    UmiOutputFileDestroy(file);
    return status == UMI_STATUS_OK ? close_status : status;
}
