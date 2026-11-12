/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/local-ai-routing/main.c
 *
 * PURPOSE:
 *   Separate offline contract exercises from explicitly requested loopback inference.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "lab.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc == 3 && strcmp(argv[1], "offline") == 0)
        return LabOffline(argv[2]);
    /* This acknowledgement is a teaching affordance, not authentication.
     * No request is sent merely because a server or a model is discovered. */
    if (argc == 6 && strcmp(argv[1], "local") == 0 &&
        strcmp(argv[2], "--send-reviewed-prompt") == 0)
        return LabLocal(argv[3], argv[4], argv[5]);
    fputs("Usage: btb-local-ai-routing offline <selection|capability|context|health|dispatch|policy>\n"
          "   or: btb-local-ai-routing local --send-reviewed-prompt <port> <model-id> <prompt>\n", stderr);
    return 2;
}
