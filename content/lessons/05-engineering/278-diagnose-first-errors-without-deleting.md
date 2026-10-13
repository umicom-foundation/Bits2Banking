# Chapter 278 — Read errors, identify the failing stage and preserve your work

**Bits to Banking · Absolute Beginner Course · Unit 4**  
**Time:** 30–45 minutes. Focus on observation and evidence before changing anything.

## A useful error is not a personal failure

A failed command is information. It tells you *which step* was attempted and *what went wrong*. The quickest reliable approach is not to paste a collection of repair commands; it is to identify the first failed stage, preserve the current state and change one thing at a time.

For a native Umicom learning project, there are four important stages: **configure → compile/link → test → run**. An error in one stage can prevent later stages from starting. If Ninja reports “file not found”, the earlier CMake configuration or source path may be wrong. If CTest says “Not Run”, that is not a test pass; the requested executable may not have been built.

## Checkpoint A — The wrong folder

If PowerShell shows `Cannot find path` or Git says `not a git repository`, first check:

```powershell
Get-Location
Get-ChildItem
```

Only then run `Set-Location` to the correct repository. Never rely solely on the text of an example prompt copied from a website: it may reflect a different computer.

## Checkpoint B — A command is missing

If `gcc`, `cmake`, `ninja`, `git` or `gh` is not recognised:

```powershell
Get-Command git, gh, cmake, ninja, gcc -ErrorAction SilentlyContinue |
    Select-Object Name, Source
```

For the UCRT64 compiler specifically:

```powershell
Test-Path "C:\msys64\ucrt64\bin\gcc.exe"
```

Do not guess PATH changes before verifying the installation. Use the documented installation method and reopen the shell.

## Checkpoint C — A compiler or linker error

For compiler output, read the **first real error**, including the filename, line, column and message. A later wall of dependent errors may be caused by the first missing declaration. A **warning** does not always stop compilation, but should be reviewed rather than ignored. A **linker** error such as an undefined reference usually means a declared function was not found in a linked object or library; it is not automatically a missing header.

Umicom Framework already provides shared diagnostic parsing through `umi_build_parse_diagnostic_line` and related APIs. Our classroom exercise does **not** introduce another production compiler parser.

## Checkpoint D — A test failed or did not run

```powershell
ctest --test-dir ".\output\learning-build\contributor-notes" -N
ctest --test-dir ".\output\learning-build\contributor-notes" --output-on-failure
```

`-N` lists registered tests without running them. It is useful before deciding whether the tests were configured and built. A **Not Run** result is incomplete evidence; reconfigure/build before attempting to interpret it as a functional failure. An actual assertion failure indicates a programme ran but did not meet its expected contract.

## Checkpoint E — Git refuses a push or submodule update

Run read-only inspections first:

```powershell
git status
git branch --show-current
git log -1 --oneline
git remote -v
```

Inside a parent Umicom OS repository, `framework` is a **submodule**, possibly checked out at a detached HEAD. Its working tree may contain modified or untracked files. Preserve those files before synchronising a submodule. Read the earlier Chapters 184–195, 260 and the Framework-owned submodule policy before changing a real repository.

**Prohibited shortcuts for novice troubleshooting:** `git reset --hard`, `git clean -fd`, unreviewed `git stash pop`, `git push --force`, repository mirroring with deletion and unverified installer scripts. These can destroy uncommitted or valuable work.

## How to ask for useful help

Supply the exact command, full error text, operating system, relevant tool versions, current folder, and whether there are uncommitted changes. Do not share private account tokens or security credentials. One focused error report is better than a summary saying “it doesn't work”.

**Practice:** In your Notes lab, distinguish a configuration error, a compilation error, a CTest failure and a Git remote permission error. Explain what evidence you would collect for each **without performing a destructive repair**.

**Next:** [Complete the beginner onboarding capstone](279-capstone-first-umicom-contributor.md).
