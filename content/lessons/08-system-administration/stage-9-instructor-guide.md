# Stage 9 instructor guide — teach evidence before administration privileges

**Audience:** mixed ages and backgrounds, including adults revisiting system administration and younger students supervised at a practice workstation.

## Classroom method

Each session should follow five steps: (1) define the relevant terminology using a familiar example, (2) show a labelled screenshot or original diagram, (3) demonstrate one observational command, (4) ask the learner to explain the fields and limitations, (5) assess what the learner would do when the command is missing, refused or contradictory. Do not require uniform output from different Windows and Linux computers.

## Safety rules for the class

No production machines, remote network scanning, firewall disablement, service restarts, partition edits or credentials are required. A learner may be unable to access journals or hardware metadata. This is a valid result and should be recorded, not bypassed. Chapter 117 writes only a practice document under the user's home directory and restores to another practice folder; require confirmation that the path is not production. Explain that a checksum and a functional recovery test answer different questions.

## Assessment rubric (20 points)

| Criterion | Points | What earns full credit |
|---|---:|---|
| Terminology | 4 | Accurately distinguishes host, service, package, filesystem and business operation. |
| Reproducibility | 4 | Records exact command, host and offset-aware time. |
| Interpretation | 4 | Separates observed state, hypothesis, and missing evidence. |
| Recovery judgement | 4 | Correct RPO/RTO decisions and `RESTORED_ONLY` vs failed release. |
| Safety | 4 | Read-only investigation, permission check, privacy and independent review. |

At least 3/4 in safety is required for a passing practical assessment. No credit for performing an unauthorised write action even if the resulting screenshot appears correct.

## Troubleshooting discussion prompts

- “Get-Service says Running: why can Notes still be unavailable?” Look for failed storage or business operations.
- “The storage log is one minute earlier: does that prove it caused the incident?” Look for clock skew and independent verification.
- “A backup file and SHA-256 exist: has recovery been demonstrated?” Look for an isolated restore and application-level checks.
- “The previous release works after rollback: did the attempted release pass?” Expected answer: No.

An instructor can encourage capable learners to explore Umicom Framework interfaces for VCS and build automation but should not introduce a second implementation or a general-purpose administration script to make a lesson easier.
