<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/88-publish-encoded-bytes-only-after-admission.md

PURPOSE:
Teach publish encoded bytes only after admission through the production Kernel implementation.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Publish encoded bytes only after admission

![Umicom](../../../assets/branding/umicom-wordmark-on-dark.svg)

## Prepare an ownership experiment

An API that returns an error can still damage the caller if it partially overwrites output first. The handoff writer promises that both destination bytes and the written counter remain unchanged on refusal. Open its final reader call and publication block, then compare the small, unreserved and bad-text modes in the hosted writer lab.

The caller must supply real accessible storage. No numeric pointer-range check can prove that an arbitrary address is mapped or writable. Keep input, the full destination capacity and the length counter pairwise separate, and prevent concurrent mutation.

## Stage before publishing

The writer first encodes into a private stack buffer. The reader validates those staged bytes into a separate temporary observation. Only an OK result reaches the final copy. This retains one semantic authority instead of maintaining parallel reservation rules in a second producer.

~~~c
UmicomKernelBootHandoff checked;
UmicomBootHandoffStatus status =
    UmicomKernelBootHandoffRead(encoded, length, &checked);
if (status != UMICOM_BOOT_HANDOFF_OK) {
    return status;
}
UmicomBootMemoryCopy(destination, encoded, length);
*written = length;
~~~

This is all-or-nothing API behavior for a serialized call. It is not an atomic transaction for another CPU observing the destination during the copy. A future loader must establish synchronization and storage lifetime separately.

## Observe refusal without trusting a message

The lab fills the output with 0xa5 and sets written to 99. It saves the original bytes, calls the writer with an invalid request, then checks the status, every destination byte and the counter. Printing Refused without checking those outputs would not verify the contract.

For the small case, only 143 bytes are offered. For unreserved, the kernel no longer fits its reservation. For bad-text, command text begins with a newline. These reach different checks while requiring the same unchanged-output behavior.

## Understand the successful prefix

On success only the encoded prefix changes. The writer leaves the rest of the supplied destination untouched. The roundtrip lab verifies the tail sentinel, reads exactly written bytes into an owned observation and then clears the entire encoded buffer. The observation must retain its command text.

A pointer into the input bytes would fail that last experiment. Ownership means the observation contains its own arrays and command storage. It does not mean the physical memory described by the integers has been allocated or reserved.

## Exercise and answer

1. Place the written counter inside the destination range. Predict ARGUMENT and no changes: publishing either output would modify the other.
2. Place destination over the input record. Predict ARGUMENT: encoding must not overwrite fields still needed for admission.
3. Give 4097 as capacity even with a large real allocation. Predict LIMIT. The documented maximum is a contract, not a suggestion to silently clamp.
4. After a successful 158-byte record, pass all 4096 bytes to the reader. Predict LENGTH, because capacity and serialized length have different meanings.

## Budget the startup stack

The writer's encoded buffer is bounded, but it also calls a reader that stages a full observation. These stack allocations are nested. Before integrating a real firmware adapter, calculate available startup stack and inspect generated code under the intended compiler settings. A host process having enough stack is not proof that early boot does.

[Hosted laboratory](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/boot-handoff/README.md) · [Complete producer example](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/boot-handoff/write.c)

[Course contents](index.md) · [Previous lesson](87-admit-fields-before-narrowing.md) · [Next lesson](89-qualify-a-boot-producer-independently.md)

<!-- Repository laboratory sources live outside the published content root.
Public repository links replace the former local-only routes, retained here for review:
../../../../labs/native/boot-handoff/README.md
../../../../labs/native/boot-handoff/write.c
Offline source files remain available in their listed repository/learning-pack locations. -->
