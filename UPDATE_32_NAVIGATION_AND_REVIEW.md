# Major Update 32 — Reviewed MkDocs navigation additions

**Important:** This is a *merge recipe*, not a full replacement for `mkdocs.yml`. The inspected public `main` of Bits2Banking still ended its engineering continuation at Chapter 166. Update 31 delivered reviewed navigation for Chapters 167–203 and Videos 58–69. If those previous entries are not yet present in your working `mkdocs.yml`, merge that earlier recipe **first**. Do not add duplicate keys, duplicate lesson paths or duplicate chapter numbers.

## Placement

Open the current `C:\umicom\Umicom-Bits2Banking\mkdocs.yml` using Beyond Compare or an editor. In the `nav:` array, add the following two **top-level groups** after the Update 31 continuation, or before the existing `Framework integration examples` group. Keep the file's indentation and formatting. Preserve the original *Islam: Blueprint for Life* navigation and all other entries unaltered.

## Additive YAML fragment

```yaml
  - "Professional Git and Framework VCS evidence (Update 32)":
      - "204. Observe Git through Umicom Framework": lessons/05-engineering/204-observe-git-through-umicom-framework.md
      - "205. Review the Git index and working tree": lessons/05-engineering/205-review-index-and-working-tree-evidence.md
      - "206. Verify fast-forwards before pulling": lessons/05-engineering/206-fast-forward-without-rewriting-history.md
      - "207. Publish a tested Framework gitlink": lessons/05-engineering/207-publish-a-tested-framework-gitlink.md
      - "208. Resolve integration conflicts without source loss": lessons/05-engineering/208-resolve-integration-without-losing-intent.md
      - "209. Diagnose rejected Git pushes safely": lessons/05-engineering/209-troubleshoot-a-rejected-push.md
      - "210. Release tags, qualification and provenance": lessons/05-engineering/210-release-tags-provenance-and-qualification.md
      - "211. Investigate failed CI without removing features": lessons/05-engineering/211-investigate-ci-without-replacing-code.md
      - "212. Preserve C23 public contracts and ABI": lessons/05-engineering/212-review-native-source-and-abi-preservation.md
      - "Git release qualification quick reference": lessons/05-engineering/git-release-qualification-quick-reference.md
      - "Video 70. Review the Git index before committing": videos/scripts/70-review-the-git-index-before-commit.md
      - "Video 71. Why a parent Git pull does not update Framework": videos/scripts/71-why-a-parent-git-pull-does-not-update-framework.md
  - "Native C23 release evidence and integration (Update 32)":
      - "213. Build a native release evidence model": lessons/05-engineering/213-build-a-native-release-evidence-model.md
      - "214. Test fail-closed release gates": lessons/05-engineering/214-test-fail-closed-release-gates.md
      - "215. Umicom release qualification capstone": lessons/05-engineering/215-complete-umicom-release-qualification-capstone.md
      - "Video 72. Release evidence gates in C23": videos/scripts/72-release-evidence-gates-in-c23.md
      - "Video 73. Publish and qualify an Umicom release": videos/scripts/73-publish-and-qualify-umicom-release.md
```

**Do not paste this fragment inside another navigation group.** The first line of each group is at the same indentation level as other root-level `nav` groups.

## Content check before publication

Ensure all referenced pages exist under `content/`. The exact 12 lesson paths, 4 video paths and quick-reference path in the fragment are included in this package. The previous update's navigation remains a separate prerequisite; this package does not supply or overwrite earlier lessons.

Validate the modified MkDocs file using the repository's existing native `umicom-education audit --repo` where available, and then the strict MkDocs build in the existing virtual environment. The native auditor verifies destination paths; it is **not a replacement for complete YAML parsing or MkDocs**. Report unavailable tools as not run.

Review the built website's navigation labels, chapter order, video links and diagrams. Preserve the historical books, earlier learning modules and existing theme/branding settings.
