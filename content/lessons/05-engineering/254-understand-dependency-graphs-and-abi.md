# Chapter 254 — Dependency graphs, stable C ABIs and downstream rebuilds

**Bits to Banking · Engineering track · Umicom Foundation**  
**Primary language:** C23 · **Lab:** `labs/native/change-impact`.

## Why one header can change many applications

Imagine extending a public Framework structure used by Umicom Studio and Umicom Bank. A compilation success for the Framework library is only one requirement: consumers compiled against an older installed header may disagree about field offsets, structure size or enum values. A stable C ABI depends on deliberate compatibility decisions, not merely matching function names. In general, adding fields to a public structure can be unsafe unless the contract provides explicit sizing/versioning and every consumer is qualified. This is especially important at plug-in and shared-library boundaries.

The **existing Framework Automated Build System** (`umi_build_automation_*` in `umicom/build/automation.h`) already handles real changed-file classification and build-target selection. Our bounded graph is an educational illustration of reverse-dependency reasoning, not another production engine. The architectural rule is that **reusable code and public contracts belong in Umicom Framework**, while applications contribute thin composition and genuine domain behaviour. Shared changes should be committed once in the authoritative Framework repository and then consumed through pinned revisions, not copied into multiple `framework/` directories.

## Three graphs that must not be confused

| Graph | Example edge | What it proves |
|---|---|---|
| CMake target dependencies | `Umicom::vcs` links base services | Which target is needed to compile/link this configuration |
| Runtime dependencies | GTK4 workspace needs a deployed settings provider | Which installed components must be present at launch |
| Git submodules | Umicom OS pins a Framework commit | Which exact revision the parent selects |

These graphs overlap but are not identical. A changed header may require dependent targets to rebuild. A changed run-time resource can break an installed desktop even if every library compiled. A new Framework commit does not automatically update a parent gitlink. The review must record all relevant boundaries.

## Reverse dependencies and transitive impact

In `impact.c`, an edge `consumer -> dependency` is stored in `BtbImpactModule.dependencies`. `BtbImpactPlanBuild` starts with the changed modules and repeatedly includes **consumers whose dependency mask intersects the already affected set**. The result is the transitive closure of downstream impact. The loop stops when no new consumer can be added.

For an eight-node teaching graph, changing `framework.base` affects every dependent node in that graph. Changing `framework.vcs` affects itself and `applications.studio`, but not `applications.bank` when the latter has no VCS dependency. This is a transparent, useful demonstration of impact selection — not a production inventory.

```c
/* The change has already been mapped to the reviewed graph node. */
BtbImpactPlan plan;
BtbImpactStatus status = BtbImpactPlanBuild(
    &graph,
    "0123456789abcdef0123456789abcdef01234567",
    UINT64_C(1) << vcsIndex,
    &plan);
if (status != BTB_IMPACT_OK) {
    /* Stop: the plan is not a valid observation. */
}
```

The full hex revision prevents ambiguity caused by abbreviated hashes. It does not prove the source tree exists or that a build was made from it; those are separate evidence requirements.

## Why the graph refuses cycles

A change graph should reject unexpected dependency cycles rather than pretend that an arbitrary compile order exists. `BtbImpactAddDependency` tests whether adding a proposed edge would create a path back to its own node. It returns `BTB_IMPACT_CYCLE` without modifying the graph. Cycles can be meaningful in some runtime designs, but this simplified teaching graph declares a directed acyclic contract to make its boundaries inspectable.

If an application's UI and business model form a circular dependency, the educational exercise is to ask which interface can be extracted to a stable Framework contract. The correct production refactor requires a separate architectural review and must preserve existing code until its replacement is verified.

## ABI review checklist in prose

Before approving a Framework-facing change, examine the public header and its consumers, exported symbol names, opaque-handle conventions, structure-size/version fields, enum assignments, memory ownership, callback lifetimes and allocator boundaries. Check whether a module is statically linked, dynamically loaded or used out of process. Then configure and test each required application profile and installation target. Never treat a Windows UCRT64 object as interchangeable with a Linux ELF library just because both were written in C23.

**Practical task:** Identify a public C header in Framework used by Studio. Draw a dependency edge from Studio to that module. Design two negative tests demonstrating an incompatible ABI change. Specify which files you would compare using Beyond Compare, but do not delete or rewrite existing source for this exercise.

**Review questions:** What is a reverse dependency? How can a package pass compilation but fail on double-click? Why does a submodule SHA differ from the parent commit SHA? Why can a cyclic dependency indicate an architecture problem?

**Next:** represent these facts in bounded C23 records with explicit invariants.
