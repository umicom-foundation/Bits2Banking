# 72. Follow a C23 programme from source to machine code

When you build an Umicom application, the compiler does not simply turn the entire project into an executable in one operation. It processes source files, generates machine instructions, and then asks a **linker** to connect independently compiled pieces.

In this lesson you will follow those steps using a small, working Bits2Banking application: a catalogue of computing, programming and banking lessons.

![C source, preprocessing, compiler, object file and linker](../../assets/diagrams/c23-compiler-pipeline.svg)

## 1. Find the source files

Open the [course catalogue laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/course-catalogue-library). It contains three ordinary C23 files and one header:

| File | Responsibility |
| --- | --- |
| `catalogue.h` | Declares the functions and public data types. |
| `catalogue.c` | Defines the functions that add and read catalogue entries. |
| `main.c` | Calls the library and displays three course modules. |
| `test_catalogue.c` | Calls the same library but checks correct and incorrect inputs. |

A **translation unit** is the source presented to a C compiler after preprocessing. Two source files can include the same header while remaining separate translation units.

The application should eventually print:

```text
Computer architecture: 4 lessons
C23 and Assembly: 9 lessons
Banking systems: 8 lessons
Total lessons: 21
```

## 2. Preprocess one file

The preprocessor processes `#include` and other preprocessing directives before the C compiler analyses the resulting programme. To see this intermediate text, open PowerShell in `C:\umicom\Umicom-Bits2Banking` and run:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
New-Item -ItemType Directory -Force -Path ".\output\compiler-lab" | Out-Null

& "C:\msys64\ucrt64\bin\gcc.exe" -std=c23 -E `
    ".\labs\native\course-catalogue-library\main.c" `
    -o ".\output\compiler-lab\main.i"
```

Open `output/compiler-lab/main.i`. Look for the declarations from `catalogue.h`. Also notice that the output is much longer than `main.c`: standard-library headers have supplied declarations the source needs.

The `.i` file is **not** machine code. It is preprocessed C source.

## 3. Generate Assembly

Run:

```powershell
& "C:\msys64\ucrt64\bin\gcc.exe" -std=c23 -O0 -S `
    ".\labs\native\course-catalogue-library\main.c" `
    -o ".\output\compiler-lab\main.s"
```

Open `main.s`. You should find instructions that set up a call to `BtbCatalogueInit` and other functions. The exact Assembly depends on the compiler, target architecture and optimisation settings.

On the Windows x86-64 target, calls generally follow the Microsoft x64 calling convention. The same source compiled on Linux x86-64 uses the System V ABI. Neither version should be mistaken for RISC-V instructions.

**Question:** Why does generating `main.s` not require us to compile `catalogue.c` first? The compiler knows the function declarations, but the linker must later find their definitions.

## 4. Create an object file

Now compile without linking:

```powershell
& "C:\msys64\ucrt64\bin\gcc.exe" -std=c23 -c `
    ".\labs\native\course-catalogue-library\main.c" `
    -o ".\output\compiler-lab\main.o"
```

An **object file** contains machine code and additional information for the linker: symbols, sections and possibly relocation records. A reference to `BtbCatalogueInit` may still be unresolved inside `main.o`.

On Windows with UCRT64, this object normally uses COFF. On Linux, an equivalent GCC object normally uses ELF. The C source does not need to change simply because the object-file container format changes.

## 5. Link the complete application

Let CMake build the library and the application in the correct order:

```powershell
cmake -S ".\labs\native\course-catalogue-library" `
    -B ".\output\learning-build\course-catalogue-library" `
    -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"

cmake --build ".\output\learning-build\course-catalogue-library" --parallel 2
ctest --test-dir ".\output\learning-build\course-catalogue-library" --output-on-failure
```

You should see two passing tests. Ninja compiles each source once when required, creates a static library from `catalogue.c`, and links that library into both the console application and the test programme.

## 6. Inspect what the linker produced

After building the updated Framework education tool, examine the executable from the learning application:

```powershell
& "C:\umicom\Umicom-Applications\build\umicom-education\bin\umicom-education.exe" `
    binary --file ".\output\learning-build\course-catalogue-library\btb-course-catalogue.exe"
```

You should see `Format: PE` and an architecture such as `x86-64`. The command reads the file header; it does not start the application.

For deeper analysis use the binutils tools included with your compiler. The `nm` tool lists symbols; `objdump` can display disassembled instructions. See [Lesson 74](74-read-elf-pe-coff-with-c23.md) for the boundaries of native file inspection.

## 7. Try one small change

In `main.c`, add a fourth module with seven lessons. Before building, calculate the expected total: **28 lessons**. Build and run the programme. The demonstration test expects the original total of 21, so it will tell you that the fixture has changed. Restore the original values when you have finished experimenting.

This shows an important distinction: a programme can compile successfully while a test correctly reports that its observed output no longer matches the agreed example.

**Continue:** [Lesson 73 — create and link a reusable C23 library](73-link-one-c-library.md).
