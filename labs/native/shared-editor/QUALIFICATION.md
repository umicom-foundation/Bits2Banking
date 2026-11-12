<!--
Umicom Bits2Banking
File: labs/native/shared-editor/QUALIFICATION.md

PURPOSE:
Separate static review, installed-SDK execution and native editor qualification.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../content/assets/branding/umicom-logo.svg)

# Qualify the shared editor lab

The source includes twelve deterministic scenarios. They are authored coverage until someone executes the corresponding binary and records its identity. A static source review is not a compiler or runtime result.

## Record the environment

1. Record the Bits2Banking revision and any local changes to this lab.
2. Record the Framework producer revision, installed prefix, SDK environment metadata, compiler, architecture and build configuration.
3. Keep the configure output that identifies the package actually selected. Record the executable path and SHA-256 after building.
4. Record the runtime library search path. The executable's location alone does not prove which dynamic dependencies a loader used.

## Execute the matching source

Follow the README commands one at a time. Build must succeed before using the new binary as evidence. List the tests and inspect the twelve names:

~~~powershell
ctest --test-dir .\build\shared-editor -N
ctest --test-dir .\build\shared-editor --output-on-failure --no-tests=error
Get-FileHash .\build\shared-editor\shared-editor.exe -Algorithm SHA256
~~~

Expect learning.shared_editor. followed by each README scenario name. A missing scenario requires checking the configured source, BUILD_TESTING and generated build files. Do not report zero selected tests as a pass. Keep a failed build separate from results produced by an older executable.

## Assess preserved state

For refusals, inspect the returned status, complete text, revision and history counts. The stale-plan baseline is the newer accepted edit, not the text before that edit. Read-only refusal must not consume history. Reusing a successfully applied plan must not apply its bytes twice.

For the other-tab scenario, the first document changes while the second document remains both active and unchanged. Then Undo and Redo operate on the first identity. This specifically checks document routing; it does not exercise native focus events.

For Unicode, compare byte offsets and UTF-16 units to the fixture table. The invalid cases include continuation bytes, a split CRLF, a split supplementary UTF-16 pair and malformed source text. These are exact representation checks, not visual rendering checks.

## Preserve distinct outcomes

Record configure, build, each test, missing tests and skipped coverage separately. Keep the first failure and source identity. Do not convert an unexecuted scenario into a passing result because its expected message appears in this guide.

A complete product qualification additionally needs owner-run native editor, IME, clipboard, file saving, allocation-failure and history-limit exercises. Use the existing Studio workflow and supplied designs for those checks. This lab supplies neither a new GUI layout nor evidence that those workflows passed.
