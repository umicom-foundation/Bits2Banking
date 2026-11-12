<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/39-inspect-an-image-without-booting-it.md

PURPOSE:
Inspect an image without booting it

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Inspect an image without booting it

## Prepare the exercise

Complete the source-build planning lessons first. You should be able to distinguish a byte buffer, a file path and a return status. Install the matching Framework SDK and follow the framework-boot-media lab README to build the C23 client and the existing practice-image tool. Keep the new practice directory, $Lab and $Image variables from that guide. No administrator account or physical drive is needed.

## Distinguish the objects you are inspecting

A kernel executable contains instructions for one target architecture and a particular startup contract. A disk image represents sectors and may contain partition tables, filesystems and loaders. An ISO image uses an optical-media filesystem layout and may carry boot catalogues. Giving a kernel file an .iso extension does not create those structures. Framework inspection reads the selected image as data; it does not execute the instructions it finds.

The supplied two-mebibyte practice image deliberately contains a synthetic MBR partition entry and no filesystem or operating system. MBR stands for master boot record. The structural flag tells you the parser accepted its supported layout and ranges. It cannot tell you whether a guest will start.

## Call the existing parser

Read the inspect branch in main.c. It uses Framework rather than duplicating the MBR, GPT or ISO parser. PRIu64 comes from inttypes.h and formats a uint64_t portably. The two NULL callback arguments request synchronous inspection without progress notifications. The report is caller-owned and remains available after the function returns.

```c
UmiBootMediaImage image = {0};
UmiBootMediaReport report = {0};
UmiStatus status = UmiBootMediaInspect(path, &image, NULL, NULL, &report);
if (status != UMI_STATUS_OK) {
    /* Present the failure; do not interpret image as accepted evidence. */
    return 1;
}
printf("Bytes: %" PRIu64 "\n", image.bytes);
```

## Make and interpret an observation

Expect Bytes: 2097152 and MBR: 1 for this particular practice file. Record the complete SHA-256 value; do not copy a sample digest from a lesson. The other structural flags should be zero. Then select a short text file in the same practice folder: inspection should refuse it rather than pretending that any readable file is a disk image.

Write two statements in your notes: what the inspector observed, and what you have not checked. A useful first statement names the absolute path, length and digest. The second should include provenance and boot behavior. A zero exit status is an observation about this parser invocation, not a release certificate.

```powershell
& $Lab inspect $Image
```

## Review and recover

If the client cannot load, compare the installed SDK and executable architecture before changing parser rules. If inspection rejects the practice image, keep the file and complete diagnostic; verify you used the named generator and did not pass its executable as the image. Do not relax sector or range checks to make an unrelated file pass. In the next lesson, use the accepted image to create a review without writing a destination.

[Lab setup and complete commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-boot-media/README.md) · [Read the C23 application](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-boot-media/main.c) · [Framework media contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/boot_media/media.h)

[Course contents](index.md) · [Previous lesson](38-plan-reproducible-build-and-resume-evidence.md) · [Next lesson](40-own-a-reviewed-media-plan.md)
