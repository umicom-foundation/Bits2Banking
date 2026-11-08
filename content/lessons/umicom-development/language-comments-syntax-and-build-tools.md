<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/language-comments-syntax-and-build-tools.md

PURPOSE:
Separate editing rules from compiler support

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Separate editing rules from compiler support

This module starts with a small command-line program and follows its calls into Umicom Framework. Each lesson includes the setup needed to begin independently. You will inspect real source while learning how document names, memory boundaries and editing capabilities fit together.

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

Stop if configure or build reports an error. The first output line should be `cpu.vhd: vhdl`, followed by its choice, comment style and matching filters. This program examines the name only; the named files need not exist. [Learning C](../../courses/learning-c/index.html) and [Learning CMake](../../courses/learning-cmake/index.html) provide longer setup explanations.

## A language has independent capabilities

Recognising a filename, colouring text, toggling comments, compiling and debugging are different operations. An identifier helps connect them but does not implement them.

The lab prints an identity, display name and line-comment profile. The installed editor can also load syntax descriptions. A project separately describes compiler and debugger commands.

## Explore comment profiles

Run with cpu.vhd, app.zig, page.php and program.pas. VHDL uses a double-hyphen line prefix in the shared profile; Zig and PHP have double-slash profiles. Pascal has no shared line-comment profile here because syntax and compatibility depend on the selected dialect.

A missing profile is an explicit result. An editor should not insert a C-style prefix into every unfamiliar language. Users can still edit text manually.

## Read the lookup

In src/editor/comment_style.c, a table connects language IDs to prefixes. UmiEditorLineCommentStyleFind returns a borrowed immutable description on success. The lab handles UMI_STATUS_NOT_FOUND with a clear message rather than dereferencing an absent result.

The prefix is only part of an editing operation. A command also needs selection bounds, indentation policy and an undo record. Those belong to document-editing services rather than another list inside each application.

## Understand syntax descriptions

GtkSourceView uses language-description files for highlighting. Framework passes a language ID to that system. If an installed description is absent, the buffer may remain plain text. The [GtkSourceView language manager documentation](https://gnome.pages.gitlab.gnome.org/gtksourceview/gtksourceview5/class.LanguageManager.html) describes lookup and search paths.

## Plan a complete workflow

Make a checklist: filename recognition, explicit selection, highlighting, comment command, project template, build command, diagnostics and debugging. Record each separately.

For VHDL, a simulator checks hardware behaviour. A synthesis tool translates supported designs towards hardware implementation. These are distinct from the C compiler that builds Studio. Adding the VHDL choice does not turn Studio into a synthesis tool.

## Exercise

Explain why a coloured editor buffer can contain invalid code, and why valid source can remain uncoloured. Both answers follow from keeping the language layers separate.

## Read the source

<!-- The lab remains repository source; this earlier checkout-only link is retained for review.
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-language-inspection/main.c)
-->
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-language-inspection/main.c).

## Continue learning

[Course contents](../../courses/umicom-development/index.html) · [Previous: Share file-opening categories between applications](language-filter-categories-and-open-dialogs.md) · [Next: Trace language support from a command to an outcome](language-support-regression-and-source-map.md)
