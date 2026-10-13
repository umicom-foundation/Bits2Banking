# Major Update 35 — Additive MkDocs navigation and review

**Do not replace `mkdocs.yml` with a partial file.** The existing website contains the original *Islam: Blueprint for Life* navigation and earlier computing, finance and Umicom curricula. Updates 28–34 may have introduced local entries not yet reflected in the public remote configuration. Preserve them all.

Once all new Markdown files are merged, add the following **new top-level navigation section under `nav:`**, using the same indentation as existing top-level sections. This is a **fragment**, not a complete YAML replacement:

```yaml
  - "Git, Framework VCS and native C23 build evidence":
      - "Update 35 learning path": lessons/05-engineering/update-35-learning-path.md
      - "Git and build diagnostics quick reference": lessons/05-engineering/git-build-diagnostics-quick-reference-update35.md
      - "240. Observe Git through Umicom Framework": lessons/05-engineering/240-observe-git-through-umicom-framework.md
      - "241. Working tree and Framework gitlinks": lessons/05-engineering/241-working-tree-status-and-gitlinks.md
      - "242. Reuse Framework compiler diagnostics": lessons/05-engineering/242-reuse-framework-compiler-diagnostics.md
      - "243. Trace CMake, Ninja and CTest failures": lessons/05-engineering/243-trace-cmake-ninja-ctest-failures.md
      - "244. Bind build evidence to one revision": lessons/05-engineering/244-source-revision-and-build-evidence-identity.md
      - "245. Build a bounded C23 evidence snapshot": lessons/05-engineering/245-build-a-bounded-c23-evidence-snapshot.md
      - "246. Compare two build diagnostic snapshots": lessons/05-engineering/246-compare-diagnostics-across-two-builds.md
      - "247. Reject truncated and stale evidence": lessons/05-engineering/247-reject-truncated-and-stale-diagnostics.md
      - "248. Diagnose real Umicom build failures": lessons/05-engineering/248-diagnose-real-umicom-build-failures.md
      - "249. Connect Framework VCS to C23 evidence": lessons/05-engineering/249-connect-framework-vcs-to-c23-build-evidence.md
      - "250. Cross-platform reproducible C23 builds": lessons/05-engineering/250-cross-platform-reproducible-builds.md
      - "251. Framework-first Git/build review capstone": lessons/05-engineering/251-capstone-framework-first-git-and-build-review.md
      - "Episode 82. Git status is not build proof": videos/scripts/82-why-git-status-is-not-build-proof.md
      - "Episode 83. One compiler parser across Umicom": videos/scripts/83-one-compiler-parser-across-umicom.md
      - "Episode 84. Compare C23 evidence snapshots": videos/scripts/84-compare-two-c23-build-evidence-snapshots.md
      - "Episode 85. Qualify Framework and OS safely": videos/scripts/85-qualify-a-framework-os-build-without-deleting-work.md
```

## Verify that the diagram links resolve

- `../../assets/diagrams/git-vcs-framework-ownership-update35.svg`
- `../../assets/diagrams/diagnostics-pipeline-update35.svg`
- `../../assets/diagrams/build-evidence-state-update35.svg`
- `../../assets/diagrams/build-comparison-update35.svg`
- `../../assets/diagrams/umicom-change-verification-update35.svg`

These are written relative to `content/lessons/05-engineering/`. All five original SVG files are included in the archive. No external image hosting is required.

## MkDocs and manuscript-preservation checks

After a reviewed manual merge, invoke the existing strict MkDocs builder if its virtual environment is present:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\.venv\Scripts\python.exe" -m mkdocs build --strict
```

This command uses the existing publishing environment and **does not create Python source**. If the MkDocs environment is not installed, record the gate as not run. Verify that every previous navigation entry is still present and that the original Islam volume is still accessible.

A successful XML/SVG validation or local C23 CTest result is not proof of a successful public website deployment. Published GitHub Pages navigation must be checked separately after it has actually been built and deployed.
