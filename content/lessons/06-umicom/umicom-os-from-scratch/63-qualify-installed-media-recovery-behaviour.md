<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/63-qualify-installed-media-recovery-behaviour.md

PURPOSE:
Teach qualify installed media recovery behaviour through the installed Framework media client.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-logo.svg)

# Qualify installed media recovery behaviour

## Identify the code that is actually running

The lab links an installed Framework package. Editing Framework source or packaging a new complete file does not update that installation. Before interpreting test results, record the producer revision, compiler, architecture, build configuration, SDK prefix and consumer executable. A matching header with an older library can expose declarations while retaining older runtime behaviour.


## Build through the existing workflow

Use the established owner workflow to build and install the intended Framework, then use the lab README commands to configure the consumer with that prefix and the matching practice-image tool. Keep the normal repository workflow unchanged. A fresh consumer build directory is useful when a previous cache selects another SDK; do not erase prior evidence just to obtain a clean log.


~~~powershell
ctest --test-dir .\build\framework-boot-media --output-on-failure --no-tests=error
~~~


## Read all twelve scenarios

The six original exercises still cover review, successful copy, existing output, stale review, wrong confirmation and tampered copy. Five new scenarios cancel at recheck, write, flush, verify and finished. A final case refuses an unknown phase before starting an operation. Case count alone is not success: retain failures, skipped cases, executable identities and test output.


## Separate three layers

| Layer | Evidence to collect |
| --- | --- |
| Injected Framework tests | Status precedence, one close attempt, clearing and publication under controlled failures. |
| Installed regular-file client | Real file creation, cancellation artifacts, public API linkage and independent comparison. |
| Product and boot qualification | Native interface lifetime, device selection, firmware startup and required OS workflows. |


## Review branding with the executable

The installed branding helper stages canonical Umicom SVG resources and embeds the approved ICO on Windows. The console uses the terminal font; HTML lessons use the shared course stylesheet and local font fallbacks. Inspect the installed and displayed identity during owner qualification. Static paths and hashes do not prove that a particular shell or desktop actually displayed the intended artwork.


## Expected result and next step

A successful run reports all twelve cases without failures, while retained artifacts match each case contract. Until that run is executed, this is an expectation and the course remains in development. Return to the OS boot-and-distribution evidence lesson to plan the independent startup checks.

<!-- Previous source-tree links are retained for review; public repository routes
     below remain usable after the lesson is published.
[Complete application](../../../../labs/native/framework-boot-media/main.c) · [Lab setup and recovery](../../../../labs/native/framework-boot-media/README.md)
-->
[Complete application](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-boot-media/main.c) · [Lab setup and recovery](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-boot-media/README.md)

[Course contents](index.md) · [Previous lesson](62-retain-failed-media-artifacts-for-recovery.md)


[Next: Recognise truncation before format fallback](64-recognise-truncation-before-format-fallback.md)
