<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/89-qualify-a-boot-producer-independently.md

PURPOSE:
Teach qualify a boot producer independently through the production Kernel implementation.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Qualify a boot producer independently

![Umicom](../../../assets/branding/umicom-wordmark-on-dark.svg)

## Prepare an evidence plan

A reader and writer can agree with each other while both contain the same offset mistake. Qualification therefore needs more than a round trip. Start with the documented wire layout, then inspect literal expected bytes, refusal ownership, freestanding linkage and finally platform integration as separate questions.

Use docs/BOOT_HANDOFF.md for the isolated host commands. The suite defines 18 reader cases and 28 writer cases. These counts describe authored coverage; only results from the tested source and environment can establish which cases passed, failed or were skipped.

## Keep an independent byte reference

The golden case uses a literal 144-byte array rather than asking the writer to generate its expected output. Its version is 1 at byte 8, header length is 64 at byte 10, record length is 144 at byte 12, and architecture is 1 at byte 16. Separate known offsets encode the kernel and memory spans.

Check those literals against the public wire table. If the producer and consumer both shift the kernel field to an incorrect offset, their round trip might still pass, but comparison with the independent golden record should fail. Review expected bytes carefully; an independent fixture can itself contain mistakes.

## Combine different kinds of checks

1. Use golden and architectures to inspect stable wire representation.
2. Use maximum and unused to check bounded work and exclusion of unused storage.
3. Use roundtrip and tail to check decoded ownership and exact publication length.
4. Use capacity, text, enum and semantic-refusal cases to exercise admission boundaries.
5. Use overlap cases to confirm that separate outputs cannot alias input or each other.

## A host library can hide a boot dependency

Hosted tests link the normal C runtime. A compiler-generated memcpy or memset may therefore work in a host executable even though early boot has no such symbol. The Kernel's UmicomBootMemoryClear and UmicomBootMemoryCopy use the established freestanding implementation to avoid that hidden dependency.

The umicom-boot-memory-contracts target links the real reader and writer with no hosted runtime at debug and optimised settings. Uncalled functions remain linked so that section removal cannot conceal their dependencies. These ELF files are link checks, not images to boot. A successful link still does not prove stack sufficiency or firmware compatibility.

## Record exactly what ran

For each qualification step, retain the source revisions, compiler and target, command, exit code and result log. A failed build means later tests may be using older executables; rebuild successfully before attributing those results to a fix. Keep skips distinct from passes and preserve the first failing diagnostic.

The hosted teaching tools receive canonical Umicom SVG and Windows ICO resources through Framework's branding helper. That establishes an authored packaging route. Inspect the built resource and staged files during owner qualification before claiming correct installed appearance. The freestanding Kernel does not inherit a GTK dependency or a console-font choice from this helper.

## Exercise and answer

You obtain a passing round trip, but the freestanding debug link reports an unresolved memset. Is the producer ready for a startup adapter? Answer: no. The host result remains useful evidence, but the runtime dependency must be corrected and the link checks rerun. Next, the adapter must establish memory accessibility, reserve the record and referenced storage, budget stack and exercise its actual platform entry.

Selecting a BIOS or EFI boot catalogue in an ISO is a separate image-production workflow. This boot-metadata writer neither creates that catalogue nor installs a loader. Keep the Kernel and Umicom OS image qualification records distinct.

[Hosted laboratory](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/boot-handoff/README.md) · [Complete producer example](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/boot-handoff/write.c)

[Course contents](index.md) · [Previous lesson](88-publish-encoded-bytes-only-after-admission.md)

<!-- Repository laboratory sources live outside the published content root.
Public repository links replace the former local-only routes, retained here for review:
../../../../labs/native/boot-handoff/README.md
../../../../labs/native/boot-handoff/write.c
Offline source files remain available in their listed repository/learning-pack locations. -->

Continue with [aligned physical frame runs](90-align-a-physical-frame-run.md) to follow memory ownership after boot admission.
