# Episode 131 — Scheduled Does Not Mean Completed

**Bits to Banking · Umicom Foundation · Stage 8**  
**Estimated length:** 8–11 minutes.  
**Presenter:** calm, professional instructor; appropriate for learners new to computers.  
**Visual material:** original Update 45 SVG diagrams; terminal demonstrations with private details omitted.

## Learning objective

Explain what each command means before showing it, distinguish an observation from a successful business outcome, and give students a safe exercise on a personal training computer.

## Scene-by-scene narration and visual directions

**0:00–1:00** — Cold open: the Notes export calendar says 09:00 but the export folder is empty. Distinguish task configured, task activated and business output verified.

**1:00–3:30** — Windows: open Windows Terminal and PowerShell 7. Type `Get-ScheduledTask | Select-Object -First 8 TaskName, TaskPath, State`. Define pipe and selection. Explain why Ready is not Completed.

**3:30–5:30** — Linux: in a disposable VM enter `systemctl list-timers --all --no-pager` and `crontab -l`. Compare timer and service result. Missing user cron is not proof that no system jobs exist.

**5:30–7:30** — Review: create a fictional table with expected output, actual result, owner, evidence and next check. The Notes export is not qualified until a correct file is verified.

**Closing** — Ask learners to write why a triggered schedule is weaker evidence than a verified report.

## Production and accessibility notes

Show Windows Terminal and PowerShell 7 as different tools: the former hosts the latter. State explicitly that `PS C:\>` and `$` are prompts and must not be typed as part of a command. Use a clearly labelled Linux terminal for Linux sections. Provide captions, a pause point after each command and textual alternatives for diagrams. Never display live authentication tokens, real host addresses, customer data, private logs or personal identity details.

When a command fails, show the failure and explain what cannot be inferred from it. Do not disable a firewall, elevate permissions or edit a production service for the video. File-writing activities use only harmless learner-owned files.

## Review and student worksheet

1. Name a fact actually observed in the demonstration.
2. Identify one missing piece of evidence which prevents a confident claim.
3. State the role that would approve a real operational change.

**Source:** System Administration Stage 8 and the accompanying C23 engineering chapters. Real reusable software stays Umicom Framework-owned. No Python or PowerShell implementation scripts are delivered.
