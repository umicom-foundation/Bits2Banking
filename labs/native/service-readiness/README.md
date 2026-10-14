# Service Readiness — Composing Existing C23 Evidence (Major Update 40)

**Bits2Banking | Umicom Foundation | Sammy Hegab | MIT**

This is a **classroom-only, deterministic C23 laboratory**. It composes the existing `labs/native/sysadmin-evidence` library introduced in Update 39. It never inspects, starts, stops or changes real host processes, services, firewalls, files, Git or data; it reads only caller-supplied fictional observations. There is **no Python or PowerShell implementation script**.

## Source layout and ownership

| File | Responsibility |
|---|---|
| `service_readiness.h` | Stable teaching API for up to eight service records with identifiers 1–32 and explicit prerequisites. |
| `service_readiness.c` | Dependency validation, cycle detection and aggregated readiness decisions; calls existing `BtbAdminReviewEvaluate`. |
| `test_readiness.c` | Fifteen named deterministic scenarios and 50,000 mutation rounds. |
| `main.c` | Fictional Umicom Notes storage → application demonstration. |
| `CMakeLists.txt` | Links Update 39's library from `../sysadmin-evidence`, retaining its 16 CTest cases. |

The graph is **caller-owned** and uses copied values, not borrowed pointers to a caller's temporary stack buffers. Rejected registration or attachment preserves existing graph state. Graph evaluation assigns the output only after the entire dependency graph is valid. An evaluation return code of `BTB_SERVICE_OK` is not the same as `BTB_ADMIN_READY` for every service.

## Build on Windows (PowerShell commands, not a script)

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\service-readiness" -B ".\output\learning-build\service-readiness" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\service-readiness" --parallel 2
ctest --test-dir ".\output\learning-build\service-readiness" --no-tests=error --output-on-failure
& ".\output\learning-build\service-readiness\btb-service-readiness-demo.exe"
```

**Expected registered cases:** 32 total: 16 new and 16 from the unchanged Update 39 library. If `../sysadmin-evidence` is missing, CMake explicitly refuses configuration and instructs you to merge Update 39. Do not copy the old implementation into this directory.

## Build on Linux

```bash
cmake -S labs/native/service-readiness -B output/learning-build/service-readiness -G Ninja -DCMAKE_C_COMPILER=gcc -DBUILD_TESTING=ON
cmake --build output/learning-build/service-readiness --parallel 2
ctest --test-dir output/learning-build/service-readiness --no-tests=error --output-on-failure
./output/learning-build/service-readiness/btb-service-readiness-demo
```

## Safety boundaries and limitations

- Lab identifiers and labels are **not authenticated service identities**.
- The capture ID is a logical teaching-session identifier, not a real timestamp or cryptographic signature.
- The graph's result must not be used to authorise a real restart, payment, trading order, configuration change or release.
- A dependency cycle or missing dependency is an evaluation error; a BLOCKED outcome can be a **successfully evaluated** but unhealthy fictional service.
- There is no concurrency, durable state, real service probing or automatic recovery.
- **Production logic belongs in existing Umicom Framework services** after review of public contracts and tests.
