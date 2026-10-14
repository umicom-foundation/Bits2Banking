# Episode 112 — Who runs a service, and what starts it?

**Bits to Banking · Umicom Foundation · Teaching script**  
**Presenter:** Sammy Hegab / Umicom contributors  
**Format:** 5–7-minute guided walkthrough · UK English  
**Linked chapters:** 50–53  
**Engineering policy:** Assembly and C23 for implementations; interactive PowerShell commands only; no new Python or PowerShell scripts.

## Teaching goal
Explain **who runs a service, and what starts it?** through a safe fictional Umicom Notes support task. Viewers should understand each observation, expected outcome, and why administrative changes require an authorised owner.

## Preparation and visual direction
Record a practice workstation rather than a production terminal. Use redacted sample output or a controlled training account. Show the complete command before pressing Enter, pause for viewers to type it, and zoom to the result without hiding errors. Do not show passwords, access tokens, real customer information or private log payloads.

## Scene-by-scene storyboard

### 00:00–00:45 · Identity question

**Screen / illustration:** Show normal user, restricted service and building-master-key icons.

**Narration:** The person who starts PowerShell is not automatically the account that runs a background service.

### 00:45–01:45 · Windows identity

**Screen / illustration:** Type `whoami`, then `Get-CimInstance Win32_Service -Filter "Name='EventLog'" | Select-Object Name, StartName, State`.

**Narration:** The first command shows your identity. The second shows a service configuration. The names may differ. Do not change permissions as a beginner exercise.

### 01:45–02:45 · Linux unit

**Screen / illustration:** Use `systemctl cat systemd-journald.service --no-pager` and find [Unit] and [Service].

**Narration:** A unit file describes lifecycle and policy. After= concerns ordering, not proof another programme completed useful work.

### 02:45–03:45 · Scheduling

**Screen / illustration:** Show `Get-ScheduledTask | Select-Object -First 5 TaskName, State` and `systemctl list-timers --all --no-pager`.

**Narration:** Scheduled work may exist even when it has never completed successfully. Read last-run evidence before drawing conclusions.

### 03:45–04:40 · Temporary configuration

**Screen / illustration:** Type `$env:UMICOM_LEARNING_MODE = "practice"`, read it, then `Remove-Item Env:UMICOM_LEARNING_MODE`.

**Narration:** This harmless variable belongs to our interactive shell. We created no script and made no permanent machine setting. Do not print secrets.

### 04:40–05:25 · Review

**Screen / illustration:** Point to the service identity and access-policy diagram.

**Narration:** Never grant broad administrator rights merely to resolve a file access error. Record evidence and follow the responsible owner's approval process.

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
