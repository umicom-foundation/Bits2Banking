# 48. Validate a book before publishing

Before creating a new edition of a book, a publisher needs to know which chapters belong in the edition and whether the source files are present. The Umicom Education tool can check these conditions in native C23 without opening or changing the published manuscript.

## 1. Locate the source book

Open PowerShell:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
Get-ChildItem ".\dropzone\documents\islam_blueprint_for_life"
```

This folder contains the original *Islam: Blueprint for Life* manuscript chapters and `volume.yml`. The YAML file is the **manifest**: it describes the volume and lists the chapters in reading order.

A simplified example shows the idea:

```yaml
title: "Introduction to Computers"
slug: introduction_to_computers
chapters:
  - what_is_a_computer.md
  - inside_a_cpu.md
  - memory_and_storage.md
```

A publisher must not alphabetically rearrange the chapter list: `chapters` records the intended order. A real book manifest may contain other fields such as authors, licensing, cover information and year.

## 2. Locate the native validator

The Framework implementation is in:

```text
Umicom-Applications/framework/src/education/book.c
```

`BookLoadManifest` reads the manifest's title and chapter list. `BookAllChaptersExist` checks that every named source file is available. The exported function `UmicomEducationBookCheck` combines those two operations and reports the result.

The C implementation intentionally understands only the small subset of YAML needed for the current book catalogue. It is not a complete YAML parser. An author must not assume that arbitrary YAML tags, expressions or document anchors will work.

## 3. List and check volumes

From the Umicom Applications checkout, run:

```powershell
Set-Location "C:\umicom\Umicom-Applications"

$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Books = "C:\umicom\Umicom-Bits2Banking"

& $Education book list --repo $Books
& $Education book check --repo $Books --volume islam_blueprint_for_life
```

The check should print an `[OK]` message that includes the slug and number of chapters. It reads the source files and does not write a new manuscript. If a chapter named in the manifest is missing, the validator returns a nonzero code.

Check the exit status immediately:

```powershell
if ($LASTEXITCODE -ne 0) {
    throw "The book source requires review before publication."
}
```

## 4. Why the validator rejects some names

An attacker or accidental edit could place a path like `../private-notes.md` in a manifest. If a naive publisher joined that value to the book directory, it might read a file outside the approved source folder.

The current book contract accepts only safe, simple `.md` basenames. It does not accept `..`, absolute paths, drive letters or directory separators. That limitation is deliberate: the catalogue's source-root boundary is more important than accepting every possible filename.

Source code can still be vulnerable to other path and race conditions. This lesson is about the existing bounded manifest contract; a fully general publishing system needs additional path-ownership and file-handle checks.

## 5. Create the review manuscript

Once the source passes the check, you can assemble the ordered chapters:

```powershell
& $Education book assemble --repo $Books --volume islam_blueprint_for_life
```

The resulting file is:

```text
C:\umicom\Umicom-Bits2Banking\output\native-books\islam_blueprint_for_life.md
```

The assembler preserves original chapter text except for a UTF-8 byte-order mark that would otherwise appear in the middle of a combined manuscript. It writes to a temporary output and publishes a complete result only when the content is ready.

If an existing manuscript differs, the tool preserves it and asks for an explicit review before `--refresh`. Do not use `--refresh` merely to bypass a warning.

## 6. An important difference: book and website

A **book manuscript** collects ordered chapters into one file. A **website** contains separate pages, menus and links. The manuscript is not yet a formatted PDF or DOCX edition, and internal links may need rewriting for a single-file publication. MkDocs remains responsible for generating the current educational website.

The distinction matters because we should not describe a correctly assembled Markdown file as a finished published book. Covers, illustrations, navigable references, accessibility and output-format checks still belong to the publication stage.

## 7. Exercise

Without editing the original Islam chapters, open `volume.yml` and identify the title, chapter list and total chapter count. Run `book check`, then `book list`, and explain how those operations differ. Inspect `book.c` and locate the function that prevents traversal filenames.

**Next:** [Assemble a book from Markdown using C23](44-native-book-manuscripts.md) and [explore the local C web server](39-build-a-c-web-server.md).
