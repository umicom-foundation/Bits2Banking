<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/54-preserve-an-observation-on-refusal.md

PURPOSE:
Teach preserve an observation on refusal through the installed Framework GPT service.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-logo.svg)

# Preserve an observation on refusal

[Course contents](index.md) · [Previous lesson](53-reserve-table-space-before-partitions.md) · [Next lesson](55-distinguish-checksums-from-trust.md)

[Complete source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-gpt-inspection/main.c) · [Build and run the lab](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-gpt-inspection/README.md) · [Qualification guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-gpt-inspection/QUALIFICATION.md)

An application often has a useful result before its next operation fails. Replacing that result with partially validated data makes recovery difficult and can mislead the user. This lesson follows the lab’s successful observation, controlled refusal and fresh retry through the same public API.

## Before you begin

Prepare the valid GPT memory fixture and a separate output structure for the last accepted observation. Review the lab refusal scenarios before injecting a read failure. Keep the original successful observation available for a field-by-field comparison after the refused call.

## Capture the successful state

~~~c
UmiGptImageInfo observation = {0}, previous;
UmiStatus status = UmiGptImageInspect(LabReadAt, &image,
    image.length, image.block, &observation);
/* Check status before accepting observation. */
memcpy(&previous, &observation, sizeof(previous));
~~~

The complete program checks status before the copy. memcpy captures the entire stored representation, including any padding bytes, so the later comparison can detect a write to output even when the visible field values happen to match. It is not a serialization format, and it should not be used to compare structures received from unrelated processes.

## Refuse a partial observation

Each malformed scenario changes the source and calls the parser again with the same output object. The parser builds a private candidate and publishes it only after all checks succeed. Failure therefore leaves the previous object unchanged. The application must still label that object as the previous observation, rather than implying it describes the newly rejected source.

~~~c
status = UmiGptImageInspect(LabReadAt, &image,
    image.length, image.block, &observation);
if (status != UMI_STATUS_OK &&
    memcmp(&previous, &observation, sizeof(observation)) == 0) {
    /* Report the current refusal and retain the earlier observation. */
}
~~~

## Inject an exact-read error

The read-failure scenario sets failRead to 3 after resetting the read counter. The next call reads two headers and then receives IO_ERROR from the primary-array read. The service must propagate that status, release temporary ownership and leave output unchanged. The callback does not supply guessed or zero-filled bytes to turn an incomplete read into success.

## Retry from a fresh source

The retry scenario first creates a malformed reservation and observes refusal. It then destroys the synthetic source and constructs a new valid one. A later call must succeed with four reads and one active partition. Reusing the output object is allowed; reusing freed source pointers is not.

~~~c
LabImageDestroy(&image);
if (!LabImageCreate(&image, block)) return 1;
status = UmiGptImageInspect(LabReadAt, &image,
    image.length, block, &observation);
~~~

The full program keeps cleanup in one exit path, including failed assertions. The new source does not inherit the old read-failure counter. This is a simple example of reconstructing a valid input before retrying instead of weakening the parser’s refusal.

## Exercise and worked explanation

Imagine a GUI with a green “one partition” label left over from the first call. The second call fails. Should the label remain green without explanation? No. Data preservation is an internal ownership guarantee, not permission to display stale success as current success. Show the latest error and clearly identify any retained observation as belonging to the earlier source.

## Qualification boundary

Run read-failure and retry separately and retain their exit codes. They exercise callback error propagation and replacement of a synthetic source. They do not test concurrent mutation, native worker scheduling or a GUI’s presentation state. Those behaviors belong to separate application tests with their own source and environment identities.

[Primary GPT format reference](https://uefi.org/specs/UEFI/2.11/05_GUID_Partition_Table_Format.html)

[Standalone lesson](../../../courses/umicom-os-from-scratch/lessons/54-preserve-an-observation-on-refusal.html)
