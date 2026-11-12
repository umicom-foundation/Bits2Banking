<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-text-editor/index.md

PURPOSE:
Introduce a course, its prerequisites, tool setup and ordered lessons.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Building a Text Editor in C

## About this course
Build a small console editor from a text buffer through insertion, deletion, undo and saving to a chosen path.

## Before you begin
You should recognise C variables and functions. The project introduces arrays, byte positions and file operations as they are needed.

## Reading order
1. [Plan a small editor with a testable model](01-plan-a-small-editor.md)
2. [Insert and erase text without losing the tail](02-insert-and-erase-text.md)
3. [Undo and save to a chosen path](03-undo-and-save-to-a-chosen-path.md)
4. [Test the model and the whole editing session](04-test-the-whole-editing-session.md)
- [Open an existing document without losing work](05-open-an-existing-document.md)
- [Load into a private candidate before replacing state](06-load-into-a-private-candidate.md)
- [Recognise line endings and end of file](07-recognise-line-endings-and-eof.md)
- [Check failure state and command results](08-check-failure-state-and-command-results.md)


- [Own a shared text buffer and respect borrowed views](09-own-a-shared-text-buffer.md)
- [Resolve exact UTF-8 offsets and UTF-16 positions](10-resolve-unicode-positions.md)
- [Select source words and physical lines without changing text](11-select-source-words-and-lines.md)
- [Capture an edit for the intended document](12-capture-and-apply-document-edits.md)
- [Traverse shared undo history and create a new edit branch](13-traverse-one-shared-document-history.md)
- [Check refused edits, preserved state and SDK identity](14-test-refused-edits-and-sdk-identity.md)

## Continue with shared Framework services

<!-- The original local lab references are retained for source review. Published manuscripts use repository URLs because labs is outside the site content root.
Lessons 1–8 retain the standalone ASCII editor. Lessons 9–14 use an installed SDK and twelve in-memory scenarios for ownership, Unicode positions, selection and document history. Follow the [shared editor lab guide](../../../../labs/native/shared-editor/README.md) and [qualification checklist](../../../../labs/native/shared-editor/QUALIFICATION.md). The console client creates no native window.
-->
Lessons 1–8 retain the standalone ASCII editor. Lessons 9–14 use an installed SDK and twelve in-memory scenarios for ownership, Unicode positions, selection and document history. Follow the [shared editor lab guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/shared-editor/README.md) and [qualification checklist](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/shared-editor/QUALIFICATION.md). The console client creates no native window.

## Prepare a development environment
A compiler translates C source. CMake describes which files belong to a program. Ninja performs the build work. CTest runs registered checks. An editor changes the source text. You may use a plain text editor before learning an IDE.

### Windows with PowerShell
1. Install MSYS2 from [its official installation guide](https://www.msys2.org/). Use the UCRT64 environment described in [the environment guide](https://www.msys2.org/docs/environments/).
2. In the MSYS2 UCRT64 terminal, follow its update instructions, then install the C tools:
~~~bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja git
~~~
3. Obtain the Bits2Banking repository. If it is already present, use that checkout; do not clone into it again. In the MSYS2 terminal, an example new location is:
~~~bash
mkdir -p /c/umicom
git clone https://github.com/umicom-foundation/Bits2Banking.git /c/umicom/Umicom-Bits2Banking
~~~
4. Open PowerShell and add the tools to that terminal's PATH. PATH is the list of directories searched for commands.
~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
gcc --version
cmake --version
ninja --version
~~~
5. Read the files under labs/native/text-editor. Run one command at a time and stop on an error. Check $LASTEXITCODE immediately after a native command; zero reports success.
~~~powershell
cmake -S labs/native/text-editor -B build/text-editor -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build build/text-editor --parallel 2
ctest --test-dir build/text-editor --output-on-failure --no-tests=error
& ".\build\text-editor\btb-text-editor.exe"
~~~

### Linux with Bash
1. Install Git, a C compiler with the required C23 mode, CMake 3.24 or newer, and Ninja using your distribution's documented package manager. Package names and compiler versions vary.
2. Clone into a new folder if needed:
~~~bash
mkdir -p "$HOME/umicom"
cd "$HOME/umicom"
git clone https://github.com/umicom-foundation/Bits2Banking.git Umicom-Bits2Banking
cd Umicom-Bits2Banking
~~~
3. Check cc --version, cmake --version and ninja --version. If you choose a different compiler, configure a new build directory with -DCMAKE_C_COMPILER set to that compiler.
4. Run each command separately and stop on a failure. echo $? immediately afterwards displays the previous result.
~~~bash
cmake -S labs/native/text-editor -B build/text-editor -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build build/text-editor --parallel 2
ctest --test-dir build/text-editor --output-on-failure --no-tests=error
./build/text-editor/btb-text-editor
~~~

## Understand the result
The editor prints its command summary and waits for input. Type append Hello, then show, then discard on separate lines. Expect TEXT: Hello. This is a bounded ASCII console lab with one-level undo, not a graphical production editor.
The -S argument selects source; -B selects a separate build directory. Building again in that same directory normally updates changed inputs and their dependencies. Testing is a separate step. A successful compile does not establish that the tests or a user workflow passed.

## If setup fails
A missing command means its tool is not installed or not on PATH. A compiler-mode error means you need a compiler that supports the requested C mode. A missing build.ninja file means configuration did not finish successfully. Read the first diagnostic before repeating later commands. Keep source separate from generated build files.

For a slower explanation, use [Learning C](../../learning-c/index.md). The [CMake command manual](https://cmake.org/cmake/help/latest/manual/cmake.1.html) explains configuration and build options.


## What to practise next
Use [Safer C Programming](../../03-native-code/safer-c-programming/index.md) to review the buffer and file-operation boundaries. Then return to chapter 3 to trace the Framework document APIs before planning a graphical editor. The [compiler course](../building-a-compiler-in-c/index.md) offers a separate language project when you are ready to study parsing.

## Scope
These are introductory chapters and practical labs. Further topics remain to be developed. Successful reading or compilation alone does not establish runtime correctness; compare expected results with your own checks.
