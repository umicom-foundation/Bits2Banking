# Chapter 59 — Triage incidents and communicate with evidence

**System Administration From Zero · Stage 4 — Managed Services and Recovery**  
**Author:** Sammy Hegab · Umicom Foundation  
**Study time:** 70–90 minutes  
**Before starting:** Chapters 12, 23, 35 and 47: logs, systematic troubleshooting and incident timelines  
**Safety level:** observation-only on real systems; any practice writes are confined to a folder owned by the learner.

## What you will achieve

By the end of this chapter, you will be able to explain **triage incidents and communicate with evidence**, identify the difference between an observation and a change, and interpret at least one Windows and one Linux administration result. You will also be able to describe the evidence that an authorised Umicom support engineer would need before taking action.

## Why this matters in everyday computing

A technical problem may affect one user or hundreds. When somebody reports ‘Umicom Notes is down’, an administrator needs to identify the actual impact before changing settings. Is the app failing to start, unable to save, or simply slow? Has another system already changed? Which observations are factual, and which are only hypotheses?

This lesson teaches a calm, evidence-driven sequence: identify scope, record time, check current state, preserve relevant diagnostics, communicate uncertainty and escalate only to authorised owners. We do not collect confidential documents, share patient or financial data, restart services or perform unapproved forensic actions.

## A mental model you can remember

Think of a doctor taking observations before choosing a treatment. ‘The patient looks tired’ is not the same as a diagnosis. Likewise, a red error banner is a symptom. The incident timeline should separate what the user reported, what the administrator observed, what changed, what was tested and what remains unknown. Clear evidence shortens recovery time and prevents a second person repeating a risky experiment.

## New words, without jargon

| Term | Meaning |
|---|---|
| **Incident** | An unplanned interruption or reduction in expected service quality. |
| **Symptom** | What users or monitoring systems observe when something is wrong. |
| **Hypothesis** | A proposed explanation that has not yet been verified. |
| **Scope** | The users, components, locations and operations actually affected. |
| **Escalation** | Passing responsibility to an authorised specialist or decision owner. |
| **Timeline** | Time-ordered observations and actions with source, clock and outcome. |

## Windows practical lesson — PowerShell 7

Open **Windows Terminal → PowerShell**, or search for **PowerShell 7**. Type only the commands inside each box; the example `PS C:\...>` prompt is not part of a command. Unless a step explicitly says otherwise, use your normal non-administrator account. The commands are interactive teaching instructions, not a `.ps1` script.

### Step 1 — Record a timestamp

```powershell
Get-Date -Format o
```

**Expected result:** An ISO-style timestamp with timezone offset is printed.

**What it means:** An incident note should use a consistent time reference. Preserve the original timezone where possible.

**If it looks different:** Do not change the system clock to make log times appear to match.

### Step 2 — Inspect a known service without altering it

```powershell
Get-Service -Name EventLog | Select-Object Name, Status
```

**Expected result:** The current service state appears.

**What it means:** This is one observation. Do not conclude a fictional Notes fault originates in the Windows event log service merely because you checked it.

**If it looks different:** Do not restart the service without authorisation.

### Step 3 — Inspect a small selection of recent Windows System events

```powershell
Get-WinEvent -FilterHashtable @{LogName='System'; StartTime=(Get-Date).AddMinutes(-30)} -MaxEvents 5 | Select-Object TimeCreated, Id, LevelDisplayName
```

**Expected result:** Up to five recent visible events appear; there may be none or access may be restricted.

**What it means:** Read the event provider, time and meaning before associating it with the reported problem. Events can contain private details, so avoid copying full messages publicly.

**If it looks different:** If this query fails because the log is inaccessible, record that as a permission boundary.

### Step 4 — Check the local source repository without changing it

```powershell
git -C "C:\umicom\Umicom-Bits2Banking" status --short
```

**Expected result:** Modified or untracked paths appear if the repository exists.

**What it means:** This command is conditional on having the repository at that location. The result is not proof a runtime incident came from source edits.

**If it looks different:** On another machine, use the actual authorised repository path or skip this step.

### Step 5 — Read the command help for a suspected tool

```powershell
Get-Help Get-WinEvent -Examples
```

**Expected result:** Usage examples are shown when the help content is installed.

**What it means:** Use help to understand an unfamiliar command before changing anything.

**If it looks different:** If help is incomplete, `Get-Help Get-WinEvent -Online` opens documentation but requires network access.

## Linux practical comparison

On a Linux computer or an authorised virtual machine, open a terminal. These are **Bash-compatible commands**; do not type the `$` prompt. A minimal container, Chromebook or non-systemd distribution may have a different set of tools. A missing optional tool should be recorded rather than bypassed.

### Linux step 1 — Capture the current clock

```bash
date --iso-8601=seconds
```

**Expected result:** A local timestamp is printed on GNU/Linux.

**Interpretation:** Record the timezone in the incident timeline.

### Linux step 2 — Inspect recent journal entries

```bash
journalctl --since '30 minutes ago' -n 10 --no-pager
```

**Expected result:** Up to ten accessible entries appear, or permission restrictions are reported.

**Interpretation:** Log entries may contain private host details. Share only a redacted, relevant excerpt with authorised people.

### Linux step 3 — Check a service's state

```bash
systemctl status systemd-journald.service --no-pager
```

**Expected result:** Systemd prints unit status if available.

**Interpretation:** A service can be active while the reported business function is unavailable. Compare with functional evidence.

## Worked support scenario — Umicom Notes

A class tutor reports that Umicom Notes cannot save practice homework for one student. Other students can save normally. The volunteer records the error time and which account is affected, tests only the student's own practice folder under supervision, and observes that storage permissions differ. They do not reset everyone’s passwords or delete shared caches. The support note separates ‘one user affected’ from ‘all services down’ and routes the permission review to the right owner.

**Evidence record:** In your own words, describe the issue, the observation time, the command used, what you actually saw, what you have *not* proved, and who would approve a change. Avoid copying usernames, credentials, private filenames, IP addresses or confidential logs into public notes.

## Common mistakes and how to correct them

| Misunderstanding | Better interpretation |
|---|---|
| The first error message identifies the root cause. | An error can be a downstream symptom. Trace dependencies and changes. |
| More logs always make a better report. | Share only relevant, redacted evidence. Excess logs can leak data and obscure the sequence. |
| An administrator should fix incidents before telling users anything. | Timely, accurate scope and uncertainty updates reduce confusion and duplicate work. |

## Guided practice and suggested responses

**Exercise 1.** Create an incident record template.

*Suggested response:* Include unique reference, start time, affected function, observed evidence, actions, owner and next update.

**Exercise 2.** Write one factual and one hypothetical sentence.

*Suggested response:* Example: ‘Save returned an access error at 10:12’ is factual; ‘a policy change caused it’ is a hypothesis.

**Exercise 3.** Practice an escalation summary.

*Suggested response:* Explain what was checked, what was not checked and why a privileged action needs approval.

## Questions for discussion

1. Which part of today's triage incidents and communicate with evidence exercise was **read-only**, and how do you know?
2. What does a successful command prove, and what would it *not* prove?
3. Explain **Incident** to somebody who has never opened a terminal.
4. If an expected result does not appear, what evidence would you collect before changing anything?
5. How would you explain this issue to a colleague without exposing private data?

## Connection to Umicom Framework and software engineering

Use the Framework's structured logging, diagnostic correlation and audit boundaries when producing real incident evidence. Do not grant AI agents, learning labs or thin applications unrestricted repair authority. The C23 maintenance-review lab deliberately records staged decisions and cannot change a host.

## Further reading (optional internet access)

- https://learn.microsoft.com/powershell/module/microsoft.powershell.diagnostics/get-winevent
- https://www.freedesktop.org/software/systemd/man/latest/journalctl.html

## Learning checkpoint

You are ready to proceed if you can explain **the command, its expected output, the boundary of what it proves, and a safe response to unexpected output**. If the exercise needed unavailable administrator access, record *not performed*; do not mark it as passed.

**Next:** [Chapter 60 — Capstone: plan, review and recover a fictional Umicom Notes change](./60-capstone-plan-review-and-recover-umicom-notes.md).
