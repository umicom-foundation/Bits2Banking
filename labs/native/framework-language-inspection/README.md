<!--
Umicom Bits2Banking
File: labs/native/framework-language-inspection/README.md

PURPOSE:
Inspect Framework document languages and file-filter contracts

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Inspect Framework document languages

This command-line lab asks Umicom Framework to identify names, find their catalogue entries and line-comment profiles, and report matching file categories. It never opens the named files.

A terminal is a window that runs written commands. PowerShell is one such terminal on Windows; Bash is common on Linux. A compiler translates C into a program your machine can run. CMake describes the build; Ninja performs the work. An SDK supplies the headers that describe a library and the compiled library files.

Install a C23-capable compiler, CMake and Ninja. Install the Umicom Framework SDK containing the document and editor components. These steps assume Windows tools in C:\msys64\ucrt64\bin and SDK files in C:\umicom\installed\framework; replace those paths if your installation differs. No GTK window or broker connection is needed.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\native\framework-language-inspection"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework"
cmake --build build
.\build\language-inspection.exe cpu.vhd app.zig CMakeLists.txt
```

On Linux, use the same lab from your checkout and your installed SDK:

```bash
cd ~/umicom/Umicom-Bits2Banking/labs/native/framework-language-inspection
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="$HOME/umicom/installed/framework"
cmake --build build
./build/language-inspection cpu.vhd app.zig CMakeLists.txt
```

Stop if configure or build reports an error. The first output line should be `cpu.vhd: vhdl`, followed by its choice, comment style and matching filters. This program examines the name only; the named files need not exist. [Learning C](../../../content/courses/learning-c/index.html) and [Learning CMake](../../../content/courses/learning-cmake/index.html) provide longer setup explanations.

## Source map

- `main.c`: argument validation, shared-service calls and status reporting.
- `CMakeLists.txt`: installed SDK lookup, C23 target and two name-inspection checks.
- Framework `src/document/language_detection.c`: basename and extension rules.
- Framework `src/document/languages.c`: immutable language descriptions.
- Framework `src/document/file_filter.c`: bounded patterns and default groups.
- Framework `src/editor/comment_style.c`: line-comment descriptions.

## Check the lab

Run `ctest --test-dir build --output-on-failure --no-tests=error` after a successful build. The two checks inspect VHDL and unknown names. They do not open Studio or verify compilation of those languages.

If the SDK package cannot be found, confirm that its installation contains `lib/cmake/UmicomFramework/UmicomFrameworkConfig.cmake`, then correct CMAKE_PREFIX_PATH. If a component is missing, install an SDK build that includes document and editor. Keep the SDK and examples on compatible revisions.

## Continue

Follow [Build language-aware document tools](../../../content/courses/umicom-development/index.html#document-language-and-file-filter-services) for eight practical lessons. Recognition, syntax highlighting, comment editing and compiler configuration are separate capabilities.
