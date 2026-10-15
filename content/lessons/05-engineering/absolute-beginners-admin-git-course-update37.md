# Absolute Beginner Course — PowerShell, System Administration, Git, GitHub and Native Umicom Development

**Bits to Banking · Umicom Foundation · Major Update 37**  
**Audience:** people new to command-line tools, programming or version control; no prior development experience required.  
**Teaching style:** professional, careful, one command at a time; explain the reason, expected outcome and common failure before advancing.  
**Main environment:** Windows 10/11 with **PowerShell 7**; Linux terminal equivalents are covered.  
**Primary implementation language for native labs:** ISO C23; Assembly only when a hardware or ABI lesson calls for it.  
**Suggested duration:** six 60–90-minute sessions plus individual practice and assessment.

## Welcome

This course begins before GitHub and before C23. Many people can use a graphical computer confidently but have never opened a terminal, created a folder using a command or read a tool's error message. We will build those skills in a controlled practice workspace. No learner is expected to understand the word *repository*, *shell* or *compiler* before we introduce it.

Our core rule is simple: **know where you are, know what a command does, inspect the result, then proceed.** We use realistic Umicom Notes, development, banking and operating-system examples. We do not require administrator rights for normal exercises, and we never ask learners to send passwords or access tokens.

![Windows 11 search results: different PowerShell programmes](../../assets/screenshots/windows-search-powershell-options-update37.jpeg)

**The first important distinction:** Windows Terminal is the *window/host*; PowerShell 7 (`pwsh`) is the *shell* running inside it; older Windows PowerShell (`powershell.exe`) is normally version 5.1; CMD is a different Windows shell. On Linux you use a terminal application, commonly running Bash. Git tracks local versions; GitHub hosts repositories online; GitHub CLI (`gh`) manages GitHub from a command line.

## Session plan and learning progression

| Session | Lessons | Skills demonstrated | Evidence expected |
|---|---|---|---|
| 1 — Open and navigate | [264](264-open-terminal-and-choose-powershell.md)–[266](266-navigate-create-and-inspect-files.md) | Find the correct PowerShell, install tools, create/read a practice file | Shell version, correct working folder, `README.md` |
| 2 — System administration | [267](267-check-system-hardware-and-storage.md)–[271](271-linux-terminal-for-first-time-users.md) | Inspect Windows, memory, disk, permissions, processes, services, network; Linux orientation | Read-only system facts and diagnosis |
| 3 — Version control | [272](272-configure-git-and-sign-in-to-github.md)–[273](273-create-and-commit-first-local-git-repository.md) | Git identity, GitHub login, staging and local history | Two checked commits in `main` |
| 4 — GitHub collaboration | [274](274-publish-the-repository-with-github-cli.md)–[275](275-clone-and-contribute-to-umicom.md) | Publish private practice repository, clone, read an Umicom project | `git remote -v`, visible commits, clear permission model |
| 5 — Build real C23 code | [276](276-install-msys2-ucrt64-cmake-and-ninja.md)–[278](278-diagnose-first-errors-without-deleting.md) | Install native toolchain, compile Notes, run CTest and diagnose failures | **8/8** executable CTests (where environment supports it) |
| 6 — Assessment and next steps | [279](279-capstone-first-umicom-contributor.md)–[283](283-capstone-verified-learning-delivery.md) | Complete capstone, review Framework ownership, native planning and safe delivery | Checked notes, change diff and honest build/test evidence |

The final four chapters, 280–283, are **optional advanced extensions**. Someone who can complete 264–279 already has the core beginner skills. Do not require people to install and build the entire Umicom Framework merely to learn Git.

## Your safe practice locations

- **Personal practice:** `$HOME\UmicomLearning\notes-practice` on Windows, or `$HOME/UmicomLearning/notes-practice` on Linux. Learners may choose another location they own.
- **Reading public lessons:** a separate clone such as `$HOME\UmicomLearning\Bits2Banking-Study`.
- **Maintainer-only integration:** established `C:\umicom\Umicom-Bits2Banking`, `C:\umicom\Umicom-Applications`, and `C:\umicom\umicomOS`. These are examples, not folders that must exist on every computer.

Do not run introductory reset, cleanup, `git add -A` or GitHub publication steps inside a work checkout until you have confirmed its identity and the implications.

## First-day warm-up (Windows)

Open **Start**, type **PowerShell**, choose the modern application if available and enter the following **one command at a time**:

```powershell
Get-Location
$PSVersionTable.PSVersion
winget --version
git --version
gh --version
```

Missing Git or GitHub CLI is expected on some computers. It means “install first”, **not** “the student failed”. Follow Chapter 265. If a line begins with `PS C:\...>`, the `PS C:\...>` part is the *prompt* and should not be copied.

## Classroom rules

1. **One action, one check.** Ask learners to read the result before proceeding. Do not paste a page of commands as one unexplained block.
2. **State the shell.** Commands labelled `powershell` run in PowerShell. Commands labelled `bash` belong to a Linux or MSYS2 terminal, as explicitly stated.
3. **Never request secret output.** Verify sign-in status without copying tokens, recovery codes, credential stores or private SSH keys into the classroom.
4. **No destructive repairs.** Preserve changes. Do not use hard resets, recursive deletes, force pushes or unreviewed overwrite commands to make a training environment appear clean.
5. **Distinguish every result.** Installed ≠ configured; Git commit ≠ GitHub push; compiler success ≠ passing tests; passing unit tests ≠ released application.
6. **Use Framework first for reusable software.** The C23 Notes lab is a deliberately small independent teaching model. Production version-control, repository automation, build scheduling and diagnostics belong to Umicom Framework.

## Downloads, videos and assessment

- **One-page command sheet:** [Beginner PowerShell and Git quick reference](beginner-command-sheet-update37.md).
- **C23 source and tests:** `labs/native/contributor-notes/` in the repository root; use [Chapter 277](277-build-and-test-first-c23-notes-program.md).
- **Video companions:** Episodes [90](../../videos/scripts/90-open-the-correct-powershell.md), [91](../../videos/scripts/91-read-computer-information-safely.md), [92](../../videos/scripts/92-create-and-publish-first-git-repository.md), [93](../../videos/scripts/93-build-your-first-umicom-notes-program.md) and [94](../../videos/scripts/94-review-framework-build-and-gitlinks.md).
- **Final assessment:** [Chapter 279](279-capstone-first-umicom-contributor.md); [instructor rubric and answer keys](../../teaching/first-contribution.md) support the assessment.

## Primary references

Microsoft PowerShell installation: https://learn.microsoft.com/powershell/scripting/install/install-powershell-on-windows  
Microsoft Winget: https://learn.microsoft.com/windows/package-manager/winget/  
Git documentation: https://git-scm.com/docs  
GitHub CLI authentication: https://cli.github.com/manual/gh_auth_login  
GitHub CLI repository creation: https://cli.github.com/manual/gh_repo_create  
MSYS2: https://www.msys2.org/  
CMake: https://cmake.org/cmake/help/latest/guide/tutorial/  
Umicom Foundation: https://github.com/umicom-foundation/Bits2Banking

**Start here:** [Chapter 264 — Open the correct PowerShell](264-open-terminal-and-choose-powershell.md).
