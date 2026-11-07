<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/learning-module-studio-installation-boundary.md

PURPOSE:
Understand how Studio opens a bundled learning module

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Understand how Studio opens a bundled learning module

A learning module is a collection of lessons and examples that an application can read. This module follows the same C services used by Umicom Studio IDE. A manifest is the small JSON document that identifies the collection and records which files belong to it. JSON is a text format made of named values, lists and objects.

## Prepare for this lesson

1. Open PowerShell on Windows, or a terminal on Linux. A terminal runs the commands you type; PowerShell and Bash are two command interpreters.
2. Choose a practice directory that you can find again. Keep the original course files unchanged.
3. Locate your built `umicom` program. The examples use `C:\umicom\Umicom-Applications\build\windows-ucrt64-all-debug\bin\umicom.exe`. Use the corresponding path on your computer.
4. Run `umicom learning-pack --help` using the full executable path if it is not on PATH. If the command is unavailable, your executable predates this feature; rebuild it before continuing.

The exercises use a content pack compatible with reader version `0.9.0`. A host version identifies the application reading the pack. Check your product and manifest compatibility before substituting another version. Nothing in these lessons requires a remote marketplace or an account.

## From an executable to its content

Studio defines known content modules, including its guide, Bits2Banking and the Framework wiki. Framework resolves a module folder relative to the executable rather than guessing from the directory in which the user started the program. This makes a desktop shortcut and a terminal launch use the same location.

~~~text
bin/
  umicom-studio-ide.exe
  learning-modules/
    bits2banking/
      learning-pack.json
      ...declared content...
~~~

The installed module must have the pack identity and entry resource expected by Studio. Copying an unrelated manifest into this directory is not a valid installation. Keep course authoring and product packaging separate.

## Follow the call

`UmiLearningModuleRoot` builds the path. `UmiLearningModuleOpen` prepares a shelf and reader using the pack ID, product ID, entry resource, compatible version and maximum bytes. A shelf is an in-memory collection of admitted packs. A reader carries the selected lesson and navigation state.

1. Framework clones the existing shelf. A clone is an independent copy.
2. It loads missing module metadata, or uses an already admitted pack.
3. It checks identity and verifies the entry resource.
4. It returns a complete candidate shelf and reader.
5. The application publishes both together after success.

If any step fails, the current shelf and reading session stay available. A missing module should therefore produce a useful diagnostic rather than erase another open lesson. Disk access belongs on a worker, leaving the GUI thread free to process input. A worker is a separate execution context for work that may take time.

## Exercise

Locate `runtime_learning_modules` in Studio source and write down the Bits2Banking module name, pack ID, product and entry ID. These values are different kinds of identity. Keep them separate when preparing content. This content-module interface reads material; it does not load executable extension code.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/teacher/learning_module.h).

## Continue learning

[Course contents](../../courses/umicom-development/index.html) · [Previous: Prepare a new revision without replacing the previous manifest](learning-module-prepare-reviewed-revision.md) · [Next: Copy an example into a learner-chosen file](learning-module-copy-example-safely.md)
