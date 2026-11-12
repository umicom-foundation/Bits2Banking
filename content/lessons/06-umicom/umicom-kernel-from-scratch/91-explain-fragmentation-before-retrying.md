<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/91-explain-fragmentation-before-retrying.md

PURPOSE:
Teach explain fragmentation before retrying through the real Kernel allocator.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Explain fragmentation before retrying

![Umicom](../../../assets/branding/umicom-wordmark-on-dark.svg)

## Count space and shape separately

An allocator snapshot reports how many pages are free. A contiguous request also depends on where those pages are. Fragmentation means that available storage is split into pieces that cannot satisfy the requested shape, even when their combined size is large enough.

The fragmentation scenario begins with sixteen modeled pages and reserves every second page. Eight pages remain free, but every free page is followed by an unavailable page. A request for two consecutive pages must fail. Returning any two free addresses would violate the public contiguous-run contract.

## Ask for a run without changing the inventory

The status name describes inability to satisfy this allocation. It does not promise that the free-frame counter is zero. Read the request, alignment, reservation layout and snapshot together when diagnosing it. The sentinel output makes accidental publication visible.

~~~c
UmicomAddress first = 0xdeadbeefU;
UmicomKernelMemoryStatus status =
    UmicomKernelPhysicalMemoryAllocateFrames(2U, 1U, &first);
/* In the alternating-reservation fixture:
 * status == UMICOM_KERNEL_MEMORY_OUT_OF_MEMORY
 * first  == 0xdeadbeefU
 * reserved=8, allocated=0, free=8
 */
~~~

## Retry after a meaningful change

The lab owns its synthetic reservations. It releases the reservation at 0x2000 and retries once. Pages 0x1000 and 0x2000 now form a valid two-page run, so the expected result is 0x1000. Releasing that run leaves seven reservations and nine free pages.

A real firmware reservation is not disposable scratch space. Never release Kernel, firmware, stack or device-owned storage merely to satisfy an allocation. A consumer can instead reduce its requested run, use a separately designed scatter/gather interface when its device permits that, or report the resource shortage. Those alternatives need their own contracts; this allocator does not silently choose one.

## Include alignment in the diagnosis

Even adjacent free pages may not begin at an eligible boundary. Imagine one free run from physical page 5 through page 7. It has three pages, but a request for two pages aligned to four cannot start there. Page 8 would meet the alignment rule, but it lies outside that free run.

Repeated calls with unchanged state should repeat the same refusal. A busy retry loop adds work without creating space. In a future concurrent system, waiting for ownership to change requires a synchronization and wakeup design. The current global allocator requires callers to serialize access and contains no blocking wait service.

## Investigate with an independent picture

The regression suite also checks per-frame state before and after refusal. Equal total counts alone could conceal an incorrect move of ownership from one page to another.

1. Draw sixteen boxes and label their absolute page numbers.
2. Mark the eight reserved pages before consulting any allocator output.
3. Mark every possible start for a two-page run; cross out starts whose next page is unavailable.
4. Repeat after releasing only the lab-owned reservation at 0x2000.
5. Compare your prediction with the scenario output after you build and execute it.

## Exercise and answer

A snapshot says free=6. The consumer asks for four pages aligned to eight and receives OUT_OF_MEMORY. Is the snapshot necessarily wrong? Answer: no. There may be no four-page free run, or its possible starts may fail alignment. Inspect shape and ownership before changing the allocator or increasing a timeout.

[Hosted laboratory](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/physical-frame-runs/README.md) · [Complete C example](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/physical-frame-runs/main.c)

[Course contents](index.md) · [Previous lesson](90-align-a-physical-frame-run.md) · [Next lesson](92-release-owned-pages-as-one-operation.md)
