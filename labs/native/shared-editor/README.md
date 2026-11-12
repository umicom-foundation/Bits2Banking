<!--
Umicom Bits2Banking
File: labs/native/shared-editor/README.md

PURPOSE:
Teach installed-SDK editor ownership, Unicode positions and document history.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../content/assets/branding/umicom-logo.svg)

# Shared editor services in C

This console lab uses Umicom Framework to own text, resolve exact Unicode positions, select source ranges and edit named documents through their existing history. It complements the earlier bounded ASCII text-editor lab, whose implementation remains available.

Start with [lesson 9](../../../content/courses/building-a-text-editor/lessons/09-own-a-shared-text-buffer.html), then follow the six new lessons in order. These exercises contain no native window, clipboard read or file save.

## Prepare and build

1. Install a Framework SDK that exports Umicom::editor and Umicom::document, including source_selection.h, text_position.h and document/edit.h. Use the Framework build guide for the producing build.
2. Identify the installed prefix. The example below uses C:/umicom/installed/framework; substitute the actual qualified prefix consistently if yours differs.
3. Keep the compiler, architecture and runtime dependencies compatible with that SDK. A source checkout alone does not update installed headers or libraries.
4. Run each command separately. Stop on an unexpected error; check $LASTEXITCODE immediately after a native command.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\shared-editor -B .\build\shared-editor -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_EXPECTED_SDK_PREFIX=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build .\build\shared-editor --parallel 2
ctest --test-dir .\build\shared-editor --output-on-failure --no-tests=error
~~~

Configuration checks the package origin, SDK environment metadata and exported layout. A package outside the requested prefix is refused. If reusing a build directory selects an old cached package, use a new build directory with the intended prefix. Do not bypass the check by mixing source headers with another installed archive.

For Linux, use the same source directory and a separate build directory with your matching compiler and absolute installed prefix. The resulting executable has no .exe suffix. This guide does not claim that either host has been qualified.

## Run the observations

The lab registers twelve CTest scenarios when BUILD_TESTING is enabled. Each has a ten-second timeout.

| Scenario | Required observation |
| --- | --- |
| ownership | Caller bytes are copied, a borrowed view is reacquired, and an independent text copy survives mutation. |
| positions | Seven exact UTF-8 offsets round-trip through zero-based UTF-16 positions. |
| position-refusals | Six invalid offsets and a split UTF-16 pair preserve output sentinels. |
| selection | Word, line-content, whole-line and empty-final-line ranges have exact byte bounds. |
| selection-refusals | A split CRLF caret and malformed UTF-8 suffix preserve the output range. |
| history | Three edits undo to empty and redo through every intermediate value. |
| redo-branch | An edit after Undo drops the old Redo branch without changing text on a later refusal. |
| stale-plan | An older capture cannot replace a newer accepted draft. |
| other-tab | A captured edit and its Undo/Redo affect their original document while the second tab stays active. |
| invalid-replacement | Malformed UTF-8 and embedded NUL preserve state, then valid text can use the unchanged capture. |
| consumed-plan | A successful plan is refused on reuse and leaves the accepted edit intact. |
| read-only | A selected read-only document refuses a replacement and preserves text/history. |

~~~powershell
& .\build\shared-editor\shared-editor.exe positions
& .\build\shared-editor\shared-editor.exe other-tab
& .\build\shared-editor\shared-editor.exe stale-plan
~~~

Expected success is the line "shared-editor SCENARIO: checks completed" and exit code zero. An unknown scenario or wrong argument count returns two. A failed contract prints the source location and condition, then returns one. These are expected outcomes for the reader to observe, not recorded execution results.

## Understand the files

- buffer.c uses the existing byte buffer, exact position conversion and source-selection contracts.
- document.c owns a registry, workbench, store and coordinator, then destroys them in reverse dependency order. Its small helpers compare results or compose public calls.
- main.c selects one teaching scenario; it does not create a second product command registry.
- lab.h declares only the two scenario entry points.
- CMakeLists.txt links the installed targets and applies Framework application branding.

On Windows, the branding helper embeds the canonical Umicom ICO in the executable. The course pages use canonical SVG artwork and SVG/ICO favicons with the shared Segoe UI and Cascadia Code/Consolas font stacks. Console font choice belongs to the terminal host.

## What the observations cannot establish

Text positions count encoding units rather than rendered glyph widths. Source-word selection is not linguistic segmentation. Undo is bounded history, not durable version control. The document cases use an owning thread and do not test concurrent editing. They do not qualify a GUI, IME, fonts on a particular machine, file recovery or system clipboard integration.

Use [QUALIFICATION.md](QUALIFICATION.md) to record the actual SDK and execution results. Build and test success must be observed separately. Preserve the original diagnostic when a check fails, and do not weaken a comparison just to make the program return zero.
