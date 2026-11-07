# Keep rejected state separate from recovery

A parser can fail halfway through a record. Its caller should not receive a half-accepted plan. `UmiOsBootConfigParse` builds temporary state and publishes it only after all fields and dependencies pass. This is a transactional output contract.

## Follow the rollback test

1. Open `labs/native/os-boot-plan/test_plan.c`.
2. Find the `rollback` case. It first accepts a valid plan, then saves a copy.
3. It submits a configuration containing a disallowed executable path.
4. It compares the accepted plan with its saved copy. Failure must preserve the original bytes.

## Locate a rejected declaration

The detailed parser returns a problem category and a one-based line number when the issue belongs to one declaration. Whole-plan problems, such as a dependency cycle, use line zero. The boot-plan inspector prints this explanation on standard error and leaves standard output empty on rejection. Diagnostics do not change the accepted plan or relax its grammar.

## Recovery is a policy choice

The command-line field `umicom.recovery=1` requests recovery. The inspector reports the configured service count but schedules no ordinary services. It does not change the configuration or start an emergency shell. The real recovery console is implemented separately in the OS source.

Duplicate controls, such as `umicom.recovery=1 umicom.recovery=0`, are rejected. Accepting whichever value appears last can hide a disagreement between the bootloader and caller.

## Exercise

Add a local test that initializes output with a valid plan, submits a missing dependency, and checks unchanged output. Then inspect `init.c` and `console.c` to find where actual recovery behavior begins. Do not run PID1 directly on your host.

<details>

<summary>Is parser rejection the same as a successful recovery boot?</summary>

No. Rejection is one admission result. Recovery qualification needs a guest execution record showing the requested mode, the expected report and orderly shutdown.

</details>

## Need an earlier explanation?

[Review the foundation concepts](../../00-getting-started/07-applications-os-and-kernel.md), then use the [connected learning map](../../../courses/learning-paths.html#os) for the longer written chapters. For C syntax or compiler commands, use the map's first-programming route before running this lab.

---

[Read this lesson in HTML](../../../courses/umicom-os-from-scratch/lessons/04-failure-and-recovery.html) · [Learning sequence](../../../start/learning-sequence.md)

[Previous: Plan startup before executing it](03-service-dependencies.md)

[Next: Know which bytes you booted](05-image-and-firmware-identity.md)
