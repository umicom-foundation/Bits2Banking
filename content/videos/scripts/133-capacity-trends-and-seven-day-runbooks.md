# Episode 133 — From a Capacity Trend to a Practical Runbook

**Bits to Banking · Umicom Foundation · Stage 8**  
**Estimated length:** 8–11 minutes.  
**Presenter:** calm, professional instructor; appropriate for learners new to computers.  
**Visual material:** original Update 45 SVG diagrams; terminal demonstrations with private details omitted.

## Learning objective

Explain what each command means before showing it, distinguish an observation from a successful business outcome, and give students a safe exercise on a personal training computer.

## Scene-by-scene narration and visual directions

**Opening** — A fictional Notes queue grows 2 → 5 → 8 → 13 while CPU use seems ordinary. Ask what happens to oldest-job age and actual completion rate.

**2:00–4:00** — Run `Get-PSDrive -PSProvider FileSystem` on Windows and `df -h` on Linux. Explain used/free amounts, quotas and why resource types must not be confused.

**4:00–6:30** — Mark fictional points on the capacity SVG. Discuss assumptions and show why an unexpected import breaks a straight-line forecast.

**6:30–8:30** — Assemble a seven-day training runbook: daily queue/disk check, weekly backup evidence, monthly isolated restore and assigned response owner.

**Closing** — Students explain why purchasing CPUs might not fix a blocked storage adapter.

## Production and accessibility notes

Show Windows Terminal and PowerShell 7 as different tools: the former hosts the latter. State explicitly that `PS C:\>` and `$` are prompts and must not be typed as part of a command. Use a clearly labelled Linux terminal for Linux sections. Provide captions, a pause point after each command and textual alternatives for diagrams. Never display live authentication tokens, real host addresses, customer data, private logs or personal identity details.

When a command fails, show the failure and explain what cannot be inferred from it. Do not disable a firewall, elevate permissions or edit a production service for the video. File-writing activities use only harmless learner-owned files.

## Review and student worksheet

1. Name a fact actually observed in the demonstration.
2. Identify one missing piece of evidence which prevents a confident claim.
3. State the role that would approve a real operational change.

**Source:** System Administration Stage 8 and the accompanying C23 engineering chapters. Real reusable software stays Umicom Framework-owned. No Python or PowerShell implementation scripts are delivered.
