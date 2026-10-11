# Build a course catalogue as a C23 library

This exercise has three separate translation units. `catalogue.c` owns the rules for adding modules; `main.c` displays one small catalogue; `test_catalogue.c` verifies the public interface. They all include `catalogue.h` to agree on types and function declarations.

## Windows (PowerShell)

From `C:\umicom\Umicom-Bits2Banking`:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\course-catalogue-library" `
    -B ".\output\learning-build\course-catalogue-library" `
    -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\course-catalogue-library" --parallel 2
ctest --test-dir ".\output\learning-build\course-catalogue-library" --output-on-failure
& ".\output\learning-build\course-catalogue-library\btb-course-catalogue.exe"
```

You should see **two passing tests** and `Total lessons: 21`.

## Linux (Bash)

```bash
cmake -S labs/native/course-catalogue-library -B output/learning-build/course-catalogue-library -G Ninja
cmake --build output/learning-build/course-catalogue-library --parallel 2
ctest --test-dir output/learning-build/course-catalogue-library --output-on-failure
./output/learning-build/course-catalogue-library/btb-course-catalogue
```

## Inspect the intermediate files

Find the archive (`.a` with GCC or `.lib` with MSVC) and one object file (`.o` or `.obj`). GCC toolchains offer:

```powershell
& "C:\msys64\ucrt64\bin\nm.exe" ".\output\learning-build\course-catalogue-library\libbtb_course_catalogue.a"
```

Look for `BtbCatalogueAdd` and `BtbCatalogueInit`. If your archive path has a different spelling, inspect the build directory rather than changing its source.

## Reproduce a linker error safely

From the laboratory directory, use this **manual demonstration**; it is intentionally excluded from CMake targets:

```powershell
& "C:\msys64\ucrt64\bin\gcc.exe" -std=c23 -Wall -Wextra `
    ".\labs\native\course-catalogue-library\examples\undefined_reference.c" `
    -o ".\output\learning-build\missing-library.exe"
```

The compiler reads the declaration in `catalogue.h`, but the linker cannot find `BtbCatalogueInit` because the library was not linked. A failure is the *expected result of this particular manual experiment*. Do not add it as a failing project target.

Fix it by linking against the compiled catalogue library, as the provided CMake targets already demonstrate. Read [Lesson 73](../../../content/lessons/05-engineering/73-link-one-c-library.md) for the step-by-step explanation.

## Modify the application

Add a module with seven lessons. Predict and verify the new total. Then try adding a module with too many characters in the title; inspect the status and verify the earlier catalogue is unchanged.

The catalogue here is a deliberately small **teaching data structure**, not a replacement for Umicom Framework's own document or database services.
