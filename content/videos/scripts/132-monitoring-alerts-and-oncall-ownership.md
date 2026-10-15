# Episode 132 — An Alert Needs an Owner and an Outcome

**Bits to Banking · Umicom Foundation · Stage 8**  
**Estimated length:** 9–12 minutes.  
**Presenter:** calm, professional instructor; appropriate for learners new to computers.  
**Visual material:** original Update 45 SVG diagrams; terminal demonstrations with private details omitted.

## Learning objective

Explain what each command means before showing it, distinguish an observation from a successful business outcome, and give students a safe exercise on a personal training computer.

## Scene-by-scene narration and visual directions

**0:00–1:00** — User symptom: Notes Save hangs; the application process still exists. Ask whether process existence proves business readiness. Answer no.

**1:00–3:30** — PowerShell: `Get-Process | Sort-Object CPU -Descending | Select-Object -First 5 Name, Id, CPU`. Explain that CPU is accumulated time, not current utilisation percentage. On Linux compare `free -h`, `df -h` and `uptime`.

**3:30–5:30** — Use the Monitoring to Action diagram. Explain metric, threshold, alert, acknowledgement and independently checked outcome. A threshold is a review trigger, not automatically a diagnosis.

**5:30–8:00** — Construct an actionable fictional Notes save alert with service, affected users, timestamp, known evidence, unknowns, primary owner and deputy. No private information is displayed.

**8:00–9:00** — Final handover: students separate fact, hypothesis and decision in a six-line report.

## Production and accessibility notes

Show Windows Terminal and PowerShell 7 as different tools: the former hosts the latter. State explicitly that `PS C:\>` and `$` are prompts and must not be typed as part of a command. Use a clearly labelled Linux terminal for Linux sections. Provide captions, a pause point after each command and textual alternatives for diagrams. Never display live authentication tokens, real host addresses, customer data, private logs or personal identity details.

When a command fails, show the failure and explain what cannot be inferred from it. Do not disable a firewall, elevate permissions or edit a production service for the video. File-writing activities use only harmless learner-owned files.

## Review and student worksheet

1. Name a fact actually observed in the demonstration.
2. Identify one missing piece of evidence which prevents a confident claim.
3. State the role that would approve a real operational change.

**Source:** System Administration Stage 8 and the accompanying C23 engineering chapters. Real reusable software stays Umicom Framework-owned. No Python or PowerShell implementation scripts are delivered.
