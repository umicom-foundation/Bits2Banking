# Major Update 33 — Additive MkDocs navigation and review

This ZIP contains **no replacement `mkdocs.yml`**. The current Bits2Banking GitHub navigation was inspected during authoring, and the earlier Update 28–32 learning paths were not all visibly registered in its published `main` navigation. Do not assume they have been applied locally. Preserve every existing entry, especially the original **Volume 1 — Islam: Blueprint for Life** collection.

## New top-level group to add under `nav:`

Copy the following YAML **as a new group**, at the same indentation level as existing groups such as `"HTTP caching, conditional requests and bounded admission"`. Do not paste it inside the `"Software engineering and administration"` inner list and do not duplicate an existing group if it was already merged.

```yaml
  - "Professional Git diagnostics and Framework evidence — Update 33":
      - "216. From Git status to trustworthy evidence": lessons/05-engineering/216-from-git-status-to-trustworthy-evidence.md
      - "217. Structured Git status and Framework API": lessons/05-engineering/217-structured-git-status-without-duplicate-parsers.md
      - "218. Detached HEAD and local main identity": lessons/05-engineering/218-detached-head-and-local-main-identity.md
      - "219. Framework gitlinks across repositories": lessons/05-engineering/219-review-umicom-framework-gitlinks.md
      - "220. Preserve local work before synchronisation": lessons/05-engineering/220-preserve-work-before-git-synchronisation.md
      - "221. Investigate divergence before Git push": lessons/05-engineering/221-inspect-divergence-before-git-push.md
      - "222. Design a C23 observation timeline": lessons/05-engineering/222-design-a-c23-observation-timeline.md
      - "223. Bind build and test proof to a revision": lessons/05-engineering/223-bind-build-and-test-proof-to-a-revision.md
      - "224. Compile the Framework VCS adapter": lessons/05-engineering/224-compile-an-optional-framework-vcs-adapter.md
      - "225. Reuse the existing C23 release gate": lessons/05-engineering/225-reuse-the-existing-c23-release-gate.md
      - "226. Verify 100,000 evidence transitions": lessons/05-engineering/226-verify-100000-c23-evidence-transitions.md
      - "227. Framework and Umicom OS Git capstone": lessons/05-engineering/227-umicom-os-framework-git-evidence-capstone.md
      - "Git investigation quick reference": lessons/05-engineering/git-investigation-quick-reference-update33.md
      - "Update 33 guided learning path": lessons/05-engineering/update-33-learning-path.md
      - "Video 74. Why clean Git status is not release proof": videos/scripts/74-why-a-clean-git-status-is-not-release-proof.md
      - "Video 75. Detached HEAD and rejected push": videos/scripts/75-understand-detached-head-and-rejected-push.md
      - "Video 76. Build a C23 Git evidence timeline": videos/scripts/76-build-a-c23-git-evidence-timeline.md
      - "Video 77. Qualify the Framework gitlink": videos/scripts/77-qualify-the-umicom-os-framework-gitlink.md
```

## Review checklist

1. Open your **current** `mkdocs.yml` in Beyond Compare or a text editor. Check the beginning and end of its `nav:` structure.
2. Confirm the new chapters and video files are physically present in the expected paths after merging.
3. Confirm Updates 28–32 are present and their navigation was integrated separately; restore any missing entries from their reviewed update notes rather than inventing paths.
4. Insert the group above exactly once, preserving prior historic chapters, navigation, source comments and links.
5. Run the existing site command `& ".\.venv\Scripts\python.exe" -m mkdocs build --strict`. This invokes existing tooling; **no Python project implementation is added**.
6. Compare the generated site with the current authoring baseline before publication and record any warnings or missing navigation targets.

The five SVGs are linked directly inside the lessons; separate navigation items are not required for illustrations. Avoid an automated rewrite of the entire YAML file until a Framework-owned native navigation editor has passed equivalent regression tests and been approved.
