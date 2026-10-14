# Episode 111 — A service can be running and still fail its job

**Bits to Banking · Umicom Foundation · Teaching script**  
**Presenter:** Sammy Hegab / Umicom contributors  
**Format:** 5–7-minute guided walkthrough · UK English  
**Linked chapters:** 49, 51  
**Engineering policy:** Assembly and C23 for implementations; interactive PowerShell commands only; no new Python or PowerShell scripts.

## Teaching goal
Explain **a service can be running and still fail its job** through a safe fictional Umicom Notes support task. Viewers should understand each observation, expected outcome, and why administrative changes require an authorised owner.

## Preparation and visual direction
Record a practice workstation rather than a production terminal. Use redacted sample output or a controlled training account. Show the complete command before pressing Enter, pause for viewers to type it, and zoom to the result without hiding errors. Do not show passwords, access tokens, real customer information or private log payloads.

## Scene-by-scene storyboard

### 00:00–00:40 · The question

**Screen / illustration:** Show a fictional Umicom Notes window: Save reports a storage failure.

**Narration:** A process being present is one fact. Saving a document is a different fact. They must not be confused.

### 00:40–01:35 · Introduce services

**Screen / illustration:** Overlay the service-layer diagram and explain the dependency arrows.

**Narration:** A service manager may confirm the programme started. A correct application also needs a working storage dependency. A healthy-looking icon cannot replace that proof.

### 01:35–02:45 · Windows observation

**Screen / illustration:** Open PowerShell 7 and type `Get-Service -Name EventLog | Select-Object Name, Status, StartType`.

**Narration:** We are reading a standard service. We are not stopping it. Running indicates the service manager sees it active; it does not prove every event write succeeds.

### 02:45–03:45 · Linux comparison

**Screen / illustration:** In a Linux terminal show `systemctl status systemd-journald.service --no-pager`.

**Narration:** On a systemd host this is a service status observation. Another Linux distribution may not use systemd. Do not change service settings to make a lesson screenshot match.

### 03:45–05:00 · Umicom connection

**Screen / illustration:** Open `service_readiness.h`; point to `BtbServiceGraphEvaluate` and the dependency mask.

**Narration:** The C23 model requires actual evidence about its prerequisites. Notes is not ready if storage is blocked. This is an offline teaching model, not a real service controller.

### 05:00–05:40 · Pause and explain

**Screen / illustration:** Show a two-column table: process exists / task works.

**Narration:** State what each command proves and one further safe check. Restarting real services is not an assignment.

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
