# C23 Maintenance Review — Updates 39 → 40 → 41

**Author:** Sammy Hegab · Umicom Foundation · MIT.

This is a deliberately offline training project. It links the Update 40
`btb-service-readiness-lib`, which already links the Update 39
`btb-sysadmin-evidence-lib`. It does **not** make or change real Windows or
Linux services, update software, read log files, invoke PowerShell scripts,
publish Git commits or execute deployments.

## What it teaches

An administrator proposes a bounded change, records the source revision and a
current baseline, obtains a *simulated* independent reviewer label, and checks
backup and rollback readiness. After starting a **fictional** change, a new
observation either verifies the same service identities or requires rollback.
A failed change cannot be marked complete. A restoration is recorded only after
an **independent** capture again proves the services ready. The code records
what an administrator should verify; it cannot claim that an operating system
actually restored anything.

The caller owns all structs. Summaries are copied, no pointers are retained,
operations are single-threaded, input labels and source identifiers are bounded,
and malformed requests preserve the complete prior record. No credentials,
hostnames, real financial data or secrets belong in training records.

## Build on Windows from the Bits2Banking repository

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\maintenance-review" -B ".\output\learning-build\maintenance-review" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\maintenance-review" --parallel 2
ctest --test-dir ".\output\learning-build\maintenance-review" --no-tests=error --output-on-failure
& ".\output\learning-build\maintenance-review\btb-maintenance-review-demo.exe"
```

If either earlier library is missing, merge Updates 39 and 40 first; never
copy their C sources into this project or add empty placeholders. The
registered tests include the earlier evidence/readiness regressions as well
as the new maintenance review test scenarios.

## Study route

1. Read `admin_evidence.h` and learn which observation states exist.
2. Read `service_readiness.h` to discover how dependencies propagate failure.
3. Read `maintenance_review.h` to find the additional lifecycle states.
4. Run the `ready-post`, `blocked-post`, `recovery-success`, `preserve` and
   `mutation` tests individually using `ctest -R`.
5. Explain why `RESTORED` is not `COMPLETE`, and why neither proves actual
   service health or permissions without trustworthy host evidence.

## Boundaries and limitations

No persistence, authentication, host-service control, policy engine, locking,
automatic rollback or Framework extension is delivered. Production Umicom
Framework remains the source of truth for reusable supervision, VCS,
configuration, audit, authentication and orchestration. All source comments and
previous implementations are preserved.
