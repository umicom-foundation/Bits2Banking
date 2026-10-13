# Major Update 33 — Git evidence, Framework reuse and C23 review path

**Author:** Sammy Hegab · **Organisation:** Umicom Foundation · **Teaching language:** UK English · **Runtime examples:** C23.

The course follows Update 32's release-qualification lessons, and continues with repository evidence, safe source recovery and native API reuse. Learners should first complete [Chapter 215](215-complete-umicom-release-qualification-capstone.md). Chapters 216–227 can be studied in the order below; every chapter connects a concrete Umicom repository problem to a precise command, a Framework ownership decision and an assessed exercise.

| Lesson | Competency |
|---|---|
| [216 — Trustworthy evidence](216-from-git-status-to-trustworthy-evidence.md) | Identify the claim behind each Git command |
| [217 — Structured status](217-structured-git-status-without-duplicate-parsers.md) | Reuse Framework's binary-safe working-tree contract |
| [218 — Reference identity](218-detached-head-and-local-main-identity.md) | Distinguish HEAD, local main and origin/main |
| [219 — Framework gitlinks](219-review-umicom-framework-gitlinks.md) | Find the owner of a source change and parent pointer |
| [220 — Preserve local work](220-preserve-work-before-git-synchronisation.md) | Protect modified, untracked and local-only work |
| [221 — Remote divergence](221-inspect-divergence-before-git-push.md) | Diagnose non-fast-forward without force push |
| [222 — Observation timeline](222-design-a-c23-observation-timeline.md) | Design a copied, bounded, failure-atomic C23 model |
| [223 — Evidence provenance](223-bind-build-and-test-proof-to-a-revision.md) | Reject stale build and test results |
| [224 — Framework adapter](224-compile-an-optional-framework-vcs-adapter.md) | Compile against the existing public VCS API |
| [225 — Policy composition](225-reuse-the-existing-c23-release-gate.md) | Reuse the Update 32 gate instead of replacing it |
| [226 — Verification](226-verify-100000-c23-evidence-transitions.md) | Run named regressions and 100,000 transitions |
| [227 — Capstone](227-umicom-os-framework-git-evidence-capstone.md) | Qualify a real Framework-to-OS publication plan |

**Videos:** [74](../../videos/scripts/74-why-a-clean-git-status-is-not-release-proof.md), [75](../../videos/scripts/75-understand-detached-head-and-rejected-push.md), [76](../../videos/scripts/76-build-a-c23-git-evidence-timeline.md), [77](../../videos/scripts/77-qualify-the-umicom-os-framework-gitlink.md).

**Practical lab:** [`git-review-timeline`](../../../labs/native/git-review-timeline/README.md). CMake builds the native example without Python or PowerShell scripts. The optional compiled adapter requires a real Framework source checkout; the complete live Framework runtime is not linked by the teaching project. Production Git services remain Framework-owned.

**Instructor checkpoint:** Do not award a release-ready pass for a clean worktree alone. The learner must identify an observed commit, remote freshness, staged changes, build/test provenance, child publication and parent gitlink separately. Accurate reporting of NOT RUN is a correct professional behaviour.
