# Episode 114 — Observe, diagnose and escalate without deleting evidence

**Bits to Banking · Umicom Foundation · Teaching script**  
**Presenter:** Sammy Hegab / Umicom contributors  
**Format:** 5–7-minute guided walkthrough · UK English  
**Linked chapters:** 54–56, 59  
**Engineering policy:** Assembly and C23 for implementations; interactive PowerShell commands only; no new Python or PowerShell scripts.

## Teaching goal
Explain **observe, diagnose and escalate without deleting evidence** through a safe fictional Umicom Notes support task. Viewers should understand each observation, expected outcome, and why administrative changes require an authorised owner.

## Preparation and visual direction
Record a practice workstation rather than a production terminal. Use redacted sample output or a controlled training account. Show the complete command before pressing Enter, pause for viewers to type it, and zoom to the result without hiding errors. Do not show passwords, access tokens, real customer information or private log payloads.

## Scene-by-scene storyboard

### 00:00–00:40 · Support ticket

**Screen / illustration:** Show a fictional ticket: Notes cannot save, other applications work.

**Narration:** We need scope and timing before a repair. An error message is a symptom, not necessarily a root cause.

### 00:40–01:25 · Capture time and state

**Screen / illustration:** Show `Get-Date -Format o` and `Get-Service -Name EventLog | Select-Object Name,Status`.

**Narration:** Write down when the observation was made and what it proves. This service status is not a diagnosis of Notes.

### 01:25–02:20 · Inspect network scope

**Screen / illustration:** Show `Get-NetTCPConnection -State Listen | Select-Object -First 8 LocalAddress,LocalPort`.

**Narration:** 127.0.0.1 stays on the local host; 0.0.0.0 is a wildcard bind. Never disable a firewall as a first troubleshooting step.

### 02:20–03:15 · Evidence versus hypothesis

**Screen / illustration:** Display ‘Save returned access denied at 10:12’ versus ‘a recent policy change caused it’.

**Narration:** The first can be a recorded observation; the second is a hypothesis until verified. Keep them separate.

### 03:15–04:10 · Review version baseline

**Screen / illustration:** Show git --version, cmake --version and winget list --id Git.Git --exact.

**Narration:** A newer package listing is not permission to upgrade a shared workstation. Capture compatibility information first.

### 04:10–05:05 · Escalate clearly

**Screen / illustration:** Show a six-field support note: time, scope, observed, tested, not tested, owner.

**Narration:** Share relevant redacted evidence only. Ask for approval before changing service identities, permissions or startup policy.

## Live demonstration checks
Before concluding, identify each operation as read-only, an authorised write to the learner’s practice folder, or a simulation. If a tool is not available, state **not performed**; do not invent a successful screenshot.

## Viewer assignment
1. Explain the difference between an observation and an action in this episode.
2. Name one thing a successful command proves and one thing it does not prove.
3. Write a four-sentence support note for the fictional Umicom Notes situation without including private data.

## Suggested instructor responses
A command that reports status is an observation. Copying a practice note creates controlled training data. A simulated maintenance model changes its own in-memory state but does not modify a real service. A trustworthy support report includes time, scope, evidence and next authorised owner.

## Accessibility and publication notes
Include subtitles, pronounce CLI as “command-line interface”, do not rely on colour alone for blocked/ready state, show monospaced commands at readable size, and link the corresponding Markdown chapter and C23 source. Record actual tool versions when publishing.
