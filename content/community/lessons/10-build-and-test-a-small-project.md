# Build and test a small notes project

Separate reusable C behaviour from its caller and test the boundary.

**Before you start:** PowerShell, GCC, CMake, Ninja and CTest. Check their versions. The downloadable source folder linked below contains a complete small project; copy it to a practice folder so you can edit it freely.

[Community learning route](../index.md) · [Printable HTML](../handouts/10-build-and-test-a-small-project.html)

## What this example does

Our small program counts words separated by spaces, tabs and new lines. It does not try to understand grammar. The counting function lives in its own source file, and a header declares how to call it. The console application and test both use that same function.

This is the same ownership principle used in Umicom: reusable behaviour belongs in a shared component. A window or command-line caller asks that component to do the work. The teaching example is independent and does not need the full Framework build.

[Open the complete project and file list](../examples/notes-word-count/README.md).

## 1. Find the files

Open examples/notes-word-count next to this community section. Copy the complete folder into your practice area. include/note_words.h declares the function. src/note_words.c implements it. src/main.c calls it. tests/test_note_words.c checks expected results. CMakeLists.txt describes how these pieces form build targets.

```powershell
Set-Location "$env:USERPROFILE\Umicom-Practice\notes-word-count"
Get-ChildItem
Get-Content .\include\note_words.h
```

A build target is a named output or task. A library groups reusable compiled code. The header’s size_t is an unsigned integer type used for sizes. const char * borrows text without changing it. The function reads a valid zero-terminated C string; it does not take ownership of the memory.

## 2. Configure

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja
$LASTEXITCODE
```

-S . names the source folder. -B build selects a separate folder for generated files. -G Ninja chooses the build tool. Configuration checks the project and writes build instructions. Continue only if the exit code is 0.

## 3. Build and test

```powershell
cmake --build build
$LASTEXITCODE
ctest --test-dir build --output-on-failure --no-tests=error
$LASTEXITCODE
```

Run one command at a time and stop at a non-zero exit code. CTest should report the notes.word_count test as passed. --no-tests=error prevents an empty test selection from looking like success. The test checks empty text, whitespace, ordinary words and a null input according to the documented contract.

## 4. Run and inspect an incremental build

```powershell
.\build\notes-word-count.exe
cmake --build build
```

The program should print Words: 4. With no changes, Ninja should have no compilation work. Change only the greeting in src/main.c, save and build again. The caller should rebuild while an unchanged library object can be reused. Header changes can affect several targets because their declarations are shared.

## If a check fails

Read the test’s expected and actual counts. Inspect the input before changing the function. If CMake selected the wrong compiler, create a different build folder after fixing PATH; do not mix compilers inside an existing build directory.

## Your turn

Add a test for two words separated by several tabs. Run it before and after changing the implementation. A passing test proves only the cases you checked, not every possible input.

## Continue when you are ready

[Previous: Write, compile and run a C program](09-build-your-first-c-program.md) · [Next: Follow a button into Umicom Framework](11-follow-a-framework-button.md)

[Explore the related course](../../courses/learning-cmake/index.html). You can finish this exercise without leaving this page.

[Video teaching script](../video-scripts/10-build-and-test-a-small-project.md) · [Short community message](../messages/10-build-and-test-a-small-project.md)
