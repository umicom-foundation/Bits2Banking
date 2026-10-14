# System Administration — Part II: Practical Operations

**Continuation of the dedicated [System Administration: From Zero](index.md) course.**

This is the intermediate foundations track. It is intentionally written so that a learner who has completed Chapters 1–24 can continue in order. If you are completely new, begin with Chapter 1 and treat every command as an individual step to understand, not a block to paste blindly.

## Learning path

- [25. Users, groups and why identity matters](25-users-groups-and-real-identity.md) — 45–65 minutes.
- [26. Understand file permissions without opening private data](26-understand-ntfs-and-linux-permissions.md) — 50–75 minutes.
- [27. Investigate a Windows service and its event records](27-windows-service-diagnosis-and-event-evidence.md) — 45–70 minutes.
- [28. Understand Linux systemd units, logs and safe inspection](28-linux-systemd-units-and-journal-logs.md) — 45–65 minutes.
- [29. Plan software updates and understand the change window](29-plan-windows-and-linux-software-updates.md) — 45–70 minutes.
- [30. SSH: encrypted remote access, identity keys and host trust](30-understand-ssh-host-keys-and-safe-remote-access.md) — 50–80 minutes.
- [31. Diagnose DNS, TCP ports and firewall boundaries](31-diagnose-dns-tcp-and-firewall-boundaries.md) — 55–85 minutes.
- [32. Understand disk space, filesystems and safe capacity checks](32-storage-space-filesystems-and-disk-health.md) — 45–70 minutes.
- [33. Backups, restore drills and proving that recovery works](33-backups-restore-drills-and-verification.md) — 60–90 minutes.
- [34. Protect credentials, use MFA and practise least privilege](34-passwords-mfa-least-privilege-and-secrets.md) — 45–70 minutes.
- [35. Read system metrics, logs and an incident timeline](35-monitor-metrics-logs-and-incident-timelines.md) — 50–80 minutes.
- [36. Capstone: investigate and hand over a support incident](36-capstone-a-safe-umicom-support-runbook.md) — 70–110 minutes.

## Study discipline

1. Use a normal account and a dedicated personal learning folder.
2. Read each step, classify it as observation or modification, then execute only with appropriate permission.
3. Compare actual output with the expected result. “Not supported”, “Access Denied” and “Not Run” are evidence, not instructions to bypass controls.
4. Practise backups on a harmless file you own; do not copy beneficiary records, production credentials or customer documents.
5. Explain the outcome using ordinary words before proceeding to more advanced work.

## Resources

- [Course glossary](glossary.md) — definitions from the original chapters.
- [Part II glossary](intermediate-glossary.md) — additional administration and security terms.
- [Intermediate workbook](intermediate-workbook.md) — tasks with verifiable results.
- [Instructor support](intermediate-instructor-guide.md) — accessible delivery and safety notes.
- [Native C23 evidence laboratory](../../labs/index.md) — C23 teaching tooling belongs in the lab area; see `labs/native/sysadmin-evidence/README.md` in the repository.
- [Original Umicom project creation guide](../../assets/reference/umicom-new-project-beginner-guide-original.html) — the supplied reference from Update 38, retained unchanged.

**Important:** the offline HTML publication for Update 39 includes Chapters 1–36 without modifying the original 24 lesson files. The MkDocs navigation must be reviewed with the included Update 39 snippet before publishing.
