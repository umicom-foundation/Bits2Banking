# Stage 9 safe command reference — Windows PowerShell and Linux

The commands below are **observational** unless otherwise specified. Read Chapters 109–120 before interpreting output. Do not copy example `PS C:\...>` prompts. Some commands require system capabilities or permission that your account does not possess; report those as Not Run rather than elevating by default.

| Purpose | PowerShell 7 on Windows | Linux terminal |
|---|---|---|
| Where am I? | `Get-Location` | `pwd` |
| Host identity | `hostname` | `hostname` |
| Time with offset | `Get-Date -Format o` | `date -Is` |
| OS version | `Get-ComputerInfo \| Select-Object OsVersion` | `cat /etc/os-release` |
| Running services | `Get-Service` | `systemctl list-units --type=service --all` (systemd) |
| Recent service logs | `Get-WinEvent -LogName System -MaxEvents 10` | `journalctl -b -n 10` (systemd) |
| Disks and free space | `Get-PSDrive -PSProvider FileSystem` | `df -hT` |
| Mounted filesystems | `Get-Volume` | `findmnt` |
| Installed Git version | `git --version` | `git --version` |
| Name resolution | `Resolve-DnsName localhost` | `getent hosts localhost` |
| List TCP listeners | `Get-NetTCPConnection -State Listen` | `ss -ltn` |
| Local TCP check | `Test-NetConnection 127.0.0.1 -Port 8765` | `curl --head --max-time 5 http://127.0.0.1:8765/` (if available) |
| File checksum | `Get-FileHash -Algorithm SHA256 FILE` | `sha256sum FILE` |

**Remember:** DNS success ≠ port success ≠ HTTP success ≠ successful Notes save. A live process is only one observation. Do not use administration or repository modification commands as a shortcut to fix a failed classroom query.
