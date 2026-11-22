<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/multikernel-systems/06-qualify-a-kernel-experiment.md

PURPOSE:
Design a staged experiment that measures when a separate kernel earns its cost.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material.
-->

# Qualify a kernel experiment

<p class="umicom-course-artwork"><span class="umicom-brand-mark"><img src="../../../assets/branding/umicom-wordmark.svg" alt="Umicom" width="180"></span> <a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="30"></a></p>

An **ISA** is the instruction set a processor can execute. QEMU can translate instructions and emulate a guest built for a different ISA. A compatible hardware-accelerated VM also needs a guest boot path, trap handlers and virtual devices. A **hart** is a hardware thread in RISC-V. The inspected Umicom Kernel bootstrap parks secondary harts, so a one-hart boot only provides evidence about that execution path.

## Choose evidence for each step

| Experiment | Evidence to retain | Claim you can make |
| --- | --- | --- |
| C23 host lab | Expected bytes, accepted and refused requests, compiler and test result | The sample request parser followed its contract on that host. |
| One emulated guest | Image identity, boot observation, current probe, bounded request and restart trace | The selected guest completed a functional service exercise. |
| Two-hart emulator | Separate stacks, trap and allocator ownership, boot handshakes and message traces | The two initialisations and specified handoff ran in that emulator. |
| Matched hardware workload | Host and guest identities, placement, latency, completed work, output quality and recovery | Performance and failure scope on the measured configuration. |

Read the RISC-V bootstrap and find the branch that parks a nonzero hart. Sketch the state that must be owned before a second hart can enter. Include its stack, trap state, timer, memory region and communication initialization. Identify which owner writes to the console. [Umicom Kernel bootstrap](https://github.com/umicom-foundation/umicom-kernel/blob/main/arch/riscv64/boot.S) · [QEMU system emulation](https://www.qemu.org/docs/master/system/introduction.html)

## Write a fair comparison plan

1. Define one job and an outcome. Use a fixed integer transform first. A later inference trial can fix model identity, input size, numeric precision and quality criteria.
2. Record ordinary Linux execution and a Framework-managed worker as baselines. Compare a separate-kernel profile only after specifying the unmet requirement and how the profile enforces it.
3. Keep hardware and major software settings consistent where practical. Record unavoidable differences. Measure time after warm-up, successful work, refusals, recovery time and resources retained after a fault.
4. Compare one hypothetical report with another. A report with lower average latency but fewer completed requests needs its rejection and timeout counts beside the latency. Keep emulator timings with functional observations and use hardware measurements for performance decisions.

## Practise separating three kinds of evidence

1. Write `0x12345678` in little-endian byte order as `78 56 34 12`. XOR the value with `0xabcd1234`. Expect the result bytes `4c 44 f9 b9`. Repeat the exercise with a three-byte span and a declared count of one word. A bounded payload operation should refuse it before changing any byte.
2. Read a device tree from the emulator release installed on your machine. A device tree is the hardware description supplied to the guest. Record how many serial devices it describes before choosing a service channel. Keep diagnostics on an independently identified channel and check that the guest has a driver for the proposed service transport.
3. Design a separate test that obtains a reply from the current guest instance after boot. Retain the emulator version, guest image, exact reply and reason for any refusal. Label your three records **payload result**, **device inventory** and **guest reply** so another learner can reproduce each observation.

## Capture binary output from a separate guest console

Use a Kernel checkout that includes the service console fixture. From its root in PowerShell, use the RISC-V Clang toolchain, Ninja and QEMU. The two boots use the same image and differ in whether a VirtIO console device is attached.

```powershell
$build = 'build/multikernel-service-console'
cmake --preset riscv64-clang-debug -B $build -DUMICOM_KERNEL_SERVICE_CONSOLE_FIXTURE=ON
ctest --test-dir $build -N -V -R '^kernel[.]riscv64[.]service_console[.]'
ctest --test-dir $build -V --output-on-failure --no-tests=error -R '^kernel[.]riscv64[.]service_console[.]'
Format-Hex -Path (Join-Path $build 'service-console-transmit.bin')
Get-FileHash -Algorithm SHA256 -Path (Join-Path $build 'bin/umicom-service-console-guest.elf')
```

1. The listing command prints the registered build and two guest test commands without running them. Find the same image path in the two guest commands. Open `tests/service_console_transport/check_guest.cmake` and follow its `MODE` setting. Both modes send the diagnostic UART to standard output through `-serial stdio`. Only the transmit mode adds a VirtIO device and a file backend.
2. Run the tests and record their statuses. The transmit boot prints `service-console: transmit and reset acknowledged` on the UART. The guest fixture writes that marker after the driver checks the completion and observes device status return to zero. Separately compare the entire backend file with `4c 44 f9 b9 00 ff 0a 0d`. Hexadecimal makes the zero and newline bytes visible.
3. Find `service-console: no console; diagnostic UART still active` in the absent-device boot. The UART remains available without the service device. The transmit file belongs to the transmit test, so an existing copy supplies no evidence about the absent-device boot.

Keep the image hash, QEMU version, two UART observations and binary output together. Use the QEMU executable printed in the test listing to check its version. If the guest tests do not appear, check that CMake found QEMU. If the build fixture fails, record the build failure before interpreting earlier files. This experiment establishes guest-to-host transmission of one synthetic payload. The receive queue stays empty. A host request and a correlated reply still need their own test.

As a final check, write one sentence each for Framework, OS and Kernel. Name who admits the work, who composes the supported profile and recovery route, and who enforces native resource access. Give each claim an observable test.
