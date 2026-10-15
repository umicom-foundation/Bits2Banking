# Major Update 45 — Technical architecture and educational scope

**Title:** System Administration Stage 8 — recurring maintenance, monitoring, capacity planning, recovery and responsible native C23 evidence.

## What is delivered

The cumulative System Administration course adds **Chapters 97–108** while preserving the 96 earlier chapter bodies. Topics include scheduled tasks on Windows, cron and systemd timers on Linux, alerts and incident ownership, disk/queue capacity, backups, RPO/RTO, disaster recovery, change windows, multi-host inventories and service-account security. Six new Stage 8 reference documents guide instructors and learners. Four engineering chapters (312–315) explain the native architecture. Five video scripts (Episodes 131–135) and eight original editable SVG diagrams support practical instruction.

A complete offline HTML edition contains **108 chapters** with new SVGs embedded as base64 data. The original New Project Beginner Guide remains retained in the earlier Update 38 repository path `content/assets/reference/umicom-new-project-beginner-guide-original.html`; this batch does not alter it or claim to have implemented its future automatic module-discovery design.

## Source and component reuse

`labs/native/operational-resilience` is a small C23 teaching layer. It imports the **original** Update 44 CMake project, which imports its previous library chain:

```
Update 39: sysadmin-evidence
   ↓
Update 40: service-readiness
   ↓
Update 41: maintenance-review
   ↓
Update 42: deployment-rehearsal
   ↓
Update 43: remote-access-review
   ↓
Update 44: security-operations-review
   ↓
Update 45: operational-resilience
```

The new `BtbOpsReview` copies the previous `BtbSecurityReview` instead of parsing or recreating prior evidence. `BtbOpsEvaluate` calls `BtbSecurityEvaluate` and adds only **educational** age, response, capacity and recovery-objective checks. The new source does not implement a production scheduler, collector, backup, filesystem editor, Git client, GUI, security authority or network stack. Reusable production capabilities must be evaluated against **Umicom Framework** before any native extension in C23/Assembly.

## Explicit contracts

- **Identity:** exact service label and full 40/64-hex source revision must match upstream review and current observation.
- **Ownership:** API parameters are borrowed during calls; successful Init/Attach copy values into caller-owned records.
- **Atomic refusal:** invalid inputs and mismatched revisions leave output and review unchanged.
- **Timeliness:** heartbeat, backup and restore timestamps use one fictional seconds domain and must not be in the future relative to their observation time; missing observations are distinct from stale ones.
- **Capacity:** an observed queued-job count exceeding the declared bound is an explicit blocker.
- **Recovery:** estimated data loss is compared against RPO; measured restoration duration is compared against RTO. They are independent metrics.
- **Alert safety:** a response owner, tested alert route, independent restore and redacted audit evidence are independently required.
- **Upstream:** an old-generation `RESTORED_ONLY` result remains `RESTORED_ONLY` and cannot be promoted into a successful new-generation review.
- **Cadence:** `BtbOpsNextDue` demonstrates checked unsigned addition without creating a timer. Overflow cannot silently wrap.

### Important limits

This is an **offline policy model** with fictional flags. A `REVIEWABLE` result means only that the test values satisfy declared classroom gates. It does not prove that any live service, alert, backup, certificate or configuration was inspected. It never grants permission for operations. Real timekeeping requires explicit clock domains, timezone records and operational monotonic elapsed-time measurement. Real scheduling, permissions and audit should use the existing Umicom Framework and OS contracts.

## Publication and compatibility

All additions use the established locations under `content/lessons/08-system-administration`, `content/lessons/05-engineering`, `content/videos/scripts`, `content/assets/diagrams`, and `labs/native`. The root contains only new Update 45 documentation. No existing source/feature/header/comment is replaced or deleted. The MkDocs navigation is deliberately an **additive snippet**, requiring a careful review against the user's current `mkdocs.yml`.
