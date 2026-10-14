# Stage 3 — Practical Infrastructure Glossary

**Use alongside Chapters 37–48.** These definitions are short enough for a first reading; the lessons give examples and important exceptions.

| Term | Explanation | Example |
|---|---|---|
| Host | Physical computer that runs a VM. | A Windows laptop running a Linux guest. |
| Guest | An OS inside a VM. | A training Linux desktop. |
| Baseline | Recorded system state before a change. | Windows version, Git version and date. |
| Drift | A relevant change compared with a baseline. | A compiler selected from a new PATH entry. |
| Security principal | Account or identity to which rights apply. | A named user or service account. |
| Scheduled task | Declarative job with trigger, identity and action. | A daily approved report. |
| Volume | Logical storage unit, possibly mounted as C: or /home. | A project build volume. |
| Restore test | A checked recovery using backup data. | Copying an archived note to a separate folder. |
| ACL | Ordered or platform-defined set of access rules. | Read permission on a practice folder. |
| DNS | Service mapping names to records. | Resolving example.org. |
| TCP port | Endpoint within a transport connection. | Loopback port 8765 for a local lesson. |
| Firewall | Policy controlling network traffic. | Allowing selected inbound connections. |
| Liveness | Narrow indication a process is responsive. | A process still running. |
| Readiness | Evidence a service can perform assigned work. | A successful authorised Notes read. |
| Dependency | Another component required to succeed. | Notes service needs document storage. |
| Maintenance window | Agreed time to perform a controlled change. | A scheduled toolchain upgrade. |
| Incident timeline | Ordered observations about a problem. | Service error before a failed read request. |
| Correlation ID | Identifier connecting records for one action. | An operation ID shared across request and log. |
| Failure-atomic | Invalid operation preserves prior state/output. | Rejected service check does not replace report. |
| NOT RUN | A required check was not performed. | Build test not executed on Windows. |
| BLOCKED | Required evidence is missing, stale or adverse. | Storage unreadable for Notes. |
| REVIEW | Required checks pass but a nonessential issue needs review. | An optional metric is unavailable. |
| READY | All declared checks passed in the specific model and capture. | Fictional C23 readiness snapshot, not production certification. |

A green training result does not grant real administrative permissions or prove production readiness. That decision belongs to the actual service owner and operational policy.
