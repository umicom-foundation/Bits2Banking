# Episode 129 — Logs, recovery and privacy in an Umicom incident

**Bits2Banking · Umicom Foundation · 8–10 minutes**  
**Companion:** System Administration Chapters 94–95; audit/retention and independent recovery diagrams.

## Goal

Teach beginners to build a trustworthy incident timeline, protect private log information, and distinguish backup copies from restored business functionality.

### 00:00–02:20 — What is a trustworthy observation?

**Visual:** Fictional Umicom Bank report request with an access-denied observation, then a dashboard showing the workstation process still running.

**Narration:** “Two things can be true at once: the program exists, and a user's report request fails. A log entry is evidence about an event, not a complete explanation of why it happened. We must separate source facts from our hypotheses.”

Explain event IDs, times with offsets, correlation values and an owner. Read a few *non-sensitive* local event headers using `Get-WinEvent ... | Select-Object TimeCreated, Id` or limited `journalctl` output. Do not claim these machine events came from Umicom unless the actual source proves it.

### 02:20–04:10 — Protect evidence

**Visual:** Redacted report replacing account names, private addresses and tokens with `[redacted]` while retaining the event category, timestamp and status.

**Narration:** “A support report is not safer because it contains every raw detail. Keep enough to investigate, but do not reveal passwords, patient records, account numbers or private keys. Retention and authorised access are part of good operational design.”

**Viewer task:** Identify which fields could be shared publicly from a fictional event and which belong only in a protected incident workspace.

### 04:10–06:50 — Recovery is an independent test

**Visual:** Update → failure → approved rollback → restore → business verification → incident report.

**Demonstration:** Using only a personal training folder, compare `notes-training.baseline.conf` with `notes-training-restored.conf` using SHA-256. Explain that byte equality does **not** prove the Umicom Notes program has been restarted or that real financial obligations were reconciled.

**Narration:** “A failed upgrade can be followed by a successful return to the previous release. That is good recovery, but it does not make the failed new version successful. Keep both results on record.”

### 06:50–08:50 — Hand over the incident

Show a report with incident time, service, observations, limitations, completed recovery check, pending business test, reviewer and next action. Require the learner to mark one item **Not verified** rather than forcing the table to green.

**Safety:** No real application restart, log deletion, account change, network command or restore to production occurs during this lesson.
