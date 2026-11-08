# Boot is the start of a service lifetime

## Connect the earlier lessons

The earlier course traces native startup, physical memory, user address spaces and bounded IPC. A boot message proves that execution reached a point. It does not prove that a service remains alive, answers requests or can be replaced safely.

Umicom Kernel's managed-service controller builds on its existing loader, supervisor, scheduler and stream owner. It supplies lifecycle policy. It does not replace the architecture adapter or turn stdout into a readiness signal.

## Read the plan

Open include/umicom/kernel/service_manager.h and docs/MANAGED_SERVICES.md in [Umicom Kernel](https://github.com/umicom-foundation/umicom-kernel). A plan supplies a name, immutable ELF bytes, launch arguments, dependencies and bounded timing/attempt budgets.

Names and launch strings are copied into owned storage. The ELF bytes are borrowed and must remain immutable and alive until the manager closes. Keep the manager at one stable zero-filled address; copying it would break its self-identity and embedded ownership.

## Worked lifecycle

A provider starts before a consumer that depends on it. Loading the provider changes it to STARTING. Only its accepted READY report, committed after the execution adapter checks restoration, makes it HEALTHY. The consumer is then eligible for admission. An exit value of zero is terminal completion, not evidence of a live service.

## Exercise and answer

The provider prints “ready” and exits. Should the consumer start? Answer: not on that evidence. A log string is not the managed report contract, and the process no longer provides a live dependency.

## Practical source trace

1. Find Initialize and its preflight of the plan.
2. Find Step and its one-admission/one-quantum structure.
3. Locate ServiceReportDispatch.
4. Locate ServiceCheckpointCommit and identify the post-return checks.
5. Explain which owner keeps each buffer alive.

Do this source exercise before changing the boot image. Host model tests exercise policy with simulated machine entry; guest execution must separately demonstrate actual RISC-V instructions and trap restoration. This lesson makes no new boot-success claim.

[Course contents](index.md)
