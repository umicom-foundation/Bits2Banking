# Stage 7 — Safe Windows PowerShell and Linux command reference

**Purpose:** An easy-to-read aid for someone at the keyboard. **No `.ps1` or other executable script is included or required.**

## How to start

On Windows, search for **PowerShell 7** or open **Windows Terminal** and select a PowerShell tab. If the screen says **Windows PowerShell**, that is the older built-in shell; it can still run many observation commands. Check `pwsh --version` to see whether PowerShell 7 is installed. The text `PS C:\...>` is a prompt—**do not type the `PS` prompt itself**. On Linux, open the distribution's Terminal application; examples use a POSIX-compatible shell.

## Read-only commands for Windows PowerShell 7

| Command to type | What it tells you | Important limitation |
| --- | --- | --- |
| `Get-Location` | Current directory. | It does not change a directory. |
| `Get-Date` | Local date/time. | Record timezone context in incident reports. |
| `whoami` | Current Windows account. | It is not proof of service permissions. |
| `Get-LocalUser` | Local user objects. | It does not enumerate all cloud/domain identities. |
| `Get-LocalGroup` | Local groups. | Names are system- and language-dependent. |
| `whoami /groups` | Security groups on the current token. | Token membership alone is not the entire access decision. |
| `Get-Acl -LiteralPath $HOME` | Owner and ACL information for home directory. | Requires careful interpretation and redaction. |
| `Get-NetFirewallProfile` | Firewall-profile settings where supported. | Enabled is not proof that all rules are correct. |
| `Get-Service` | Local service observations. | Running does not guarantee functional readiness. |
| `Get-HotFix` | A subset of Windows updates. | Not a complete Windows Update inventory. |
| `winget upgrade` | Candidate package updates. | May contact configured sources; **does not install** without upgrade selection. |
| `Get-Date` | Current timestamp. | Does not attest to a remote system's time. |
| `Get-FileHash -Algorithm SHA256 -LiteralPath FILE` | Digest of a specific file. | Does not prove that a service loaded the file. |
| `Get-WinEvent -LogName Application -MaxEvents 5` | Recent local application events. | May expose private values; access may be restricted. |

## Read-only Linux observations

| Command | Purpose | Limitation |
| --- | --- | --- |
| `pwd` | Show current directory. | No directory change. |
| `date -Is` | Local timestamp with offset. | Clock accuracy is not independently proven. |
| `id` | Current user and group IDs. | Does not list all application permissions. |
| `getent passwd` | Account entries from configured identity sources. | Not all entries allow interactive login. |
| `stat -c '%A %U:%G %n' "$HOME"` | Basic path permissions and owner. | Extended ACLs may apply. |
| `systemctl --failed --no-pager` | Failed systemd units. | Only applies when systemd is running. |
| `ss -lnt` | Local TCP listeners. | Does not prove external reachability. |
| `apt list --upgradable` | Candidate updates on Debian/Ubuntu. | May reflect stale package metadata. |
| `sha256sum FILE` | File content digest. | The digest must be associated with a trusted source. |
| `journalctl --since '10 minutes ago' --no-pager -n 10` | Recent journal entries. | Access and privacy restrictions apply. |

## Commands that create or alter *personal practice files only*

- `New-Item -ItemType Directory -Path $Practice -Force` (Windows): creates a chosen training folder.
- `Set-Content -LiteralPath $PracticeFile -Value ...` (Windows): **replaces** the named practice file. Do not use on system settings.
- `Copy-Item -LiteralPath $Source -Destination $Baseline` (Windows): copies a harmless practice file; check before overwriting an existing baseline.
- `mkdir -p "$HOME/UmicomLearning/SecurityOps"` (Linux): creates a chosen training directory.
- `cp "$SRC" "$BASE"` (Linux): copies a practice file; an existing destination may be replaced.

**Never run as a classroom shortcut:** bulk permission changes (`chmod -R 777`), forceful Git history rewrites, disabling antivirus/firewalls, bypassing certificate verification, deleting incident logs, uploading secrets, unauthorised SSH logins, or system-wide package updates. If any command fails, record the exact error and ask the instructor or system owner.
