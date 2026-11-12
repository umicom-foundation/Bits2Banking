<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/95-follow-startup-owner-transitions.md

PURPOSE:
Teach follow startup owner transitions through the native Kernel coordinator.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../assets/branding/umicom-logo.svg)

# Follow startup owner transitions

## Draw owners before drawing services

Startup is a sequence of ownership decisions. The Kernel first reserves its memory, then admits a complete job plan, executes bounded work, closes the job owners and checks that temporary frames returned. The console becomes useful only after those obligations succeed. A line saying that a job finished does not prove its resources were collected.

## Follow the coordinator in order

The session-environment job depends on runtime-contract. The first job may use two attempts; the second allows one. An attempt limit is a total count, not a count of extra retries. The existing controller remains responsible for fresh process identities and collection.

- Find UmicomKernelBootMemoryInitialize and the first physical-memory snapshot.
- Read the two job definitions and their dependency bits.
- Follow Initialize, repeated Step calls and Close on the same stable controller.
- Compare the later frame counters with the saved counters.
- Locate the readiness marker and the subsequent shell call.

## Keep the cleanup check separate

This is the important relationship in the real source. The coordinator checks several counters and validates the allocator after closing the jobs. A mismatch selects recovery even if the jobs appeared to complete.

~~~c
if (UmicomKernelBootServicesClose(&umicomSystemServices)
        != UMICOM_BOOT_SERVICE_OK)
    UmicomStartupRecovery("startup-cleanup", UMICOM_FALSE);
/* The following snapshot must match the saved allocation baseline. */
~~~

## Understand what a host observation substitutes

The coordinator fixture supplies controller outcomes and physical-memory snapshots deliberately. That lets a test force a cleanup error or change one counter while holding other inputs constant. Separate controller and allocator suites exercise their real implementations. Combining these evidence types is useful; calling the synthetic snapshot a physical-memory test would hide the boundary.

## Exercise and troubleshooting

A job reports success, Close refuses cleanup, and the old frame counts happen to match. Should the shell start? No. Cleanup refusal is its own failed obligation; matching counters do not erase it. Preserve the cleanup status, the job identity and the source revision. Do not reset the owner simply to obtain an empty-looking state.

Companion source: umicom-kernel/kernel/normal_boot.c and tests/boot_services/normal_boot_tests.c. Read docs/NORMAL_BOOT_COORDINATOR.md in the same Kernel checkout. Match source revisions before running the exercises.

[Course contents](index.md) · [Previous lesson](94-choose-a-kernel-startup-purpose.md) · [Next lesson](96-read-linker-boundaries-as-addresses.md)
