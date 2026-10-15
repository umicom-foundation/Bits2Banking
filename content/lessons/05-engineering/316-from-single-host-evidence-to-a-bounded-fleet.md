# Chapter 316 — From single-host evidence to a bounded C23 fleet review

**Bits to Banking · C23 engineering track · Umicom Foundation**  
**Required reading:** System Administration Chapters 109, 116, 118 and the Update 45 operational-readiness source.  
**Laboratory:** `labs/native/fleet-readiness`.

## Why a new composition is necessary

A service can depend on two different machines. A gateway may handle HTTP correctly while storage fails its own write checks. Update 45 already built a C23 educational evaluator for one service: `BtbOpsEvaluate`. Rather than copying all its heartbeat, backup, RPO, RTO, reviewer and recovery rules into a second service, Update 46 **composes its existing result** for every required host. In an actual Umicom product this aggregation belongs in Framework's service and observability contracts; the course repository supplies only a bounded, offline teaching example.

The illustration separates machine identity, release identity, observed evidence and decision. These are different fields. A host name such as `notes-storage` is not an authenticated remote endpoint; a fictional source commit is not proof that its bytes were installed; a package checksum is only a byte-identity claim. A real implementation would obtain these assertions through authorised Framework-owned adapters and inspect provenance.

![The two-host review flow](../../assets/diagrams/sysadmin-fleet-inventory-update46.svg)

## Read the public contract before the implementation

Open `labs/native/fleet-readiness/fleet_readiness.h`. Identify `BtbFleetPolicy`, `BtbFleetHostEvidence`, `BtbFleetReview` and `BtbFleetDecision`. Policy is a caller-owned value containing the required host names, one expected commit identity, one 64-character SHA-256 artifact digest, an observation-time boundary and a maximum evidence age. Host evidence includes a **copied** `BtbOpsReview`, not a pointer to a temporary stack object. The new module stores at most four hosts so learners can inspect the complete state with a debugger. It is not a scalable fleet agent.

Why do we copy? Suppose a function borrowed the address of a local record built by a caller. After that caller returns, a dangling pointer could appear to contain a valid previous observation or arbitrary memory. With by-value copies, the lifetime is explicit. The functions are still not thread-safe; a shared mutable review must be serialised externally.

## Failure-atomic registration

`BtbFleetInit` validates the count, duplicate host names, lower-case hexadecimal identities and nonzero review window before replacing `outReview`. `BtbFleetAttach` validates an externally supplied record and refuses unregistered or duplicate host identities without changing the previous review. `BtbFleetEvaluate` constructs a local result and assigns it to the caller only after all input is validated. An invalid host flag therefore cannot partially corrupt an existing decision.

There is an important nuance: a **valid record can describe a failed service**. `BtbOpsEvaluate` may return OK as an API call while its decision is BLOCKED. The fleet aggregator must preserve that semantic distinction; an API success does not mean the service is ready.

## Run the laboratory

From PowerShell 7, after merging Updates 39–46:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\fleet-readiness" -B ".\output\learning-build\fleet-readiness" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\fleet-readiness" --parallel 2
ctest --test-dir ".\output\learning-build\fleet-readiness" --no-tests=error --output-on-failure
```

These are interactive terminal commands, not PowerShell project scripts. On Linux use the same CMake source folder with `-DCMAKE_C_COMPILER=gcc` and a Linux output directory.

## Questions and review answers

1. **What if gateway evidence is present but storage evidence is missing?** `PENDING` and a missing-host issue. No change is authorised.
2. **Why not reimplement backup evaluation?** The original `BtbOpsEvaluate` remains responsible for that contract. Duplicate rules drift and invalidate evidence.
3. **Can a green fleet decision deploy an application?** No. This is a policy simulation using fictional evidence, not a production permission system.
4. **What if an externally supplied host claims an unregistered name?** Refuse the attach and preserve the existing review.

**Next:** Chapter 317 examines the decision states and why a restored previous version is not a successful new release.
