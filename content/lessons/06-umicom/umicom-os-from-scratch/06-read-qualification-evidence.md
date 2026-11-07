# Separate a check from a release claim

Different checks answer different questions. A parser test checks accepted values and state ownership. An inert process fixture checks arguments, timeouts and result files. A guest run checks the image's behavior on a specified machine profile. Hardware and release checks add further requirements.

## Read evidence in this order

1. Record source revisions and any uncommitted source differences.
2. Read the configure result and selected compiler and toolchain.
3. Confirm that the required targets compiled and linked.
4. Inspect the test log, including failures, missing tests and skips.
5. For a guest run, inspect the request, console transcript and result together. Check source, firmware, exit code, cancellation and timeout.

The OS CI has separate user-space and independent foundation jobs. Download artifacts from failed runs too. The identity-transition test requires a private chroot and runs separately from unprivileged parser tests.

## Inspect a captured report

The OS application accepts `--boot-report ABSOLUTE_FILE` and an optional `--source SHA256`. It uses Framework to read at most 512 bytes and parse the existing boot-report protocol. Supply the report record, not an entire serial transcript. A source mismatch or malformed file is rejected without presenting an accepted report.

Successful inspection means the file was readable and internally consistent. A valid report can still say `state=recovery` with a service failure reason. It is also possible for a once-valid report to be old. Explain those limits in your evidence table.

## Exercise

Create a small evidence table with columns: check, source identity, environment, outcome and limitation. Fill one row for the boot-plan lab. If you have not executed it, write **not run**. If a case is skipped, retain that as a separate outcome.

## Next work

A full OS course still needs qualified image construction, normal and recovery guest sessions, persistent storage, package/update policy, networking and desktop integration. The initial lessons establish the source-reading and admission checks needed before those steps. They do not claim a complete bootable course image.

<details>

<summary>Can a fixture emit a perfect-looking boot transcript?</summary>

Yes. A transcript alone is not authenticated execution evidence. Keep fixture results explicitly labeled and retain the identity of the program actually launched.

</details>

## Need an earlier explanation?

[Review the foundation concepts](../../00-getting-started/07-applications-os-and-kernel.md), then use the [connected learning map](../../../courses/learning-paths.html#os) for the longer written chapters. For C syntax or compiler commands, use the map's first-programming route before running this lab.

---

[Read this lesson in HTML](../../../courses/umicom-os-from-scratch/lessons/06-read-qualification-evidence.html) · [Learning sequence](../../../start/learning-sequence.md)

[Previous: Know which bytes you booted](05-image-and-firmware-identity.md)

[Next: Make recovery decisions testable](07-boot-admission.md)
