# Bits2Banking — Major Update 41

**Title:** System Administration — Managed Services, Change Windows and Recovery in C23  
**Owner:** Sammy Hegab · Umicom Foundation  
**Scope:** Education repository only; new files, no replacements or deletions.

## Learner-facing changes

The dedicated *System Administration From Zero* course now includes **60 sequential chapters**. New Chapters **49–60** cover service lifecycle and dependencies, service identity, Linux systemd unit files, Windows scheduled tasks and systemd timers, environment/configuration/secret boundaries, controlled software upgrades, health metrics, listener exposure, backup retention, verified restores, incident communication and an Umicom Notes maintenance capstone. Stage 4 includes a new workbook, glossary, instructor guide, safe-command reference and course overview.

The updated offline HTML course combines earlier 48 chapters with these 12; prior material is preserved, and the package also includes a copy of the new self-contained course under a new filename. Your original *Creating a New Umicom Application* beginner guide remains preserved in its earlier authoritative location and is not edited by this update.

## Engineering changes

Chapters **296–299** teach source-revision evidence, owned C23 value composition, failure-atomic state transitions, negative testing and Framework ownership. Episodes **111–115** accompany the lessons. Seven new SVG diagrams illustrate service dependencies, privilege boundaries, scheduling, effective configuration, network exposure, verified recovery and staged maintenance.

The `maintenance-review` laboratory composes the existing Update 39 evidence and Update 40 readiness libraries. It can record a fictional `ROLLBACK_REQUIRED` state and independent `RESTORED` result without changing operating-system state. It is intentionally **not** a production change manager, deployment tool, authorisation service, backup system or Git client. No scripting-language implementations were introduced.

## Verification boundaries

Focused C23 tests and sanitizers were exercised in the available Linux container. Windows UCRT64 compilation, full-site MkDocs build and any production Framework/OS integration are host acceptance gates that remain unverified here. See the validation report and `UPDATE_41_BUILD_TEST_AND_GIT.md` before publishing.
