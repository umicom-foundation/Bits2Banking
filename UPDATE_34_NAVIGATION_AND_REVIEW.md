# Major Update 34 — Additive MkDocs navigation and editorial review

**IMPORTANT:** This batch does not replace `mkdocs.yml`. The current remote Bits2Banking configuration was inspected during authoring; the locally merged navigation from Updates 28–33 may not exactly match that remote snapshot. Preserve every existing navigation entry, especially **Volume 1 — Islam: Blueprint for Life**, previous educational volumes, teacher content and authored manuscripts.

## Add one new top-level `nav:` group

Insert this YAML group **once** at the same indentation level as other existing top-level groups under `nav:`. Do not put it inside another chapter's children, and do not repeat a group already merged.

```yaml
  - "Git conflict recovery and C23 three-way review — Update 34":
      - "228. Inspect Git objects before resolving history": lessons/05-engineering/228-inspect-git-objects-before-resolving-history.md
      - "229. Merge bases and divergent main": lessons/05-engineering/229-understand-merge-bases-and-divergent-main.md
      - "230. Git index stages 1, 2 and 3": lessons/05-engineering/230-read-index-stages-1-2-and-3.md
      - "231. Preserve functionality during conflict resolution": lessons/05-engineering/231-resolve-conflicts-with-source-preservation.md
      - "232. Bounded three-way C23 model": lessons/05-engineering/232-build-a-bounded-three-way-model-in-c23.md
      - "233. Delete/edit and add/add conflicts": lessons/05-engineering/233-handle-delete-edit-and-add-add-conflicts.md
      - "234. Test failure-atomic merge decisions": lessons/05-engineering/234-prove-atomic-merge-decisions-with-c23-tests.md
      - "235. Reuse Umicom Framework VCS": lessons/05-engineering/235-use-framework-vcs-instead-of-a-second-git-client.md
      - "236. Update Framework gitlinks safely": lessons/05-engineering/236-update-framework-gitlinks-without-copying-source.md
      - "237. Recover commits with reflog": lessons/05-engineering/237-recover-commits-using-reflog-and-read-only-probes.md
      - "238. Tags, dependencies and release provenance": lessons/05-engineering/238-verify-tags-dependencies-and-release-provenance.md
      - "239. Recover, review and publish to main": lessons/05-engineering/239-capstone-recover-review-build-and-publish-to-main.md
      - "Update 34 — Git recovery quick reference": lessons/05-engineering/git-three-way-safety-quick-reference-update34.md
      - "Update 34 — guided learning path": lessons/05-engineering/update-34-learning-path.md
      - "Video 78. Read Git conflict stages": videos/scripts/78-read-git-conflict-stages.md
      - "Video 79. Build the C23 merge-review model": videos/scripts/79-build-a-c23-three-way-review-model.md
      - "Video 80. Recover a blocked OS submodule": videos/scripts/80-recover-a-blocked-umicom-os-submodule.md
      - "Video 81. Review and publish the learning batch": videos/scripts/81-review-and-push-an-umicom-learning-batch.md
```

## Before publication

1. Confirm all 18 path targets exist under `content/`, with exactly the names shown.
2. Confirm source files and diagrams linked from the Markdown exist; SVGs live under `content/assets/diagrams/` and are not separate navigation entries.
3. Inspect the complete current `mkdocs.yml` and verify prior Updates 28–33 navigation entries. If some are absent, restore their reviewed entries from their respective delivered navigation documents; do not invent paths.
4. Preserve every existing Volume 1 and other original book entry, including comments and publication metadata.
5. Run the already-installed strict MkDocs build on your Windows computer. This batch adds no Python files: the existing `python.exe -m mkdocs build --strict` command invokes the repository's established publication toolchain.
6. If navigation validation or the site build fails, keep the update uncommitted until the exact failure is examined. Do not hide missing Markdown paths or silently drop authored content.

## Explicit publication boundary

Passing the 36 CTest cases confirms the native teaching model only. Rendering the site and validating every previous chapter is a separate acceptance gate. The current remote configuration is not automatically changed by extracting this ZIP. This update makes no Framework, Applications, Kernel or OS changes.
