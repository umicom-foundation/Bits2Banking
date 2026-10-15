# Stage 7 — Plain-English glossary and reference

**Umicom Foundation · System Administration From Zero**

| Term | Explanation | Practical meaning |
| --- | --- | --- |
| Access-control list (ACL) | Rules describing which identity can do something to a resource. | A user may read a file without being able to edit it. |
| Account | An identity known to a computer or application. | Human, service and emergency accounts have different responsibilities. |
| Alert | A notification about a condition that needs attention. | A certificate may approach expiry; an alert should reach a responsible owner. |
| Audit event | A record intended to support accountability. | Who approved a configuration or transaction change, and when? |
| Authorisation | A permission decision about an action and target. | A successful health test does not authorise a production restart. |
| Baseline | The approved reference state used for comparison. | A verified configuration revision, not just any old copy. |
| Certificate | A signed public-key identity statement with validity dates. | TLS clients use it while authenticating intended services. |
| Certificate authority (CA) | An entity that issues and signs certificates. | A chain must satisfy the client's trust policy. |
| Confidentiality | Information is visible only to authorised parties. | A service must not leak patient or customer data. |
| Configuration | Settings selected for a deployment. | Data directory, permitted listener address, logging level. |
| Credential | Proof presented to authenticate an identity. | A password, cryptographic key or certificate-based credential. |
| Drift | Difference between expected and observed state. | A configuration changed without a matching approved revision. |
| Endpoint protection | Security mechanisms on a computer. | Malware detection and other controls are not a full system audit. |
| Evidence capture | Observation recorded with its source and time. | Which test ran against which source and machine? |
| Group | Collection of accounts with shared access requirements. | Maintainers may have write access that ordinary readers lack. |
| Hash (SHA-256) | Fixed-length digest derived from bytes. | Useful for verifying exact file content equality, not proof of authorisation. |
| Integrity | Correctness and traceability of data and actions. | Balanced accounting entries and controlled edits. |
| Least privilege | Grant only access necessary for a job. | A Notes reader does not need release-deployment rights. |
| Maintenance window | Approved period and scope for a change. | An update is scheduled and can be safely monitored or rolled back. |
| Monitoring | Collecting and interpreting system signals over time. | Logs, metrics and status checks complement one another. |
| Patch | Software change intended to fix or improve behaviour. | Must be selected, tested and applied according to risk. |
| Redaction | Removing sensitive values from a report. | Share error codes without exposing account numbers or secrets. |
| Restore | Recover files or state from a saved copy. | A copied file still needs functional verification. |
| Rollback | Return a change to an earlier approved state. | “Failed and restored” is not the same as “new release passed”. |
| RPO | Recovery Point Objective—maximum tolerable data loss period. | How old can a recovery point be? |
| RTO | Recovery Time Objective—target time to restore service. | How long may an outage last before reaching the recovery target? |
| Secret | A protected private value. | Do not include passwords or keys in examples, Git or logs. |
| Service identity | Account used by software rather than a person. | Must have a limited scope and managed lifecycle. |
| TLS | Transport Layer Security. | Helps protect and authenticate network sessions. |
| Verification | Checking that an expected result actually occurred. | A restored file opens; a bank's journal reconciles. |

## Vocabulary that must not be confused

**Observed** means a tool or person recorded a result; it does not mean the result was approved. **Not verified** means no adequate evidence exists, even when a person expects the system is healthy. **Blocked** means the teaching policy rejects the candidate until required evidence is supplied. **Restored only** means previous operation recovered after a failed change. **Reviewable** means the fictional review record satisfies a modelled checklist; it does *not* mean “permitted to operate on a real computer”.
