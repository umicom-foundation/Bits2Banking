# Teaching a first Umicom contribution

**Course:** Absolute Beginner System Administration, PowerShell, Git, GitHub and Native Umicom Development  
**Audience:** new Umicom Foundation contributors; no prior terminal or developer-tool experience needed.  
**Curriculum:** Chapters 264–279 (foundation) and 280–283 (optional intermediate bridge).  
**Course authorship:** Sammy Hegab · Umicom Foundation · Bits to Banking.

## Teaching contract

Teach the vocabulary before the command. Prefer one instruction, one observation and one explanation; then invite the student to repeat it. Do not introduce password prompts, admin privileges, registry edits or Git cleanup operations as normal setup shortcuts. Show exact shell identifiers above command blocks: PowerShell 7 versus MSYS2 UCRT64 versus Linux Bash. When demonstrating `PS C:\...>` or `$` prompts, explicitly say the **prompt is not part of the command**. Use learner-owned `$HOME\UmicomLearning` rather than creating practice repositories inside Framework.

Windows Start search can show several similar PowerShell launcher names. An important assessment criterion is whether learners can **verify** the version from `$PSVersionTable.PSVersion` rather than rely on the icon. Explain that PowerShell 7 can be launched with `pwsh`, while Windows PowerShell 5.1 normally uses `powershell.exe`.

## Lesson pacing

| Instructor session | Chapters | Suggested teaching method | Observable checkpoint |
|---|---|---|---|
| First shell | 264–266 | Tutor models a command, then learners repeat using their own paths | Student can show a current folder and create/read `README.md` |
| First administration | 267–271 | Read-only observations; group interprets what each result can prove | OS, CPU, RAM, storage, process and network checks distinguished |
| First local history | 272–273 | Build a practice repo; compare working tree, stage and commit | Two labelled commits, no live project affected |
| First remote | 274–275 | Authenticate through browser, create private repo, clone study copy | Student explains `origin`, `--push` and repository permissions |
| First native build | 276–278 | Use installed UCRT64 toolchain, run CMake, Ninja and CTest | Correct test registrations and an actual 8/8 result or honest blocked status |
| Capstone | 279 | Student demonstrates steps, explains each and answers safety questions | Rubric; 80/100 threshold with no unsafe assumptions |
| Advanced optional | 280–283 | Present actual Framework-owned APIs; no app-local reimplementation | Differentiates planned work, executed tests and release approval |

## Common errors to anticipate

**“Git, GitHub and GitHub CLI are the same programme.”** Correct by asking which one records local commits, hosts the remote, and helps with online authentication.

**“Windows Terminal means PowerShell 7.”** Explain host versus shell. Show two tabs with different shells if available.

**“The screenshot's selected Windows PowerShell is PowerShell 7.”** Explain that this is typically the older Windows PowerShell; check version in the actual window.

**“I typed `git - -version` exactly like the written message.”** Demonstrate two adjacent hyphens: `git --version`.

**“I copied `PS C:\Users\Student>`.”** Revisit prompt versus input; type only after the prompt.

**“PowerShell says `'C:\msys64\ucrt64\bin\gcc.exe'`.”** A quoted path is a string; `& "C:\msys64\ucrt64\bin\gcc.exe" --version` actually calls the executable.

**“The CMake build exists, therefore every test passed.”** Require actual CTest output and distinguish configured, built, registered, executed, skipped and not-run.

**“My push was rejected; I should force it.”** Stop; inspect remote divergence, branch identity and local modifications. Do not rewrite remote history during onboarding.

**“The child Framework checkout moved; the OS gitlink is already updated.”** Show Git mode 160000 and the separate parent commit. No parent push is implicit.

## Instructor demonstration 1 — Windows PowerShell (no admin)

1. Open Windows Start search and identify the available PowerShell launchers.
2. Open the available shell and type `Get-Location`.
3. Type `$PSVersionTable.PSVersion`; ask the group to name the major version.
4. Type `winget --version` and `git --version`. If either is missing, state which installation lesson applies; do not mark the learner as having failed.
5. Make `"$HOME\UmicomLearning\notes-practice"` and create a real `README.md` with `Set-Content`; demonstrate `Get-Content`.
6. Show `Remove-Item ... -WhatIf` on a disposable copy, stressing that no deletion occurred.

## Instructor demonstration 2 — Git staging versus commit

In a new disposable practice folder, make one commit on `main`. Edit the README, show `git diff`, then stage only the intended file and show `git diff --cached`. Ask whether a commit exists merely because the change is staged (answer: no). Commit and compare `git log --oneline`. The lesson should be about **evidence**, not memorising command spelling without comprehension.

## Instructor demonstration 3 — Native C23 Notes

The lab intentionally has four independently identifiable source roles: public header, implementation, demo, tests. During the build, point out which tool configures, which compiles and which executes test cases. Show the negative tests and how they preserve state when an operation is rejected. Do not claim the lab uses Framework production persistence or implements a bank-grade Notes module.

Expected default lab test labels: `add`, `update`, `too-long`, `capacity`, `missing`, `invalid`, `ownership`, and `demo`. CTest registers eight checks. The optional installed Framework SDK consumer is a separate, **not yet validated** exercise.

## Capstone rubric: 100 points

| Competence | Maximum | Evidence |
|---|---:|---|
| Starting correct shell and creating a safe workspace | 20 | Student verifies PowerShell version, location, filesystem operations |
| Git identity, local commits, staging and remote publishing | 30 | Status/diff/commit logic explained; private practice repo |
| Native C23 build and tests | 30 | Real build command, executable and 8 CTest results or a precise blocked diagnosis |
| Safety, confidentiality and communication | 20 | Avoids destructive operations, explains permissions and reports errors faithfully |

**Completion policy:** 80/100 plus no unresolved safety-critical errors. A learner who reports an unavailable toolchain accurately can complete a diagnostic reassessment instead of inventing tests.

## Review question answer key

1. **Terminal or shell?** Windows Terminal is a host window; PowerShell 7 runs inside it. An existing shell can also run without Windows Terminal.
2. **PowerShell 5.1 or 7?** `$PSVersionTable.PSVersion`; `pwsh` normally starts PowerShell 7.
3. **Git or GitHub?** Git tracks local versions; GitHub hosts remote repositories online.
4. **What does GitHub CLI do?** Authenticates and manages GitHub resources from a terminal; it is not the Git database.
5. **Working tree versus stage?** Working tree contains edits; the index/stage records proposed commit content.
6. **Commit versus push?** Commit records local history; push offers committed history to a remote.
7. **Why check `Get-Location`?** Relative commands operate from the current folder. Wrong locations can stage or alter unrelated files.
8. **Who runs CMake, GCC and Ninja?** CMake generates a plan, GCC compiles/links, Ninja executes configured build steps.
9. **What does `ctest -N` mean?** List registered tests, not execute them.
10. **What does 8/8 passing mean?** The eight tested cases passed in this build, not that the entire Umicom platform is ready for release.
11. **Why not copy Framework source into OS?** The shared Framework has one source owner, and OS records a gitlink to a chosen commit.
12. **What is wrong with force push?** It can overwrite remote history and hide unresolved divergence.
13. **When is admin rights justified?** Only for a clearly authorised system-level operation. Normal practice projects and Git commits do not require it.
14. **What does `--private` mean?** Restricts online repository visibility; it does not make secrets safe to commit.
15. **Where does Notes lab data live?** Only in memory, lost when the process exits; no persistence or authentication is provided.
