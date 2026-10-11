# Build a C program with CMake and Ninja

When a C program grows from one file to several source files, a developer needs a reliable way to tell the compiler which files belong together, which libraries they depend on and how the result should be tested. CMake and Ninja solve different parts of that problem.

You will build the same Notes application introduced in [Writing safer C](../03-native-code/36-safer-c-programming.md).

## 1. The four stages from source to executable

A **source file** contains code that a programmer writes. A **header** contains declarations that other source files may use. A **compiler** checks and translates source code. A **linker** combines compiled object files and referenced libraries into an executable or library.

```text
notes.h                  notes.c                     main.c
   │                        │                          │
   └─ included by ──────────┼──────────────────────────┘
                            ▼
                 Compiler (GCC or Clang)
                            │
                     notes.o + main.o
                            │
                       Linker
                            │
                       bits-notes
```

A compiler can compile a source file separately and save the machine instructions in an **object file**. The linker resolves names such as `UmicomNoteSet` when one object refers to a function implemented in another object.

## 2. Understand the difference between build tools

| Tool | Responsibility |
|---|---|
| **GCC / Clang** | Compile C and C++ and usually drive the linker. |
| **Assembler** | Convert Assembly source into machine-code objects. |
| **Linker (LLD, GNU ld, etc.)** | Combine objects, resolve symbols and construct executables/libraries. |
| **CMake** | Describe targets, sources, options and dependencies; generate build instructions. |
| **Ninja** | Execute the generated build graph efficiently and rebuild changed targets. |
| **CTest** | Run registered test programs and report results. |
| **Make / Meson** | Additional build technologies, with different configuration and execution models. |

CMake does not replace the compiler. Ninja does not decide which C files form a library; it executes the dependency graph configured by CMake.

## 3. Examine the project structure

Open `labs/native/safe-notes/` in the Bits2Banking repository:

```text
safe-notes/
├── CMakeLists.txt
├── notes.h
├── notes.c
├── main.c
├── test_notes.c
└── README.md
```

The `notes.c` implementation is shared by both the example program and its test. The source is not copied into two different projects.

## 4. Read the CMake target declarations

The relevant part of `CMakeLists.txt` is:

```cmake
cmake_minimum_required(VERSION 3.24)
project(BitsSafeNotes LANGUAGES C)
include(CTest)

add_library(bits_safe_notes STATIC notes.c)
set_target_properties(bits_safe_notes PROPERTIES
    C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
target_include_directories(bits_safe_notes PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(bits-notes main.c)
target_link_libraries(bits-notes PRIVATE bits_safe_notes)
```

`add_library` creates a target called `bits_safe_notes`. The word `STATIC` tells CMake to produce a linkable archive containing compiled objects. `add_executable` creates the runnable Notes program. `target_link_libraries` records the fact that the executable uses the library.

`PUBLIC` include directories become available to programs that consume the library. `PRIVATE` means only the target being configured needs the dependency. These visibility rules matter as a framework grows: they prevent unrelated modules from inheriting private build settings accidentally.

## 5. Configure, build and test on Windows

Open PowerShell:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\labs\native\safe-notes" `
      -B ".\build\safe-notes" `
      -G Ninja `
      -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"

cmake --build ".\build\safe-notes" --parallel 2

ctest --test-dir ".\build\safe-notes" --output-on-failure

& ".\build\safe-notes\bits-notes.exe"
```

The first command is **configuration**: CMake reads the project and writes a build graph into `build/safe-notes`. The second command compiles and links. The third command runs tests. The final command executes the program.

## 6. Understand an incremental build

Run the build command again without editing anything. Ninja should normally have no source files to recompile. Now change the sentence in `main.c` and build again. Only affected objects and executables should be rebuilt.

A build folder contains generated files such as `CMakeCache.txt`, Ninja rules and object files. These are not the authored source files. Do not add a generated build folder to Git.

If you change compilers, do not reuse a cache configured for another incompatible toolchain. Create a different build directory such as `build/safe-notes-clang` instead.

## 7. Read a compiler diagnostic

A diagnostic usually includes the source file, line number, category and message. For example, an attempt to use an undeclared function may fail during compilation, while a function declared but not implemented may produce a linker error.

Use this distinction when troubleshooting:

- **Configuration error:** CMake cannot find a compiler or required library.
- **Compile error:** the compiler cannot translate the source into an object.
- **Link error:** compiled objects contain unresolved symbols or incompatible dependencies.
- **Test failure:** a built program runs but violates an expected result.
- **Runtime error:** the program starts but fails during execution.

Read the first complete failure rather than copying only the final `build failed` message.

## 8. Compare other build systems

GNU Make executes rules from a `Makefile`. Meson describes software projects and commonly selects Ninja as its backend. CMake can generate Ninja files, platform-specific project files and IDE configurations. Umicom Framework uses CMake and Ninja as its primary development path so that multiple applications consume compatible build targets.

A package manager such as MSYS2 `pacman`, `vcpkg` or Conan performs a different job: it retrieves or builds the libraries that a project depends on. The next chapter examines that boundary.

### Exercises

1. Make one edit in `main.c`; rebuild and check which targets Ninja changes.
2. Read `test_notes.c`; identify the assertion that checks a failed oversized update.
3. Create a separate Clang build directory and compare the results if Clang is installed.
4. Explain why putting every source file directly into one enormous executable target would make Umicom Framework harder to maintain.

Continue with [Package managers and useful C libraries](38-package-managers-and-c-libraries.md).
