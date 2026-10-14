# Stage 4 — Safe command reference

**Commands below are typed interactively in PowerShell 7 or a Linux terminal. No `.ps1` or `.py` scripts are delivered.** Commands that write are confined to learner-owned practice folders. Read the relevant chapter first; this sheet is a reminder, not a substitute for understanding.

| Purpose | Windows PowerShell 7 | Linux terminal | Important limitation |
|---|---|---|---|
| Where am I? | `Get-Location` | `pwd` | Directory, not service state |
| Current time | `Get-Date -Format o` | `date --iso-8601=seconds` | Note timezone |
| Check a known service | `Get-Service -Name EventLog` | `systemctl status systemd-journald.service --no-pager` | Process status does not prove application readiness |
| Service configured identity | `Get-CimInstance Win32_Service -Filter "Name='EventLog'"` | `systemctl show systemd-journald.service -p User -p Group` | Identity is not permission proof |
| List scheduled work | `Get-ScheduledTask \| Select-Object -First 8 TaskName,State` | `systemctl list-timers --all --no-pager` | A trigger is not completed work |
| Inspect available drives | `Get-PSDrive -PSProvider FileSystem` | `df -h .` | Check the actual data volume |
| Check tool version | `cmake --version` | `cmake --version` | Versions do not prove compatibility |
| List listeners | `Get-NetTCPConnection -State Listen` | `ss -ltn` | Bind scope is not full security posture |
| Firewall profile (read) | `Get-NetFirewallProfile \| Select-Object Name,Enabled` | `command -v ufw \|\| command -v firewall-cmd` | Do not disable/change firewall rules |
| Check Git without mutation | `git status --short` | `git status --short` | Run inside actual repository |
| Hash a practice file | `Get-FileHash -Algorithm SHA256 -LiteralPath .\notes.txt` | `sha256sum ./notes.txt` | Hash equality is not database recovery |
| Validate C23 learning lab | `ctest --test-dir .\output\learning-build\maintenance-review --no-tests=error --output-on-failure` | `ctest --test-dir output/learning-build/maintenance-review --no-tests=error --output-on-failure` | Only tests already configured and built |

**Never use `git reset --hard`, `git clean -fd`, an unreviewed force push, `Stop-Service`, `systemctl stop`, firewall disabling or system-wide package upgrades as a short-cut to make an introductory exercise pass.** Record unexpected results and ask the system owner before making changes.
