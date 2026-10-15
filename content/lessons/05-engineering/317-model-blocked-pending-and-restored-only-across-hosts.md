# Chapter 317 — Model blocked, pending and restored-only outcomes across hosts

**Bits to Banking · C23 engineering track · ISO C23**  
**Source:** `labs/native/fleet-readiness/fleet_readiness.c`.

## Separate an API result from a release decision

The public operation `BtbFleetEvaluate` returns `BTB_FLEET_OK` when the input was valid and the decision was successfully calculated. That is **not** equivalent to `BTB_FLEET_REVIEWABLE`. The latter is one possible value stored in the caller's `BtbFleetDecision.status`. Confusing the two would allow a developer to mistake a correctly evaluated **failure** for a passed operational check.

Four states are necessary:

| State | Meaning | What the administrator should do |
|---|---|---|
| `PENDING` | At least one registered host lacks reviewed evidence and no observed hard blocker was found. | Collect the missing evidence; do not approve. |
| `BLOCKED` | A host has a failed or stale control, invalid release identity, or failed functional operation. | Preserve facts and investigate with the owner. |
| `REVIEWABLE` | All required fictional inputs satisfy the classroom policy. | Present for human review; never grant live permission. |
| `RESTORED_ONLY` | A previous release was independently recovered after an attempted change failed. | Record recovery while leaving the proposed release Failed. |

There can be several issues at once. For example, gateway storage and package identity may pass while Notes save fails and an independent reviewer is missing. The C23 decision contains a bit mask so neither failure disappears. In a user interface, each visible problem should link back to the host and the original source evidence. A real Umicom product must use Framework-owned diagnosis, security and audit services to provide these links.

## Walk through a real test case

Read `test_fleet.c` and find the `operation` case. The test starts from a complete fictional two-host review and changes the storage host's `applicationOperationVerified` flag to false. `BtbFleetEvaluate` must return API `BTB_FLEET_OK`, with **decision** `BTB_FLEET_BLOCKED` and `BTB_FLEET_SERVICE_FAILURE`. The successful return status means the evaluator ran correctly, not that storage works.

Repeat for `restored-only`: the existing Update 45 evidence marks the failed new release as independently restored to the older version. Update 46 does not reinterpret this as success. This is the source-preservation equivalent at the operational level: preserve the historical result even when a later state improves.

## A subtle ordering question

Suppose one host is missing and another host reports a restoration. The aggregate state should not imply a successful release. The classroom evaluator conservatively reports restoration of a previous release when present and no independent hard blocker takes precedence, while the issue mask still records the missing host. Product release authorities must apply stricter approval rules rather than treating this simplified ordering as a production specification.

## Test and compare

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\output\learning-build\fleet-readiness\btb-fleet-readiness-test.exe" operation
& ".\output\learning-build\fleet-readiness\btb-fleet-readiness-test.exe" restored-only
& ".\output\learning-build\fleet-readiness\btb-fleet-readiness-demo.exe"
```

The demonstration first reports PENDING, then REVIEWABLE with both fictional hosts, then BLOCKED when the Notes operation fails, and finally RESTORED_ONLY for independently recovered older software. None of those operations opens a network socket or modifies an actual service.

## Exercises

1. Add a review note explaining why a green `Get-Service` result cannot override a failing Notes save check.
2. Explain why copying a previous release's checksum into the proposed release field would falsify deployment evidence.
3. Sketch a GUI with a distinct status label for each host and one overall decision, without hiding missing hosts.

**Next:** Chapter 318 covers invalid input, failure-atomicity and reproducible tests.
