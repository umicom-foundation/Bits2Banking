# Episode 113 — A backup copy is not proven until it restores

**Bits to Banking · Umicom Foundation · Teaching script**  
**Presenter:** Sammy Hegab / Umicom contributors  
**Format:** 5–7-minute guided walkthrough · UK English  
**Linked chapters:** 57–58  
**Engineering policy:** Assembly and C23 for implementations; interactive PowerShell commands only; no new Python or PowerShell scripts.

## Teaching goal
Explain **a backup copy is not proven until it restores** through a safe fictional Umicom Notes support task. Viewers should understand each observation, expected outcome, and why administrative changes require an authorised owner.

## Preparation and visual direction
Record a practice workstation rather than a production terminal. Use redacted sample output or a controlled training account. Show the complete command before pressing Enter, pause for viewers to type it, and zoom to the result without hiding errors. Do not show passwords, access tokens, real customer information or private log payloads.

## Scene-by-scene storyboard

### 00:00–00:45 · The missing notebook

**Screen / illustration:** Show one Notes file and two copies on the same physical disk.

**Narration:** Two files on one disk do not protect against disk failure. A backup strategy needs independence, retention, access policy and tested recovery.

### 00:45–01:40 · Create practice content

**Screen / illustration:** Create a private UmicomLearning/BackupStudy folder and write one fictional Notes line with Set-Content.

**Narration:** Only use a training path you own. We do not open patient records or copy anyone else's files.

### 01:40–02:35 · Copy and verify

**Screen / illustration:** Use Copy-Item to create notes-copy.txt and Get-FileHash -Algorithm SHA256 on both paths.

**Narration:** Matching digests show selected files contain the same bytes. They do not prove a database or application can recover.

### 02:35–03:35 · Restore separately

**Screen / illustration:** Create RestoreStudy, copy the backup into notes-restored.txt, compare SHA-256 and read the contents.

**Narration:** A restore drill needs an independent destination and a content check. The original remains untouched.

### 03:35–04:30 · Explain RPO and RTO

**Screen / illustration:** Show a diagram of backup points and downtime.

**Narration:** RPO asks how much recent data may be lost. RTO asks how long recovery may take. A daily backup cannot satisfy an hourly recovery point objective alone.

### 04:30–05:15 · Exercise and caution

**Screen / illustration:** Ask students to design three independent copies for a school notebook.

**Narration:** Production Umicom data belongs behind Data Server recovery boundaries. Copying a single executable is not safe database recovery.

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
