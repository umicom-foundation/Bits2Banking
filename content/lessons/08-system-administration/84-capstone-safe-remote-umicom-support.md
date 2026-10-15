# Chapter 84 — Capstone: prepare a safe remote Umicom support review

**Bits to Banking · System Administration From Zero · Stage 6 · Umicom Foundation**  
**Prerequisite:** Chapters 73–83 and Stage 5 private deployment.  
**Learning outcome:** Explain and verify the *readiness evidence* required before a remote support session.  
**Safety:** Offline simulation by default; no production account, firewall, SSH server, certificate or service is changed.

## Your task

You are a junior administrator supporting a fictional Umicom Notes training service. Another person reports that it has stopped responding. Your supervisor asks you to prepare a short preflight review **without connecting to production**. You have an account label and a claimed host name, but no approved host-key fingerprint yet. A professional should recognise that some information is missing and refuse a remote session until those checks are completed.

This capstone combines remote identity, SSH keys, listener investigation, network boundaries, least privilege, configuration changes, backup/recovery and incident evidence. It also connects the classroom exercise to the new C23 `remote-access-review` laboratory, which consumes the previous deployment evidence model rather than building another production security engine.

![Remote support: independent evidence before human approval](../../assets/diagrams/sysadmin-remote-support-evidence-update43.svg)

## Step 1 — write down the system boundary

Create a private training note containing the following **fictional** fields:

| Field | Example value | How it is verified |
|---|---|---|
| Service | `notes-demo` | Approved application inventory |
| Remote host label | `notes.training.invalid` | Must be replaced with a real authorised target before access |
| Requester | `MakerA` | Authorised identity system |
| Independent reviewer | `CheckerB` | Separate accountable approval |
| Source revision | Exact Git commit | Read from the actual deployed artifact/manifest |
| Host key | Not yet verified | Obtain fingerprint from a separate trusted channel |
| Network scope | Local or approved sources only | Authorised firewall/routes review |
| Recovery plan | Drafted, not executed | Approved runbook and restore drill |

The **correct decision with the host key missing is BLOCKED**. Do not fill in a value you have not checked.

## Step 2 — confirm the local environment

Windows PowerShell:

```powershell
$PSVersionTable.PSVersion
Get-Location
Get-Command ssh, git, cmake -ErrorAction SilentlyContinue |
    Select-Object Name, Source
```

Linux terminal:

```bash
uname -s
pwd
command -v ssh
command -v git
command -v cmake
```

**Expected:** Your actual tool inventory. If a command is missing, record its absence; do not silently install tools or claim you ran tests with them.

## Step 3 — verify the previous native evidence laboratory

From your checked-out `Umicom-Bits2Banking` root on Windows PowerShell:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\remote-access-review" `
    -B ".\output\learning-build\remote-access-review" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\remote-access-review" --parallel 2
ctest --test-dir ".\output\learning-build\remote-access-review" --no-tests=error --output-on-failure
```

The `remote-access-review` laboratory requires previous Updates 39–42. **Do not run the commands if those files have not yet been merged.** Each prior library remains the authoritative C23 implementation of its own educational contract.

On Linux:

```bash
cmake -S labs/native/remote-access-review -B output/learning-build/remote-access-review -G Ninja -DBUILD_TESTING=ON
cmake --build output/learning-build/remote-access-review --parallel 2
ctest --test-dir output/learning-build/remote-access-review --no-tests=error --output-on-failure
```

These commands may create files inside the private build directory; they do not configure a real operating-system service.

## Step 4 — run relevant negative tests separately

Windows PowerShell:

```powershell
ctest --test-dir ".\output\learning-build\remote-access-review" `
    -R "bits2banking\.remote-review\.(host-key|stale|rollback|atomic-output)$" `
    --no-tests=error --output-on-failure
```

Read the results for four different concerns: missing remote identity evidence, stale observations, unsuccessful deployment and preservation of output when data is invalid. A test passing means the **simulation's policy** behaved as expected. It does **not** establish that a real host is trustworthy.

## Step 5 — decide whether to escalate or proceed

Imagine two situations:

1. The service's host identity is unknown, but network access appears possible. **Decision:** Block and request verified host identity; do not try credentials.
2. The last deployment failed, but the previous state was restored and independently checked. **Decision:** Report restoration, not successful delivery of the new release.

For either case, record what was done, what was not done, who owns the decision and which checks must happen next. Escalation is a professional action, not a personal failure.

## Practical assessment — 10 points

| Criterion | Points |
|---|---:|
| Identifies requester, reviewer, scope and authorised target | 2 |
| Distinguishes host-key identity from user authentication | 2 |
| Inspects environment without creating service changes | 2 |
| Runs native tests and records *actual* observed result | 2 |
| Reports BLOCKED versus RESTORED_ONLY without overstating evidence | 2 |

**Suggested passing standard:** 8/10 with **no critical safety error**. Critical errors include ignoring a host-key warning, publishing a private key, changing a firewall without permission or falsely claiming production readiness.

## Instructor notes and answer guide

The learner should demonstrate the `ssh -G` *read-only* configuration preview, understand why an SSH hostname is not automatically trusted, and be able to say “not tested” when no authorised server exists. The C23 lab is deliberately non-operational: no tool-generated decision is an access grant. Review the case notes for accurate uncertainty and sensitive-data redaction.

## From beginner skills to Umicom architecture

A Framework application should not build its own shadow SSH or credential subsystem. **Umicom Framework** owns reusable C23/Assembly contracts for VCS, configuration, security, service lifecycle and build verification; **Umicom OS** composes approved system services; **Umicom Kernel** owns privileged hardware/kernel behaviour. **Bits2Banking** supplies isolated exercises and helps learners understand each boundary. When the native lab is ready for production consideration, first compare it with existing Framework capabilities, design the contract, and obtain project-owner approval before any cross-repository modification.

**Next stage:** Secure administration beyond remote login—permission reviews, secure recovery, infrastructure inventories, automation governance and real operational acceptance tests.
