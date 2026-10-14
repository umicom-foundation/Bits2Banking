# Bits2Banking — Roadmap after Major Update 41

| Course stage | Chapters | Status | Expected outcomes |
|---|---|---|---|
| Absolute beginner foundations | 1–24 | Previously delivered (Update 38) | Terminal, folders, package management, Git, basic C23 |
| Intermediate administration | 25–36 | Previously delivered (Update 39) | Identity, Linux/Windows services, SSH, backups, security |
| Practical infrastructure | 37–48 | Previously delivered (Update 40) | Baselines, metrics, DNS, storage, safe backup and incident traces |
| Managed services and recovery | **49–60** | **Delivered in Update 41** | Service identity, scheduling, monitoring, config, retention, post-change verification, offline C23 model |
| Applied Umicom platform operations | **61–72** | Planned, not implemented | Safe VM and QEMU training, package/install acceptance, Framework/OS userspace supervision, auditable release integration |

**Next: Major Update 42 — Reproducible Training Environments and Safe Service Deployment.** Continue Chapters 61–72 and Engineering Chapters 300 onwards. Proposed content: VM and QEMU isolation, Linux user-space baseline, Windows application packaging, service configuration, supervised deployment, immutable environment snapshots, controlled install/uninstall, read-only diagnostic evidence and recovery drills. Every new native capability must be assessed against existing Umicom Framework contracts before implementation.

**Standing policy:** C23 and Assembly first. Do not implement functionality with Python, PowerShell or other scripts. Preserve all existing source, comments, documentation, lessons and public APIs; use Framework first and applications as thin consumers. PowerShell remains appropriate for interactive user instructions.
