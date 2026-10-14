# Source register — Update 39

## Earlier Umicom materials retained

- Previous self-contained baseline: Update 38, `content/lessons/08-system-administration/01-` through `24-` (unchanged, incorporated into cumulative offline course).
- Original submitted guide: `content/assets/reference/umicom-new-project-beginner-guide-original.html` (preserved from Update 38; not reauthored or replaced here).
- Original Windows Start-menu screenshot illustrating different PowerShell programs (retained from Update 38; embedded in the cumulative offline course where referenced).
- Umicom Framework native VCS and build contracts: `include/umicom/vcs/working_tree.h`, `include/umicom/build/automation.h`, `include/umicom/build/parser.h`, `include/umicom/repository/submodule_lock.h`. Those are referenced for production architecture; no Framework source code is copied into this batch.

## Official technical references for learners

- Microsoft PowerShell documentation: https://learn.microsoft.com/powershell/
- Get-Service: https://learn.microsoft.com/powershell/module/microsoft.powershell.management/get-service
- Get-WinEvent: https://learn.microsoft.com/powershell/module/microsoft.powershell.diagnostics/get-winevent
- Windows Package Manager inventory: https://learn.microsoft.com/windows/package-manager/winget/list
- Windows SSH key management: https://learn.microsoft.com/windows-server/administration/openssh/openssh_keymanagement
- Windows ACL inspection: https://learn.microsoft.com/windows-server/administration/windows-commands/icacls
- systemd `systemctl`: https://www.freedesktop.org/software/systemd/man/latest/systemctl.html
- systemd `journalctl`: https://www.freedesktop.org/software/systemd/man/latest/journalctl.html
- GNU coreutils permissions/filesystem: https://www.gnu.org/software/coreutils/manual/
- SSH protocol and OpenSSH: https://www.openssh.com/manual.html
- GitHub account security: https://docs.github.com/authentication/keeping-your-account-and-data-secure/about-authentication-to-github

Examples describe expected semantics, but exact commands and outputs depend on OS edition, environment, permissions, installed versions and organisation policy. Authors must verify platform-specific behaviour before declaring a platform-qualified build.
