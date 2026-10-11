# Episode 28 — A Program, Its Address Space and a Page Fault

**Duration:** approximately 15–19 minutes  
**Lesson:** [92. Understand a process address space](../../lessons/05-engineering/92-understand-a-process-address-space.md) and [93. Understand page faults](../../lessons/05-engineering/93-understand-page-faults-in-c23.md)  
**Demonstration source:** [`labs/native/page-fault-model`](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/page-fault-model)

## Opening: why does a notes application need memory protection? (0:00–1:45)

**On screen:** Show the Umicom Notes use case, then the diagram `process-address-space.svg`.

**Narration:**

“Imagine opening a note-taking application. You press the Add Note button, type some text and save your changes. There is more happening than drawing a window. The operating system must keep the application’s instructions and data somewhere in memory. It must also prevent an accidental write in the notes program from changing the instructions of a different application.

“Today, we will follow one address from a program to memory. We will also deliberately ask our teaching program to access memory in a way that should be refused. We will see the difference between an unmapped address and a mapped page with insufficient permissions.”

**Presenter:** Open the written chapter link and highlight the distinction between a file containing program instructions and a process that has been created from the file. Avoid implying that an ELF reader starts a process.

## From an ELF file to memory regions (1:45–4:30)

**On screen:** Show Lesson 87’s load-plan table, then the address-space illustration. Use a pointer to identify code `0x1000`, data `0x2000` and unmapped `0x3000`.

**Narration:**

“An executable file describes regions that should be loaded into memory. It may have one region containing machine instructions and another containing writable data. The loader must validate those descriptions. Then, subject to operating-system rules, it obtains memory, establishes mappings, and gives the regions suitable access rights.

“We will model three 4 KiB pages. The page starting at hexadecimal 1000 is for code. We give it read and execute permissions. The page at 2000 is for editable note data, so it is readable and writable. We do not map 3000 at all.

“A virtual address is a name within an address space, not a physical chip location. The system uses page tables and hardware translation to find the physical frame backing a permitted access. The offset within the page is carried across into the physical address.”

**Demonstration:** Write `0x1018`, `0x80001000`, and `0x80001018` on screen. Explain how the low `0x18` offset is preserved. Show the appropriate entries in `page_map.c`.

## Reading the public C23 interface (4:30–7:20)

**On screen:** Open `labs/native/page-fault-model/page_map.h` and `page_map.c`.

**Narration:**

“The example is a simple C23 program. We start with a fixed-size table of mappings. There is no dynamic memory allocation, no system call, and no privileged instruction. That simplicity allows us to inspect every condition.

“The access function receives a borrowed address-space pointer, a virtual address, a requested operation, and an output pointer for the physical address. It checks whether the address is valid, whether the page is mapped, and whether the mapping permits the request. Notice the order. We do not write the output address first and try to undo it after a failed check. The output is changed only after all checks pass.”

**Presenter:** Pause on `BtbPageAccessAddress` and point to the relevant checks. Explain that an output parameter is a memory location that the caller has allowed the function to fill, but only on success.

## Build and run the model (7:20–10:20)

**On screen:** Windows PowerShell. Start at `C:\umicom\Umicom-Bits2Banking`.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\page-fault-model" -B ".\output\learning-build\page-fault-model" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\page-fault-model" --parallel 2
ctest --test-dir ".\output\learning-build\page-fault-model" --output-on-failure
& ".\output\learning-build\page-fault-model\btb-page-fault-demo.exe"
```

**Narration:**

“The configure command asks CMake to create a build plan. The build command invokes the compiler and linker. CTest checks the supported and refused operations. Only after the tests pass do we run the demonstration.

“The first request is an instruction fetch from the code page: allowed. The second request tries to write to that same page: protection fault. The third request reads from a page with no mapping: unmapped page fault.”

**On screen:** Show the expected labels `allowed`, `protection fault`, `unmapped page fault` rather than inventing hardware exceptions.

## What does a real kernel do? (10:20–13:10)

**On screen:** Umicom Kernel’s actual `kernel/physical_memory.c`, `kernel/virtual_memory.c` and hardware-translation guide.

**Narration:**

“The teaching program performs no actual hardware translation. Umicom Kernel is the separate repository that owns real page-table structures, frame ownership, traps and privilege control. In its virtual-memory implementation, a page-table walk uses RISC-V Sv39’s three indices to reach a physical mapping. In later qualification work, hardware translation is activated under carefully controlled conditions.

“A real page fault transfers execution into a kernel-controlled exception path. Sometimes the kernel can repair a missing mapping. Sometimes it must refuse the operation. The application does not get to grant itself new permissions.”

**Presenter:** Emphasise that a simulator and a real operating-system kernel are different deliverables.

## Exercises and close (13:10–16:30)

**Narration:**

“Your first task is to make the data page read-only and add an attempted write. Predict the result before running it. Your second task is to verify that the physical-address output remains unchanged after a rejected access. Finally, read the corresponding actual Umicom Kernel documentation and explain which responsibilities cannot be implemented by an unprivileged classroom C program.

“You can find the written lessons, complete source files and tests in the Bits2Banking repository. If you can explain the difference between a virtual address, a mapping, a physical frame and a page fault, you are ready for the next lesson: why ELF segment permissions must be checked at page granularity.”

**End card:** Bits2Banking learning website · Umicom Framework · Umicom Kernel · “Service to Many Leads to Greatness.”
