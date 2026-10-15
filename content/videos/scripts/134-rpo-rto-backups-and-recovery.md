# Episode 134 — A Backup Exists — Can You Restore It?

**Bits to Banking · Umicom Foundation · Stage 8**  
**Estimated length:** 10–14 minutes.  
**Presenter:** calm, professional instructor; appropriate for learners new to computers.  
**Visual material:** original Update 45 SVG diagrams; terminal demonstrations with private details omitted.

## Learning objective

Explain what each command means before showing it, distinguish an observation from a successful business outcome, and give students a safe exercise on a personal training computer.

## Scene-by-scene narration and visual directions

**0:00–2:30** — Draw a fictional timeline: verified backup at 09:00, outage at 09:18, service usable at 10:38. Explain separately the 18-minute data gap and 80-minute restoration time.

**2:30–5:30** — Demonstrate practice files only under `$HOME\UmicomTraining`: `Set-Content`, `Copy-Item` and `Get-FileHash -Algorithm SHA256`. Hash equality compares selected bytes; it is not a full database recovery guarantee.

**5:30–7:30** — On disposable Linux show `cp`, `sha256sum` and `cmp`. Do not request root and do not open any other person’s files.

**7:30–10:00** — Open restored copy from a separate training folder. Explain why real recovery also requires consistency, keys, permissions and useful application operation.

**10:00–12:00** — Explain why restoring the *old* release does not mean the *new* release passed. Preserve the failed-update evidence.

**Closing** — Learners compare a 20-minute loss with a 15-minute RPO and 130-minute recovery with a 120-minute RTO.

## Production and accessibility notes

Show Windows Terminal and PowerShell 7 as different tools: the former hosts the latter. State explicitly that `PS C:\>` and `$` are prompts and must not be typed as part of a command. Use a clearly labelled Linux terminal for Linux sections. Provide captions, a pause point after each command and textual alternatives for diagrams. Never display live authentication tokens, real host addresses, customer data, private logs or personal identity details.

When a command fails, show the failure and explain what cannot be inferred from it. Do not disable a firewall, elevate permissions or edit a production service for the video. File-writing activities use only harmless learner-owned files.

## Review and student worksheet

1. Name a fact actually observed in the demonstration.
2. Identify one missing piece of evidence which prevents a confident claim.
3. State the role that would approve a real operational change.

**Source:** System Administration Stage 8 and the accompanying C23 engineering chapters. Real reusable software stays Umicom Framework-owned. No Python or PowerShell implementation scripts are delivered.
