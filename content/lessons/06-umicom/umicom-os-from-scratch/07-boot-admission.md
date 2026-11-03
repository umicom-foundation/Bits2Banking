# Make recovery decisions testable

Some startup code must mount filesystems or set the machine hostname. Other code only decides what should happen after those operations. Separating these responsibilities lets us check a failure policy without running an operating system inside the host process.

## Trace observations into a decision

1. Read `boot/foundation/boot_admission.h` in Umicom OS. Each boolean records a specific observation, such as whether configuration was accepted.
2. Read `admission.c`. It returns mode, state, reason and whether ordinary services may start. It does not perform the operations represented by its inputs.
3. Read the call in `init.c`. PID1 gathers actual results before asking for a decision.
4. Find `labs/native/os-boot-plan/test_admission.c` in Bits2Banking. The lab supplies observations and links the same policy source.

## Study failure precedence

A requested recovery boot is expected to avoid normal service startup. A failed hostname operation also prevents startup, but it is an error worth showing. The decision therefore keeps `reason=configuration` when hostname application failed, even if recovery was requested. It reports `reason=requested` only when the prerequisites were accepted.

Mount failure has higher precedence because it may prevent configuration and report storage from being available. Rejected command-line options cannot choose the boot mode. An empty service configuration cannot produce a normal startup decision.

## Run the focused lab after configuring it

```text
cmake --build "C:\umicom\Umicom-Bits2Banking\build\os-boot-plan" --target btb-os-admission-tests
ctest --test-dir "C:\umicom\Umicom-Bits2Banking\build\os-boot-plan" -R "^bits2banking[.]os_admission[.]" --output-on-failure --no-tests=error
```

Use the source paths and configuration command from lesson two first. Expected result: the three cases pass. That would check the supplied observations against the policy; it would not prove that guest mounting, hostname setup or recovery itself works.

## Exercise

Add a local case with `sourceValid=false`. Keep the normal-service flag false and expect a configuration reason. Then add a mount-failure case. Explain why merely setting every boolean to true is not evidence of an OS boot.

<details>

<summary>Why keep the recovery policy outside Framework?</summary>

This policy is specific to minimal PID1 startup. Independent recovery must remain available when a normal Framework service cannot start. Reusable host image and qualification tools still belong in Framework.

</details>

## Need an earlier explanation?

[Review the foundation concepts](../../00-getting-started/07-applications-os-and-kernel.md), then use the [connected learning map](../../../courses/learning-paths.html#os) for the longer written chapters. For C syntax or compiler commands, use the map's first-programming route before running this lab.

---

[Read this lesson in HTML](../../../courses/umicom-os-from-scratch/lessons/07-boot-admission.html) · [Learning sequence](../../../start/learning-sequence.md)
