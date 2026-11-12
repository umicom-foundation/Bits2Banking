<!--
Umicom Bits2Banking
File: labs/native/framework-iso-inspection/README.md

PURPOSE:
Explain an installed Framework ISO client and its structural limits.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->



# Inspect optical-image records with Umicom Framework

<!-- Earlier artwork reference retained for comparison; active documentation uses the canonical light-background wordmark.
![Umicom](../../../content/assets/branding/umicom-wordmark-on-dark.svg)
-->
![Umicom](../../../content/assets/branding/umicom-logo.svg)

This C23 application supplies a memory reader to the installed Framework ISO inspector. It demonstrates a service boundary: the application owns bytes and decides how they are read; Framework owns structural parsing. Its synthetic image contains enough descriptors for this exercise, but no working filesystem or boot loader. It creates no file and opens no device.

## Build the installed consumer

1. Install the matching Framework development SDK with the iso_image component, approved resources and application-branding helper. Headers and archives must come from the same compiler, architecture and source revision. A missing component usually means the installation predates this API.
2. In the commands below, C:/umicom/installed/framework is the example SDK prefix. Replace it if your installation is elsewhere. Run commands separately and stop on an error; PowerShell does not automatically stop after a failed native command.
<!-- The original six-case scope is preserved; the boundary continuation extends the same client.
3. Configure, compile and run the six checks yourself. These commands are qualification instructions, not recorded passing results.
-->
3. Configure, compile and run the thirteen checks yourself. These commands are qualification instructions, not recorded passing results.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\framework-iso-inspection -B .\build\framework-iso-inspection -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DCMAKE_PREFIX_PATH=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build .\build\framework-iso-inspection --parallel 2
ctest --test-dir .\build\framework-iso-inspection --output-on-failure --no-tests=error
.\build\framework-iso-inspection\btb-framework-iso-inspection.exe efi-zero
~~~

On Linux, select your matching native C23 compiler and SDK prefix; the executable has no .exe suffix. Do not use Windows archives with a Linux compiler. The console inherits your terminal font. Framework stages the approved SVG resources and, on Windows, embeds its ICO and version metadata. The lab adds no private logo or GTK dependency.

## Read the observations

| Scenario | Expected status | Expected flags | Exit |
| --- | --- | --- | --- |
| bios | 0 (OK) | ISO9660, El Torito, BIOS | 0 |
| efi-zero | 0 (OK) | ISO9660, El Torito, EFI | 0 |
| efi-one | 0 (OK) | ISO9660, El Torito, EFI | 0 |
| endian | 9 (parse error) | all zero | 1 |
| bios-zero | 9 (parse error) | all zero | 1 |
| read-failure | 8 (I/O error) | all zero | 1 |

The checker requires each exact exit and status, so a crash cannot count as an expected refusal. Initial output flags are zero and remain unchanged on a parser error. The source reader deliberately fails its second call in read-failure. That is an injected port failure, not a disk-health measurement.

## Follow the C ownership

Read accepts an offset and count, checks the offset first, then subtracts it from the buffer size. Only after those checks does it convert the offset to size_t and copy the requested bytes. UmiIsoImageInspect is synchronous and does not retain the context. main frees the buffer after that call returns. A real file adapter must enforce the same exact-read contract and keep the source stable; it should reuse Framework filesystem services.

The fixture writes the volume size twice because ISO9660 stores this field in both byte orders. The endian case changes one copy. The boot entry's sector count is measured in 512-byte units, while its start LBA identifies a 2048-byte block. UEFI uses zero and one counts specially to mean the remainder of the medium. That rule belongs to the EFI platform profile, not to an arbitrary BIOS entry.

## Extend and recover

Add a case that places the boot image at the end of the source. Predict why there are then no bytes to load, and assert a parse error with unchanged flags. Keep the old successful cases. If the new case passes unexpectedly, inspect the field offsets and platform value before changing the parser.

If the installed component is absent, install the corresponding SDK; do not copy parser source into this lab. If linking fails, compare installed header and archive revisions. If expected flags differ, preserve stdout, exit status, compiler identity and SDK revision. No result from this program establishes an actual ISO boot, USB transfer, CD burn, publisher trust or firmware compatibility.

Continue with the [OS ISO inspection lessons](../../../content/courses/umicom-os-from-scratch/lessons/45-share-a-read-only-image-inspector.html).


## Classify a truncated descriptor

The additional scenarios change the source's advertised extent while retaining the same allocated synthetic buffer. The callback must respect that shorter view even when bytes still exist beyond it. The client delegates all classification to the installed Framework inspector.

| Scenario | Expected status / exit | Expected flags | Callback count for the final inspection |
| --- | --- | --- | --- |
| prefix-short | OK / 0 | All zero | 0 |
| prefix-unknown | OK / 0 | All zero | 1 |
| prefix-truncated | PARSE_ERROR / 1 | All zero | 1 |
| prefix-sector | PARSE_ERROR / 1 | All zero | 1 |
| prefix-read-failure | IO_ERROR / 1 | All zero | 1 |
| retained-error | PARSE_ERROR / 1 | Earlier ISO9660, El Torito and BIOS flags | 1 |
| retained-noniso | OK / 0 | All zero, replacing the earlier flags | 1 |

The first two scenarios lack a complete matching ISO identifier. A complete identifier with an incomplete descriptor is recognised truncation. A callback error is neither success nor absence. The retained scenarios first perform a successful full inspection, then reuse that result storage. A failed second call leaves historical flags intact; a successful non-ISO observation replaces them with zeros.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
.\build\framework-iso-inspection\btb-framework-iso-inspection.exe prefix-truncated
.\build\framework-iso-inspection\btb-framework-iso-inspection.exe retained-error
.\build\framework-iso-inspection\btb-framework-iso-inspection.exe retained-noniso
ctest --test-dir .\build\framework-iso-inspection --output-on-failure --no-tests=error
~~~

The first two direct commands intentionally return exit 1. Their exact expected refusal is handled by the registered CTest wrapper. Run each command separately; do not continue past an unexplained failure.

For retained-error, expect status 9, the earlier BIOS flags, one callback and this explanation:

~~~text
Flags retained from prior inspection; they do not describe the refused source.
~~~

The original six cases remain registered. The complete thirteen-case suite, installed-SDK link and Windows ICO/resource appearance remain unexecuted until owner qualification. Read [Recognise truncation before format fallback](../../../content/courses/umicom-os-from-scratch/lessons/64-recognise-truncation-before-format-fallback.html) before extending the fixture. Keep the callback, parser and firmware evidence as separate claims.
