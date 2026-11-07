# Video script: Build and test a small notes project

**Aim:** Separate reusable C behaviour from its caller and test the boundary.

**Preparation:** PowerShell, GCC, CMake, Ninja and CTest. Check their versions. The downloadable source folder linked below contains a complete small project; copy it to a practice folder so you can edit it freely. Use a separate practice folder and hide notifications or personal account details before recording.

[Lesson and exact commands](../lessons/10-build-and-test-a-small-project.md)

## Opening words

Next, we will take this topic one step at a time: build and test a small notes project. Follow one step at a time. Pause the video whenever you need a little more time.

## Scene 1

Open the five source files and draw one shared library connected to the application and test. Explain the header before the implementation.

## Scene 2

Configure, build and test one step at a time. Show that CTest launches a program which returns success or failure.

## Scene 3

Build again without changes, then change only main.c. Compare the build output and finish with the new test exercise.

## Walkthrough and pauses

### What this example does

**Say:** Our small program counts words separated by spaces, tabs and new lines. It does not try to understand grammar. The counting function lives in its own source file, and a header declares how to call it. The console application and test both use that same function.

**Say:** This is the same ownership principle used in Umicom: reusable behaviour belongs in a shared component. A window or command-line caller asks that component to do the work. The teaching example is independent and does not need the full Framework build.

### 1. Find the files

**Say:** Open examples/notes-word-count next to this community section. Copy the complete folder into your practice area. include/note_words.h declares the function. src/note_words.c implements it. src/main.c calls it. tests/test_note_words.c checks expected results. CMakeLists.txt describes how these pieces form build targets.

**On screen — type one line at a time:**

```powershell
Set-Location "$env:USERPROFILE\Umicom-Practice\notes-word-count"
Get-ChildItem
Get-Content .\include\note_words.h
```

Pause. Read the result before continuing.

**Say:** A build target is a named output or task. A library groups reusable compiled code. The header’s size_t is an unsigned integer type used for sizes. const char * borrows text without changing it. The function reads a valid zero-terminated C string; it does not take ownership of the memory.

### 2. Configure

**On screen — type one line at a time:**

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja
$LASTEXITCODE
```

Pause. Read the result before continuing.

**Say:** -S . names the source folder. -B build selects a separate folder for generated files. -G Ninja chooses the build tool. Configuration checks the project and writes build instructions. Continue only if the exit code is 0.

### 3. Build and test

**On screen — type one line at a time:**

```powershell
cmake --build build
$LASTEXITCODE
ctest --test-dir build --output-on-failure --no-tests=error
$LASTEXITCODE
```

Pause. Read the result before continuing.

**Say:** Run one command at a time and stop at a non-zero exit code. CTest should report the notes.word_count test as passed. --no-tests=error prevents an empty test selection from looking like success. The test checks empty text, whitespace, ordinary words and a null input according to the documented contract.

### 4. Run and inspect an incremental build

**On screen — type one line at a time:**

```powershell
.\build\notes-word-count.exe
cmake --build build
```

Pause. Read the result before continuing.

**Say:** The program should print Words: 4. With no changes, Ninja should have no compilation work. Change only the greeting in src/main.c, save and build again. The caller should rebuild while an unchanged library object can be reused. Header changes can affect several targets because their declarations are shared.

### If a check fails

**Say:** Read the test’s expected and actual counts. Inspect the input before changing the function. If CMake selected the wrong compiler, create a different build folder after fixing PATH; do not mix compilers inside an existing build directory.

### Your turn

**Say:** Add a test for two words separated by several tabs. Run it before and after changing the implementation. A passing test proves only the cases you checked, not every possible input.

## Closing words

Before moving on, try the exercise once more in your own practice folder. If the result is different, compare the command and current location with the lesson. You can come back to this step at any time.
