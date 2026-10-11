# Episode 27 — Virtual Memory, Sv39 and Umicom Kernel

**Duration:** 14–18 minutes. **Related lessons:** [89. Sv39](../../lessons/05-engineering/89-sv39-virtual-address-translation.md), [90. Permissions](../../lessons/05-engineering/90-memory-permissions-traps-and-privilege.md), [91. Kernel source](../../lessons/06-umicom/91-follow-umicom-kernel-memory-source.md). **Lab:** `labs/native/sv39-address-translation`.

## 00:00–02:00 — Two kinds of address

**On screen:** Show a CPU, two running applications, virtual addresses and a physical RAM diagram.

**Narration:**

"When you write a C programme, you may use a pointer to access data. That pointer normally represents a virtual address. Virtual memory does not mean that a programme is pretending RAM exists when it does not. It means that the addresses the programme sees are translated to physical locations under rules set by the operating system. Two processes can use the same virtual address without owning the same physical memory. This is one reason we can separate processes and protect the system from accidental or malicious writes."

"Today we will follow one address through RISC-V Sv39 page tables. Then we will compare our classroom model with the actual Umicom Kernel implementation."

## 02:00–04:30 — The three Sv39 indices

**On screen:** Display [the Sv39 page-table diagram](../../assets/diagrams/sv39-page-table-walk.svg). Highlight VPN[2], VPN[1], VPN[0] and the offset.

**Narration:**

"A canonical Sv39 virtual address divides the useful low 39 bits into four parts. The first nine-bit index selects one entry in the top table. The second selects an entry in the middle table. The third selects an entry in the bottom table. The final twelve bits are the offset of one byte within a 4096-byte page. Each page table fits into one physical page because it has 512 entries and each entry contains eight bytes."

"Imagine looking up a chapter in a book. First you choose the subject, then the chapter, then the section, and finally the line. Sv39 follows multiple levels of references until it finds a leaf entry that identifies a physical frame. The page offset is not changed. It is copied into the physical address that the translation returns."

## 04:30–08:00 — Run the C23 page-walk model

**On screen:** Build in PowerShell:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\sv39-address-translation" `
  -B ".\output\learning-build\sv39-address-translation" -G Ninja `
  -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\sv39-address-translation" --parallel 2
ctest --test-dir ".\output\learning-build\sv39-address-translation" --output-on-failure
```

**Narration:**

"We have two tests: one demonstrates translation and one checks refusal cases. The demonstration maps the virtual page beginning at hexadecimal 40201000 to the physical frame beginning at 9000. It asks for an offset of 120 hexadecimal. The result is the physical address 9120. Pause and confirm why the final three hexadecimal digits stay the same: they identify the byte's position inside the 4096-byte page."

**On screen:** Highlight `CanonicalSv39`, `BtbSv39MapOne`, and `BtbSv39Translate` in `sv39.c`.

**Narration:**

"Before our model uses an address, it checks the Sv39 sign-extension rule. It then checks that the first two entries point to the expected next tables, and that the final entry is valid and permits the requested access. The teaching model has only one 4 KiB leaf mapping. It does not modify a real processor register or the computer's physical memory."

## 08:00–11:20 — Permissions and page faults

**On screen:** Three boxes labelled R, W, X, then a denied instruction fetch from a writable data page.

**Narration:**

"Translation is not only about finding a destination. A page may be readable but not writable, or readable and executable without being writable. Many systems apply the principle that an ordinary data page should not also be executable. When a processor sees an access that violates an active mapping, it can raise an exception. A privileged handler investigates whether the access should be denied, whether a page must be brought into memory, or whether another kind of recovery is permitted."

"Our classroom model returns a status rather than raising a real page fault. That difference is deliberate. A real kernel also has to manage user privilege, supervisor privilege, protection regions, TLB entries, address-space switching and the lifetime of every physical frame. These are security-sensitive responsibilities."

## 11:20–14:30 — Compare with Umicom Kernel

**On screen:** Browse real repository links: [physical_memory.c](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/physical_memory.c), [virtual_memory.c](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/virtual_memory.c), [hardware translation](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/HARDWARE_ADDRESS_TRANSLATION.md).

**Narration:**

"The Umicom Kernel code owns physical frames separately from its page-table hierarchy. If an address space is destroyed, its page-table frames can be reclaimed. But data frames belong to the callers that allocated them; the page-table service must not free unrelated objects merely because a mapping no longer exists. This is the same ownership rule we learned when building a C23 Notes application."

"The Kernel's software page walk can examine its Sv39 structure without asking the processor to execute that translation. A separate qualification path tests hardware-backed translation using controlled loads and stores. The hardware experiment is especially important: it checks whether the page-table format interpreted by the processor matches the software's expectations. Read the explanation of `MPRV` and `sfence.vma` in the actual Kernel documentation before studying the implementation."

## 14:30–16:30 — Learner exercise and closing

**On screen:** A table with three memory requests: read from a mapped page, execute from a data-only page, read from an unmapped page.

**Narration:**

"Try changing your model's mapped permissions to read and execute. Predict which requests will succeed before running the tests. Then look at Umicom Kernel's own `kernel/virtual_memory.c` and find its page-table entry flag definitions. Explain why an invalid write-only entry is refused, why a new mapping must be aligned, and who owns the mapped physical frame."

"Our next lessons will build towards page faults, process address spaces and the native boundary between the kernel and a programme. Remember that the aim is not simply to run code. We want to understand the reasons behind each rule and use that knowledge to help someone else learn."

**End card:** Bits2Banking · Umicom Foundation · Links to Chapters 89–91, Umicom Kernel, Framework, repository contribution guide and source laboratories. *Service to Many Leads to Greatness*.
