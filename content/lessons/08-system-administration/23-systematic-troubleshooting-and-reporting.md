# Chapter 23 — Troubleshoot problems systematically and write useful evidence

**Bits to Banking · System Administration: From Zero · Umicom Foundation**  
**Audience:** first-time users and returning learners; no prior system-administration knowledge required.  
**Code policy:** interactive PowerShell 7 and Bash commands; native C23/Assembly for Umicom executable development.  
**Estimated study time:** 25–50 minutes (longer when practising).

## What you will learn

Apply a repeatable incident investigation without deleting evidence.

## Why this matters

![Diagnose a service by collecting several independent observations](../../assets/diagrams/sysadmin-process-log-update38.svg)


Troubleshooting starts with a precise symptom, not a speculative fix. Record what the user expected, what actually happened, the time, the computer and program versions, the smallest steps that reproduce it, and the exact error message. Next form a hypothesis and choose a low-risk test that could disprove it. Keep the raw evidence even after the issue is resolved.

One important distinction is between symptoms and causes. “The screen is blank” is a symptom. It might be caused by a closed application, a display driver, a file that failed to load or a network connection. A useful administrator narrows the possibilities layer by layer. Do not run broad cleanup commands, reinstall unrelated tools or disable security simply because an error message is unfamiliar.

For a learning community, communication is part of diagnosis. Another contributor should be able to repeat the exact steps and understand which tests were performed. Avoid including passwords, tokens, patients’ records, private file paths or complete network inventories in public issue reports.

## New words, explained

| Term | Plain-English meaning |
|---|---|
| **Symptom** | Observed effect of a problem. |
| **Hypothesis** | Proposed explanation that can be tested. |
| **Reproduction** | Steps that cause the issue to happen again. |
| **Evidence** | Saved output, logs or observations supporting an investigation. |
| **Regression** | Previously working behaviour that fails after a change. |

## Windows practice — PowerShell 7

> **Before typing:** Run these commands in a normal, non-elevated PowerShell window. Where a file is used, complete the previous practice-folder chapters first. Do not paste the `PS C:\...>` prompt into the terminal.

**Start:** Use the Windows Start menu or Windows Terminal to open PowerShell. Check the prompt is ready. Commands beginning with `$` are still commands; type them exactly as shown.

### Step 1 — Identify your working location

```powershell
Get-Location
```

**Expected observation:** You can confirm which repository or folder is active.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 2 — Check the relevant Git working tree

```powershell
git status --short
```

**Expected observation:** Changed, added and deleted files are identified if you are inside a Git repository.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 3 — Check available compiler version

```powershell
gcc --version
```

**Expected observation:** The installed compiler version is displayed if GCC is available.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

### Step 4 — Inspect one recent Windows event when needed

```powershell
Get-WinEvent -LogName Application -MaxEvents 1 | Select-Object TimeCreated, Id, ProviderName
```

**Expected observation:** One application event is shown if the log is accessible.

**Check:** Read the output before continuing. If it does not match, stop and investigate the specific command; do not add `-Force` or run as Administrator automatically.

## Linux comparison — terminal/Bash

> Linux commands are alternatives on a Linux machine or authorised VM. Do not paste them into Windows PowerShell as though the shells have identical syntax.

### Linux step 1 — Inspect a short journal excerpt if permitted

```bash
journalctl -n 10 --no-pager
```

**Expected observation:** Recent journal entries are shown.

### Linux step 2 — Confirm process and repository context

```bash
pwd && git status --short
```

**Expected observation:** The location and Git changes are shown if the directory is a Git repository.

## Worked support scenario

A contributor reports a native Umicom test crash. Capture the failing test name, exact CTest output, compiler, target preset, Git SHA, whether a submodule differs from its parent pin, and whether the same test fails repeatedly. That evidence is far more valuable than “the build is broken.”

## Common problems and how to respond

| Problem or assumption | Better response |
|---|---|
| Sending only a screenshot of the last error line | Include the surrounding command, versions and preceding failure where relevant. |
| Changing several unrelated settings at once | Apply one reviewed change, retest, and attribute the outcome correctly. |
| Pushing experimental fixes before tests pass | Keep changes local until the required validation gates succeed. |

## Exercise: demonstrate understanding

1. Write down the purpose of **two commands** from this chapter, in your own words.
2. Run a **read-only command** and record only the information needed to answer its question.
3. Explain which command would change the machine, if any, and why the chapter avoids it.
4. Explain the difference between an observation, a conclusion and an unverified assumption.

## Review questions

1. What makes a bug report reproducible?
2. Why should you preserve original logs?

<details><summary>Show the suggested answers</summary>

1. Exact commands, versions, environment, expected result, actual result and error output.
2. They allow later comparison and help identify root causes and regressions.

</details>

## How this connects to Umicom

Every Umicom batch should provide the change summary, required build/test commands, actual results, outstanding unverified gates and safe Git staging/commit instructions.

## Where to go next

Continue with [Chapter 24 — Capstone: perform a safe support check from start to finish](24-capstone-your-first-support-check.md).
