<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/57-read-file-effects-separately-from-status.md

PURPOSE:
Teach read file effects separately from status through the installed Framework media client.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-logo.svg)

# Read file effects separately from status

## Before you begin

Open the framework-boot-media lab README and use its regular-file practice fixture in a dedicated scratch directory. Identify the installed Framework SDK and the client executable before interpreting report fields. Do not select a physical disk; the exercises in this module rely on disposable regular files.

## Begin with an incomplete operation

A file-copy function returning an error does not necessarily leave the filesystem unchanged. Opening a new output may create an empty file before allocation or metadata checks fail. Writing can fail after accepting some bytes. The media report therefore carries observations separately from its final status. Open the installed-client main.c and find Result, which prints the same fields for success and failure.


~~~c
UmiBootMediaReport report = {0};
UmiStatus status = UmiBootMediaApply(plan, fingerprint, confirmation,
    NULL, NULL, &report);
/* Inspect status and report before deciding what evidence to retain. */
~~~


| Observation | Meaning |
| --- | --- |
| outputCreated | Exclusive creation of a new regular-file destination occurred. |
| writeStarted | A payload write was attempted; it does not count completed bytes. |
| verified | The operation completed its required agreement checks and release without a failure. |


## Follow the native boundary

Framework records creation immediately after the operating system creates the leaf file. Later admission failure cannot erase that fact. This is why deriving outputCreated from status == UMI_STATUS_OK is incorrect. Physical-device writes have different ownership and do not use the regular-file creation flag. These lessons exercise regular files only.


## Read and predict

- Locate BmCreateObserved in Framework src/boot_media/io.c and the regular-file branch in transfer.c.
- Predict the three flags when allocation fails after exclusive creation. Compare your answer with the created-no-memory injected regression.
- Run the owner-controlled cancellation exercises later in this module and compare their printed reports with the files retained on disk.


## Expected observation and recovery

A created but unwritten output can have outputCreated equal to one, writeStarted equal to zero and verified equal to zero. Keep it for diagnosis; do not label it an approved distribution image. If a report contradicts the observed artifact, record the executable and SDK identities before changing code. Authored test expectations are not evidence that your installed library contains the fix.

<!-- Previous source-tree links are retained for review; public repository routes
     below remain usable after the lesson is published.
[Complete application](../../../../labs/native/framework-boot-media/main.c) · [Lab setup and recovery](../../../../labs/native/framework-boot-media/README.md)
-->
[Complete application](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-boot-media/main.c) · [Lab setup and recovery](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-boot-media/README.md)

[Course contents](index.md) · [Previous lesson](56-qualify-an-installed-image-client.md) · [Next lesson](58-own-a-synchronous-progress-context.md)
