# Stage 9 template — two-host support and recovery report

**All names below are fictional. Replace only with authorised, appropriately redacted observations in real support work.**

## Incident overview

- Support case identifier:
- Reporter and authorised incident owner:
- Time opened (with UTC offset):
- Affected functionality (for example, Notes save):
- User impact known / unknown:
- Existing approved application revision:
- Proposed revision and package SHA-256:

## Inventory

| Host ID | Host purpose | Owner | Operating system | Observed time | Verified? |
|---|---|---|---|---|---|
| notes-gateway | Requests / API | Example owner | Not observed | Not observed | No |
| notes-storage | Persistent documents | Example owner | Not observed | Not observed | No |

## Observations and caveats

| Host | Time and source | Exact observation | What it does NOT prove | Next safe check |
|---|---|---|---|---|
| notes-gateway | | | | |
| notes-storage | | | | |

Record suspected clock skew, missing logs, package mismatch, permissions and storage mount state as separate fields. Do not replace an original observation with a later hypothesis.

## Release and recovery decision

- Proposed release status (Passed / Failed / Not Run / Blocked):
- Previous release status (not restored / restoration attempted / independently verified restored):
- Backup last verified via a restore:
- RPO target and measured loss:
- RTO target and measured duration:
- Business-facing operation verified by:
- Independent reviewer and time:

**Closure rule:** `RESTORED_ONLY` is not success for a failed proposed release. An online socket does not establish business correctness. Record remaining unknowns and the responsible next owner.
