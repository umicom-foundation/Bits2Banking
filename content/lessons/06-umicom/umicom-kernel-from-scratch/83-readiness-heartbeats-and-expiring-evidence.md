# Treat readiness and heartbeats as expiring evidence

## A lease on a fact

A readiness report says that one process instance reached its own ready condition. A heartbeat renews evidence that the same instance is still participating. Neither should grant unlimited execution or permanent trust.

The managed-service ABI uses explicit operation and sequence fields. The first accepted report is READY with sequence one. Subsequent HEARTBEAT reports advance the sequence. The monitor checks the exact current session and reserved arguments; a copied or stale session cannot report for a replacement.

## Follow the clock

Before READY, the deadline bounds startup. After an accepted report, healthTicks determines the new deadline and reportTicks determines when the retained continuation may resume. A report at the deadline is late. Arithmetic that would overflow a deadline is refused.

The controller does not refresh syscall or slice budgets on a heartbeat. Otherwise a program could use an innocuous health message to escape its execution limit.

## Worked timeline

Suppose a conceptual service reports at tick 100 with health interval 50. Its evidence expires at 150. A report at 149 can be considered under the remaining checks; a report at 150 is too late. This example illustrates the comparison, not a promise that a stalled kernel handles the event at an exact wall-clock instant.

## Exercise and answer

The same process sends sequence two twice. Why reject the second report? Answer: the sequence identifies progress within an instance. Accepting a duplicate could renew health from replayed evidence.

## Source exercise

Read ServiceReportDispatch and ServiceCheckpointCommit in kernel/service_manager.c. The first records a pending report; the second publishes readiness only after the architecture return has been checked. Explain why publishing directly in the syscall handler would weaken that boundary.

The existing tests cover late reports, duplicate readiness, bad sequence, stale sessions and budget exhaustion. They are useful regression targets, but reading their assertions is not an executed result. Keep model tests, QEMU execution and physical-machine evidence separate.

[Course contents](index.md)
