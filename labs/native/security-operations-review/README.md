# Native C23 security-operations review laboratory

**Bits2Banking · Major Update 44 · Umicom Foundation · MIT**

This is an **in-memory educational evidence gate**. It consumes the existing
`BtbRemoteReview` from Update 43 and therefore reuses the previously introduced
system-administration evidence, dependency readiness, maintenance, deployment and
remote-access models. No Git, SSH, Windows service, Linux unit, firewall,
credential, user account, log or filesystem operation occurs inside the library.

This teaching model does **not** independently attest to the truth of a submitted
flag. Its `REVIEWABLE` output means that a *fictional provided record* satisfies
an explicit teaching policy. It is **not operational authorisation**.

## Build on Windows with PowerShell 7 (interactive commands only)

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\security-operations-review -B .\output\learning-build\security-operations-review -G Ninja -DCMAKE_C_COMPILER='C:\msys64\ucrt64\bin\gcc.exe' -DBUILD_TESTING=ON
cmake --build .\output\learning-build\security-operations-review --parallel 2
ctest --test-dir .\output\learning-build\security-operations-review --output-on-failure --no-tests=error
& '.\output\learning-build\security-operations-review\btb-security-operations-demo.exe'
```

## Build on Linux

```bash
cmake -S labs/native/security-operations-review -B output/learning-build/security-operations-review -G Ninja -DCMAKE_C_COMPILER=gcc -DBUILD_TESTING=ON
cmake --build output/learning-build/security-operations-review --parallel 2
ctest --test-dir output/learning-build/security-operations-review --output-on-failure --no-tests=error
./output/learning-build/security-operations-review/btb-security-operations-demo
```

## Test cases

New tests include a positive fictional scenario; missing account, group,
privilege, configuration, drift, patch, restore, audit, credential, rotation,
certificate, independent approval and monitoring evidence; stale observations;
time-window checks; invalid and conflicting identities; immutable attachment;
upstream rollback; restored-only results; failure-atomic output; and 25,000
reproducible mutations.

**Ownership:** input and output structs are caller-owned. Initialisation and
attachment copy their input. An invalid call leaves the destination unchanged.
Caller code must not treat labels as access credentials or status as a system
control decision. The shared native Umicom Framework owns real production
platform security, configuration and observability functionality.
