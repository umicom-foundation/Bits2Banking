# Episode 25 — Inspect ELF symbols and understand a kernel memory layout

**Length:** approximately 17–22 minutes, including command demonstrations.  
**Reading:** [Lessons 84–86](../../lessons/05-engineering/84-read-sections-and-linker-scripts.md).  
**Source references:** [Umicom Framework ELF inspector](https://github.com/umicom-foundation/umicom-framework/tree/main/src/education), [Umicom Kernel boot](https://github.com/umicom-foundation/umicom-kernel/blob/main/arch/riscv64/boot.S).

## 00:00–03:00 — From machine code to an object file

**On screen:** Show a simple `.o` file and the diagram `elf-symbol-lifecycle.svg`.

**Narration:**

The previous episode finished with a linked C23 and Assembly programme. Today we will inspect what the compiler leaves inside an object file before that final link, and we will follow the same principles into the startup of Umicom Kernel.

A native object file normally contains more than instructions. It can contain data, section headers, a symbol table, string tables and relocation records. These components help the linker combine independently compiled files.

The object format depends on the target. On Windows x64, GCC normally produces COFF objects. On Linux x86-64 or for RISC-V64 cross-compilation, the output is usually ELF. These formats have different metadata structures. We cannot reliably read one using the other's rules.

We will use a small, read-only C23 tool in Umicom Framework to inspect ELF symbols and relocation counts. This is a local learning tool, not an executable loader. It does not run or modify the file it reads.

## 03:00–07:00 — Inspect ELF without trusting its bytes

**On screen:** Open the header `include/umicom/education/elf_symbols.h`, then the implementation.

**Narration:**

We begin with a C function that accepts a byte pointer, a byte count and an output report. The byte count is important. We must never assume that a file header is complete just because a pointer exists.

The parser checks the ELF magic bytes, class and byte order. ELF32 and ELF64 use different field widths. A file can also specify big-endian or little-endian encoding. Rather than casting the input to a host structure, the parser reads the fields explicitly, one byte at a time.

Next come section headers. A section may describe executable instructions, string storage or symbol metadata. The parser checks each offset and size before accessing bytes. It checks that a symbol table's entry size is valid, that the linked string table exists, and that symbol names terminate inside the string table.

A bad offset is refused. A declared table that would require too much work is refused. The parser builds its report privately and only publishes the complete result after validation.

This is the same engineering principle used for a safe Notes edit or a fictional account update: a partial result should not be presented as a successful complete operation.

The tool has clear limits. It reads files of at most 32 MiB, counts symbol and relocation entries, and shows at most 16 symbol names. It does not inspect every possible ELF extension, and it does not apply relocations or disassemble instructions.

## 07:00–10:00 — Run the Framework tests

**On screen:** PowerShell in `C:\umicom\Umicom-Applications`.

**Narration:**

We configure and build the existing standalone Umicom Education project. Then we run the two tests related to ELF symbols. The first constructs a little-endian ELF64 fixture and a big-endian ELF32 fixture. It checks declared symbols, their bindings and whether references are defined or undefined.

The same test tries truncated files, invalid string-table offsets, malformed table lengths and twelve thousand deterministic byte mutations. It verifies that failed parses do not alter the output report.

The second test runs the actual Umicom Education command against a valid fixture path containing spaces. The test is designed to work even on Windows, where our normal compiled object format would be COFF. The fixture is ELF regardless of the host.

We should expect passing tests, but a local build failure is useful evidence too. If it fails, keep the exact diagnostic and investigate before committing changes. A test report tells us what actually happened on this machine, not what we hoped would happen.

**On screen command:**

```powershell
ctest --test-dir ".\build\umicom-education" `
  -R "^framework\.education\.(elf_symbols|symbols\.cli)$" `
  --output-on-failure
```

## 10:00–14:00 — Where a kernel puts its first instructions

**On screen:** Show `linker-sections-and-kernel.svg` and open `arch/riscv64/boot.S` from Umicom Kernel.

**Narration:**

An ordinary application starts with assistance from its operating system. The operating-system loader maps its code and data and supplies an execution environment. The earliest kernel code has a different job. There is no completed operating system underneath it to provide these services.

Umicom Kernel's RISC-V64 bootstrap starts in Assembly. It selects the initial hart, disables interrupts before a trap handler is available, sets the stack pointer and clears the memory region for zero-initialised static objects. Only then does it call the C23 kernel entry function.

The Assembly source places `_start` in a `.text.boot` section. The linker script arranges this section as part of the kernel image at the required location. In the documented first-boot QEMU profile, the kernel ELF is loaded as firmware and entered in machine mode.

Look closely at the responsibilities. The linker script chooses addresses and section placement. The Assembly bootstrap establishes enough machine state to call C safely. The C23 kernel code then begins its higher-level work. These three stages solve different problems and cooperate through explicit interfaces.

We do not copy the kernel's boot code into Bits2Banking. The real implementation belongs to the Umicom Kernel repository. Our lesson links directly to that source, so the explanation can evolve along with the project.

## 14:00–17:00 — Cross-compile, inspect and compare

**On screen:** Show the host/target table from Lesson 85. Open the existing RISC-V64 object laboratory.

**Narration:**

Cross-compilation lets us run a compiler on our Windows x64 workstation and produce RISC-V64 object files. The output can be valid RISC-V machine code even though Windows cannot execute it.

The difference is visible in the binary metadata. An x86-64 Windows object is COFF. An x86-64 Linux object is ELF for x86-64. A RISC-V64 ELF object declares the RISC-V machine architecture in its header.

With `umicom-education binary --file`, we can inspect the basic binary type and machine without execution. With `umicom-education symbols --file`, we can inspect the ELF symbol and relocation summaries. A COFF object is correctly refused by the ELF-only command. This is not a defect; it is the parser respecting its contract.

We can also use familiar toolchain readers. `readelf` examines ELF structure, `nm` lists symbols, and `objdump` can display sections, relocations or disassembled instructions. These tools provide complementary views; none proves by itself that the kernel is safe or complete.

## 17:00–20:00 — Review questions and next step

**On screen:** Present three questions over the section map.

**Narration:**

A compiled file has a physical byte layout, but it also contains logical descriptions of what those bytes mean. Section headers describe regions. Symbol tables connect names to declarations and definitions. Relocations record places that still require target-dependent address adjustments.

Before a kernel can call ordinary C code, its Assembly entry must establish a working stack and the memory guarantees expected by that code. The linker must have placed the boot code and data where the platform can access them. That is why source files, object formats, linker scripts and boot protocols all matter when creating an operating system.

Here are three questions to check your understanding. First: why does our binary reader use checked offsets instead of casting arbitrary file bytes into host pointers? Second: why can a compiler-produced object contain undefined symbols without being broken? Third: why does the kernel bootstrap clear the BSS region before entering C?

After answering, open Lessons 84 through 86 and follow the practical commands. Then read the first-boot guide in the Umicom Kernel repository. Treat that repository as the authoritative source for the current kernel implementation and its limits.

The next part of the course will explore how program loaders map executable segments, how virtual addresses differ from physical addresses, and how kernel memory management builds on those foundations.

**Final screen:** Bits2Banking learning site, Framework source, Umicom Kernel source and the link to the QEMU build guide.
