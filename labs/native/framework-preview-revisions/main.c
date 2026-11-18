/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-preview-revisions/main.c
 *
 * PURPOSE:
 *   Demonstrate captured revisions and edits arriving during a preview build.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom/frontend/hot_reload.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define REQUIRE(call) do { UmiStatus status = (call); if (status != UMI_STATUS_OK) { \
    fprintf(stderr, "Operation failed: %s (status %d)\n", #call, (int)status); \
    result = EXIT_FAILURE; goto finish; } } while (0)

int main(void)
{
    /* Allocate bounded snapshots off the stack. The main function owns them;
     * Framework borrows each pointer only for the duration of a call. */
    UmiFrontendHotReload *reload = calloc(1, sizeof(*reload));
    UmiFrontendReloadBatch *batch = calloc(1, sizeof(*batch));
    UmiFrontendReloadReceipt receipt = {0};
    int result = EXIT_SUCCESS;
    if (reload == NULL || batch == NULL) {
        fputs("Cannot allocate the preview bookkeeping objects.\n", stderr);
        result = EXIT_FAILURE;
        goto finish;
    }
    REQUIRE(umi_frontend_hot_reload_init(reload, 1));
    REQUIRE(umi_frontend_hot_reload_queue(reload, "counter.c", 10));
    REQUIRE(umi_frontend_hot_reload_queue(reload, "theme.css", 20));
    REQUIRE(umi_frontend_hot_reload_capture(reload, batch));
    printf("Captured %zu paths at generation %" PRIu64 "\n", batch->count, batch->base_generation);

    /* Model a second edit arriving while the captured build is in progress.
     * This lab does not start a compiler, thread, watcher or GTK application. */
    REQUIRE(umi_frontend_hot_reload_queue(reload, "counter.c", 11));
    REQUIRE(umi_frontend_hot_reload_queue(reload, "dialog.ui", 30));
    REQUIRE(umi_frontend_hot_reload_acknowledge(reload, batch, &receipt));
    printf("Applied generation %" PRIu64 ": acknowledged=%zu pending=%zu\n",
           receipt.generation, receipt.acknowledged, receipt.remaining);
    for (size_t i = 0; i < reload->pending_count; ++i)
        printf("Pending %s revision %" PRIu64 "\n",
               reload->pending[i].path, reload->pending[i].revision);

    REQUIRE(umi_frontend_hot_reload_capture(reload, batch));
    REQUIRE(umi_frontend_hot_reload_acknowledge(reload, batch, &receipt));
    printf("Applied generation %" PRIu64 ": acknowledged=%zu pending=%zu\n",
           receipt.generation, receipt.acknowledged, receipt.remaining);
    if (receipt.generation != 3 || receipt.acknowledged != 2 || receipt.remaining != 0)
        result = EXIT_FAILURE;
finish:
    free(batch);
    free(reload);
    return result;
}
