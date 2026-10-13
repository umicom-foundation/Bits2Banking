# Major Update 36 — Change impact, native build recovery and evidence

**Bits to Banking · Umicom Foundation · Chapters 252–263**

This learning path follows Update 35's Framework VCS and compiler-diagnostics material. Its aim is to teach how a shared native change can affect other products and which observations must be collected before an integration is suitable for review. The companion code is **ISO C23**; no new Python, PowerShell or JavaScript implementation scripts are introduced.

## Recommended order

1. Read [Chapter 252](252-change-impact-as-repository-engineering.md) and [Chapter 253](253-read-framework-vcs-observations.md) to distinguish repository facts from policy decisions.
2. Follow [Chapters 254](254-understand-dependency-graphs-and-abi.md) and [255](255-implement-bounded-impact-planning-in-c23.md) to understand dependencies, ABI boundaries and bounded C23 impact propagation.
3. Complete [Chapters 256](256-map-changes-to-verification-gates.md) and [257](257-bind-revision-to-complete-build-evidence.md) to map affected consumers to genuinely observed build/test evidence.
4. Practise [Chapters 258](258-find-the-first-failing-build-stage.md) and [259](259-investigate-crashes-and-tests-not-run.md) to differentiate compile/link/test/launch failures.
5. Use [Chapter 260](260-recover-framework-os-submodules-safely.md) for safe Git submodule inspection and [Chapter 261](261-use-framework-vcs-and-build-sdk.md) for optional real Framework SDK reuse.
6. Run the 43 CTest checks in [Chapter 262](262-test-impact-planning-with-fault-injection.md) and submit the review note in [Chapter 263](263-capstone-review-framework-change-and-os-boot.md).

The core laboratory is `labs/native/change-impact/` (its source README is in the repository, outside the MkDocs docs directory). It neither reads nor changes any Git repository. An optional `framework_example.c` consumer can be built with a compatible installed Framework SDK; unavailable SDK acceptance is reported as *not run*.

## Companion media

Episodes [86](../../videos/scripts/86-a-shared-framework-change-does-not-end-at-compile.md), [87](../../videos/scripts/87-from-dependency-graph-to-c23-verification-gates.md), [88](../../videos/scripts/88-where-native-umicom-builds-really-fail.md), and [89](../../videos/scripts/89-preserve-source-then-publish-framework-and-os.md) follow the chapters in sequence.

## Exit criteria

A reader can explain what a complete SHA means; read parent/child gitlinks; distinguish detached HEAD from a local `main` branch; map a reviewed dependency graph to downstream affected nodes; differentiate passed/failed/not-run/missing verification; identify the first observed failing build stage; reproduce the C23 tests; preserve tracked, untracked and unpublished work; and issue a source-preserving recommendation without falsely asserting that Studio/OS was tested.

The edition's diagrams are editable SVG sources stored under `content/assets/diagrams/`. The original Islam and financial volumes remain outside this batch and are not modified.
