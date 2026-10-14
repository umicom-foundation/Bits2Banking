# Part II Workbook — Controlled Administration and Evidence

**Complete these tasks only on a computer or virtual machine you own or are authorised to use.** A restricted system may refuse some observations; record that accurately. If you are under 18, ask a responsible adult or course leader before installing software or using remote services.

## Practical assessment (12 checkpoints)

| Checkpoint | Evidence to collect | Safe completion criterion |
|---|---|---|
| 25. Identity | `whoami` / `id` and one explanation | Correctly distinguish login account from privileges. |
| 26. Permissions | Owner and permissions of your training README | No private files opened, no broad permission changes. |
| 27. Windows services | One service name/status and one filtered event | No start/stop actions; event relevance explained. |
| 28. Linux service manager | `ps -p 1` and listed service or “unsupported” | No forced service installation or restart. |
| 29. Updates | One installed version and pending update inventory | No upgrades applied during observation. |
| 30. SSH | Local `ssh -V` and a host-key trust explanation | No private key disclosure or unknown remote access. |
| 31. Networks | DNS + TCP reachability difference | Port test not presented as application health. |
| 32. Storage | Available space for the actual practice filesystem | No cleanup or formatting without approval. |
| 33. Backup | SHA-256 of source, backup and restored sample file | Restoration demonstrated to a separate directory. |
| 34. Security | One potential secret-leak scenario | Safe reporting with no real credentials shared. |
| 35. Observability | Timeline with timestamp and time zone | Distinguish facts, hypotheses and missing data. |
| 36. Capstone | One-page handover with evidence and next owner | Every claim names a command and actual observed result. |

## Handover form (fill manually in a text editor)

**Incident title:**  
**Machine and OS (non-sensitive description):**  
**Date/time and time zone:**  
**Affected user action:**  
**Permission/consent received:**  
**Steps performed:**  
**Exact results:**  
**Tests NOT RUN and reasons:**  
**Private information redacted:**  
**Possible causes, with confidence:**  
**Next authorised action and responsible person:**  
**Recovery/rollback preparation:**  

## Self-review

Your evidence meets this course's standard when another learner can repeat every read-only check, the command runs in the appropriate shell, changes are clearly marked, and missing or denied checks are never called successes.
