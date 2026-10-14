# Update 39 — Technical and educational overview

## Scope and continuity

This delivery advances the dedicated **System Administration: From Zero** course from Chapter 24 through Chapter 36 without replacing the original Chapter 1–24 files. The cumulative offline course includes all 36 system-administration chapters and embeds earlier illustrations from Update 38. The original contributed `umicom-new-project-beginner-guide-original.html` is retained in the existing repository and linked by the new intermediate index; it is not duplicated or altered in this additive batch.

## Learner-centred coverage

Part II covers identity/groups, NTFS and Linux access models, Windows services and Event Viewer, Linux systemd, software updates, SSH trust, DNS/TCP troubleshooting, filesystem capacity, backup/restoration, credential safety, metrics/logs and incident response. Every chapter defines terms before using them, provides PowerShell and Linux terminal paths, identifies observable output and failure cases, uses sandbox-only practice files where writes are unavoidable, and ends with exercises and suggested answers.

## Native laboratory

`labs/native/sysadmin-evidence` is an independent, **fictional** evidence-policy evaluator implemented entirely in ISO C23. It copies up to 16 observations with check IDs in 1..32, a nonzero capture identifier, a state and a NUL-terminated 64-byte label. The caller specifies required IDs using a `uint32_t` bitmask. The evaluator returns READY, REVIEW or BLOCKED for this model while preserving the output report on invalid input. Missing/stale/failed/unrun required checks block readiness. Optional adverse checks cause REVIEW; they cannot be silently promoted to READY. No side effects or live OS reads occur.

This is not a monitoring service, real permissions checker or substitute for Umicom Framework. Production integration should use the established Framework contracts: repository/VCS observation, system services, diagnostics, build plans and audit where relevant. A new reusable production component requires explicit Framework-first review.

## Ownership and compatibility

- Preserve authorship and licences in every source and guide.
- New source: **C23 only**, CMake is declarative build metadata.
- No Python, PowerShell or JavaScript implementation scripts are added.
- PowerShell and Bash examples are for *interactive instruction*, not packaged automation.
- No existing code or educational content is deleted or replaced by this update.
- All Git commit instructions use main; no branch creation is required for the owner's delivery workflow.

## Qualification boundaries

Focus tests check the native evidence model and its failure-atomic behaviour. Linux compiler/sanitizer success does not imply Windows UCRT64 acceptance. The MkDocs publisher, remote GitHub Pages, actual service managers and the project owner's computer have not been exercised by this package; they remain explicit acceptance steps.
