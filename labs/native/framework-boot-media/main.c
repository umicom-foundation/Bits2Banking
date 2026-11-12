/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-boot-media/main.c
 *
 * PURPOSE:
 *   Teach reviewed regular-file media copying through installed Framework APIs.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/boot_media/media.h"
#include "umicom/platform/native_arguments.h"
#include "umicom/setup_centre/setup.h"
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

/* Preserve the previous error-only presentation. Every result now exposes creation, write and verification observations for recovery teaching. The previous implementation is retained for review. */
#if 0
static int Result(UmiStatus status, const UmiBootMediaReport *report)
{
    if (status != UMI_STATUS_OK) {
        fprintf(stderr, "%s: %s\n", UmiSetupStatusText(status), report->detail);
        return 1;
    }
    return 0;
}


#endif
/* Present the Framework's observation after every operation, including refusal.
 * A nonzero status does not imply that exclusive creation or writing never took
 * place. This client formats results; it does not infer or repair file effects. */
static int Result(UmiStatus status, const UmiBootMediaReport *report)
{
    printf("Report: returned=%s status=%s phase=%d output-created=%d write-started=%d verified=%d\n",
        UmiSetupStatusText(status),UmiSetupStatusText(report->status),(int)report->phase,
        report->outputCreated,report->writeStarted,report->verified);
    printf("Progress: %" PRIu64 "/%" PRIu64 "\n",report->bytesDone,report->bytesTotal);
    if (status != UMI_STATUS_OK) {
        fprintf(stderr, "%s: %s\n", UmiSetupStatusText(status), report->detail);
        return 1;
    }
    return 0;
}

typedef struct MediaLessonStop {
    UmiBootMediaPhase phase;
    int observed;
} MediaLessonStop;

/* The callback runs synchronously inside Apply. Its stack-owned context remains
 * live until Apply returns; never free a plan or close a handle from here. */
static int StopAtPhase(const UmiBootMediaReport *report,void *context)
{
    MediaLessonStop *stop=context;
    if(report->phase!=stop->phase)return 0;
    stop->observed=1;
    return 1;
}

static int ReadStopPhase(const char *name,MediaLessonStop *stop)
{
    const struct {const char *name;UmiBootMediaPhase phase;} phases[]={
        {"recheck",UMI_BOOT_MEDIA_RECHECK},{"write",UMI_BOOT_MEDIA_WRITE},
        {"flush",UMI_BOOT_MEDIA_FLUSH},{"verify",UMI_BOOT_MEDIA_VERIFY},
        {"finished",UMI_BOOT_MEDIA_FINISHED}
    };
    for(size_t i=0;i<sizeof phases/sizeof phases[0];++i){
        if(strcmp(name,phases[i].name)==0){stop->phase=phases[i].phase;return 1;}
    }
    return 0;
}

static int MediaLessonMain(int argc, char **argv)
{
    /* Framework captures the original Unicode process arguments before this
     * callback. Each option below describes a regular file, never a device. */
    if (argc < 2) return 2;
    UmiBootMediaReport report = {0};
    if (argc == 3 && strcmp(argv[1], "inspect") == 0) {
        UmiBootMediaImage image = {0};
        UmiStatus status = UmiBootMediaInspect(argv[2], &image, NULL, NULL, &report);
        if (Result(status, &report)) return 1;
        printf("Bytes: %" PRIu64 "\nSHA-256: %s\n", image.bytes, image.sha256);
        printf("MBR: %d; GPT: %d; ISO9660: %d; El Torito: %d\n",
            image.mbrLayout, image.gptLayout, image.iso9660, image.elTorito);
        puts("Structural observations do not establish bootability.");
        return 0;
    }
    if (argc == 4 && strcmp(argv[1], "verify") == 0) {
        UmiStatus status = UmiBootMediaVerifyFile(argv[2], argv[3], NULL, NULL, &report);
        if (Result(status, &report)) return 1;
        puts("Verified equal regular-file contents; bootability remains untested.");
        return 0;
    }
    int review = argc == 4 && strcmp(argv[1], "review") == 0;
/* Retain the earlier two-command admission while the practice client adds an
 * explicit stop phase. Invalid phases are refused before review or acquisition. */
#if 0
    int copy = argc == 6 && strcmp(argv[1], "copy") == 0;
    if (!review && !copy) {
#endif
    int copy = argc == 6 && strcmp(argv[1], "copy") == 0;
    int stopCopy = argc == 7 && strcmp(argv[1], "copy-until") == 0;
    MediaLessonStop stop={0};
    if(stopCopy&&!ReadStopPhase(argv[6],&stop)){
        fputs("Choose recheck, write, flush, verify or finished. No operation started.\n",stderr);
        return 2;
    }
    if (!review && !copy && !stopCopy) {
        fputs("Usage: btb-framework-boot-media inspect IMAGE\n"
              "       btb-framework-boot-media review IMAGE NEW_FILE\n"
              "       btb-framework-boot-media copy IMAGE NEW_FILE FINGERPRINT CONFIRMATION\n"
              "       btb-framework-boot-media verify IMAGE COPY\n"
              "       btb-framework-boot-media copy-until IMAGE NEW_FILE FINGERPRINT CONFIRMATION PHASE\n"
              "Use host-absolute paths. No physical-device command is provided.\n", stderr);
        return 2;
    }
    UmiBootMediaPlan *plan = NULL;
    UmiStatus status = UmiBootMediaReviewFile(argv[2], argv[3], &plan, NULL, NULL, &report);
    if (status == UMI_STATUS_OK && review) {
        /* The plan owns these strings. Read them before destroying the plan;
         * an application retaining them beyond this call must make copies. */
        printf("Destination: %s\nFingerprint: %s\nConfirmation: %s\n",
            UmiBootMediaPlanDestination(plan), UmiBootMediaPlanFingerprint(plan),
            UmiBootMediaPlanConfirmation(plan));
    } else if (status == UMI_STATUS_OK) {
        /* Reconstruct current observations, then compare the user's earlier
         * review. Never substitute a freshly generated token automatically. */
/* Preserve the callback-free invocation; copy-until adds a caller-owned cancellation policy through the same Framework service. The previous implementation is retained for review. */
#if 0
        status = UmiBootMediaApply(plan, argv[4], argv[5], NULL, NULL, &report);
#endif
        status = UmiBootMediaApply(plan, argv[4], argv[5],
            stopCopy?StopAtPhase:NULL,stopCopy?&stop:NULL,&report);
        if(stopCopy)printf("Requested stop observed: %d\n",stop.observed);
        if (status == UMI_STATUS_OK && report.verified)
            puts("Copied and verified a new regular file.");
    }
    UmiBootMediaPlanDestroy(plan);
    return Result(status, &report);
}

int main(int argc, char **argv)
{
    int result = 1;
    UmiStatus status = UmiNativeArgumentsDispatch(argc, argv, MediaLessonMain, &result);
    if (status != UMI_STATUS_OK) {
        fprintf(stderr, "Cannot capture native arguments (%d).\n", (int)status);
        return 1;
    }
    return result;
}
