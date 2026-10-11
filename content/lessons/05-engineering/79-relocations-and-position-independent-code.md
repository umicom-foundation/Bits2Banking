# 79. Relocations, executable sections and position-independent code

A compiler usually does not know the final address of every function and variable. The programme may be linked with other libraries, or a loader may place it at a different memory address when it starts.

A **relocation** is information that helps the linker or loader adjust a reference to a symbol or address. It is a normal part of producing native programmes.

## 1. Follow one call across files

Our static-library laboratory has a call from `main.c` to `BtbLedgerTotalPence`. Before linking, the application object contains machine instructions for the call and information identifying the symbol it needs.

The linker processes the application object and the library archive. It selects the object that provides `BtbLedgerTotalPence` and applies the required relocations or other target-specific transformations.

Some calls use an address relative to the current instruction. Others need a table or an absolute-address relocation. The exact encoding depends on the processor architecture, ABI and linker options.

## 2. Examine executable sections

Most native object files divide content into **sections**. Common ELF names include `.text` for executable instructions, `.rodata` for read-only constants, `.data` for initialised writable objects, and `.bss` for zero-initialised storage.

On Windows COFF, section names and conventions can differ. A compiler may also split each function into its own section when appropriate options are used. Do not assume every source file creates exactly one `.text` section.

After building the static-library laboratory, list its object files:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

Get-ChildItem ".\output\learning-build\static-library-map" `
    -Recurse -File -Include "ledger.c.obj", "ledger.c.o"
```

Use the exact path returned by that command:

```powershell
& "C:\msys64\ucrt64\bin\objdump.exe" -h "PASTE_OBJECT_PATH_HERE"
```

`-h` shows section headings. To inspect relocations:

```powershell
& "C:\msys64\ucrt64\bin\objdump.exe" -r "PASTE_OBJECT_PATH_HERE"
```

Not every object contains the same relocations. Optimisation, platform conventions and the compiler can change what appears.

## 3. Understand linking as a transformation

Think of a relocatable object as a partially prepared part of the final programme. It contains machine instructions and data, but the relationship between separate objects still needs to be resolved.

The linker uses symbol and relocation records to connect components. It also arranges sections in the output image according to the target's rules and any linker script. A linker script can explicitly select section positions, define symbols and describe target memory regions.

For ordinary applications the toolchain normally supplies these rules. For a kernel, the developer often needs much more explicit control.

## 4. Position-independent code

**Position-independent code (PIC)** is designed so that executable instructions can function when placed at different addresses, using suitable relative addressing or indirection.

On many Unix-like systems, shared libraries are built as PIC. On Windows, PE images and DLLs use the platform's relocation and import mechanisms, so the details differ. Turning on `POSITION_INDEPENDENT_CODE` in CMake does not by itself create a DLL or establish a safe public ABI.

A useful CMake property is:

```cmake
set_target_properties(my_library PROPERTIES POSITION_INDEPENDENT_CODE ON)
```

This is an *example of a build option*, not a required change to the lesson's working library. Changing compiler flags may alter both the object code and the relocation table. Compare before and after only in a separate local experiment.

## 5. Understand what the object-file inspector can tell you

The `umicom-education binary --file` command recognises ELF, PE and ordinary COFF headers. It reports format and architecture. It does **not** yet decode every relocation record or reconstruct source-level instructions.

Use `objdump -r` and the relevant architecture's documentation for that detail. When reading RISC-V object code, use a toolchain that understands RISC-V relocation types; the ordinary Windows GCC `objdump` may be built only for x86 targets.

## 6. A connection to Umicom Kernel

The original Umicom Kernel uses a linker script to place `_start` at a deliberate boot address. The RISC-V Assembly bootstrap then establishes its initial execution environment before calling C23.

Compare the programme layout concepts in this lesson with the actual [Umicom Kernel boot source](https://github.com/umicom-foundation/umicom-kernel/blob/main/arch/riscv64/boot.S) and [first-boot explanation](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/FIRST_BOOT.md). A hosted application's loader is not equivalent to the startup path of a freestanding kernel image.

## 7. Practical exercise

Find one relocation in the application object or library object. Write down the associated symbol and its section. Then build the programme and identify that symbol or archive member in `btb-ledger-demo.map`.

Next: [Cross-compile C23 to RISC-V64](80-cross-compile-c23-riscv64.md).
