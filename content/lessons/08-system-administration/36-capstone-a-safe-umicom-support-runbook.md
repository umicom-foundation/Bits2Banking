# Chapter 36 — Capstone: investigate and hand over a support incident

**Bits to Banking · System Administration: From Zero · Umicom Foundation**  

**Audience:** first-time users and returning learners; practical examples appropriate for supervised younger learners.  

**Estimated study time:** 70–110 minutes.  

**Prerequisites:** Chapters 25–35.


## Why this matters

This capstone asks you to support an imaginary training computer used for Umicom Notes and Bits2Banking. The student reports that a practice file cannot be found, a build recently failed, and their GitHub push was rejected. The challenge is to determine which facts can be verified **without risking production code or another person’s data**.

![Capstone: investigate and hand over a support incident](../../assets/diagrams/sysadmin-incident-timeline-update39.svg)


## What you will be able to do

By the end of this chapter you should be able to explain the new terms in ordinary language, select a safe read-only command for the right operating system, recognise a normal result and identify an unverified result. You should also be able to describe what permission would be needed before making a real system change.


## The mental model

A professional support runbook begins with scope and authority. It separates **observation**, **controlled change**, **verification** and **handover**. You will collect identity, current directory, file existence, disk space, Git state and test results in that order. Then you will assess missing evidence with a native C23 teaching model. You will not run an OS repair command, override a Git push, change user permissions, restart services or invent a passing test. Many support incidents remain partially unresolved at handover; a clear list of unknowns is part of a successful investigation.

### A complete support investigation has boundaries

Imagine two people use the same Umicom Framework remote repository through independent parent repositories. A clean `umicomOS` parent does not prove the Framework submodule worktree is clean or on `main`. A user may also have untracked source files inside the submodule that are not yet published. Before a `git pull`, report the repository root, branch/detached state, untracked-file status and any unpublished commits. If a checkout would overwrite local work, **stop** and preserve it for review. Never select `--force` or `reset --hard` to make a training screenshot look successful.

After the investigation, a second engineer should be able to reproduce your observations. Your handover states: “I tested X using command Y against revision Z at time T; it returned R. I did not run A because permission or prerequisites were missing.” That is a more valuable result than an unsupported statement that everything was repaired. The lesson ends where professional systems administration begins: clear evidence, explicit authority and controlled change.


## Words you should know
| Term | Meaning |
|---|---|
| **Scope** | Which machine, service, repository and time window are relevant. |
| **Handover** | Structured notes that allow another authorised person to continue. |
| **Blast radius** | Systems or people that might be affected by a change. |
| **Evidence gap** | A fact that has not been collected or verified. |
| **Change approval** | Explicit permission to apply a potentially disruptive action. |


## Windows: PowerShell 7, one command at a time

> Use a **normal non-elevated PowerShell** window. Do not type the `PS C:\...>` prompt. If a command is unavailable or returns Access Denied, record that result; do not attempt to defeat the restriction.

The lines in a code block may contain more than one interactive command. Run them in order, checking each result before continuing. **No `.ps1` file is created or required.**

### Windows step 1 — Confirm your own current context

```powershell
whoami
Get-Location
$PSVersionTable.PSVersion
```

**Expected result:** Three read-only commands: the user, current directory and PowerShell version.

**What this does:** PowerShell runs the command in your current session and displays information or, where clearly indicated, changes only your own practice files. If output differs, record the actual result before going further.

### Windows step 2 — Check the harmless training file

```powershell
Test-Path "$HOME\UmicomLearning\Notes\README.md"
```

**Expected result:** True/False. If False, do not attempt to repair permissions blindly.

**What this does:** PowerShell runs the command in your current session and displays information or, where clearly indicated, changes only your own practice files. If output differs, record the actual result before going further.

### Windows step 3 — Check free space

```powershell
Get-PSDrive -PSProvider FileSystem
```

**Expected result:** Use the drive containing the practice workspace.

**What this does:** PowerShell runs the command in your current session and displays information or, where clearly indicated, changes only your own practice files. If output differs, record the actual result before going further.

### Windows step 4 — Check Git state **inside the correct repository only**

```powershell
Set-Location "$HOME\UmicomLearning\git-first-project"
git status
git branch --show-current
```

**Expected result:** Only enter an actual practice repository created in Chapter 19. If absent, report not-run and skip Git checks.

**What this does:** PowerShell runs the command in your current session and displays information or, where clearly indicated, changes only your own practice files. If output differs, record the actual result before going further.

### Windows step 5 — Inspect build evidence without cleaning anything

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
ctest --test-dir ".\output\learning-build\sysadmin-evidence" --no-tests=error --output-on-failure
```

**Expected result:** Run only after configuring and building the Update 39 learning lab; otherwise explicitly report NOT RUN.

**What this does:** PowerShell runs the command in your current session and displays information or, where clearly indicated, changes only your own practice files. If output differs, record the actual result before going further.

### Windows step 6 — Summarise the condition in ordinary words

```powershell
Get-Date -Format o
```

**Expected result:** Record an offset-aware timestamp on the report.

**What this does:** PowerShell runs the command in your current session and displays information or, where clearly indicated, changes only your own practice files. If output differs, record the actual result before going further.


## Linux: terminal and distribution differences

> Run the following only in an authorised Linux computer or VM. If you use Windows only, read this section for comparison. A program being absent does not mean the whole operating system is faulty.

### Linux step 1 — Observe the current account, directory and space

```bash
id
pwd
df -h "$HOME"
```

**Expected result:** Read-only measurements, three separate commands.

### Linux step 2 — Inspect a private practice repository only when it exists

```bash
git -C "$HOME/UmicomLearning/git-first-project" status
```

**Expected result:** If missing, record not-run rather than creating a repository to make the output green.

### Linux step 3 — Run the previously compiled C23 teaching tests

```bash
ctest --test-dir "$HOME/Umicom-Bits2Banking/output/learning-build/sysadmin-evidence" --no-tests=error --output-on-failure
```

**Expected result:** Adapt to your own clone and build directory; do not invent pass results.


## Worked support scenario

Prepare a one-page handover headed “Training workstation — 14 October 2026”. Include system type, reporter, agreed scope, evidence timestamps, commands, exact observed results, steps deliberately not run, possible causes ranked by evidence, the next permitted action and the person who must approve it. Your final outcome may be “Unable to confirm the original save failure; learning workspace verified; Git push issue needs repository-specific investigation.” That is a valid honest conclusion.


## Common mistakes and safe responses
| Mistake | Better response |
|---|---|
| “I must fix something to pass the course.” | A safe diagnosis with accurate unknowns can be a complete professional outcome. |
| “The latest `git status` includes all submodule changes.” | Submodules and parent gitlinks are separate histories; inspect both explicitly when authorised. |
| “Any green teaching model means the production OS is healthy.” | The C23 model evaluates supplied fictional observations and cannot certify a real OS. |


## Exercises

1. Write a support report with six evidence lines and one unresolved question.

2. Explain why an error from a missing directory does not justify resetting Git.

3. List three changes requiring explicit approval before you would proceed.


## Review questions and suggested answers

<details><summary>Show the suggested answers after attempting the exercises</summary>



1. Use actual results or mark NOT RUN, and include time and scope.

2. Filesystem navigation errors and Git history repair are unrelated until evidenced otherwise.

3. Broad permission changes, force pushes, service restarts or deletion of build/source directories.



</details>


## Connecting this chapter to Umicom

Production Umicom software should use the appropriate **Umicom Framework** service for identities, processes, filesystem operations, Git, diagnostics, build planning or observability. The teaching commands here are interactive; they are **not** substitute Python or PowerShell implementations. Any reusable new executable component must first be considered for Framework ownership and designed in C23 or justified Assembly.


## References and further reading

- https://docs.github.com/en/get-started/using-git/about-git

- https://learn.microsoft.com/powershell/


**Course progression:** [Chapter 35](35-monitor-metrics-logs-and-incident-timelines.md) → **Chapter 36** → [Intermediate practice index](intermediate-index.md).


---

**Practical safety reminder:** No exercise requires access to private records, bank accounts, live production systems or another person’s computer. A successful “not permitted” or “not run” observation is an acceptable learning outcome.
