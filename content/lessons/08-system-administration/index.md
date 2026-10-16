# System Administration — From Zero

**A dedicated Bits2Banking course for absolute beginners and returning learners.**

Start with no assumed knowledge. Learn the tools, understand the environment, practise on your own data, and gain the skills needed to contribute confidently to the Umicom ecosystem.

> **Safety rule:** all exercises default to a normal user account and a personal practice folder (`$HOME\UmicomLearning` on Windows; `$HOME/UmicomLearning` on Linux). No production system or Umicom repository needs to be changed.

## What makes this course different

- Commands are shown exactly as they should be entered, with their shell clearly labelled.
- Every practical step describes the expected outcome and how to recognise an error.
- Windows and Linux coverage distinguish what can and cannot be translated directly.
- The course uses realistic Notes, training, educational service and Umicom development examples.
- Permissions, data protection, backups, reproducibility and honest evidence are taught from the beginning.
- No new PowerShell or Python implementation scripts are introduced; the native laboratory uses C23.

## Course map

### Orientation and terminals

- [01. What does a system administrator do?](01-what-system-administrators-do.md)
- [02. Understand the computer, operating system and user account](02-computer-os-and-user-accounts.md)
- [03. Open PowerShell 7 or the Linux terminal without confusion](03-open-powershell-or-linux-terminal.md)
- [04. Read a command, its arguments and the help system](04-read-commands-options-and-help.md)

### Files, tools and identity

- [05. Folders, file paths and your own safe practice workspace](05-folders-paths-and-safe-workspace.md)
- [06. Create, open and read text files without scripting](06-create-open-and-read-text-files.md)
- [07. Copy, rename and remove files carefully](07-copy-move-delete-with-rollback.md)
- [08. Install and verify PowerShell 7, Git and development tools](08-install-programmes-and-verify-tools.md)
- [09. Users, administrators and the meaning of permissions](09-accounts-permissions-least-privilege.md)

### Windows processes, services and evidence

- [10. Processes: what is running on your computer?](10-understand-running-processes.md)
- [11. Windows services: background programs and startup](11-windows-services-and-startup.md)
- [12. Windows Event Viewer and useful troubleshooting records](12-read-windows-events-and-logs.md)
- [13. Inspect processor, memory, Windows version and resources](13-inspect-hardware-memory-and-os.md)
- [14. Disks, backups and checking that restoration works](14-disks-backups-and-restore-verification.md)

### Networks and Linux administration

- [15. IP addresses, networks, DNS and ports](15-ip-dns-ports-and-the-internet.md)
- [16. Troubleshoot a failed connection one layer at a time](16-diagnose-dns-firewall-and-connections.md)
- [17. Linux terminal, home directory, files and processes](17-linux-terminal-files-and-processes.md)
- [18. Linux permissions, packages, services and logs](18-linux-users-permissions-packages-logs.md)

### Git, Umicom and professional practice

- [19. Git from zero: create, inspect, stage and commit](19-git-local-repository-and-first-commit.md)
- [20. GitHub: authenticate, publish and collaborate responsibly](20-github-cli-publish-and-collaborate.md)
- [21. Create a new Umicom application: repositories, modules and discovery](21-new-umicom-application-module-and-discovery.md)
- [22. Build, test and inspect a read-only C23 program](22-c23-build-tests-and-safe-inspection.md)
- [23. Troubleshoot problems systematically and write useful evidence](23-systematic-troubleshooting-and-reporting.md)
- [24. Capstone: perform a safe support check from start to finish](24-capstone-your-first-support-check.md)

## Course resources

- [Full glossary](glossary.md) — words that appear in Windows, Linux, PowerShell, Git and Umicom work.
- [Practice workbook and final assessment](workbook-and-assessment.md) — checked outcomes and a support report template.
- [Instructor/mentor instructions](instructor-notes.md) — safe classroom delivery and accessibility.
- [Original contributed project-creation guide](../../assets/reference/umicom-new-project-beginner-guide-original.html) — preserved as supplied; distinguish current procedures from future proposed automation.

## Suggested schedule

| Week | Focus | Outcome |
|---|---|---|
| 1 | Chapters 1–6 | Open the correct shell, organise a safe workspace, read text. |
| 2 | Chapters 7–12 | Work carefully with files, identity, running processes, services and logs. |
| 3 | Chapters 13–18 | Inspect hardware, backups, networks and Linux. |
| 4 | Chapters 19–24 | Create a local Git history, understand GitHub, build C23 and complete a support handover. |

### Assessment standard

A learner completes the course by demonstrating each observed result, identifying when a step is **not verified**, and explaining how to avoid changing systems they do not own. Speed and memorisation are not the criteria.

## More practice: troubleshooting without guessing

After you have practised the introductory course, try two further investigations. They are read-only exercises suitable for your own computer and do not require administrative access:

- [133. When did it fail? Understand time zones before comparing logs](133-understand-time-zones-before-comparing-logs.md)
- [134. “The program cannot save”: find the cause before changing anything](134-when-a-program-cannot-save-a-file.md)
