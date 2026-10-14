# Chapter 291 — Capstone: from administrator observations to a verified C23 report

**Bits to Banking · Advanced Engineering · Umicom Foundation**  
**Implementation language:** C23.  
**Prerequisite:** System Administration Chapters 1–36 and Engineering Chapter 287.

## Why this matters

This chapter brings together the dedicated System Administration course and the C23 learning laboratory. Learners diagnose a **fictional Umicom Notes support scenario** with personal files, read-only commands and an offline evidence model. The result is a transparent report, not an automated system repair.

## Step 1 — Define required checks

Agree on the smallest set needed for the learning task: (1) the harmless Notes README exists and is readable, and (2) its deliberately created practice backup restores correctly. You may add an optional network observation, but failure of that optional check should still be reported for review. Do not add an OS administrator check just to look professional.

## Step 2 — Gather and verify actual observations

```powershell
Set-Location "$HOME\UmicomLearning"
Test-Path ".\Notes\README.md"
Get-PSDrive -PSProvider FileSystem
```

The commands return real observations. If the Notes file does not exist, mark its check NOT_RUN or FAILURE according to the pre-agreed runbook; do not pretend it passed by using some unrelated file. Use [the restore drill](../08-system-administration/33-backups-restore-drills-and-verification.md) only on your own practice README.

## Step 3 — Run the independent C23 laboratory

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
cmake --build ".\output\learning-build\sysadmin-evidence" --parallel 2
ctest --test-dir ".\output\learning-build\sysadmin-evidence" --no-tests=error --output-on-failure
& ".\output\learning-build\sysadmin-evidence\btb-sysadmin-evidence-demo.exe"
```

The demonstration has **fictional** observations hard-coded as classroom inputs. Its `REVIEW` result illustrates the policy but does not automatically ingest your PowerShell output. That distinction is intentional: interpreting real system state belongs behind approved Framework service boundaries, and your observations must be recorded separately unless an approved integration exists.

## Step 4 — Write a usable handover

Include: scope and consent; date, time and time zone; commands and resulting facts; precise source revision if inspecting Git; required evidence missing or NOT_RUN; actions you deliberately avoided; and the next person authorised to apply a change. Explain how your conclusion would change if the backup were stale or a required test never started.

## What the capstone does not prove

Passing sixteen tests demonstrates this model's tested cases; it does not certify security, Linux service health, Windows deployment or Umicom OS. A `README.md` restore drill is not a disaster-recovery qualification. An unchanged Framework branch is not proof a new application passed its tests. Honest boundaries are a core engineering result.

## Review questions

1. Which checks require real observations rather than fictional demonstration values?
2. How does C23 code prevent a malformed label from changing already collected evidence?
3. Why should an optional network outage produce a review rather than a hidden success?

**Answers:** All real support conclusions need real capture-specific evidence; the model validates before copying; optional adverse evidence remains visible to the reviewer.


## The Umicom Framework ownership rule

This chapter teaches a reproducible concept and, where applicable, uses a stand-alone learning-only model. Production tools must reuse Framework-owned VCS, build, diagnostics, process, security, storage and observability contracts before any new shared functionality is proposed. No PowerShell or Python implementation files are introduced.

## Safe completion criterion

Write one short paragraph distinguishing **observed facts**, **policy decisions** and **not-yet-verified outcomes**. Preserve the previous source and comments. If you cannot reproduce a result on your operating system, state the limitation rather than guessing.
