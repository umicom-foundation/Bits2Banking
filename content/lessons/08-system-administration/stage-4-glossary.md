# Stage 4 Glossary — Managed Services and Recovery

Definitions are written for beginners; terms may have additional meanings in particular products. Always consult the installed system documentation for platform-specific behaviour.

| Term | Plain-English meaning |
|---|---|
| **Access denied** | The operating system refusing an operation under the current effective permissions. |
| **ACL** | Access-control list: rules describing who may perform operations on an object. |
| **After=** | An ordering relation: start this unit after another when both are scheduled. |
| **Alert** | A signal that an agreed threshold or check warrants attention. |
| **Baseline** | Measurements representing known, ordinary behaviour under stated conditions. |
| **Baseline capture** | A numbered observation of requirements before a change. |
| **Bind address** | The address on which a service accepts incoming connections. |
| **Change record** | A specific, reviewable description of the proposed work and its identity. |
| **Compatibility matrix** | A record of supported combinations of tools, runtimes and versions. |
| **Configuration** | Settings that influence a programme without changing its compiled code. |
| **cron** | Traditional Unix-like time-based job scheduler. |
| **Cutover** | The controlled step that directs users or traffic to a newly prepared environment. |
| **Dependency** | Another service or resource that must be available first. |
| **Environment variable** | A named value a process may inherit when it starts. |
| **Escalation** | Passing responsibility to an authorised specialist or decision owner. |
| **Exit code** | A number returned by a programme to indicate its completion status. |
| **Exposure** | Which other computers or users may reach a service, subject to routing and policy. |
| **False positive** | An alert that fires even though the relevant system is operating acceptably. |
| **Firewall profile** | A collection of traffic-control rules for a network context. |
| **Hypothesis** | A proposed explanation that has not yet been verified. |
| **Immutable backup** | A backup protected from unauthorised modification or deletion under a defined policy. |
| **Incident** | An unplanned interruption or reduction in expected service quality. |
| **Integrity hash** | A digest that helps compare file bytes when produced and trusted appropriately. |
| **Least privilege** | Give each service only the rights required for its declared duties. |
| **Listening socket** | A network endpoint waiting for connections. |
| **LocalSystem** | A highly privileged built-in Windows service identity; not a normal user account. |
| **Loopback** | Traffic addressed to the same host, commonly 127.0.0.1 or ::1. |
| **Maintenance window** | A planned period during which authorised changes may occur. |
| **Maker/checker** | A model in which one person proposes work and a different authorised person reviews it. |
| **Metric** | A numerical measurement such as available memory, disk space or process CPU time. |
| **Migration** | A controlled transformation of stored data or schema. |
| **Missed run** | A scheduled occurrence that was not executed, for example while the computer was off. |
| **Package manager** | A programme that locates, installs and updates software packages. |
| **Precedence** | The documented rule deciding which configuration source overrides another. |
| **Process scope** | Settings visible to a running process and, commonly, children it launches. |
| **Read-only inspection** | A command that reports status without requesting a configuration change. |
| **Readiness probe** | A functional test that decides whether the service can do its intended work. |
| **Ready** | A service has passed the checks required for its intended work, not merely started. |
| **Reconciliation** | Checking that recovered data agrees with authoritative expected records. |
| **Recovery point objective (RPO)** | The maximum acceptable amount of data loss measured backward in time. |
| **Recovery time objective (RTO)** | The targeted time to restore an acceptable service. |
| **Requires=** | A stronger unit dependency with failure implications; details depend on the transaction. |
| **Restart=** | A policy controlling whether systemd retries a terminated service. |
| **Restore** | Bring back data from a protected copy into a chosen location. |
| **Restore drill** | A planned test that recovers data and checks it can be used. |
| **Restore point** | A specific recoverable copy identified by date, version or immutable manifest. |
| **Restored** | A state where independently collected evidence shows a recovery condition, not a claim the upgrade succeeded. |
| **Retention** | How long a backup remains available before approved expiry. |
| **Rollback** | Return a changed system to an approved previous state. |
| **Rollback plan** | The documented steps to return to a verified previous state after a failed change. |
| **Rollback required** | A state indicating that failed verification needs approved recovery. |
| **Scheduled task** | A Windows definition for a command launched under specified conditions. |
| **Scope** | The users, components, locations and operations actually affected. |
| **Secret** | Sensitive information such as a password, token or private key. |
| **Secret reference** | An identifier that lets an authorised provider retrieve a secret without storing it in ordinary configuration. |
| **Service** | A programme managed by the operating system and often started automatically. |
| **Service account** | An account assigned to a programme for controlled access to resources. |
| **Service identity** | The operating-system account or security principal a service runs as. |
| **Service manager** | The system component that starts, tracks and stops services. |
| **Smoke test** | A small, focused check that essential functions still work after a change. |
| **Symptom** | What users or monitoring systems observe when something is wrong. |
| **systemd timer** | A unit that triggers another systemd unit on a time or event schedule. |
| **Threshold** | A value at which a measurement triggers review. |
| **Timeline** | Time-ordered observations and actions with source, clock and outcome. |
| **Trigger** | An event or timetable that requests a job start. |
| **Unit** | The name used by systemd for a managed service, timer or other object. |
| **Unit file** | Configuration describing a systemd service or another managed object. |
| **Verification gate** | A condition that must pass before a workflow can move on. |
| **Wants=** | A weaker relationship that requests another unit without the same failure coupling. |
| **Wildcard address** | An address such as 0.0.0.0 that accepts connections for multiple IPv4 interfaces. |

## Five distinctions to remember

- **Started** is not necessarily **ready**.
- **Scheduled** is not necessarily **completed**.
- **A copied file** is not necessarily **a recoverable backup**.
- **A reviewer label in a training model** is not **production approval**.
- **RESTORED** after a failed upgrade is not **COMPLETE**.
