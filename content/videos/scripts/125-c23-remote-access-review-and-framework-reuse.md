# Episode 125 — C23 Remote Access Review and Framework Reuse

**Bits2Banking · Umicom Foundation · Target: 12–15 minutes**  
**Related chapters:** System Administration 84; Engineering 304–307.

## Objective

Build the offline C23 lab, observe failure-closed review and explain why reusable production authentication belongs in Umicom Framework, not in an educational repository.

## Segment 1 — The composition chain

Show [the Update 39–43 evidence chain](../../assets/diagrams/sysadmin-remote-support-evidence-update43.svg). Explain why each library retains authority over its original work: evidence, service readiness, maintenance, deployment and the new remote preflight decision. The new library links the prior targets instead of copying code.

## Segment 2 — Build and test

In PowerShell 7 from the Bits2Banking repository:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\remote-access-review -B .\output\learning-build\remote-access-review -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build .\output\learning-build\remote-access-review --parallel 2
ctest --test-dir .\output\learning-build\remote-access-review --no-tests=error --output-on-failure
```

Show the **actual** local result and stop if it fails. Do not claim Windows passed merely because a Linux reference report passed.

## Segment 3 — Run negative checks

Demonstrate the named cases `host-key`, `stale`, `rollback`, `restored` and `atomic-output`. Explain why an invalid plan leaves the caller's result unchanged. Call out the difference between `BLOCKED`, `REVIEWABLE` and `RESTORED_ONLY`.

## Segment 4 — Where production code belongs

The instructor opens public Umicom Framework security, VCS and build APIs for reading, without adding any duplicate authentication code. Note that `BtbRemoteReview` does **not** verify a host key, read a real clock, authenticate an operator or grant a real permission. If the project later needs production remote administration, it requires a separate owner-approved architecture and security review.

## Closing activity

Students submit a redacted report showing source revision, toolchain, actual test count, negative test outcomes, and remaining unverified integration gates. No key material or machine secrets are requested.
