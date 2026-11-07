<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/78-reserve-what-startup-already-owns.md

PURPOSE:
Reserve what startup already owns

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Reserve what startup already owns

This lesson explains one boundary between startup software and a kernel. It begins with a small hosted C program, uses synthetic addresses, and links the real Umicom Kernel reader. No previous operating-system course is required.

## Prepare a small host laboratory

A terminal accepts commands as text. A compiler translates C into machine instructions. CMake describes which files form a program; Ninja executes the build steps. Use a C23-capable GCC, CMake 3.24 or later and Ninja. On Windows these commands use an existing MSYS2 UCRT64 installation. Open PowerShell, enter one command at a time, and stop if it fails. Replace the checkout paths if yours differ. No boot disk or administrator access is needed.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S labs/native/boot-handoff -B build/boot-handoff -G Ninja -DUMICOM_KERNEL_SOURCE=C:/umicom/umicom-kernel
cmake --build build/boot-handoff --parallel 2
& .\build\boot-handoff\boot-handoff.exe
ctest --test-dir build/boot-handoff --output-on-failure --no-tests=error
```

On Linux, open a Bash terminal and use these equivalent paths:

```bash
cd ~/umicom/Umicom-Bits2Banking
cmake -S labs/native/boot-handoff -B build/boot-handoff -G Ninja -DUMICOM_KERNEL_SOURCE="$HOME/umicom/umicom-kernel"
cmake --build build/boot-handoff --parallel 2
./build/boot-handoff/boot-handoff
ctest --test-dir build/boot-handoff --output-on-failure --no-tests=error
```

The expected messages begin with `Accepted:` and `Refused:`. The latter confirms a deliberate invalid-input exercise. A nonzero exit code indicates the expected result was not obtained. If CMake cannot find the reader, check `UMICOM_KERNEL_SOURCE`; if a compiler option is unsupported, check the compiler version. These host checks do not establish that a kernel can boot.


## Availability and ownership

Knowing that an address is inside RAM does not mean it is free. The kernel image, boot metadata and other startup structures may already occupy it. A reservation prevents later allocation from overwriting information still in use.

The reader requires the entire kernel span to fit inside one RAM range and one reserved range. It does not infer coverage by combining adjacent entries. This conservative rule makes the producer responsible for expressing a complete covering range.

## Reproduce the refusal

1. Run the unchanged lab and observe its accepted message.
2. The program copies the result bytes into a snapshot.
3. It reduces the reservation from 8192 bytes to 4096.
4. The kernel still starts 4096 bytes into RAM, so the reservation ends exactly where the kernel begins.
5. The second call returns UMICOM_BOOT_HANDOFF_MEMORY, and the snapshot comparison checks that the prior result is intact.

The deliberate error demonstrates a useful contract: refusal does not destroy an earlier valid observation.

## Extend the reasoning

A real startup adapter must also protect the input record until parsing completes. The reader's copied output removes the later dependency on input-buffer lifetime, but does not itself reserve that buffer. This is a separate ownership duty at the adapter boundary.

## Exercise and recovery

Increase the kernel length to 8192 and calculate the smallest reservation beginning at 0x80000000 that covers it. The answer is 12288 bytes. Test the smaller value only as an expected-refusal experiment, then restore the original fixture. If a future allocator damages the kernel, investigate the point where reservations enter allocator state; a valid parser result alone does not prove that integration occurred.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/boot_handoff.c).

## Continue learning

[Course contents](../../../courses/umicom-kernel-from-scratch/index.html) · [Previous: Check physical-memory spans without integer wrap](77-check-physical-memory-spans.md) · [Next: Admit firmware and framebuffer descriptions](79-admit-optional-boot-descriptors.md)
