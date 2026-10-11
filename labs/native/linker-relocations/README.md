# Link a C23 course module with an Assembly function

In this laboratory you will build a small reusable library for a Bits2Banking course progress application. The public function adds two lesson counts only after checking for unsigned overflow. Its final arithmetic instruction lives in an Assembly file selected for the target ABI.

The application and its tests call the same C23 API. They do not know which Assembly source was used, because the build system owns that decision.

## 1. Read the source files

| File | Role |
| --- | --- |
| `include/btb/course_totals.h` | Public declarations shared by clients |
| `src/course_totals.c` | Checked C23 wrapper and private `static` helper |
| `asm/add_x86_64.S` | Windows x64 or Linux x86-64 calling convention |
| `asm/add_riscv64.S` | RISC-V64 C ABI implementation |
| `src/add_portable.c` | C23 fallback on other architectures |
| `src/main.c` | An application calling the compiled library |
| `tests/test_course_totals.c` | Arithmetic, overflow and ABI regression tests |
| `CMakeLists.txt` | Compiler, architecture and linking instructions |

The `extern` declaration of `BtbAssemblyAddU32` in `course_totals.c` is a promise: an object defining this symbol must be present when the final application is linked. The C compiler does not have to see the Assembly function's implementation to produce its own object.

## 2. Configure the project on Windows

Open PowerShell:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\labs\native\linker-relocations" `
  -B ".\output\learning-build\linker-relocations" `
  -G Ninja `
  -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
  -DBUILD_TESTING=ON
```

CMake selects the x86-64 Assembly source on an x86-64 Windows build. Its preprocessor uses the Windows calling convention, accepting the two integer parameters in `ECX` and `EDX`. The system linker then combines the C and Assembly object files.

## 3. Build and run the tests

```powershell
cmake --build ".\output\learning-build\linker-relocations" --parallel 2

ctest --test-dir ".\output\learning-build\linker-relocations" `
  --output-on-failure
```

Two tests should pass. The regression test tries 16,384 combinations and checks that overflow is refused without changing the output. The demonstration's expected text is:

```text
Bits2Banking learning path: 21 lessons
```

The numeric example is a training calculation, not the total number of published chapters.

## 4. Look inside the library

A static `.a` library is an archive of compiled objects. Find it:

```powershell
Get-ChildItem ".\output\learning-build\linker-relocations" `
  -Filter "*course_totals*.a" -Recurse
```

Inspect its members with the native inspector introduced in Update 10:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
& $Education archive --file "FULL_PATH_TO_LIBRARY"
```

Replace `FULL_PATH_TO_LIBRARY` with the `.a` path discovered above. The archive inspector shows member metadata; it does not extract or execute those members.

For individual symbol names on Windows, run the toolchain's `nm.exe` against the `.a` file:

```powershell
& "C:\msys64\ucrt64\bin\nm.exe" "FULL_PATH_TO_LIBRARY"
```

Look for a defined `BtbCourseTotalsAdd`, a defined Assembly `BtbAssemblyAddU32`, and any unresolved symbols in the intermediate objects. An archive itself is not an executable.

## 5. Compare the generated object formats

On Windows UCRT64, `.o` files are commonly COFF. On Linux, they are ELF. Both contain symbol and relocation records, but their header layouts differ. The Framework `umicom-education symbols --file` command from Update 11 accepts **ELF only**. Use it with Linux or RISC-V64 ELF output, not with native Windows COFF objects.

On a Linux development host:

```bash
cmake -S labs/native/linker-relocations -B output/learning-build/linker-relocations -G Ninja
cmake --build output/learning-build/linker-relocations --parallel 2
ctest --test-dir output/learning-build/linker-relocations --output-on-failure
```

Use `readelf -s` to list the symbols and `readelf -r` to view the relocations in one of the produced object files. Compare the first few names with the Framework's ELF inspector.

## 6. Make the linker fail in a controlled way

Use a *temporary copy* of this laboratory. Remove the Assembly source from the target's source list or change the Assembly label without changing its C declaration. Reconfigure and build. You should see an undefined-reference error during **linking** because C still calls the old name.

Restore the source and build again. The same files should link successfully.

Never modify the authoritative Umicom Framework linker implementation to create this example failure. All deliberately broken variations should remain in your disposable local copy.

## 7. Check the ABI assumptions

The C wrapper accepts two `uint32_t` values and returns the checked result through `uint32_t *outTotal`. For ordinary inputs the Assembly leaf function adds two values and returns the low 32 bits. The wrapper rejects overflow first, so the low result matches the checked mathematical sum.

- Windows x64: parameters enter in `ECX` and `EDX`.
- System V x86-64: parameters enter in `EDI` and `ESI`.
- RISC-V64: parameters enter in `a0` and `a1`.

Each implementation is a leaf function and does not call another function, so it does not need its own stack frame. A more complex Assembly routine would have additional register and stack obligations.

## 8. Questions

1. Why can a C file compile when one referenced function is missing?
2. What makes a C helper private to its translation unit?
3. What is the difference between an archive and the final executable?
4. Why does the same C function need different Assembly on Windows and Linux?
5. Why must the checked wrapper validate before calling the Assembly function?

Continue with [Lesson 82: ELF symbols](../../../content/lessons/05-engineering/82-inspect-elf-symbols-in-c23.md), [Lesson 83: relocations](../../../content/lessons/05-engineering/83-follow-relocations-and-linker-decisions.md), and [Lesson 86: defensive parsing](../../../content/lessons/05-engineering/86-test-native-binary-boundaries.md).
