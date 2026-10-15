# Episode 135 — Build a C23 Operational Review Without Touching a Server

**Bits to Banking · Umicom Foundation · Stage 8**  
**Estimated length:** 11–15 minutes.  
**Presenter:** calm, professional instructor; appropriate for learners new to computers.  
**Visual material:** original Update 45 SVG diagrams; terminal demonstrations with private details omitted.

## Learning objective

Explain what each command means before showing it, distinguish an observation from a successful business outcome, and give students a safe exercise on a personal training computer.

## Scene-by-scene narration and visual directions

**0:00–2:00** — State the boundary: no real timer, SSH, credentials, firewall modifications, file restore or service management. Show the Update 39–44 C23 library chain.

**2:00–5:00** — Read `operations_review.h` and explain `BtbOpsInit`, `BtbOpsAttach`, `BtbOpsEvaluate`, `BtbOpsNextDue`, caller ownership, source identity and failure-atomic output.

**5:00–7:30** — In PowerShell use CMake/Ninja and CTest against the original prior labs; read actual registration counts, do not substitute sample code for missing previous sources.

**7:30–10:00** — Run demo: compare `REVIEWABLE`, `BLOCKED` without on-call owner, and `RESTORED_ONLY`. A classroom `REVIEWABLE` status cannot authorise deployment.

**10:00–12:30** — Run focused tests `source-mismatch`, `cadence-overflow`, `upstream-restored` and `mutations`; explain each refusal.

**Closing** — A learner submits a seven-day fictional operations plan and an incident note with incomplete evidence identified honestly.

## Production and accessibility notes

Show Windows Terminal and PowerShell 7 as different tools: the former hosts the latter. State explicitly that `PS C:\>` and `$` are prompts and must not be typed as part of a command. Use a clearly labelled Linux terminal for Linux sections. Provide captions, a pause point after each command and textual alternatives for diagrams. Never display live authentication tokens, real host addresses, customer data, private logs or personal identity details.

When a command fails, show the failure and explain what cannot be inferred from it. Do not disable a firewall, elevate permissions or edit a production service for the video. File-writing activities use only harmless learner-owned files.

## Review and student worksheet

1. Name a fact actually observed in the demonstration.
2. Identify one missing piece of evidence which prevents a confident claim.
3. State the role that would approve a real operational change.

**Source:** System Administration Stage 8 and the accompanying C23 engineering chapters. Real reusable software stays Umicom Framework-owned. No Python or PowerShell implementation scripts are delivered.
