![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Learning AArch64 Assembly

Trace Arm registers and branches, then inspect and link AArch64 ELF and Windows ARM64 COFF objects.

Start with the objects your computer can inspect. AArch64 is Arm’s 64-bit instruction set, called ARM64 on Windows. You can follow the first four lessons on paper. For the object exercises, install Clang, LLVM’s inspection tools and LLD, and confirm their names in your PowerShell session. The final two lessons use a built Umicom C that provides the AArch64 ELF and Windows ARM64 COFF commands. Keep each exercise in its own writable folder. Download its linked source files and keep the exact names used in the commands.

A compiler or linker can create Arm objects on an x64 development machine. The exercises inspect those bytes and predict what they would do. Run the commands one at a time and stop if one reports an error. No exercise starts a target executable, virtual machine or boot image.

## Reading order

1. [Trace a write to W0](01-trace-a-register-write.md)
2. [Build a signed result in two instructions](02-build-an-immediate.md)
3. [Compare the same bits as signed and unsigned](03-compare-signed-and-unsigned.md)
4. [Trace a loop with an explicit maximum](04-trace-a-bounded-loop.md)
5. [Preserve the return address across a nested call](05-preserve-a-return-address.md)
6. [Follow an unresolved call into an ELF link](06-link-an-elf-call.md)
7. [Compare ELF64 and Windows ARM64 COFF](07-compare-an-elf-and-coff-object.md)
8. [Link a Windows ARM64 call without executing the image](08-link-a-windows-arm64-caller.md)

## Memory spans and native call frames

Read these five lessons after the object-format labs.

9. [Read one stored byte in two integer forms](09-load-a-stored-byte.md)
10. [Check a C record offset before using it in Assembly](10-check-a-native-record-offset.md)
11. [Check a byte span before reading it](11-admit-a-counted-byte-span.md)
12. [Describe a saved stack frame to debugging tools](12-describe-a-frame-to-the-debugger.md)
13. [Check the same byte-span contract in host C](13-check-the-byte-contract-in-host-c.md)

[Browser edition](../../../courses/learning-aarch64-assembly/index.html) · [Computer architecture](../../../courses/learning-computer-architecture/index.html) · [RISC-V Assembly](../learning-riscv-assembly/index.md)
