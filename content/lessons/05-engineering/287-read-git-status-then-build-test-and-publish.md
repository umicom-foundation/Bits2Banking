# Chapter 287 — A first responsible source-control and testing handover

**Bits2Banking · Engineering track · Umicom Foundation**  
**Previous material:** Chapters 264–283 and the dedicated [System Administration from Zero](../08-system-administration/index.md) course.  
**Engineering policy:** C23/Assembly first, existing Umicom Framework services before new implementations.

## Purpose and context

A contributor's first safe Git sequence is `git status`, review changes, `git add -A`, `git diff --cached --check`, `git diff --cached`, `git commit -m "..."` and `git push origin main`—but only after confirming the intended repository and `main` branch, and after checking that the staged snapshot contains no unrelated files. Git operations have different consequences: add stages locally, commit saves a local revision, and push publishes to a remote.

Because Umicom Framework is consumed through submodules, a parent repository records a gitlink to one Framework commit. A child checkout in detached HEAD is not automatically a data-loss error. Do not force-push, reset hard, clean a dirty working tree or blindly update `--remote` while local edits remain. Preserve unpublished changes and inspect ancestry first.

The system-administration course uses a personal practice repository for initial Git learning. Real Framework/Studio/OS work follows the established dependency order: test and publish the changed child, then test and pin the parent. Production changes must not be promoted based solely on a green command prompt.

**Final exercise:** report the local source SHA, build command, actual test total, any unrun checks, staged file inventory and final Git push outcome. If an action is blocked, report why; do not pretend it succeeded.

## Worked example: observe before changing

On Windows, open PowerShell 7, then type the following interactive commands:

```powershell
Get-Location
$PSVersionTable.PSVersion
Get-Command git, cmake, gcc -ErrorAction SilentlyContinue | Select-Object Name, Source
```

**Expected:** the working directory, shell version and installed executable paths are printed. Missing executables simply do not appear; investigate installation separately rather than changing source. Do not invoke elevated commands as part of this example.

## Guided lab

1. Begin in a personal training directory; confirm it using `Get-Location`.
2. Identify which commands in this chapter are observations and which would modify source or computer state.
3. Read the linked course chapter for your current skill level.
4. When ready for C23, configure the standalone read-only inspector as documented in its README.
5. Record the actual CTest result and keep any failure output.
6. Connect the lesson to an existing Framework-owned API, rather than copying the teaching implementation into Studio or OS.

## Troubleshooting and common questions

**Why does a command not exist?** Confirm the shell and platform, check `Get-Command`, and read the official install instructions. A shell error is not proof the C23 source is wrong.

**Why should a test failure not be ignored?** A build only proves that the source was compiled and linked. It cannot prove a function implements the intended behaviour, especially around error handling and resource ownership.

**Can I commit directly to main?** Authorised Umicom maintainers use the established main-branch workflow after reviewing tests and staged changes. External contributors need the appropriate permissions and may use pull requests.

## Review questions

1. Explain why the command prompt is not the operating system kernel.
2. Describe one way to preserve evidence before making a change.
3. Why should an educational native C23 library not automatically become a duplicate production Framework service?
4. What information must a tester report if Windows UCRT64 has not yet been tested?

## Next steps

Continue through the [dedicated System Administration course](../08-system-administration/index.md), then complete the [practice workbook](../08-system-administration/workbook-and-assessment.md).
