# Stage 8 command reference — PowerShell 7 and Linux

**Use only on computers you own or are authorised to examine.** The commands below are intended for learning and observation. They do not install software, create scheduled jobs, restart services or edit system permissions. A few lessons explicitly create harmless files in the learner's own home directory; this reference contains only read-only commands.

## Start with the shell

Windows: open **Windows Terminal → PowerShell** or search for **PowerShell**. Start PowerShell 7 from a Windows PowerShell window by typing `pwsh` if it is installed. To verify:

```powershell
$PSVersionTable.PSVersion
Get-Location
Get-Command pwsh, git, gh -ErrorAction SilentlyContinue | Select-Object Name, Source
```

The first command shows the version of the current shell. The second shows the current directory. The third searches for installed programs; an absent result means that a program may not be installed or discoverable in the current PATH.

Linux: open a terminal, then:

```bash
pwd
whoami
uname -m
```

## Observe without changing

| Question | Windows PowerShell 7 | Linux terminal | What a result cannot prove |
|---|---|---|---|
| What time is it? | `Get-Date` | `date -Is` | That clocks across several hosts agree |
| Where am I? | `Get-Location` | `pwd` | That the directory is safe to change |
| Who am I? | `whoami` | `id` | That you may change service permissions |
| What is running? | `Get-Process \| Select-Object -First 5 Name, Id` | `ps -ef \| head -n 6` | That the process is healthy |
| Which filesystem has space? | `Get-PSDrive -PSProvider FileSystem` | `df -h` | That an application has permission or quota |
| What is scheduled? | `Get-ScheduledTask \| Select-Object -First 5 TaskName, State` | `systemctl list-timers --all --no-pager` | That a job produced its intended output |
| Has this user configured cron? | *Windows Task Scheduler instead* | `crontab -l` | That the entire machine has no jobs |
| What is recent local evidence? | `Get-WinEvent -LogName System -MaxEvents 5` | `journalctl --user -n 5 --no-pager` | The root cause of an incident |
| What is the Git state? | `git status` | `git status` | That the software builds and passes tests |

**Important:** In the table, `\|` displays the PowerShell/Linux pipeline symbol `|`; type the actual pipe character, not a backslash. System command availability depends on the operating system and installed tools. An access-denied response is a boundary to record, not an instruction to bypass it.

## Troubleshooting the commands themselves

If `Get-ScheduledTask` is not recognised, confirm you are running on Windows and whether the ScheduledTasks module exists. If `systemctl` reports the system is not using systemd, identify the actual init system before proceeding. If `Get-WinEvent` reports insufficient permissions, record “Not verified — access unavailable” and ask an authorised operator. If a command returns no lines, do not automatically interpret that as zero problems; ensure the intended scope was queried.

## Never perform these as a beginner shortcut

Do not use `git reset --hard`, `git clean -fd`, a force push, `sudo` permission changes, edits to firewall rules, `Stop-Service`, `Disable-ScheduledTask`, `crontab -e`, edits under `/etc` or `C:\Windows`, or deletion of backup generations in order to make a test pass. Such operations require explicit authorisation, review and backup/recovery controls in the appropriate environment.
