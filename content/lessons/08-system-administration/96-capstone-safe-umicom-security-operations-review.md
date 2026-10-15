# Chapter 96 — Capstone: a safe Umicom security-operations review

**Bits to Banking · System Administration From Zero · Stage 7**  
**Prerequisite:** Chapters 1–95. **Scope:** An entirely fictional Umicom Notes training deployment and the in-memory C23 laboratory. **No real account, credential, firewall or service is changed.**

## Your assignment

You are a junior administrator supporting the fictional `notes.training.invalid` training service. The team proposes a service credential rotation and a software security update. Your mentor asks you to prepare a review **without connecting to a production host**. Some evidence is deliberately missing so you must make an explicit judgement rather than simply tick every box.

The fictional facts are: source revision and configuration digest have been recorded; a reviewer approved the planned window; the app reportedly starts; the access matrix has been reviewed; the monitoring alert route has **not** been checked; and an independent backup restore drill has **not** been performed. An unrelated certificate may also be approaching its expiry date. These are case-study statements, not live evidence.

![Combine all Stage 7 observations into one reviewed decision](../../assets/diagrams/sysadmin-security-review-lifecycle-update44.svg)

## Part A — Understand the 13 security checks

The native `BtbSecurityEvidence` teaching record contains flags for account review, group review, least privilege, configuration comparison, unexplained drift, patch evidence, independent restore testing, audit-retention review, credential safety, rotation-plan review, certificate review, independent approval and the monitoring response path.

A value of `1` means only **the fictional test input claims an observation**. It is not a proof that a real computer was scanned or a password was rotated. For the reported case, the restore and monitoring flags must remain `0`: they are **missing evidence**, not passed controls. This is the principal lesson of the capstone.

## Part B — Build the C23 model on Windows

Open PowerShell 7. Merge Updates 39–43 first; Update 44 consumes their original source libraries. From the Bits2Banking repository, type:

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S '.\labs\native\security-operations-review' -B '.\output\learning-build\security-operations-review' -G Ninja -DCMAKE_C_COMPILER='C:\msys64\ucrt64\bin\gcc.exe' -DBUILD_TESTING=ON
cmake --build '.\output\learning-build\security-operations-review' --parallel 2
ctest --test-dir '.\output\learning-build\security-operations-review' --no-tests=error --output-on-failure
```

Only after building successfully, run the harmless demonstration:

```powershell
& '.\output\learning-build\security-operations-review\btb-security-operations-demo.exe'
```

It prints a fictional **REVIEWABLE** case and a **BLOCKED** case where the independent restore observation is withheld. Note that `REVIEWABLE` is not permission to administer any real service.

## Part C — Run the same learning target on Linux

```bash
cmake -S labs/native/security-operations-review -B output/learning-build/security-operations-review -G Ninja -DBUILD_TESTING=ON
cmake --build output/learning-build/security-operations-review --parallel 2
ctest --test-dir output/learning-build/security-operations-review --no-tests=error --output-on-failure
```

**Expected:** The CTest suite includes the new named cases and the earlier regression cases. The count comes from the actual CMake configuration. An unavailable compiler, missing previous chapter lab or failed test must be recorded honestly, not silently skipped.

## Part D — Write an evidence-based handover

Create a table with columns *check*, *claimed observation*, *independently verified?*, *owner* and *next action*. Enter at least five rows. For the missing restore drill, propose a controlled test by a qualified operator; do not perform recovery yourself. For the monitoring path, ask the monitoring owner for a safe test and expected alert route. For the certificate, request an authorised expiry review of the **correct endpoint** rather than trusting an unrelated local certificate.

Now summarise the recommendation in no more than eight sentences. It should say that the fictional change is **not yet qualified** because required evidence is missing. The language should distinguish source and configuration identity, proposed work, observations, blocked gates and next decisions.

## Part E — Investigate a failure instead of bypassing a rule

Run the `bits2banking.security-operations.restore` CTest case and explain which flag was withheld. Then run `bits2banking.security-operations.upstream-restored`. Explain why a restored **old** release must not be labelled as a successful **new** release. The exercise proves the policy model's behaviour, not operational recovery.

## Assessment and suggested answers

**1. Why does a correct SHA-256 digest not prove a service is secure?** It proves a specific byte comparison, not permissions, secrets handling, effective runtime configuration or authorisation.

**2. Who makes the real decision to rotate credentials?** An authorised accountable operator under the approved policy and change process.

**3. What should the report say about a missing restore drill?** “Not verified—change not qualified; owner and follow-up required.”

**4. What may be published from this fictional test?** Source code, generated training statuses, fictional labels and redacted test outcomes—never real credentials, customer data or private infrastructure identifiers.

## Source-preservation and architecture boundary

Do not replace the Umicom Framework's identity, audit, configuration or repository-control services with an ad hoc application script. The C23 training code is intentionally offline and must first be compared against the Framework public interfaces before being considered for production reuse. Existing educational source is preserved in full.

**Next:** Stage 8—production-style monitoring, safe recovery rehearsals and multi-machine operational fundamentals.
