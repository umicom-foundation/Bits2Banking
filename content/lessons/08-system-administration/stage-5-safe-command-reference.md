# Stage 5 safe-command reference — Windows PowerShell 7 and Linux terminal

Commands below are **interactive learner instructions**, not PowerShell or shell implementation scripts. Replace a placeholder before executing any command that names a file.

| Purpose | Windows PowerShell 7 | Linux terminal | Change to machine? |
|---|---|---|---|
| Current directory | `Get-Location` or `pwd` | `pwd` | No |
| Shell version | `$PSVersionTable.PSVersion` | `printf '%s\n' "$SHELL"` (shell path) | No |
| Processor | `Get-CimInstance Win32_Processor` | `lscpu` | No |
| OS | `Get-ComputerInfo` | `cat /etc/os-release` | No |
| Find an executable | `Get-Command cmake` | `command -v cmake` | No |
| Filesystem space | `Get-PSDrive -PSProvider FileSystem` | `df -h "$HOME"` | No |
| Identity | `whoami` | `id` | No |
| Folder permissions | `Get-Acl "$HOME\UmicomLearning"` | `ls -ld "$HOME/UmicomLearning"` | No |
| Processes | `Get-Process` | `ps -ef` | No |
| Services | `Get-Service` | `systemctl --user list-units --type=service` | No |
| Recent logs | `Get-WinEvent -LogName Application -MaxEvents 8` | `journalctl --user -n 12 --no-pager` | No |
| QEMU capabilities | `qemu-system-riscv64 -machine help` | `qemu-system-riscv64 -machine help` | No |
| ISO checksum | `Get-FileHash -Algorithm SHA256 -LiteralPath <file>` | `sha256sum <file>` | No |
| CMake presets | `cmake --list-presets` | `cmake --list-presets` | No |
| Git changes | `git status --short` | `git status --short` | No |
| Git revision | `git rev-parse HEAD` | `git rev-parse HEAD` | No |
| Native tests | `ctest --test-dir <build> --output-on-failure` | Same | Test executables may write under a private build tree |
| Private staging | `cmake --install <build> --prefix C:\umicom\learning-stage-update42` | `cmake --install <build> --prefix "$HOME/umicom-learning-stage"` | **Yes**, private prefix only |

**Never run as a shortcut:** `git reset --hard`, `git clean -fd`, `git push --force`, `Stop-Service`, `systemctl stop`, `chmod -R 777`, `mkfs`, `diskpart clean`, or a system-wide package upgrade. These operations may be appropriate only in separately authorised professional work, never as a generic beginner troubleshooting step.

If a command is unavailable, **say “not installed”** rather than fabricate a result. If a path is missing, check the current directory and correct it before doing anything else. If a step would write files, verify that the destination is a practice folder you own and that its existing contents are not important.
