# Major Update 33 — Source and dependency baseline

**Observed:** 13 October 2026 (UTC reference date). These commit IDs are provenance notes, not mandatory reset targets.

| Source | GitHub reference observed at authoring | Role |
|---|---|---|
| `umicom-foundation/Bits2Banking` | `99c6739295fff57d42aabc07723229caccdb6aff` | Educational repository; delivered Update 33 files are new |
| `umicom-foundation/umicom-framework` | `0d40b2d9222d0a0a0eaf912b8594e0e29fbb2796` | Authority for native Git/VCS/repository services |
| Update 32 ZIP supplied in this conversation | `Umicom-Bits2Banking-Update-32-Git-Release-Qualification-and-C23-Evidence.zip` | Reused optional `gate.c` and `gate.h` regression dependency |

The local repository may be ahead of either observed SHA. Before merging, inspect your actual checkout. No `git pull`, `git push`, branch switch or GitHub write was executed on the user's behalf to prepare this batch.

**Architecture references actually reviewed:** `include/umicom/vcs/working_tree.h`, `include/umicom/vcs/git_cli.h`, `include/umicom/repository/gitlink.h`, `include/umicom/repository/submodule_lock.h` and `docs/SHARED_FRAMEWORK_SUBMODULE_UPDATE_POLICY.md` from the canonical Framework. The Update 33 bridge is optional and should be compiled against the local header revision before claiming Framework integration.

**Previous update prerequisite:** Update 32's `labs/native/git-release-evidence` is required only for the `release_gate_composition` CTest. All other Update 33 tests run as a standalone C23 lab. The Update 33 package never includes or replaces the prior gate source.
