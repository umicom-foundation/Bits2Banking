# 85. Cross-compile safely and check the target ABI

You can develop software on one computer for a different processor. For example, an x86-64 Windows workstation can compile C23 and Assembly into RISC-V64 object files. This is **cross-compilation**. It is central to Umicom Kernel development because the project's first target is QEMU's RISC-V64 `virt` machine.

A file produced for a different target is not automatically runnable on the host. The compiler and linker may produce a valid RISC-V64 ELF object, while Windows still cannot execute RISC-V instructions directly.

## 1. Separate host from target

The **host** is the environment running the compiler. The **target** is the platform the generated machine instructions are intended for. The two may use different object formats, calling conventions and system libraries.

| Case | Host | Target | Typical output |
| --- | --- | --- | --- |
| Native Windows build | Windows x64 | Windows x64 | COFF object / PE application |
| Native Linux build | Linux x86-64 | Linux x86-64 | ELF object / ELF application |
| Kernel cross-build | Windows x64 | RISC-V64 | RISC-V ELF |

Do not infer the target from the filename extension alone. Inspect the object's machine field with `readelf`, `llvm-readobj`, or the appropriate native inspection command.

## 2. Inspect the prior cross-target laboratory

The previous lesson's source laboratory is in:

[`labs/native/cross-target-object`](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/cross-target-object)

It contains C23, a small RISC-V64 Assembly file and a CMake toolchain definition. The RISC-V exercise builds object files only: it does not execute privileged instructions.

The relevant Assembly operation reads the `mhartid` CSR. This register identifies a hardware thread (hart) on RISC-V. A normal Windows programme has neither that instruction set nor permission to execute such a machine-mode operation. The exercise demonstrates code generation and binary inspection, not a successful kernel boot.

## 3. Build a target object

From PowerShell with a suitable Clang installed, first check the compiler:

```powershell
clang --version
```

Then use the supplied toolchain file for the existing cross-target CMake laboratory rather than inventing a new flag combination. Its README lists the configure and compile-only commands.

After compilation, inspect the output file with the native Framework tools:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
& $Education binary --file "PATH_TO_RISCV_OBJECT"
& $Education symbols --file "PATH_TO_RISCV_OBJECT"
```

Replace the placeholder with an actual compiled RISC-V64 ELF object path. The first command recognises its basic ELF header. The second reports symbols and relocations, provided its supported ELF sections are present. The `symbols` command refuses PE/COFF files and objects beyond its input-size limit.

## 4. Match the function contract at every boundary

A function declaration in C is not enough to establish ABI correctness. C and Assembly must agree on:

- Target architecture and instruction set.
- Width and representation of each parameter.
- Registers or stack positions used for arguments and return values.
- Which registers the callee preserves.
- Stack alignment and any required unwind/debug metadata.

For example, the [linker-relocations laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/linker-relocations) chooses different Assembly source for Windows x64, Linux x86-64 and RISC-V64. It does not attempt to run RISC-V64 code on Windows.

The public C23 wrapper checks for arithmetic overflow before calling the Assembly leaf function. ABI correctness and input validation solve different problems; both are necessary.

## 5. Go from an object to a kernel image

A kernel needs more than a compiled object. It needs a defined entry point, a suitable linker script, a boot protocol, privileged instruction handling and platform-specific hardware support. Umicom Kernel documents these choices in its [first-boot guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/FIRST_BOOT.md).

The RISC-V64 first-boot image is loaded as firmware with QEMU's `-bios` option. This is not interchangeable with loading an arbitrary user-space ELF using `-kernel`. Following the project's current `BUILD_AND_TEST.md` avoids assuming the wrong privilege-level hand-off.

The **Umicom OS** repository is a different project: it develops an operating-system distribution with an existing kernel baseline. Its user-space Umicom Framework is not part of the freestanding boot kernel.

### Questions

1. What are host and target, and why are they often different?
2. How can you identify the target architecture without executing the object?
3. Why does selecting the wrong calling convention produce failures even if linking succeeds?
4. What additional work does a kernel need beyond compiling C source?
5. Why is an ELF file not necessarily a programme that can be launched on your current machine?

**Next:** [86. Test file readers and compiler boundaries](86-test-native-binary-boundaries.md).
