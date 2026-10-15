# Episode 121 — Remote Administration: Trust Before Login

**Bits2Banking · Umicom Foundation · Target: 8–10 minutes**  
**Related chapters:** System Administration 73–75.  
**Production rule:** No actual remote connection is required.

## Learning outcomes

Explain client, server, TCP connection, host-key verification, account authentication and authorisation in distinct sentences. Identify one unsafe way to bypass an identity warning.

## Opening — 0:00–1:30

**On screen:** Local Windows computer, network and an instructor-approved training host. Use [the SSH trust-boundary diagram](../../assets/diagrams/sysadmin-ssh-trust-boundary-update43.svg).  
**Narration:** “Suppose Umicom Notes is running on another computer. Reaching its port means we have found a route—not that we have found the right host, and not that we have permission to change anything. Remote administration is a set of controlled decisions, not one command.”

## Demo — 1:30–4:30

Show Windows Terminal, explain why the shell is PowerShell 7, and type:

```powershell
$PSVersionTable.PSVersion
Get-Command ssh -ErrorAction SilentlyContinue
ssh -V
ssh -G learner@notes.training.invalid
```

Point out that `-G` prints configuration and does not initiate a login. The `.invalid` hostname is deliberate. On Linux show `command -v ssh`, `ssh -V` and `ssh -G` as equivalents. A missing client is an honest outcome; do not disguise it.

## Trust test — 4:30–7:00

**On screen:** Draw three gates: verify remote host, authenticate student, approve read-only action.  
**Narration:** “If an SSH host key suddenly changes, stop. Verify the fingerprint using a separate approved channel. `ssh-keyscan` by itself does not establish trust; switching off host-key checking destroys the very check we need.”

## Real-world application — 7:00–9:00

Discuss a service operator with permission to view logs but not modify banking accounts. Even a technically successful SSH login must be limited to that job. End with two questions: “What does a TCP connection prove?” and “Who authorises a real support change?”

**Viewer exercise:** Write a four-line remote access request for a fictional Umicom Notes host. Include the owner, limited purpose, host-key verification and reviewer. Do not use credentials.
