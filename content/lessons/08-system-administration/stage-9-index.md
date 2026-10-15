# Stage 9 — Multi-host administration, fault isolation and verified recovery

**System Administration From Zero · Chapters 109–120 · Umicom Foundation**

## Who this stage is for

This stage starts with ordinary computer knowledge, then builds towards the skill of investigating **two systems that depend upon each other**. Learners never have to administer someone else's computer. Windows PowerShell and Linux commands are read-only observations of your own practice host. Any example involving Umicom Notes servers is fictional; changing production servers is not authorised by these lessons.

## The stage in four learning weeks

| Week | Read | Practice and evidence |
|---|---|---|
| 1 — know your machines | 109–111 | Draw a two-host inventory; distinguish OS, application and source versions; read Windows services. |
| 2 — understand dependencies | 112–114 | Inspect an authorised Linux unit, compare package provenance and measure local filesystem capacity. |
| 3 — find the failing boundary | 115–117 | Separate DNS/TCP/application checks, normalise event timestamps and restore one practice file into a different folder. |
| 4 — qualify recovery | 118–120 | Distinguish liveness/readiness/correctness, draft a rollout plan and present the complete fictional Notes incident. |

Read each explanation before copying commands. When a command is unavailable, mark **Not Run** in your workbook; do not make up a result. The final question is whether you can defend your conclusion using evidence—not whether every command printed green text.

## Completion criteria

You can explain: why a host name is not release identity; why a running process can be unable to serve users; the difference between OS package, source commit, and deployed artifact checksum; why an untested backup is not verified restoration; why clock skew can invalidate a timeline; and why an old restored version does not qualify a failed new release.

The [Stage 9 workbook](stage-9-workbook.md) has written and practical exercises. The [instructor guide](stage-9-instructor-guide.md) includes example marking points, accessibility and safety controls. A compact [command reference](stage-9-safe-command-reference.md) and [incident template](stage-9-incident-template.md) support later real-world revision.

## C23 continuation

Chapters 316–319 in the engineering track connect these administration concepts to **existing** Bits2Banking C23 evidence components. The [fleet-readiness lab](../../labs/index.md) is not a production system-management agent, and it does not inspect a real host or grant release approval. Real shared tooling must reuse Umicom Framework's VCS, build, process, security, and application-lifecycle APIs.

The user's supplied *Creating a New Umicom Application* guide stays intact as a separate contributor handbook; Stage 9 does not propose rewriting its original material.
