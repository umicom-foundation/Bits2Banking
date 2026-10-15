# Chapter 83 — Remote support, monitoring and incident evidence

**Bits to Banking · System Administration From Zero · Stage 6 · Umicom Foundation**  
**Prerequisite:** Chapters 35, 47, 59 and 73–82.  
**Safety:** Observe your own system or approved lab; never paste credentials, patient/customer data or full internal network inventories into public reports.

## The support question is not simply “is it running?”

Imagine a fictional Umicom Notes service becomes unresponsive just as a trainee tries to open a saved document. A process may be alive, its TCP port may accept connections, and its log may contain no fatal error—yet the requested Notes operation can still fail because a storage dependency is unavailable. Reliable support therefore separates **uptime**, **service readiness** and **business correctness**.

A professional incident report records a timeline of observations, not a string of guesses. Include the time, machine or service label, source revision, check performed, observed result, expected result and relevant error code. Distinguish *observed*, *inferred* and *not checked*. If a remote operator cannot access a required log, record that limitation explicitly.

![Observed evidence, change decisions and human review](../../assets/diagrams/sysadmin-remote-support-evidence-update43.svg)

## Terms

| Word | Meaning |
|---|---|
| **Event log** | A stream of events recorded by an operating system or service. |
| **Metric** | A measurement such as memory use, request count or queue depth. |
| **Correlation ID** | Identifier used to connect records belonging to one operation. |
| **Incident** | Unexpected event affecting a service's quality or availability. |
| **Escalation** | Transferring a problem to someone with the right role, expertise or authority. |
| **Redaction** | Removing sensitive information before sharing a record. |

A **metric** such as high CPU is evidence of resource use, not automatic proof of the root cause. A **log message** may describe a symptom while the underlying failure lies elsewhere.

## Windows PowerShell — capture your own process baseline

**Step 1.** Read the timestamp:

```powershell
Get-Date -Format o
```

The ISO 8601 output includes a timezone offset, helping later readers compare records. Confirm the system clock is accurate before relying on event ordering.

**Step 2.** Read basic process observations:

```powershell
Get-Process |
    Sort-Object -Property CPU -Descending |
    Select-Object -First 8 ProcessName, Id, CPU, WorkingSet64
```

This reports cumulative CPU time and memory-related metrics. High `CPU` in this table does not necessarily mean high current CPU utilisation; the sampling method matters.

**Step 3.** Inspect recent application-log entries only if your account is allowed:

```powershell
Get-WinEvent -LogName Application -MaxEvents 8 |
    Select-Object TimeCreated, LevelDisplayName, ProviderName, Id
```

This does not expose every service error. Some systems restrict event-log access, and an empty list does not prove health. Do not export entire logs into a public issue.

## Linux terminal — ordinary user observations

```bash
date --iso-8601=seconds
ps -eo pid,comm,%cpu,%mem --sort=-%cpu | head -n 9
```

For a user systemd session, where supported:

```bash
journalctl --user -n 12 --no-pager
```

Record *journal unavailable* if your environment has no user journal. Do not switch to root to obtain every system log for a class exercise.

## Practical Umicom incident example

At 10:00 a trainee says “Notes will not open.” At 10:02 the operator observes a running process. At 10:03 a local TCP test succeeds. At 10:04 the Notes operation still fails. At 10:06 an approved storage-health check reports an unavailable dependency. The responsible team assesses whether to restore the previous configuration. A technician should not declare success at 10:03 merely because the network port works.

A clear support report might contain:

| Time (local offset) | Observation | Evidence | Remaining uncertainty |
|---|---|---|---|
| 10:02+01:00 | Process present | PID and process name | No business health confirmed |
| 10:03+01:00 | TCP accepted | Loopback connection check | Authentication/operation untested |
| 10:04+01:00 | Open Note failed | Sanitised error code | Exact storage cause uncertain |
| 10:06+01:00 | Storage unavailable | Authorised readiness probe | Remediation not approved |

Do not add real customer records to such a table. Use pseudonymous service labels and technical identifiers approved for disclosure.

## Guided exercise

Create an incident timeline for a fictional failed remote SSH access: DNS resolves, TCP connects, the SSH host key is unexpected, and the operator stops. Identify the correct outcome: **connection blocked pending host verification**. Record the warning, the target from the approved inventory, and the person responsible for verifying identity; do not attempt a second connection with validation disabled.

## Common mistakes

Changing a firewall before examining listeners, rebooting a host to clear an unknown state, discarding logs before analysis and calling recovery “deployment success” all destroy useful distinctions. When changes are genuinely required, obtain approval, record the last known-good configuration and test the result independently.

## Review questions

1. Why use a timezone-aware timestamp? **It helps compare events from different systems.**
2. Is high CPU proof of a coding defect? **No; investigate workloads, sampling and dependencies.**
3. What makes an incident report useful? **Reproducible observations, chronology, uncertainty, ownership and safe next actions.**

**Next:** Chapter 84 — full capstone and professional support handover.
