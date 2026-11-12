<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/93-qualify-contiguous-memory-without-device-claims.md

PURPOSE:
Teach qualify contiguous memory without device claims through the real Kernel allocator.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Qualify contiguous memory without device claims

![Umicom](../../../assets/branding/umicom-wordmark-on-dark.svg)

## Test the production implementation

The lesson executable links the actual Kernel physical allocator and checked-address helpers. It has no second allocation algorithm that might drift away from the product. The four scenarios teach alignment, fragmentation, complete release and coexistence with the single-page API.

Use the README to configure a new host build directory with explicit Kernel and Framework source paths. Framework supplies canonical SVG and Windows ICO resources to the hosted teaching executable. It is not linked into the freestanding allocator, and the lab does not introduce GTK into the Kernel.

## Layer the evidence

The 40 authored allocator cases cover argument refusal, absolute alignment, barriers, fragmentation, complete release, subranges, compatibility, top-of-address-space geometry, maximum capacity and reinitialization. Counts describe coverage that exists in source, not passing execution evidence.

The link-only contract targets include the actual allocator without discarding unused sections. This matters because hosted tests can hide compiler-generated runtime dependencies. The resulting ELF files are linkage artifacts, not new boot images.

1. Build and run the four teaching scenarios, keeping their source revision and output.
2. Build the isolated tests/physical_memory project in the Kernel checkout and execute its registered tests.
3. Build the Kernel umicom-boot-memory-contracts target using the prepared RISC-V toolchain to check freestanding linkage at debug and optimized settings.
4. Only after those checks pass, design and qualify a real consumer and its target-platform lifetime.

## Keep expected outcomes explicit

If the build fails, stop before attributing later test output to the new source. Old executables can remain in a build directory. Record command, compiler, source revisions, exit status and logs; keep skipped tests distinct from passes.

~~~text
alignment     first=0x4000, then allocated=0 after release
fragmentation two-page request refused with eight isolated free pages
release       refused whole release retains three live allocations
coexist       single-page and run ownership return to the same baseline
~~~

## Understand what the host did not prove

The host examples never access physical RAM. They prove properties of bookkeeping only when actually executed successfully. A physical device consumer still needs accessible mappings, DMA address constraints, cache management, completion ownership and a release point after the device has stopped using the buffer.

An aligned physical run also does not create an ISO, install a loader, choose a USB device or prove that firmware can boot it. Umicom OS image preparation and the Framework boot-media service handle those separate workflows. Keep their qualification records separate from this allocator contract.

## Troubleshoot the boundary

If the compiler cannot find AllocateFrames, verify that UMICOM_KERNEL_SOURCE selects the checkout containing the new declarations and implementation. If the branding helper is missing, correct UMICOM_FRAMEWORK_SOURCE rather than removing its resource checks. If a refused allocation changes a sentinel or a refusal changes ownership, retain the exact fixture and source identity before proposing a fix.

Exercise: all four hosted examples pass, but a target driver still corrupts a buffer after release. Does that prove the run allocator failed? Answer: no. Inspect whether the driver released ownership before DMA completion, whether addresses were correctly mapped and whether the platform cache rules were followed. The allocator cannot infer that a device still holds an address.

[Hosted laboratory](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/physical-frame-runs/README.md) · [Complete C example](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/physical-frame-runs/main.c)

[Course contents](index.md) · [Previous lesson](92-release-owned-pages-as-one-operation.md)


Continue with [Choose a Kernel startup purpose](94-choose-a-kernel-startup-purpose.md) to connect memory ownership with normal startup and recovery.
