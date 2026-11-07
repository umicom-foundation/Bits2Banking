<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/20-check-only-affected-preview-inputs.md

PURPOSE:
Check only affected preview inputs

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Check only affected preview inputs

A compiler reads a program and translates it into another representation. An IDE adds editing, project navigation and commands around that compiler. In this module, Umicom C accepts a deliberately small arithmetic language. Umicom Framework supplies the project recipe and Studio presents it. We follow the connection between those three responsibilities.

## Prepare the tools

1. Open PowerShell on Windows or a terminal running bash on Linux. A terminal accepts written commands; each command below starts an existing program.
2. Find your Umicom C executable. Run `umicom-c --version`. If it is not found, add its actual installation directory to PATH for this terminal or use its full path. PATH is the list of folders searched for program names.
3. Run `cmake --version` and `ninja --version`. CMake prepares a build description; Ninja follows that description. Install any missing tool through your platform's normal package manager.
4. Choose a practice destination, such as `C:\umicom\examples\arithmetic-preview`. The Studio starter requires a new folder: choose its parent first and do not create the final folder in advance.
5. In a Studio build containing the new Framework recipe, use **File → New Project**, choose **Umicom C Arithmetic Preview**, enter project details and the new destination, then create it. Generation creates text files only. It does not install dependencies or run the program.

The terminal exercises use that generated project independently of Studio's interface. See [Learning CMake](../../../courses/learning-cmake/index.html) for a longer introduction.

## Dependencies describe inputs

A dependency is an input needed to produce an output. This starter declares a marker, `source.checked`, as the output of a successful syntax check. The source and Umicom C executable are inputs. The marker is written only after checking succeeds.

1. Run `cmake --build --preset preview`. This invokes the default `check-source` target.
2. Repeat without changing files. Ninja can keep the previous result when tracked inputs and command remain unchanged.
3. Edit and save `src/main.uc`; build again. The changed source is an input, so checking must run again.
4. Introduce `return 6 +;` and build. Checking should fail. Read the diagnostic position, restore the expression and build again.
5. Execute the program explicitly:

```powershell
cmake --build build/preview --target preview
```

The preview target depends on successful checking and invokes `umicom-c run`. Requesting this action executes again. That differs from reusing a marker representing an unchanged syntax-check result.

## What the builder knows

Ninja follows declared dependencies and timestamps. It does not prove two different source texts mean the same thing. A comment-only edit can trigger checking. Do not promise semantic change detection when a build graph tracks files.

A build marker also does not mean tests passed. This starter's CTest cases are small enough to request after changes; the example does not implement a persistent test-result cache.

## Exercise

Make a table for unchanged source, changed expression and invalid expression. Record the command, whether checking ran and its exit status. In PowerShell inspect `$LASTEXITCODE` immediately after a native command; in bash inspect `$?`. Expected behaviour remains a hypothesis until observed on your setup.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/developer_project/templates/umicom_c_preview.c).

## Continue learning

[Course contents](../../../courses/building-a-compiler-in-c/index.html) · [Previous: Select the preview build profile](19-select-the-preview-build-profile.md) · [Next: Test language failures through the tool](21-test-language-failures-through-the-tool.md)
