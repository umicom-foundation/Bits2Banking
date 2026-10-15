# Stage 8 glossary — operations and recovery

These definitions are intended to be read before the technical lessons. Each includes a practical example rather than expecting the learner to memorise a dictionary.

| Term | Meaning | Umicom Notes training example |
|---|---|---|
| Scheduler | Tool that requests work at times or events | Ask for a daily practice export |
| Trigger | Rule that starts a scheduled job | Every weekday at 09:00 |
| Scheduled task | Named job with trigger and action | Verify a report exists |
| Cron | Traditional Linux time-based scheduler | Read your own entries with `crontab -l` |
| Systemd timer | Timer unit linked to service activation | View the last/next activation |
| Observation | Information gathered from a named source | Disk free space at 10:15 |
| Evidence | Observation with time, context and relevant identity | Same sample revision and timestamp |
| Monitoring | Repeated observations to identify change | Track queue depth over time |
| Alert | Notification that calls for a response | Notes save test failed |
| Acknowledgement | Someone accepts responsibility | Named on-call person begins triage |
| Incident | Unplanned service disruption | Students cannot save documents |
| Escalation | Passing a problem to its designated owner | Refer to storage service specialist |
| Threshold | Value chosen to trigger review | Queue greater than five jobs |
| Capacity | Maximum useful work or storage within constraints | Available disk space for Notes files |
| Saturation | A component cannot keep up with demand | Exports arrive faster than processing |
| RPO | Recovery Point Objective: maximum tolerable data-loss age | No more than 15 minutes of saved work lost |
| RTO | Recovery Time Objective: maximum planned restoration duration | Usable Notes service within two hours |
| Backup | A retained copy made for recovery | Copy of training Notes data |
| Restore | Recover information from a backup | Reopen restored sample document |
| Restore drill | Controlled rehearsal verifying the recovery process | Separate practice directory + functional check |
| Retention | Policy for how long backup copies remain | Several daily and monthly generations |
| Change window | Agreed period for specified work | Saturday 10:00–11:00 UTC |
| Approval | Explicit decision by authorised person | Reviewer accepts a change plan |
| Rollback | Return to a previous state after failure | Restore earlier known working revision |
| Restored-only | Old version recovered; new deployment still failed | Do not record upgrade success |
| Inventory | List of hosts, roles and dependencies | Notes desktop, service and storage |
| Clock skew | Difference between clocks used by different machines | Log order appears reversed |
| Correlation ID | Identifier linking events from one operation | Same saved-document request through two services |
| Least privilege | Grant only necessary access | Export job writes only to its export folder |
| Audit trail | Protected record of decisions and actions | Ticket + who reviewed + time + result |
| Failure-atomic | A rejected operation does not partially change owned state | C23 training API preserves caller output on invalid input |

**Check your understanding:** Can you explain how a cron entry differs from evidence that a job finished? Can you explain why restoring old software does not prove a new update succeeded? If not, revisit Chapters 97, 99 and 105.
