# Major Update 36 — Source baseline and compatibility boundaries

## Public repository snapshot used for review

At preparation time, the GitHub `main` heads inspected for source/API alignment were:

| Repository | Reviewed `main` commit | Purpose |
|---|---|---|
| `umicom-foundation/Bits2Banking` | `c942958200c804702c5b94492cb3029e47a7597b` | Existing learning structure, chapter sequence through 251, videos through 85 and navigation conventions |
| `umicom-foundation/umicom-framework` | `0d40b2d9222d0a0a0eaf912b8594e0e29fbb2796` | Existing public C23 VCS and build parser contracts |

These identifiers record a **public source-reading baseline**, not the unknown state of the user's Windows working trees. No claim is made that the installed SDK matches the reviewed Framework commit or that the user has already merged every previous ZIP. `git status`, full commit SHAs and local file comparison must be performed before merging this batch.

## Existing Framework APIs evaluated

- `include/umicom/build/automation.h`: `UmiBuildAutomation` already implements changed-file classification, scoped dependencies and deterministic build/test planning. It MUST be reused for real product functionality; this batch does not create a replacement production planner. The optional SDK example calls this API.
- `src/build/automation.c`, `tests/test_build_automation.c` and `tools/umicom/src/command_automation.c`: reference implementation, tests and existing native CLI adapter.
- `include/umicom/vcs/working_tree.h`: `UmiVcsWorkingTreeRead`, `UmiVcsWorkingTreeDescribe`, `UmiVcsWorkingTreeDestroy`; `UmiVcsWorkingTreeSummary` includes staged/untracked/child and detached/divergence fields.
- `include/umicom/vcs/working_tree_review.h`: display-only summaries and entry formatting; original path bytes are not display labels.
- `include/umicom/build/parser.h`: `umi_build_parse_diagnostic_line`, `umi_build_parse_output`.
- `include/umicom/diagnostics/compiler_parser.h`: shared GCC/Clang/MSVC/CMake diagnostic interpretation.
- `docs/SHARED_FRAMEWORK_SUBMODULE_UPDATE_POLICY.md`: canonical Framework checkout, tested parent gitlinks, use of native `umicom repo verify .` and `umicom repo lock .` where available.
- Installed CMake target names `Umicom::vcs`, `Umicom::build`, and package name `UmicomFramework` are taken from the existing Framework examples/definitions. Optional linkage is not represented as tested in the isolated environment.

## Why these details matter

The source baseline prevents inventing fictional Framework functions and helps users compare lesson examples with their checked-out public headers. This batch does **not** copy Framework implementation code into Bits2Banking; the new lab remains a separate educational decision model. For real application integration, a user must build/install a compatible Framework SDK, run the optional C23 example and record the actual result.

## Local merge preservation

The ZIP is a **partial, additive** payload, not a mirror or new repository. It does not include a replacement `mkdocs.yml`: the owner reviews the supplied additive fragment against their local navigation and preserves the original Islam volume and earlier lessons. It does not include the user's complete repository, generated site or toolchain. Do not interpret the ZIP as a clone or authoritative snapshot of anything beyond its manifest.
