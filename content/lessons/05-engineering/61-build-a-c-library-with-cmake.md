# 61. Organise a C23 library with CMake and CTest

A useful application rarely fits into one source file. A note-taking programme needs storage, a user interface, a save command and tests. These parts should be independently understandable and reusable where appropriate.

In this lesson, you will build the Notes model as a **static library** and link it to two separate programmes: a demonstration and an automated test.

## 1. Understand the three project files

Open the `labs/native/owned-notes` directory. It contains:

```text
owned-notes/
├── notes.h          Public declarations
├── notes.c          Library implementation
├── main.c           Notes demonstration
├── test_notes.c     Contract tests
└── CMakeLists.txt    Build description
```

A **header** tells another source file which types and functions are available. The `.c` file contains their implementation. `main.c` calls the public functions without needing to know the structure of `BtbNoteStore`.

The file `CMakeLists.txt` explains how the compiler and linker should turn these sources into programmes. CMake generates the instructions for a chosen build tool, such as Ninja.

## 2. Create a static library

The learning CMake project contains:

```cmake
add_library(btb_owned_notes STATIC notes.c)
```

This compiles `notes.c` into an object file and then archives the object into a static library. It does **not** create an executable on its own, because it has no `main` function.

The demonstration uses the library:

```cmake
add_executable(bits2banking-owned-notes main.c)
target_link_libraries(bits2banking-owned-notes PRIVATE btb_owned_notes)
```

The keyword `PRIVATE` means that the Notes library is needed to build this executable; it does not become part of a reusable public interface for consumers of the executable.

The tests link to the same library:

```cmake
add_executable(bits2banking-owned-notes-test test_notes.c)
target_link_libraries(bits2banking-owned-notes-test PRIVATE btb_owned_notes)
```

This is important: the test programme exercises the code that the demonstration uses rather than a separately copied implementation.

## 3. Configure, build and test

From PowerShell:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\labs\native\owned-notes" `
    -B ".\output\learning-build\owned-notes" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"

cmake --build ".\output\learning-build\owned-notes" --parallel 2
ctest --test-dir ".\output\learning-build\owned-notes" --output-on-failure
```

`-S` selects the directory containing the source files. `-B` selects the separate build directory. The `Ninja` generator creates an incremental build graph, so changing one source file does not necessarily rebuild unrelated files.

The test is registered with:

```cmake
add_test(NAME bits2banking.owned_notes COMMAND bits2banking-owned-notes-test)
```

CTest runs the produced test programme and reports whether it returned success or failure.

## 4. Inspect the generated objects

Inside the build directory you will see an archive named `libbtb_owned_notes.a` on common GCC/Clang Linux toolchains. Windows toolchains may use a different output name or path. The archive contains machine-code object files.

A linker combines the executable's `main` code with the symbols provided by the static library. If a programme calls a function without linking the library that provides it, the link step will fail even though the source file compiled successfully.

This is a natural next step after [Lesson 57: Read object files and follow the linker](57-examine-object-files-and-linkers.md).

## 5. Your next change

Add a small read-only function to `notes.h` and `notes.c` that reports the maximum permitted note count. Write a test that calls it. Do not duplicate the constant value in the test or the application implementation. Rebuild and check that the new function is available to both targets.

**Check your understanding:** What is the difference between a header and an implementation file? Why does the executable need a linker? What is a static library? How does a test prove that it exercises the same library as the demonstration?

### Next: Umicom Framework

Umicom Framework contains many reusable C libraries under one CMake project. Explore its [public headers](https://github.com/umicom-foundation/umicom-framework/tree/main/include/umicom) and [CMake configuration](https://github.com/umicom-foundation/umicom-framework/blob/main/CMakeLists.txt). Real Umicom Applications link to Framework-owned components; they should not maintain independent copies of those core services.
