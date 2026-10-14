# Episode 115 — C23 capstone: simulate a safe Umicom maintenance window

**Bits to Banking · Umicom Foundation · Teaching script**  
**Presenter:** Sammy Hegab / Umicom contributors  
**Format:** 5–7-minute guided walkthrough · UK English  
**Linked chapters:** 60 and 296–299  
**Engineering policy:** Assembly and C23 for implementations; interactive PowerShell commands only; no new Python or PowerShell scripts.

## Teaching goal
Explain **c23 capstone: simulate a safe umicom maintenance window** through a safe fictional Umicom Notes support task. Viewers should understand each observation, expected outcome, and why administrative changes require an authorised owner.

## Preparation and visual direction
Record a practice workstation rather than a production terminal. Use redacted sample output or a controlled training account. Show the complete command before pressing Enter, pause for viewers to type it, and zoom to the result without hiding errors. Do not show passwords, access tokens, real customer information or private log payloads.

## Scene-by-scene storyboard

### 00:00–00:55 · Change request

**Screen / illustration:** Display the imaginary Umicom Notes change and distinct reviewer/operator labels.

**Narration:** The lab does not approve a real change. It models what a responsible review must consider.

### 00:55–01:50 · Read the existing modules

**Screen / illustration:** Open admin_evidence.h, service_readiness.h and maintenance_review.h.

**Narration:** One library owns supplied observations, one handles prerequisites, and one reviews the change. We did not copy old code or create a production service manager.

### 01:50–02:45 · Configure and compile

**Screen / illustration:** From the Bits2Banking root show the documented CMake Ninja commands for labs/native/maintenance-review.

**Narration:** Use the exact compiler path from the Windows chapter when required. Stop and investigate if configuration fails; never fabricate a missing dependency.

### 02:45–03:35 · Run automated tests

**Screen / illustration:** Run CTest and pause at the final count.

**Narration:** The reconstructed lab registers 57 tests, including unchanged evidence and readiness regressions. Not Run must never be counted as Passed.

### 03:35–04:35 · Run the demonstration

**Screen / illustration:** Show btb-maintenance-review-demo reporting ROLLBACK_REQUIRED and then RESTORED.

**Narration:** The fictional upgrade failed verification. A distinct capture allowed the simulated restoration to be recorded. RESTORED is not COMPLETE.

### 04:35–05:20 · Review and commit

**Screen / illustration:** Show git status, git add -A, diff --cached --check, commit and push for Bits2Banking only.

**Narration:** Do not change Framework or OS for a teaching batch. Preserve comments, original chapters and test evidence.

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
