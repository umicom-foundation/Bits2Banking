<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/learning-module-publication-and-limits.md

PURPOSE:
Review content, accessibility and publication separately

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Review content, accessibility and publication separately

A learning module is a collection of lessons and examples that an application can read. This module follows the same C services used by Umicom Studio IDE. A manifest is the small JSON document that identifies the collection and records which files belong to it. JSON is a text format made of named values, lists and objects.

## Prepare for this lesson

1. Open PowerShell on Windows, or a terminal on Linux. A terminal runs the commands you type; PowerShell and Bash are two command interpreters.
2. Choose a practice directory that you can find again. Keep the original course files unchanged.
3. Locate your built `umicom` program. The examples use `C:\umicom\Umicom-Applications\build\windows-ucrt64-all-debug\bin\umicom.exe`. Use the corresponding path on your computer.
4. Run `umicom learning-pack --help` using the full executable path if it is not on PATH. If the command is unavailable, your executable predates this feature; rebuild it before continuing.

The exercises use a content pack compatible with reader version `0.9.0`. A host version identifies the application reading the pack. Check your product and manifest compatibility before substituting another version. Nothing in these lessons requires a remote marketplace or an account.

## Four different reviews

A lesson can have valid JSON while still being confusing. A code example can compile while its explanation is wrong. A page can look attractive while keyboard users cannot navigate it. Review these independently.

1. **Teaching review:** state the goal, explain every new term, show exact steps, give expected output and recovery advice. Keep one main topic per lesson.
2. **Source review:** compare named functions and paths with the current Framework implementation. Mark excerpts as excerpts. Do not describe a future feature as available.
3. **Content review:** verify the manifest against the exact distribution bytes. Line-ending conversion can change a digest; prepare and verify the actual packaged form.
4. **Reader review:** use keyboard navigation, a narrow window, readable contrast and the supported content format. Record what was actually exercised.

## Extend without duplication

Put shared parsing, verification and navigation in Framework. A Studio command should select the module and present the result. A Bank or Trader help command can use the same services with its own product identity and material. This keeps application guides distinct while sharing the reliability rules.

A browser can render a full HTML page with CSS. A native lesson reader may support a smaller set of structured text, links and illustrations. Test both; matching source files do not guarantee identical presentation.

## Final exercise

Prepare a two-lesson practice module: one concept lesson and one lab. Give each a stable ID, link the lab to a C example, and include a review checklist. Explain what happens if the lab file changes after verification. Expected answer: a later read compares the bytes again and refuses a mismatched digest.

Keep personal progress, private logs and credentials outside public content. Do not claim that this module implements remote registration, paid distribution, signature trust or an executable plugin marketplace. Those require their own contracts and tests.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/teacher/learning_reader.h).

## Continue learning

[Course contents](../../courses/umicom-development/index.html) · [Previous: Test a learning module through observable outcomes](learning-module-regression-design.md)
