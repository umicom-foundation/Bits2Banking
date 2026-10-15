# Chapter 91 — Firewalls, endpoint security and control evidence

**Bits to Banking · System Administration From Zero · Stage 7**  
**Prerequisite:** Chapters 74, 78, 85 and 90. **Safety:** Read-only observations; never disable a control to make a test pass.

## A green icon is not a security assessment

An antivirus product, firewall dashboard or endpoint agent can provide useful protection. But one green indicator does not prove that every security requirement is met. **Endpoint protection** can include malware detection, disk encryption, tamper controls and update monitoring. A **firewall** applies rules to network connections. **Monitoring** checks whether important behaviours or warnings have been observed. Each addresses a different part of risk.

A security review asks: *Which machine? Which time? Which control and policy revision? What was checked? What is still missing?* A command may be unavailable on a system because a third-party provider supplies the control or because the account lacks permission to view it. That result should be recorded as an observation limitation, not quietly converted into a pass or fail.

![Observe and review security evidence without changing a machine](../../assets/diagrams/sysadmin-security-review-lifecycle-update44.svg)

## Windows PowerShell 7: examine the state, not change it

```powershell
Get-NetFirewallProfile | Select-Object Name, Enabled, DefaultInboundAction
Get-Command Get-MpComputerStatus -ErrorAction SilentlyContinue
Get-MpComputerStatus | Select-Object AMServiceEnabled, AntivirusEnabled, RealTimeProtectionEnabled
```

The first line reports firewall profile information. Enabled does not prove that its rules are appropriate for a bank or hospital. The security-status command depends on Windows and installed security providers. If it fails, do not assume antivirus has been disabled: record that the particular command could not provide evidence. The correct tool may depend on organisational policy.

## Linux terminal: identify tools and local listeners

```bash
command -v ufw
command -v firewall-cmd
ss -lnt
```

The first two lines identify whether particular firewall utilities are installed. Their absence does not prove there is no firewall. `ss -lnt` lists **local listening TCP sockets**. It does not prove that an external computer can connect: remote routing and firewall rules also matter.

## Three layers of network evidence

For the fictional `notes.training.invalid` service, distinguish three claims: *the application is listening on a local port*, *the relevant firewall policy permits the intended traffic*, and *an authorised client can actually connect*. These are different observations. A healthy listener does not prove that the client has access; successful connectivity does not prove that the client is authorised to read sensitive Notes data.

Suppose an agent's status has stopped updating. Turning off firewall protection may appear tempting, but it destroys evidence and exposes new risks. A professional first records the agent state, checks which path it needs and seeks an approved diagnosis plan. A missing heartbeat may also be caused by a stopped agent, DNS failure, missing credentials or server-side outage.

## Learner exercise

Create a matrix with columns *expected control*, *observed tool output*, *evidence status* and *next owner*. Enter three fictional rows: Windows firewall profile, endpoint-protection heartbeat and application authentication. Mark one deliberately *Not verified*. Explain why **unknown** is not equivalent to **passed**.

**Question:** Does an open listening port imply that the service is reachable from the internet? **Answer:** No. It is a local socket state, not a proof of external reachability or routing.

**Question:** What should you do if a security command cannot run? **Answer:** Record the limitation and ask for the supported inspection mechanism; do not bypass protection.

### Common mistakes

Do not disable real-time protection, add broad firewall exceptions or turn off logging in order to make a classroom command succeed. Do not publish raw IP inventories, device names or account identifiers from managed computers.

**Umicom connection:** Framework security and observability modules should expose explicit unknown and degraded states. A graphical shell reports those states without silently rewriting OS protection policy.

**Next:** Chapter 92 — safe credential rotation.
