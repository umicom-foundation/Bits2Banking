# Stage 3 Practical Workbook — Read, Check, Explain

**System Administration: From Zero · Chapters 37–48**

Print this workbook or copy its questions into a practice notebook. Use fictional data whenever a device or organisation policy prevents access. Record real results rather than the example values.

## Exercise A — Baseline (Chapters 37–38)

1. Write your chosen practice-folder path and why it is safe.
2. Record OS family, PowerShell/Bash environment, architecture and a timezone-aware observation time.
3. Explain what an unavailable tool means. Can you conclude it is not installed from an unsuccessful command alone?

**Evidence:** one table of `item / command / observed result / time / limitation`.

## Exercise B — Ownership and files (Chapters 39–42)

1. Sketch identity → group → resource permission → permitted action.
2. Draw disk → partition/volume → mount point → practice folder.
3. Complete the practice Notes backup from Chapter 41: show **source**, **backup** and **restored** file paths and their SHA-256 values.
4. Explain two reasons why access can be denied without a software defect.

**Evidence:** a safe storage map and a verified, non-overwriting restore.

## Exercise C — Connections and security (Chapters 43–44)

1. Trace domain name → DNS → address → TCP port → HTTP application response.
2. What could cause a TCP connection to fail after DNS succeeds?
3. Why is a loopback-only server preferable for a first local C23 lesson?
4. Which observation would you collect before considering a firewall-rule change?

**Evidence:** one diagram and two hypotheses with distinct checks.

## Exercise D — Service and updates (Chapters 45–46)

1. Define liveness, readiness and degraded operation in your own words.
2. Complete a fictitious maintenance proposal for a compiler upgrade: owner, old/new version, approval, baseline, tests and rollback.
3. Explain why process Running and test PASS are different claims.

**Evidence:** one five-field service health checklist and one maintenance record.

## Exercise E — Incident capstone (Chapters 47–48)

Fictional evidence: Notes process runs; storage check FAIL; yesterday's backup PASS; current save/read NOT RUN; DNS optional WARNING.

1. List what is known and what is uncertain.
2. Decide READY, REVIEW or BLOCKED and justify it.
3. Explain which check to perform next and whose approval would be needed for a restore.
4. Use the Update 40 C23 service-readiness demonstration to connect a blocked storage prerequisite to an application result. Do not mistake the fictional test for a real service probe.

### Suggested answers

A. Missing access might mean disabled command, missing module, wrong PATH or denied permission; record the exact message rather than claiming absence.  
B. Backup is not proven until hashes and a separate restore are checked.  
C. DNS success does not establish listener/TCP/TLS/application health.  
D. A running process can have failed dependencies or incorrect output.  
E. **BLOCKED**: a required dependency failed, a current business-operation test was not run, and yesterday's backup is not current readiness evidence.

## Marking rubric

| Criterion | Beginning | Developing | Ready for next stage |
|---|---|---|---|
| Safety | Cannot identify boundary | Knows to ask permission | Keeps work scoped and never bypasses controls |
| Evidence | Copies expected result | Records some actual results | Records actual results/time/limitations |
| Commands | Runs without explaining | Can describe basic purpose | Chooses the least risky relevant command |
| Recovery | Assumes copy is enough | Verifies backup hash | Restores to a separate location and verifies |
| Incident judgement | Guesses a cause | Separates some observations | States facts, hypotheses, missing checks and plan |

There is no required administrator access, live cloud account or production server in this workbook.
