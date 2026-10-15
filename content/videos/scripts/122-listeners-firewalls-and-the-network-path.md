# Episode 122 — Listeners, Firewalls and the Network Path

**Bits2Banking · Umicom Foundation · Target: 9–12 minutes**  
**Related chapters:** System Administration 74, 78 and 79.

## Objective

Learners should be able to separate DNS resolution, network route, listening port, firewall policy and application response. They should understand what loopback means and why turning off a firewall is not a diagnostic procedure.

## Scene 1 — The address and room analogy

Show [DNS-to-application diagram](../../assets/diagrams/sysadmin-dns-port-route-update43.svg). Explain that the address reaches the machine while the port selects a service. Highlight `127.0.0.1` as the local computer and `0.0.0.0` as a wildcard listener, not an external public IP address.

## Scene 2 — Read-only PowerShell demonstration

Open PowerShell 7 and type:

```powershell
Get-NetTCPConnection -State Listen | Select-Object -First 10 LocalAddress, LocalPort, OwningProcess
Get-NetFirewallProfile | Select-Object Name, Enabled, DefaultInboundAction
Get-NetConnectionProfile | Select-Object Name, NetworkCategory
```

Describe what each column means. If access is denied or a command is missing, mark the observation unavailable rather than running as administrator automatically.

## Scene 3 — Linux comparison

In an ordinary terminal:

```bash
ss -ltn
ip -4 route
command -v nft
```

Avoid installing a firewall manager or editing existing system policy. Contrast a listening socket with a successful end-to-end application operation.

## Scene 4 — Guided diagnosis

A student reports that `http://127.0.0.1:8765/` does not respond. List the checks in sequence: was the course server started, is there a loopback listener, does a local TCP connection work, and did the HTTP handler respond? Do not open the service to other computers or assume an unrelated firewall is the cause.

**Viewer exercise:** Classify three messages—DNS failed, TCP refused, HTTPS certificate mismatch—by layer and identify one safe next observation for each.
