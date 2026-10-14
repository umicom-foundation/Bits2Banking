/*-----------------------------------------------------------------------------
 * Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
 * File: labs/native/sysadmin-readonly-text/main.c
 * PURPOSE: A first safe native read-only system-administration command.
 *---------------------------------------------------------------------------*/
#include "inspector.h"

#include <inttypes.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    BtbTextSummary summary = {0};
    BtbTextInspectStatus status;
    if (argc != 2) {
        fprintf(stderr, "Usage: btb-sysadmin-text <local-text-file>\n");
        return 2;
    }
    status = BtbTextInspectFile(argv[1], BTB_SYSADMIN_TEXT_MAX_BYTES, &summary);
    if (status != BTB_TEXT_OK) {
        fprintf(stderr, "Unable to inspect text: %s\n", BtbTextInspectStatusText(status));
        return 1;
    }
    printf("Inspection complete (read-only)\nBytes: %" PRIu64
           "\nLines: %" PRIu64 "\nFinal newline: %s\n",
           summary.byteCount, summary.lineCount,
           summary.endsWithNewline != 0 ? "yes" : "no");
    return 0;
}
