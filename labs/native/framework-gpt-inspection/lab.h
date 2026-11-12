/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/framework-gpt-inspection/lab.h
 *
 * PURPOSE:
 *   Own a synthetic image and an exact-read port for the installed Framework GPT service.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#ifndef UMICOM_GPT_COURSE_LAB_H
#define UMICOM_GPT_COURSE_LAB_H
#include "umicom/image_inspection/gpt.h"
#include <stddef.h>
#include <stdint.h>

typedef struct LabImage {
    unsigned char *bytes;
    size_t length;
    uint32_t block;
    unsigned reads, failRead;
} LabImage;
/* Construction creates synthetic metadata only. No executable boot code,
 * filesystem, path, device handle or real disk identifier is supplied. */
int LabImageCreate(LabImage *image, uint32_t block);
void LabImageDestroy(LabImage *image);
int LabImageChange(LabImage *image, const char *scenario);
UmiStatus LabReadAt(void *context, uint64_t offset, void *destination, size_t length);
#endif
