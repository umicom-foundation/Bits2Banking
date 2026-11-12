<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/64-recognise-truncation-before-format-fallback.md

PURPOSE:
Teach optical format recognition and retained observations through the installed Framework ISO client.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->


![Umicom](../../../assets/branding/umicom-logo.svg)

# Recognise truncation before format fallback

<!-- Previous source-tree links are retained for review; public repository routes
     below remain usable after the lesson is published.
[Course contents](../../../courses/umicom-os-from-scratch/index.html) · [HTML edition](../../../courses/umicom-os-from-scratch/lessons/64-recognise-truncation-before-format-fallback.html) · [Complete lab](../../../../labs/native/framework-iso-inspection/README.md)
-->
[Course contents](../../../courses/umicom-os-from-scratch/index.html) · [HTML edition](../../../courses/umicom-os-from-scratch/lessons/64-recognise-truncation-before-format-fallback.html) · [Complete lab](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-iso-inspection/README.md)

## Start with three different questions

A format detector asks whether bytes identify a known format. A parser asks whether a recognised structure satisfies that format’s supported rules. A boot qualification asks whether a particular machine actually starts from the produced image. These questions have different evidence. In this lesson you extend the existing memory-only ISO client to distinguish an absent identifier, a recognised truncation and a completed structural observation. No file is created and no device is opened.


## Draw the first descriptor on paper

The supported optical profile places its first descriptor at byte 16 × 2048. Its first byte identifies a descriptor type; the next five bytes spell CD001. A source ending five bytes after the descriptor offset cannot supply the complete identifier. A source ending six bytes after that offset can identify the format but cannot contain the full descriptor. The second source is malformed recognised input, even though both are far shorter than a usable image.

| Scenario | Advertised extent | Expected result | Reads |
| --- | --- | --- | --- |
| prefix-short | 16 × 2048 + 5 | OK; zero flags | 0 |
| prefix-unknown | 16 × 2048 + 6; different identifier | OK; zero flags | 1 |
| prefix-truncated | 16 × 2048 + 6; CD001 present | PARSE_ERROR; output unchanged | 1 |
| prefix-sector | 17 × 2048; no following descriptor | PARSE_ERROR; output unchanged | 1 |


## Change the view, not the allocation

The laboratory allocates its usual synthetic buffer and changes Source.size to advertise a shorter extent. Bytes may still exist in the allocation after that boundary, but the callback must not expose them. This models a bounded input view. Allocated capacity and admitted source length are separate quantities. A parser that reads past the admitted view is incorrect even when the underlying allocation happens to be larger.

~~~c
Source source = {image, IMAGE_BYTES, 0, 0, 0};
source.size = 16U * BLOCK + 6U;
UmiIsoImageInfo info = {0};
UmiStatus status = UmiIsoImageInspect(Read, &source, source.size, &info);
~~~


## Keep parsing in Framework

The client sets up scenarios and owns the read callback. It never copies the ISO parser into its repository. The shared service probes only the available identifying bytes for an incomplete first sector. Once a complete sector is available, its existing parser checks descriptors, byte-order fields and the supported catalogue profile. Reusing that boundary ensures the Setup and Boot Media clients can receive the same classification from a matching Framework revision.


## Preserve the difference between an error and absence

The prefix-read-failure scenario makes the callback fail its first requested read. The inspector must return that I/O error and leave the destination unchanged. It must not convert the inability to read into “not ISO.” An actual storage failure, cancellation or permission refusal belongs to the reader’s own contract. This laboratory injects an error in memory; its output says nothing about the health of a disk.

~~~c
if ((source->fail && source->calls == 2U) ||
    (source->failAt != 0U && source->calls == source->failAt)) {
    return UMI_STATUS_IO_ERROR;
}
~~~


## Read retained flags in their original context

The retained-error scenario first inspects the complete synthetic BIOS fixture successfully. It then advertises a truncated descriptor and inspects again into the same output. The second call returns PARSE_ERROR while the earlier BIOS flags remain intact. That is the promised output-preservation behavior, not acceptance of the second source. The program prints a separate explanation so the historical flags cannot be mistaken for a current success. In retained-noniso, the second inspection succeeds with a different prefix and replaces the earlier flags with zeros.


## Run the installed client deliberately

Use the existing lab README to configure and build against one matching Framework SDK. Then run each command below separately. The two refusal demonstrations intentionally exit with code 1; CTest checks that exact result as well as the status, flags, read count and explanation. A crash or different error does not count as an expected refusal.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
.\build\framework-iso-inspection\btb-framework-iso-inspection.exe prefix-short
.\build\framework-iso-inspection\btb-framework-iso-inspection.exe prefix-truncated
.\build\framework-iso-inspection\btb-framework-iso-inspection.exe retained-error
ctest --test-dir .\build\framework-iso-inspection --output-on-failure --no-tests=error
~~~


## Complete a boundary experiment

Before executing a change, predict the result at one byte below, exactly at and one byte above the six-byte identifier boundary. Write down both the expected status and callback count. Keep the original cases. If an expectation fails, compare the advertised extent, callback bounds and installed SDK identity before changing the assertion. The source, lesson and thirteen installed-client checks are authored; their build and execution remain owner qualification. A passing memory fixture would still not establish CD burning, USB boot, firmware compatibility or publisher trust.

- Explain why unreadable is not the same as absent.
- Explain why a valid allocation can still contain bytes outside the admitted input.
- Identify which result owns the flags after a failed second inspection.
- Record compiler, architecture, SDK revision and the exact scenario with any observed failure.

