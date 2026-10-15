# Stage 9 glossary — systems, packages and verified recovery

| Term | Meaning for an absolute beginner | Real operational distinction |
|---|---|---|
| Host | One computer or VM running an operating system | A label is not proof of machine identity. |
| Inventory | List of systems, purpose, owner and reviewed configuration | Entries need dates and sources; an old list can be inaccurate. |
| OS architecture | Processor/operating-system execution architecture such as x86-64 or ARM64 | Does not identify application source revision. |
| Patch | Change intended to fix or improve installed software | Deployment requires testing and an authorised window. |
| Process | Running instance of a program | May exist while a user request fails. |
| Service | Background application supervised by Windows SCM or Linux service manager | Service state is not business correctness. |
| Unit | systemd description of a service or other managed object | Not every Linux system uses systemd. |
| Journal | Time-ordered system log | Permissions and retention may limit what can be read. |
| Package provenance | Evidence of artifact source, publisher and version | A filename is not identity proof. |
| SHA-256 | A checksum used to identify exact file bytes | Hash equality is not a full vulnerability or recovery assessment. |
| Partition | Region of a storage device | Not identical to a filesystem or mount. |
| Mount | A directory location that exposes a filesystem | Mounts may be read-only even while a process runs. |
| DNS | Name-to-address lookup | Successful DNS says nothing about the destination application's health. |
| TCP port | Number used to reach a network endpoint | An open port is not a valid Notes save operation. |
| Clock skew | Difference between system clocks | Can change the apparent order of events. |
| Timeline | Ordered set of observed events, times and sources | Ordering alone does not establish causation. |
| Backup | Recoverable copy made under a documented procedure | Existence alone is not restore evidence. |
| RPO | Maximum tolerated data-loss interval | A measured drill can exceed the target. |
| RTO | Maximum tolerated recovery duration | Must be measured against the approved objective. |
| Canary | Limited initial deployment of a proposed change | A successful canary does not test all dependencies. |
| Rollback | Return to previous state/release | Independently verify recovery; it does not turn a failed update into success. |
| REVIEWABLE | A fictional teaching policy has enough valid evidence for review | Not production deployment approval. |
| RESTORED_ONLY | Previous revision independently recovered after failed change | Proposed new revision remains failed. |
