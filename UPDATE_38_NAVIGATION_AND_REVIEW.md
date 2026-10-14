# Major Update 38 — MkDocs navigation and review instructions

The source-of-truth `mkdocs.yml` may have changed since the supplied baseline. **Do not replace your entire file.** Open the current `mkdocs.yml`, preserve every existing book, chapter, video and historical *Islam: Blueprint for Life* entry, and append the new section under the existing top-level `nav:` mapping. Validate the result with the existing MkDocs build.

The course's internal index links allow all 24 chapters to be reached even before the navigation is manually expanded. Adding the full chapter list to the site navigation is preferable for discovery.

## New top-level navigation entry (add under `nav:`)

```yaml
  - "System Administration — From Zero (dedicated course)":
      - "Start here and choose a learning path": lessons/08-system-administration/index.md
      - "01. What does a system administrator do?": lessons/08-system-administration/01-what-system-administrators-do.md
      - "02. Understand the computer, operating system and user account": lessons/08-system-administration/02-computer-os-and-user-accounts.md
      - "03. Open PowerShell 7 or the Linux terminal without confusion": lessons/08-system-administration/03-open-powershell-or-linux-terminal.md
      - "04. Read a command, its arguments and the help system": lessons/08-system-administration/04-read-commands-options-and-help.md
      - "05. Folders, file paths and your own safe practice workspace": lessons/08-system-administration/05-folders-paths-and-safe-workspace.md
      - "06. Create, open and read text files without scripting": lessons/08-system-administration/06-create-open-and-read-text-files.md
      - "07. Copy, rename and remove files carefully": lessons/08-system-administration/07-copy-move-delete-with-rollback.md
      - "08. Install and verify PowerShell 7, Git and development tools": lessons/08-system-administration/08-install-programmes-and-verify-tools.md
      - "09. Users, administrators and the meaning of permissions": lessons/08-system-administration/09-accounts-permissions-least-privilege.md
      - "10. Processes: what is running on your computer?": lessons/08-system-administration/10-understand-running-processes.md
      - "11. Windows services: background programs and startup": lessons/08-system-administration/11-windows-services-and-startup.md
      - "12. Windows Event Viewer and useful troubleshooting records": lessons/08-system-administration/12-read-windows-events-and-logs.md
      - "13. Inspect processor, memory, Windows version and resources": lessons/08-system-administration/13-inspect-hardware-memory-and-os.md
      - "14. Disks, backups and checking that restoration works": lessons/08-system-administration/14-disks-backups-and-restore-verification.md
      - "15. IP addresses, networks, DNS and ports": lessons/08-system-administration/15-ip-dns-ports-and-the-internet.md
      - "16. Troubleshoot a failed connection one layer at a time": lessons/08-system-administration/16-diagnose-dns-firewall-and-connections.md
      - "17. Linux terminal, home directory, files and processes": lessons/08-system-administration/17-linux-terminal-files-and-processes.md
      - "18. Linux permissions, packages, services and logs": lessons/08-system-administration/18-linux-users-permissions-packages-logs.md
      - "19. Git from zero: create, inspect, stage and commit": lessons/08-system-administration/19-git-local-repository-and-first-commit.md
      - "20. GitHub: authenticate, publish and collaborate responsibly": lessons/08-system-administration/20-github-cli-publish-and-collaborate.md
      - "21. Create a new Umicom application: repositories, modules and discovery": lessons/08-system-administration/21-new-umicom-application-module-and-discovery.md
      - "22. Build, test and inspect a read-only C23 program": lessons/08-system-administration/22-c23-build-tests-and-safe-inspection.md
      - "23. Troubleshoot problems systematically and write useful evidence": lessons/08-system-administration/23-systematic-troubleshooting-and-reporting.md
      - "24. Capstone: perform a safe support check from start to finish": lessons/08-system-administration/24-capstone-your-first-support-check.md
      - "System Administration glossary": lessons/08-system-administration/glossary.md
      - "Practical workbook and assessment": lessons/08-system-administration/workbook-and-assessment.md
      - "Notes for instructors and mentors": lessons/08-system-administration/instructor-notes.md
  - "System Administration and Umicom contributor bridge":
      - "284. From your first terminal command to responsible administration": lessons/05-engineering/284-system-administration-from-the-first-command.md
      - "285. Inspect processes, services and logs before attempting fixes": lessons/05-engineering/285-inspect-process-services-and-logs-before-fixes.md
      - "286. Build a bounded read-only text inspector in C23": lessons/05-engineering/286-keep-file-inspection-readonly-and-bounded.md
      - "287. A first responsible source-control and testing handover": lessons/05-engineering/287-read-git-status-then-build-test-and-publish.md
      - "Video 95. Which PowerShell should you open?": videos/scripts/95-which-powershell-should-you-open.md
      - "Video 96. Build your first safe practice folder": videos/scripts/96-build-your-first-safe-practice-folder.md
      - "Video 97. Inspect a computer without changing it": videos/scripts/97-inspect-a-pc-without-changing-it.md
      - "Video 98. Understand network failures and begin Linux administration": videos/scripts/98-understand-network-failures-and-linux.md
      - "Video 99. Publish your first private Git repository": videos/scripts/99-publish-your-first-private-git-repository.md
      - "Video 100. Understand a new Umicom module and build a C23 inspector": videos/scripts/100-new-umicom-module-and-native-c23-lab.md
```

## Review requirements

1. Confirm `git status` and the `main` branch before editing.
2. Do not duplicate any navigation item or remove a previous chapter to make room.
3. Preserve the current `theme`, `plugins`, `markdown_extensions`, original manuscript catalogue and other book navigation.
4. Review the HTML copy of the user-contributed project guide: it is included unchanged under `content/assets/reference/` and linked from Chapter 21.
5. The dedicated course's sequence is 01–24; the cross-track engineering sequence continues Chapters 284–287. They serve different learning purposes and do not overwrite Chapters 1–24 elsewhere.
6. Run `& ".\.venv\Scripts\python.exe" -m mkdocs build --strict` **only when the existing MkDocs publishing environment is already available**. This invokes the retained external publisher; the batch introduces no Python application code. Report unavailable dependencies as NOT RUN, not PASS.
7. Verify the static guide HTML is included in the generated website and open its link from course Chapter 21.
