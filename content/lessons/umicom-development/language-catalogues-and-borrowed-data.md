<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/language-catalogues-and-borrowed-data.md

PURPOSE:
Read a shared language catalogue safely

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Read a shared language catalogue safely

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

## A catalogue gives names a stable meaning

A catalogue is a collection of descriptions. Framework owns the document-language catalogue so Studio and other clients can use the same identifiers and display names. Applications ask this catalogue rather than maintain competing lists.

UmiDocumentLanguageChoiceCount reports the number of entries. UmiDocumentLanguageChoiceAt reads one entry by index. UmiDocumentLanguageChoiceFind searches by language ID. Indexes start at zero; an index equal to the count is already outside the collection.

## Read an entry without taking ownership

The lab starts choice as NULL, then passes &choice to Find. choice is a pointer variable. &choice points to that variable, allowing Find to set it to the selected entry. The arrow in choice->display_name reads a member through a pointer.

The result is borrowed from Framework's static catalogue: do not free it or write into it. A borrowed pointer is a view of somebody else's object. A dangling pointer points to an object whose lifetime has ended. This catalogue has static lifetime, but a pointer borrowed from a window or document generally does not. Learn the ownership contract of each API.

## Add an inspection loop

In a separate copy of the lab, print each catalogue entry before processing arguments:

```c
for (size_t i = 0U; i < UmiDocumentLanguageChoiceCount(); ++i) {
    const UmiDocumentLanguageChoice *entry = UmiDocumentLanguageChoiceAt(i);
    if (entry == NULL) return 1;
    puts(entry->display_name);
}
```

size_t is the unsigned type used for object sizes and array indexes. The less-than comparison avoids requesting the entry at count. The null check makes the caller's assumption explicit.

## Verify the contract

1. Run with app.zig and observe the Zig display name.
2. In a small experiment calling Find directly, request an unregistered ID.
3. Handle UMI_STATUS_NOT_FOUND. Do not dereference choice on that path.
4. Read src/document/languages.c in Framework and locate the static choices array.
5. Compare the ID, display name and example filename for one entry.

A catalogue row makes a choice discoverable. It does not install a compiler, enable debugging or provide a syntax grammar. Those capabilities have separate owners and checks.

## Read the source

<!-- The lab remains repository source; this earlier checkout-only link is retained for review.
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-language-inspection/main.c)
-->
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-language-inspection/main.c).

## Continue learning

[Course contents](../../courses/umicom-development/index.html) · [Previous: Identify a document from its filename](language-names-and-document-identity.md) · [Next: Separate a filename from its directories](language-basename-and-suffix-matching.md)
