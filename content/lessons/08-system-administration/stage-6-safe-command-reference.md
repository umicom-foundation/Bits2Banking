# Stage 6 command reference — safe local checks and optional practice writes

**Audience:** First-time system administrators. Every command in this reference is interactive shell usage, never an implementation script. Check current directory and user authority before every write.

| What you need | PowerShell 7 (Windows) | Linux | Changes files? |
|---|---|---|---|
| Show your current folder | `Get-Location` | `pwd` | No |
| Local computer name | `$env:COMPUTERNAME` | `hostname` | No |
| Find OpenSSH client | `Get-Command ssh` | `command -v ssh` | No |
| SSH client version | `ssh -V` | `ssh -V` | No |
| Preview SSH configuration, **no connection** | `ssh -G learner@notes.training.invalid` | Same | No |
| List local TCP listeners | `Get-NetTCPConnection -State Listen` | `ss -ltn` | No |
| Check approved loopback port | `Test-NetConnection 127.0.0.1 -Port 8765` | `ss -ltn '( sport = :8765 )'` | No; Windows command makes local TCP attempt |
| Your login identity | `whoami` | `whoami` and `id` | No |
| Firewall profile/manager | `Get-NetFirewallProfile` | `command -v nft` | No |
| Public example DNS | `Resolve-DnsName example.org -Type A` | `getent ahostsv4 example.org` | No local files; uses network if available |
| Local routes | `Get-NetRoute -AddressFamily IPv4` | `ip -4 route` | No |
| HTTPS HEAD on approved example | `curl.exe --head https://example.org/` | `curl -I https://example.org/` | No local file; makes internet request |
| View a key fingerprint | `ssh-keygen -lf "$Key.pub"` | `ssh-keygen -lf "$HOME/.../practice_ed25519.pub"` | No |
| Create a *private* practice folder | `New-Item -ItemType Directory -Path "$HOME\UmicomLearning"` | `mkdir -p "$HOME/UmicomLearning"` | **Yes** — only your practice folder |
| Copy a harmless training text | `Copy-Item -LiteralPath .\sample.txt -Destination .\received\sample.txt` | `cp -n sample.txt received/sample.txt` | **Yes** — review destination first |
| Compare file digests | `Get-FileHash -Algorithm SHA256 -LiteralPath .\sample.txt` | `sha256sum sample.txt` | No |
| Review local Git changes | `git status --short` | Same | No |
| Review native C23 tests | `ctest --test-dir <build> --output-on-failure` | Same | Tests write only where their own contracts allow |

**Do not use as routine fixes:** `ssh -o StrictHostKeyChecking=no`, `curl --insecure`, firewall disablement, broad recursive permission changes, deletion of all `known_hosts`, `git reset --hard`, `git clean -fd`, `git push --force`, or unapproved service starts/stops. A failing or missing command is diagnostic evidence, not a request to escalate privileges.

If a step requires a specific server, replace placeholders only with **approved training hostnames** supplied with independent identity verification. Never paste private keys, tokens or sensitive network diagrams into public chats or repositories.
