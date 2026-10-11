# Episode 26 — From an ELF File to a Memory Layout

**Duration:** 11–14 minutes. **Related lessons:** [87. ELF load plans](../../lessons/05-engineering/87-read-elf-program-headers-and-load-plan.md), [88. Physical frames](../../lessons/05-engineering/88-physical-pages-and-frame-ownership.md). **Lab:** the Framework `umicom-education load-plan` command. This video uses source from the Umicom Framework and Umicom Kernel repositories.

## 00:00–01:10 — A programme is a file before it runs

**On screen:** A C23 source file, compiler, linker, ELF image and a row of memory pages. Show the [ELF load-plan diagram](../../assets/diagrams/elf-program-headers-to-memory.svg).

**Narration:**

"We have already learned how a C programme becomes machine code. But a file stored on a disk is not the same thing as a running process. Even if the file contains valid machine instructions, the computer still needs to know where those instructions belong in memory. It also needs to know which bytes are writable, which are executable and where the programme begins. The operating system — or an earlier boot loader in the case of a kernel — performs that preparation. Today we will inspect the plan stored inside an ELF image without executing the image."

## 01:10–03:30 — What the ELF programme header tells us

**On screen:** Highlight the fields `p_offset`, `p_vaddr`, `p_filesz`, `p_memsz`, `p_flags` and `p_align` in a two-segment table.

**Narration:**

"An ELF file contains a header identifying its format and processor architecture. It can also contain several programme headers. A programme header of type PT_LOAD describes bytes that should be made available in memory. One field says where the bytes begin inside the file. Another says where they should appear in the programme's virtual address space. The file size and memory size can differ. For example, if a segment occupies 512 bytes in memory but provides only 128 bytes from the file, the remaining 384 bytes need to be zero-initialised. That is how a common class of initially empty global variables can occupy memory without requiring thousands of zero bytes in the executable."

"The permission flags also matter. Instructions may need to be readable and executable. Mutable data may need read and write permissions. A loader that ignores these differences can weaken security or fail to run the programme correctly."

## 03:30–06:50 — Demonstrate the native C23 inspector

**On screen:** Windows PowerShell in `C:\umicom\Umicom-Applications`. Type each line, explain the result before proceeding.

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
ctest --test-dir ".\build\umicom-education" `
  -R "^framework\.education\.(elf_load_plan|load_plan\.cli)$" -V
```

**Narration:**

"The first test builds a small teaching ELF file. Its processor architecture field identifies RISC-V64. This is a synthetic fixture, not a kernel we can boot. The test makes sure the parser accepts good metadata and refuses broken offsets or impossible memory ranges. It also proves that a file name with spaces is handled as one path."

**On screen:** Run:

```powershell
& $Education load-plan --file `
  ".\build\umicom-education\education-load-plan-test\fixture with spaces\umicom kernel.elf"
```

**Narration:**

"The report displays two loadable segments. Their total file-backed data is 160 bytes and the required zero-fill is 608 bytes. The entry address lies within the executable segment. The programme prints where the file's bytes would go, but it does not copy those bytes into a process address space. No kernel is started, no memory is mapped, and no executable instruction is run. This makes the command suitable for careful inspection and learning."

## 06:50–09:40 — Where the pages come from

**On screen:** [Physical-frame diagram](../../assets/diagrams/physical-frame-allocation.svg). Open the `physical-frame-pool` laboratory.

**Narration:**

"A load plan describes the required memory, but another service must actually provide the physical pages. Our next laboratory models 128 frames, each 4096 bytes long. The first eight are protected. The ninth frame — numbered eight because counting begins at zero — is the first one our model may allocate. Why reserve memory? Because some frames may already contain the kernel, a boot stack, a device tree or the allocator's own data. If we hand those pages to a Notes application, that application might overwrite something essential to system operation."

"Our learning allocator refuses such attempts. It checks a requested reservation completely before modifying any record. It also refuses to free the same frame twice. Real Umicom Kernel uses separate bitmaps to track reserved and allocated frames. Our small C23 example is deliberately easier to follow, not a replacement for the Kernel's allocator."

## 09:40–11:30 — Check the real source and conclude

**On screen:** Show [Umicom Kernel `arch/riscv64/boot.S`](https://github.com/umicom-foundation/umicom-kernel/blob/main/arch/riscv64/boot.S), [physical memory](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/physical_memory.c), and the Bits2Banking website.

**Narration:**

"We have connected three stages: the linker prepares an executable image, the ELF programme headers describe its memory layout, and the operating system manages the pages used to hold it. A kernel's very first instructions are special because they execute before the system can offer these ordinary services. In our next episode we will study virtual memory: how one virtual address can refer to a completely different physical address, and how RISC-V Sv39 describes that relationship."

**End card:** Bits2Banking learning chapters 87–88 · Umicom Foundation · *We Value Each Other and Together Everyone Achieves More* · *Service to Many Leads to Greatness*. Invite viewers to improve a lesson or help another learner.
