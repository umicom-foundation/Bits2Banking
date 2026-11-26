/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/boot-evidence-review/main.c
 *
 * PURPOSE:
 *   Compare distinct virtual boot observations in a local teaching exercise.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>

typedef enum BootRoute {
    BOOT_DIRECT,
    BOOT_OPTICAL,
    BOOT_VIRTUAL_USB
} BootRoute;

typedef enum Firmware {
    FIRMWARE_BIOS,
    FIRMWARE_UEFI
} Firmware;

typedef enum BootMode {
    MODE_NORMAL,
    MODE_RECOVERY
} BootMode;

typedef struct Capture {
    BootRoute route;
    Firmware firmware;
    BootMode mode;
    const char *imageDigest;
    const char *transcriptDigest;
    bool launched;
    bool shutdownSeen;
    int exitCode;
} Capture;

typedef struct Evidence {
    const char *reviewedImageDigest;
    BootRoute expectedRoute;
    Firmware expectedFirmware;
    bool structureReviewed;
    Capture normal;
    Capture recovery;
} Evidence;

typedef struct Assessment {
    bool complete;
    const char *message;
} Assessment;

static const char imageDigest[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
static const char otherImageDigest[] = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
static const char normalDigest[] = "cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc";
static const char recoveryDigest[] = "dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd";

static bool IsDigest(const char *digest)
{
    /* Keep the classroom rows comparable to lowercase SHA-256 records from the tools. */
    return digest && strlen(digest) == 64U && strspn(digest, "0123456789abcdef") == 64U;
}

static bool IsComplete(const Capture *capture)
{
    return capture->launched && capture->shutdownSeen && capture->exitCode == 0;
}

static Assessment Review(const Evidence *evidence)
{
    const Capture *normal = &evidence->normal;
    const Capture *recovery = &evidence->recovery;

    /* Each decision checks one kind of observation before relying on the next. */
    if (!evidence->structureReviewed)
        return (Assessment){false, "Review the image structure before admitting a boot claim."};
    if (!IsDigest(evidence->reviewedImageDigest) ||
        !IsDigest(normal->imageDigest) || !IsDigest(recovery->imageDigest) ||
        !IsDigest(normal->transcriptDigest) || !IsDigest(recovery->transcriptDigest))
        return (Assessment){false, "Check the format of every SHA-256 pin."};
    if (normal->route != evidence->expectedRoute || recovery->route != evidence->expectedRoute)
        return (Assessment){false, "The capture used a different boot path."};
    if (normal->firmware != evidence->expectedFirmware || recovery->firmware != evidence->expectedFirmware)
        return (Assessment){false, "A capture used different firmware."};
    if (strcmp(evidence->reviewedImageDigest, normal->imageDigest) != 0 ||
        strcmp(evidence->reviewedImageDigest, recovery->imageDigest) != 0)
        return (Assessment){false, "A boot capture refers to a different image."};
    if (normal->mode != MODE_NORMAL || recovery->mode != MODE_RECOVERY)
        return (Assessment){false, "Check which capture actually ran in normal or recovery mode."};
    if (!IsComplete(normal) || !IsComplete(recovery))
        return (Assessment){false, "A launch, shutdown marker or process result is missing or unsuccessful."};
    if (strcmp(normal->transcriptDigest, recovery->transcriptDigest) == 0)
        return (Assessment){false, "Save separate transcripts for normal and recovery."};

    return evidence->expectedRoute == BOOT_OPTICAL
        ? (Assessment){true, "Virtual optical boot evidence complete."}
        : (Assessment){true, "Virtual USB boot evidence complete."};
}

typedef enum Change {
    KEEP_OPTICAL,
    SELECT_USB,
    OMIT_REVIEW,
    USE_DIRECT,
    REPLACE_IMAGE,
    CHANGE_FIRMWARE,
    OMIT_SHUTDOWN,
    PROCESS_FAILED,
    REUSE_LOG,
    WRONG_MODE,
    BAD_PIN
} Change;

typedef struct Example {
    const char *name;
    Change change;
} Example;

static const Example examples[] = {
    {"optical", KEEP_OPTICAL}, {"virtual-usb", SELECT_USB},
    {"no-file-review", OMIT_REVIEW}, {"direct-only", USE_DIRECT},
    {"wrong-image", REPLACE_IMAGE}, {"wrong-firmware", CHANGE_FIRMWARE},
    {"no-shutdown", OMIT_SHUTDOWN}, {"process-error", PROCESS_FAILED},
    {"repeated-log", REUSE_LOG}, {"swapped-modes", WRONG_MODE},
    {"malformed-pin", BAD_PIN}
};

static Evidence MakeExample(Change change)
{
    /* Use fixed, fictional pins and vary one observation at a time. */
    Evidence evidence = {
        .reviewedImageDigest = imageDigest,
        .expectedRoute = BOOT_OPTICAL,
        .expectedFirmware = FIRMWARE_UEFI,
        .structureReviewed = true,
        .normal = {BOOT_OPTICAL, FIRMWARE_UEFI, MODE_NORMAL, imageDigest, normalDigest, true, true, 0},
        .recovery = {BOOT_OPTICAL, FIRMWARE_UEFI, MODE_RECOVERY, imageDigest, recoveryDigest, true, true, 0}
    };

    switch (change) {
        case KEEP_OPTICAL: break;
        case SELECT_USB:
            evidence.expectedRoute = BOOT_VIRTUAL_USB;
            evidence.normal.route = BOOT_VIRTUAL_USB;
            evidence.recovery.route = BOOT_VIRTUAL_USB;
            break;
        case OMIT_REVIEW: evidence.structureReviewed = false; break;
        case USE_DIRECT: evidence.normal.route = BOOT_DIRECT; break;
        case REPLACE_IMAGE: evidence.recovery.imageDigest = otherImageDigest; break;
        case CHANGE_FIRMWARE: evidence.recovery.firmware = FIRMWARE_BIOS; break;
        case OMIT_SHUTDOWN: evidence.recovery.shutdownSeen = false; break;
        case PROCESS_FAILED: evidence.normal.exitCode = 1; break;
        case REUSE_LOG: evidence.recovery.transcriptDigest = normalDigest; break;
        case WRONG_MODE: evidence.normal.mode = MODE_RECOVERY; break;
        case BAD_PIN: evidence.recovery.transcriptDigest = "incomplete"; break;
    }
    return evidence;
}

int main(int argc, char **argv)
{
    if (argc == 2) {
        /* The case name selects a local row and is never used as a path. */
        for (size_t i = 0; i < sizeof examples / sizeof examples[0]; ++i) {
            if (strcmp(argv[1], examples[i].name) == 0) {
                const Evidence evidence = MakeExample(examples[i].change);
                const Assessment result = Review(&evidence);
                if (puts(result.message) == EOF || fflush(stdout) == EOF)
                    return 1;
                return result.complete ? 0 : 1;
            }
        }
    }

    fputs("Choose a case listed in the lab README.\n", stderr);
    return 2;
}
