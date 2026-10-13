# Chapter 255 — Implement a bounded change-impact planner in C23

**Bits to Banking · Engineering track · Umicom Foundation**  
**Lab:** `labs/native/change-impact` · **Files:** `impact.h`, `impact.c`, `test_impact.c`.

## Learning objectives

After this chapter, explain why the graph is bounded, why bit shifts require limits, how module identities are copied, how an edge is validated, and why an unsuccessful operation must not change caller output. These skills apply to C23 APIs beyond build tooling: banking commands, GUI document edits and engine lifecycle transitions use the same ownership discipline.

## Read the public structure before the algorithm

For real Umicom applications, reuse Framework's existing `UmiBuildAutomation` rather than copying this algorithm into an application. We implement a small version here **only to teach** capacity checks, bitsets, transitive closure and failure atomicity.

The teaching graph contains at most `BTB_IMPACT_MAX_MODULES` (12) nodes. A `uint64_t` bitset can encode their indices: bit zero represents module zero, bit one represents module one, and so on. The limit stays below 64 so `UINT64_C(1) << index` is always defined after index validation. We chose twelve for clarity, not because production Framework has twelve modules.

```c
typedef struct BtbImpactModule {
    char name[BTB_IMPACT_NAME_CAPACITY];
    uint64_t dependencies;
    uint32_t requiredGates;
} BtbImpactModule;
```

Each module identifier is a bounded, NUL-terminated ASCII string. The accepted grammar is `[A-Za-z0-9._-]+`. This is deliberately narrower than arbitrary filesystem paths; module names are logical identifiers, not paths or URLs. Input strings are copied into `graph->modules[]`, so changing the original caller buffer cannot change the graph afterwards.

## Follow the graph construction

`BtbImpactAddModule` first validates the existing graph, name and gates. It refuses duplicates and checks capacity before writing. The current count is published only after the complete candidate record has been stored. The function writes `outIndex` only when it returns `BTB_IMPACT_OK`.

`BtbImpactAddDependency` checks both indices, refuses self-edges and duplicates, then asks whether the proposed dependency can already reach the dependent module. If it can, the new edge would form a cycle and is rejected. The source contains no dynamic allocation, so callers can inspect every state byte in a debugger.

## Trace the impact loop

The planner copies the caller-supplied changed bitmask into a local `affected` variable. It walks all modules. Whenever a module is not yet affected but depends on an affected module, its bit is added. A later pass may then include that module's dependants. The passes stop when the set no longer grows. The planner then ORs together each affected module's required evidence gates.

This is **not** a compiler's full incremental-build algorithm. A production build graph must model file dependencies, custom commands, generated source, configuration, ABI and platform-specific outputs. Here we isolate the policy question: given a reviewed module-level dependency map, which categories of checks become mandatory?

## Failure-atomic outputs

Suppose a contributor passes `abc123` as the revision. Six hexadecimal characters are useful for display but not sufficiently explicit for a replayable full-revision contract. `BtbImpactPlanBuild` returns `BTB_IMPACT_INVALID_ARGUMENT` and leaves the caller's existing plan unchanged. The test `plan_atomic` fills its output with a known pattern, calls the function with invalid input and proves the pattern was not modified.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\output\learning-build\change-impact\btb-change-impact-test.exe" plan_atomic
& ".\output\learning-build\change-impact\btb-change-impact-test.exe" cycle_indirect
& ".\output\learning-build\change-impact\btb-change-impact-test.exe" plan_transitive
```

These commands assume Chapter 262's build steps have already been completed. The cycle test confirms the proposed edge is rejected and the graph's previous bytes remain unchanged. A test that expects refusal should itself exit successfully when refusal occurs.

## What can still go wrong?

Even perfect bitset code cannot detect an omitted dependency. The user of the planner must provide an approved graph and changed-module mapping from authoritative Framework tooling and review. The API also does not prove build artefacts were generated from the claimed SHA. It is a small policy module, suitable for understanding invariants, not a source-of-truth system.

**Exercises:** Add a fictional `applications.notes` node that depends on `framework.ui`. Predict the changed and affected masks for a UI modification. Add a test for a name longer than 47 characters. Explain why using `strcpy` before capacity validation would violate the contract. For an advanced task, propose a safe way to scale past 64 modules without creating undefined shifts.

**Review questions:** Which object owns the module name? What does a zero return from `BtbImpactGraphValid` mean? Why are changing the plan output early and truncating a source identifier dangerous? What is the difference between a module identifier and a filesystem path?

**Next:** convert impact into concrete categories of required evidence.
