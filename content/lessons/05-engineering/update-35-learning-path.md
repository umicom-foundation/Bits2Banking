# Major Update 35 — A guided path through Git observations and build diagnostics

**Bits to Banking · Umicom Foundation · Chapters 240–251 · Episodes 82–85**

This path follows the existing Git engineering sequence, Chapters 182–239, and adds a Framework-first native C23 build-evidence laboratory. The goal is to learn how to **observe** source and build status without accidentally changing repositories, then distinguish a verified result from incomplete evidence. All new executable learning code is C23; PowerShell examples are individual interactive commands, not project scripts.

## Recommended reading and practical sequence

| Stage | Reading | Exercise and expected evidence |
|---|---|---|
| Source ownership | [240](240-observe-git-through-umicom-framework.md), [241](241-working-tree-status-and-gitlinks.md) | Record HEAD, local branch and parent Framework gitlink using read-only Git commands |
| Tool feedback | [242](242-reuse-framework-compiler-diagnostics.md), [243](243-trace-cmake-ninja-ctest-failures.md) | Identify compiler/parser authority; classify first observed failed build phase |
| Evidence identity | [244](244-source-revision-and-build-evidence-identity.md), [245](245-build-a-bounded-c23-evidence-snapshot.md) | Compile the C23 library and explain deep-copy and source-SHA checks |
| Investigate change | [246](246-compare-diagnostics-across-two-builds.md), [247](247-reject-truncated-and-stale-diagnostics.md) | Predict introduced, persistent and resolved problems; execute negative tests |
| Real practices | [248](248-diagnose-real-umicom-build-failures.md), [249](249-connect-framework-vcs-to-c23-build-evidence.md) | Produce a build-failure incident note; optionally link the installed Framework SDK |
| Qualification | [250](250-cross-platform-reproducible-builds.md), [251](251-capstone-framework-first-git-and-build-review.md) | Cross-toolchain build matrix and end-to-end repository evidence report |

## Video sequence

- [Episode 82 — Clean Git status is not build proof](../../videos/scripts/82-why-git-status-is-not-build-proof.md)
- [Episode 83 — One compiler parser across Umicom](../../videos/scripts/83-one-compiler-parser-across-umicom.md)
- [Episode 84 — Compare two C23 evidence snapshots](../../videos/scripts/84-compare-two-c23-build-evidence-snapshots.md)
- [Episode 85 — Qualify a Framework/OS build without deleting work](../../videos/scripts/85-qualify-a-framework-os-build-without-deleting-work.md)

## Core practical lab

`labs/native/build-evidence` is a **standalone** C23 project. It uses no real Git repository in its default demonstration. Learners build the library, run **56 named CTest cases**, inspect `evidence.h`, and complete a source-preserving review. The optional SDK target consumes genuine Framework VCS/build types and links `Umicom::vcs` and `Umicom::build`; that integration is a separate acceptance gate on a computer with an installed compatible Framework SDK.

## Completion criteria

A learner should be able to explain a gitlink, avoid detached HEAD push mistakes, preserve dirty worktrees, reproduce named build/test commands, identify incomplete diagnostic capture, refuse stale tests and determine when a profile/toolchain comparison is not meaningful. The final report must list unknown or unrun gates explicitly. Passing a test of rejection behaviour is not permission to commit or push unrelated source changes.

[Return to the engineering overview](index.md) · [Open the Git/build quick reference](git-build-diagnostics-quick-reference-update35.md)
