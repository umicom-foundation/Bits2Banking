# Episode 24 — Where does the linker find a function?

**Length:** approximately 16–20 minutes, including command demonstrations.  
**Reading:** [Lesson 82](../../lessons/05-engineering/82-inspect-elf-symbols-in-c23.md) and [Lesson 83](../../lessons/05-engineering/83-follow-relocations-and-linker-decisions.md).  
**Source laboratory:** [`labs/native/linker-relocations`](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/linker-relocations).

## 00:00–02:00 — What we are going to build

**On screen:** The project tree shows the public header, C23 implementation, Assembly implementation, application and tests.

**Narration:**

We are going to build a small course-progress application. The application asks a reusable C23 library to add two lesson counts. The library checks the request, and then calls a tiny Assembly function to perform the arithmetic. We will compile the files separately, link them together and inspect the result.

There is a useful problem hidden in this small programme. When the compiler reads the C source, it sees a function named `BtbAssemblyAddU32`, but it does not see the machine instructions for that function. Those instructions live in a different file. How can compilation succeed when part of the implementation is missing?

The answer is that compilation and linking are separate steps. We need to understand the contract between them. This matters when you are working with Umicom Framework, combining libraries, debugging a missing-symbol error or constructing a kernel image from C and Assembly.

The public header declares `BtbCourseTotalsAdd`. Other C files include the header because it tells them how to call the function. The corresponding C implementation defines that function. A separate Assembly file defines the lower-level addition operation.

The header is a promise about an interface. It is not itself a compiled implementation.

## 02:00–05:00 — Compile the C file and inspect the symbols

**On screen:** Open PowerShell and the `src/course_totals.c` file. Highlight the `extern` declaration and `static` helper.

**Narration:**

Inside our C file, the word `extern` introduces a declaration for the Assembly function. We are telling the compiler that this function exists elsewhere and that its inputs and output have these C types. The compiler can now generate code that calls it, even though the final memory address is unknown.

Another function in the file begins with `static`. For a file-scope C function, `static` makes its name private to this translation unit. Other source files cannot link to it directly by that name. The helper is part of the implementation, not part of the library's public API.

These two choices are intentional. We expose `BtbCourseTotalsAdd` to client applications and keep `BtbCanAdd` private. We leave the Assembly function external so the linker can resolve it later.

Now we use GCC's `-c` option to compile the file without linking the application. Before we do that, create the output directory. Then run the compile command from Lesson 82. The result is an object file. It contains machine code and metadata, but it is not yet a complete executable.

On our Windows UCRT64 development computer, we inspect the object with `nm.exe`. Look for the public C function, the local helper and the unresolved Assembly reference. The exact letter codes and ordering may differ by toolchain. We should not memorise the presentation; we should understand what each state means.

A name marked as unresolved is normal at this stage. We have not yet linked the Assembly object that defines it.

**Pause the demonstration** while the actual symbol output is visible. Ask the viewer to identify one defined external name, one private name and one undefined name.

## 05:00–08:00 — Let Assembly provide the missing definition

**On screen:** Show `asm/add_x86_64.S`. Place the Windows and System V branches side by side.

**Narration:**

The Assembly file supplies the missing implementation. On Windows x64, the first two integer inputs arrive in `ECX` and `EDX`. We move the first input into `EAX`, add the second, and return. On Linux x86-64 with the System V convention, the inputs arrive in `EDI` and `ESI`. The instruction sequence is similar, but the register names are different.

This difference illustrates an application binary interface, or ABI. C declares the function's meaning and type. The ABI explains exactly how its parameters and result travel through registers and the stack. If the C compiler and Assembly source disagree, the programme can behave incorrectly even if the linker finds a matching symbol name.

Our C wrapper performs an overflow check before calling Assembly. That check matters independently of the ABI. A calling convention tells us where the value arrives, not whether the value is a valid input for the application.

We now configure the laboratory with CMake and build it with Ninja. CMake picks the Assembly source appropriate for the target. We run the tests and see two passing cases: the checked operation and the demonstration output.

The application prints a fictional learning-path count of 21 lessons. That number is only an example value. What matters is that we combined a C23 contract and target-specific Assembly correctly.

## 08:00–11:00 — The relocation is the missing link

**On screen:** Diagram `relocation-to-executable.svg`. Zoom in on the C object, Assembly object and linker.

**Narration:**

Before linking, the C object still does not know the final location of the Assembly function. To tell the linker what needs to be fixed, the object format contains relocation records.

A relocation identifies a place in compiled code or data that needs a target-dependent adjustment. It also identifies the symbol or section involved. The linker reads these records, locates the required definitions, arranges the output sections and adjusts the relevant fields according to the relocation type.

There is more than one relocation model. Some formats carry the addend, or constant adjustment, explicitly. Others obtain it from the field being relocated. ELF has `REL` and `RELA` relocation sections. Windows COFF describes relocations differently. An ELF reader must not simply interpret COFF bytes as if they had the same layout.

On Windows we inspect our C object with `objdump -r`. On Linux we can use `readelf -r` for an ELF object. The exact relocation type depends on the target instruction set and compiler options. Do not assume that the sequence will look identical across GCC, Clang, Windows and Linux.

After linking, the executable contains enough information for the operating-system loader to map and start it. Dynamic linking can defer some symbol work until startup, so a finished executable may still contain dynamic relocations.

## 11:00–14:00 — Reproduce and repair a real linker error

**On screen:** Create a temporary copy of the laboratory. Change the Assembly label only. Rebuild and capture the unresolved-symbol diagnostic.

**Narration:**

Let us introduce one controlled fault. In our temporary copy, rename the exported Assembly label but leave the C declaration unchanged. The C compiler can still process its source. The assembler can still process its instructions. But when the linker looks for `BtbAssemblyAddU32`, that definition is gone.

The build should fail with an unresolved-symbol error. This is not a syntax error in the C function. It is not an arithmetic failure or a memory leak. It is a failure to satisfy the linking contract.

Restore the correct label, build again and run the tests. The programme works because the declaration, ABI and external definition now agree.

This is a practical debugging method: first identify **which stage** failed. A compiler diagnostic requires a different investigation from a linker diagnostic. A failed test after successful linking requires another kind of investigation again.

The same reasoning applies when a Framework application forgets to link a required Framework library or when a freestanding kernel image is missing one of its boot objects.

## 14:00–17:00 — Review and finish

**On screen:** Return to the programme tree and draw three arrows: *C source → C object*; *Assembly source → Assembly object*; *both → linked application*.

**Narration:**

Here is the full sequence. A header declares the public C interface. The C source defines a wrapper, validates its inputs and references an external Assembly function. The assembler defines that function for the selected architecture. The linker joins the compiled objects and resolves the call. Then we execute the finished application and test the result.

We also saw why a `static` function is normally private and why a missing definition can remain acceptable in an intermediate object. We saw the role of relocation metadata, and we saw why binary formats and calling conventions cannot be guessed from filenames.

Before continuing, open the source files yourself. Find the public declaration, private helper, external Assembly declaration and matching Assembly label. Build the library, inspect the symbols, then explain what would break if the C and Assembly names stopped matching.

In the next episode, we will take a deeper look at the ELF object format and the read-only Umicom Education command that counts symbols and relocations. We will connect those ideas to the first instructions executed by Umicom Kernel.

**Final screen:** Written lessons 82–83, source laboratory and the Umicom Framework repository.
