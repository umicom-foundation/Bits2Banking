# System Administration: From Zero — Stage 3, Practical Infrastructure

**Bits to Banking · Umicom Foundation · Major Update 40**

This is **the third stage of a single 48-chapter course**, not a competing new course. Chapters 1–24 (Getting Started) and 25–36 (Intermediate Foundations) remain unchanged. This stage helps learners investigate everyday operating-system situations carefully before making changes. It is suitable for first-time learners, adults returning to computing and supervised younger students.

## Choose your starting point

- Never used a terminal? Begin at [Chapter 1](01-what-system-administrators-do.md) and follow the [beginner course index](index.md).
- Can read basic PowerShell and create your own files? Review [Chapter 24](24-capstone-your-first-support-check.md), then Chapters 25–36.
- Comfortable with user accounts, logs, backups and DNS? Continue with Chapter 37 below.
- Teaching a class? Read [Stage 3 Instructor Guide](advanced-instructor-guide.md) before running practical exercises.

## Stage 3 — Complete lesson sequence

- **37.** [Plan a safe home administration laboratory](37-plan-a-safe-home-administration-laboratory.md) — 55–75 minutes
- **38.** [Capture an operating-system baseline and recognise drift](38-capture-an-operating-system-baseline.md) — 50–70 minutes
- **39.** [Understand accounts, groups and scheduled work](39-accounts-groups-and-scheduled-work.md) — 60–80 minutes
- **40.** [Understand disks, volumes, filesystems and free space](40-understand-disks-volumes-and-free-space.md) — 55–80 minutes
- **41.** [Make and verify a recoverable practice backup](41-make-and-verify-a-recoverable-backup.md) — 65–90 minutes
- **42.** [Read access-control rules without changing them](42-read-access-control-without-changing-it.md) — 55–75 minutes
- **43.** [Follow one network request from a name to a port](43-follow-one-network-request-from-name-to-port.md) — 65–85 minutes
- **44.** [Understand firewalls and listening services without changing rules](44-understand-firewalls-and-listening-services.md) — 60–80 minutes
- **45.** [Recognise service health versus process state](45-recognise-service-health-versus-process-state.md) — 65–85 minutes
- **46.** [Plan software updates with approval, testing and rollback](46-plan-updates-with-an-approval-and-rollback-window.md) — 60–85 minutes
- **47.** [Build an incident timeline from logs and metrics](47-build-an-incident-timeline-from-logs-and-metrics.md) — 70–95 minutes
- **48.** [Capstone: support and verify a fictional Umicom service](48-capstone-support-and-verify-a-fictional-umicom-service.md) — 90–140 minutes

## How to study

Each lesson explains *what the idea means*, *why administrators need it*, a **Windows PowerShell 7** sequence, a **Linux terminal** sequence, expected results, common errors, a fictional Umicom scenario, exercises and suggested answers. Terminal commands are executed interactively; **no PowerShell or Python implementation scripts are introduced**.

The deliberate rule is **read first, change only in your own practice directory, and document the result**. The course does not ask students to restart services, lower firewall security, modify other people's permissions, force-push Git history or apply system-wide updates.

## Connected resources

- [Stage 3 practical workbook](advanced-workbook.md)
- [Stage 3 glossary](advanced-glossary.md)
- [Safe administration command reference](safe-command-reference.md)
- [Native C23 service-readiness laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/service-readiness) (reference for repository browsing; the site navigation can link the lab index separately).
- [Existing Umicom contributor guides](../06-umicom/24-development-setup.md)

**Course status:** Content delivered for offline study. Publishing in MkDocs requires a reviewed navigation merge and successful strict site build; the offline course is not proof of a live GitHub Pages deployment.
