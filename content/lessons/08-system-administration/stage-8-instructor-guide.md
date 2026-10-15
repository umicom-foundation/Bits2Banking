# Stage 8 instructor guide — teaching across ages and backgrounds

**Umicom Foundation · Bits2Banking · System Administration From Zero**

This stage is designed for adults beginning a technical career, students, older learners refreshing their knowledge, and younger participants working with a trusted instructor. The language should be accessible, but the engineering standards must not be simplified into incorrect claims.

## Before learners enter the room

Provide a training account with no administrative privileges, a local terminal or Windows PowerShell 7, a practice directory beneath each learner's home directory and a copy of the course. Never distribute shared administrator passwords or expose a production system to an exercise. Linux access is optional; equivalent paper exercises are acceptable when no disposable guest is available.

The course can be completed without creating scheduled tasks, installing packages or opening a real network connection. If a command is not supported on the chosen host, explain the difference and use the instructor workstation to show redacted screenshots. A failed command is often a useful teaching moment about operating-system boundaries.

## Suggested six-session timetable

| Session | Chapters | Learning result | Approximate time |
|---|---|---|---|
| 1 | 97–99 | Compare Windows tasks, cron and systemd timers; locate evidence | 75 min |
| 2 | 100–102 | Turn observations into an owned incident and useful alert | 90 min |
| 3 | 103–104 | Explain RPO, RTO and perform a harmless file restore drill | 90 min |
| 4 | 105–106 | Design UTC maintenance window and three-host inventory | 75 min |
| 5 | 107 | Explain service-account least privilege, privacy and audit | 60 min |
| 6 | 108 and 312–315 | Complete capstone; optionally build/test the C23 lab | 105 min |

Shorten sessions and use breaks for younger learners. Use a **paired reading** method: the learner predicts what a command will show, the instructor explains the arguments, and the learner interprets the result. Avoid “type a long command and hope” demonstrations.

## Rubric

A strong response identifies the evidence source, explains its limitations, distinguishes observation from action, has an owner, and provides a safe next step. It does not claim that a running process, successful checksum or green scheduler entry proves full service recovery. Assign points for accurate uncertainty, not mere confidence.

For the capstone, use ten criteria worth one point each: host identity, service dependencies, schedule, checkpoint evidence, alert owner, capacity trend, RPO, RTO, restoration verification and honest outcome classification. **7/10 with no unsafe actions** is a reasonable course completion target. A dangerous action proposal requires correction even if the written score is high.

## Common misconceptions to address

- **Windows Terminal is not PowerShell:** the window hosts a shell; PowerShell 7 is started with `pwsh` where installed.
- **Scheduled ≠ ran ≠ succeeded:** three separate facts need evidence.
- **Backup created ≠ recoverable:** a controlled restore must be exercised.
- **RPO ≠ RTO:** data-loss age and time to useful recovery are separate.
- **Git commit ≠ deployment qualification:** the source revision must be built, tested, staged and operationally checked.
- **Rollback ≠ successful upgrade:** preserve both outcomes.

## Source and engineering governance

The optional laboratory links the existing C23 security-operations module from Update 44. It adds an offline policy adapter; it does not implement an operating-system scheduler, network or backup engine. For real Umicom work, inspect and reuse Framework's scheduling, observability, identity, audit and change-management services. PowerShell remains an interactive command teaching environment rather than a project implementation language.
