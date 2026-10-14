# Safe Windows PowerShell and Linux Administration — Quick Reference

This sheet summarises **interactive** commands. No `.ps1` or `.py` files are delivered. Do not type `PS C:\>` or `$` prompts displayed in examples. Commands marked *practice write* act only on folders owned by the learner.

| Question | Windows PowerShell 7 | Linux terminal | Note |
|---|---|---|---|
| Where am I? | `Get-Location` or `pwd` | `pwd` | Reads working directory |
| What shell? | `$PSVersionTable.PSVersion` | `echo $SHELL` | These identify different things |
| What OS? | `Get-ComputerInfo \| Select-Object WindowsProductName, OsVersion, OsArchitecture` | `cat /etc/os-release` | Choose only needed fields |
| What CPU? | `Get-CimInstance Win32_Processor \| Select-Object Name, NumberOfCores` | `lscpu` | Availability varies |
| Disk capacity? | `Get-PSDrive -PSProvider FileSystem` | `df -h .` | Check the volume containing your project |
| Who am I? | `whoami` | `id` | Avoid sharing full account info |
| File ACL? | `Get-Acl -LiteralPath $HOME` | `ls -ld "$HOME"` | Observe; do not grant rights |
| Services? | `Get-Service \| Select-Object -First 10 Name, Status` | `systemctl --user list-units --type=service --all` | Stopped need not be broken |
| Recent log? | `Get-WinEvent -LogName Application -MaxEvents 6` | `journalctl --user -n 6 --no-pager` | Redact messages |
| Name lookup? | `Resolve-DnsName example.org` | `getent ahosts example.org` | Optional internet connection |
| TCP port? | `Test-NetConnection 127.0.0.1 -Port 8765` | `ss -lnt` | No service: refusal may be expected |
| Firewall summary? | `Get-NetFirewallProfile` | `command -v nft` | Never disable rules for a class exercise |
| Package versions? | `winget --version` | `cat /etc/os-release` | These describe different systems |
| Available updates? | `winget upgrade` | `apt list --upgradable` | List only; do not install |
| File digest? | `Get-FileHash -Algorithm SHA256 -LiteralPath PATH` | `sha256sum PATH` | Use real paths you own |
| Git working tree? | `git status --short` | `git status --short` | Reads local changes only |
| Native test report? | `ctest --test-dir BUILD --output-on-failure` | Same command | Does not prove all suites were run |

### Before any real change

Verify: **permission** → **target** → **expected behaviour** → **backup/rollback** → **approval** → **actual acceptance test**. If any required condition is unknown, stop and ask the owner. The default purpose of this course is inspection, not system modification.
