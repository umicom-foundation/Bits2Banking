# Chapter 270 — Networks, DNS, HTTPS and safe connection checks

**Bits to Banking · Absolute Beginner Course · Unit 2**  
**Time:** 30 minutes. All examples send ordinary diagnostic queries; use networks you are authorised to access.

## Why GitHub depends on networking

When you run `git commit`, Git stores a new local revision; the internet is not required. When you run `git push`, Git contacts a **remote** server, usually over HTTPS or SSH, and asks it to accept commits. When you run `gh auth login`, you authorise the GitHub CLI to act on an account. These actions depend on network availability, credentials and repository permissions, but they are still three different operations.

An **IP address** identifies a network endpoint. **DNS** maps human-readable names such as `github.com` to addresses. A **port** identifies a service on a host; HTTPS commonly uses TCP port 443. **HTTPS** protects data in transit using TLS. None of these prove that your GitHub account has permission to push to a particular repository.

## Step 1 — Inspect local network settings

```powershell
Get-NetIPConfiguration | Select-Object InterfaceAlias, IPv4Address, IPv4DefaultGateway
```

The output depends on your adapters, including VPNs and Wi-Fi. Avoid sharing complete local network details publicly when they are not needed.

## Step 2 — Ask DNS for an address

```powershell
Resolve-DnsName github.com
```

You may see several records, including IPv4 and IPv6 addresses. The particular addresses can change. A DNS response means the name resolved; it does not prove that GitHub authentication works.

## Step 3 — Test the HTTPS port

```powershell
Test-NetConnection github.com -Port 443
```

The field `TcpTestSucceeded` indicates whether the TCP connection was established. A failure may mean loss of internet access, a proxy, a firewall or temporary service unavailability. It does not necessarily mean GitHub is down, and a success does not prove that `git push` will be authorised.

## Step 4 — Distinguish local and remote failures

If `git --version` works but `git push` fails, check the remote and authentication:

```powershell
git remote -v
gh auth status
```

Run these **inside your intended Git repository**. A message saying “not a git repository” is not a network error; it means you are in the wrong folder or have not run `git init`.

## Concept-to-evidence table

| Question | Appropriate first observation |
|---|---|
| Is Git installed? | `git --version` |
| Is GitHub's hostname resolving? | `Resolve-DnsName github.com` |
| Can I connect to HTTPS? | `Test-NetConnection github.com -Port 443` |
| Is GitHub CLI authenticated? | `gh auth status` |
| Which remote repository does Git use? | `git remote -v` |
| May I push to that repository? | Repository permissions and actual push result |

**Practice:** Explain why successful DNS, TCP, authentication and repository permission are separate facts. Do not change proxy, firewall or credential settings during this initial exercise.

**Next:** [Open a Linux terminal and use equivalent commands](271-linux-terminal-for-first-time-users.md).
