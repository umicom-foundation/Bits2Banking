<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/introduction-to-version-control/05-read-a-parent-pin-and-a-child-checkout.md

PURPOSE:
  Present "Read a parent pin and a child checkout" with source-based exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read a parent pin and a child checkout

An application can use Framework as a separate Git repository. This lesson reads the two revisions involved: the child revision recorded by the parent, and the revision currently checked out inside the child folder. All commands in the exercise inspect state without changing it.

Source to open: `Umicom-Applications/.gitmodules`.

## Setup recap

Use a text editor, this course and a checkout of the named source. A checkout is a folder containing a repository's files. This is a source-reading and reasoning lab; it needs no running service or account. Choose your own practice folder and keep the original example unchanged. The commands below display source rather than compile or execute it. Replace the example directory with your checkout location. The detailed terminal and editor guide explains how to obtain a checkout, open a terminal and prepare later executable exercises.

A terminal accepts commands. Set-Location (PowerShell) and cd (Bash) choose the folder in which subsequent commands work. Get-Content and sed display text. If a path is missing, locate the repository first instead of creating an empty replacement file.

### PowerShell

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
Get-Content -LiteralPath '..\Umicom-Applications\.gitmodules'
```

### Bash

```bash
cd /path/to/umicom/Umicom-Bits2Banking
sed -n '1,200p' '../Umicom-Applications/.gitmodules'
```

## Understand the idea

A commit identifies a recorded repository state. A submodule is a separate repository used inside a parent repository. The parent's gitlink records a child commit, while .gitmodules describes paths and remote locations. Fetching a new child commit does not automatically change that parent pin. The child's working files may also differ from its commit. These are three distinct observations: parent pin, child HEAD, and uncommitted child changes. A newer child is not automatically the revision selected for a release.

```text
Parent HEAD --gitlink--> selected Framework commit
Child HEAD ------------> currently checked-out Framework commit
Child working files ---> may contain additional uncommitted edits
```

## Work through the lab

1. Open .gitmodules and find the framework entry. Record its path and URL. The URL identifies where commits can be obtained; it does not identify which commit the parent currently records.
2. In a terminal at your Applications checkout, inspect git ls-tree HEAD framework and git -C framework rev-parse HEAD. Write their commit IDs in separate columns. These read-only commands are the same in PowerShell and Bash.
3. Inspect git -C framework status --short --branch. If it reports changed files, note that a matching HEAD still does not prove the working content is identical to the committed content.
4. Use git diff --submodule=log to inspect a changed parent pointer. Describe the intended publication order in words: review and publish the shared child once, update clean dependency copies, then record the selected child revisions in parents. Stop for separate review if a checkout has divergent or uncommitted work.

## Expected result

Your comparison has three separate entries. A difference between the two commit IDs is evidence to investigate, not permission to discard files or change branches. A clean status describes working-file state; it does not prove that all local commits were published.

## If the result differs

If git says the path is not a repository, check your location and whether the child was initially populated. Do not use a reset, forced checkout or cleanup command to make the numbers match. Preserve differences and choose the intended revision through review.

## Explain it yourself

Both commit IDs match, but the child status lists one modified C file. Are the parent pin and the child working content fully aligned?

<details>
<summary>Worked explanation</summary>

The committed revisions align, but the working content includes an extra change. The parent pin cannot capture an uncommitted child edit. That edit needs its own review and publication before a parent can record it as a child commit.

</details>

## Use the idea in Umicom

Record inputs, expected outputs and refusal cases before extending the example. Reusable production behaviour belongs in Umicom Framework; applications translate user actions and show the service result. A traced example explains a contract. It does not establish that every application using a similar idea has been integrated or tested.

[HTML edition](../../../courses/introduction-to-version-control/lessons/05-read-a-parent-pin-and-a-child-checkout.html)

[Terminal and editor setup guide](../../learning-c/terminal-to-visual-studio.md)

[Previous lesson](04-submodules-and-application-dependencies.md) · [Course contents](index.md)

## Technical references

[Git documentation: submodules and gitlinks](https://git-scm.com/docs/gitsubmodules)

