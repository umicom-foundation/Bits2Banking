# Chapter 295 — Capstone: from a support incident to Framework readiness evidence

**Bits to Banking · Native engineering and system administration · ISO C23**

## Problem: Umicom Notes appears to run but users cannot open a document

This capstone joins System Administration Chapters 37–48 with native C23 contract design. You are investigating a **fictional** Umicom Notes application. A presentation window is visible, but document reads fail intermittently. A teammate suggests restarting the service and changing its storage permissions. Before any change you need actual evidence, a safe hypothesis and an appropriate owner.

The fictional notes service depends on a document storage component. Its required operational check is a successful authorised read. The storage component's required check is access to the correct configured practice directory. The UI's cosmetic indicator is optional and must not overrule required service failures.

## Step 1 — Record the incident as facts

| Field | Example classroom entry |
|---|---|
| Incident | `PRACTICE-NOTES-01` (fictional) |
| Time | A timestamp recorded during your lesson, with timezone |
| Symptom | Document cannot be opened using the expected practice action |
| Process state | Window visible; not evidence of successful read |
| Storage check | `FAIL` (fictional worksheet) |
| Notes read check | `NOT RUN` (not tested this capture) |
| Backup | An older copy exists; current recoverability unverified |
| Initial decision | **BLOCKED**, pending required checks |

Do not paste a real user's home directory, account names, cloud access tokens or sensitive logs into a public incident. A support report can share the necessary error category and redacted path without disclosing personal records.

## Step 2 — Decide which components own each responsibility

**System administrator:** obtains permission, observes operating-system facts and proposes safe changes. **Umicom Framework:** owns reusable service supervision, application runtime, filesystem contracts, monitoring, build/test processes and repository management. **Umicom Notes module:** owns note-specific business behaviour, not shared process, VCS or permissions infrastructure. **Teaching laboratory:** merely evaluates supplied fictional states and does not modify the host.

If a Framework service already exists, reuse it. Do not create a new PowerShell or Python implementation to inspect live systems. Do not move a teaching queue, diagnostic parser or readiness evaluator wholesale into Framework without reviewing existing public interfaces and lifetime contracts.

## Step 3 — Reproduce the classroom failure

In the native `labs/native/service-readiness` source, identify `TestInheritedBlock`: storage check FAIL and Notes check PASS. Run the case:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
ctest --test-dir ".\output\learning-build\service-readiness" -R "service-readiness.inherited-block" --no-tests=error --output-on-failure
```

The test should pass because it **correctly expects** a BLOCKED decision for Notes. Passing the test does not mean the fictional Notes service is healthy. Be precise about what the test proves.

Next run `stale`, `missing-dependency`, `cycle` and `preserve`. Explain to a peer why each refusal protects the integrity of the result. Finally run the full 32-case suite including Update 39's earlier checks.

## Step 4 — Draft a safe recovery proposal

A defensible proposal might be:

1. Confirm the configured practice storage path and account context, without changing permissions.
2. Check the actual volume and available capacity; capture errors with time context.
3. Inspect only the relevant and authorised application log, keeping the original evidence private.
4. Verify whether a suitable backup exists and restore to a **separate review path** if recovery is authorised.
5. Make an approved, narrow change in the owning component; preserve existing code and comments.
6. Re-run the required Notes read test plus relevant Framework integration and regressions on the target revision.
7. Record the exact source commit, test results, OS/compiler and rollback path before announcing recovery.

Neither `git reset --hard` nor broad ACL changes nor a blanket service restart is justified merely by the information given. The exercise provides an evidence deficit, not a licence to modify a real host.

## Step 5 — Explain what remains to be validated

The Update 40 laboratory is deterministic and offline. It has no systemd backend, Windows Service Control Manager adapter, network listener or production service identity. Real integration into Umicom Framework would require review of existing supervision, security, observability and value contracts; explicit permissions; error provenance; concurrency rules; correct persistence authority; and platform-specific tests.

The current ZIP is scoped to **Bits2Banking only**. It does not edit Umicom Framework, OS, Kernel or Applications. Do not claim those components were changed or that a real service was qualified.

## Final assessment

Explain, without reading notes: (a) why a running process can still be unready; (b) why a backup hash is not a full recovery test; (c) why missing or stale required observations block readiness; (d) where shared runtime functionality belongs in Umicom; (e) which Git commands may be used safely to inspect a repository before committing; and (f) why test and release results must identify their source revision.

A sound final statement is: **“The evaluation engine is functioning, but the fictional service is blocked because required current evidence is missing or failing. No production change has been authorised.”**

**Continue:** [System Administration Stage 3 Index](../08-system-administration/advanced-index.md) and [native C23 laboratory README](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/service-readiness).
