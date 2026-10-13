# Major Update 36 — Additive MkDocs navigation and source review

**Preservation rule:** Do not replace or regenerate the complete `mkdocs.yml` from a partial update ZIP. Existing education pages, manuscripts, videos and especially *Volume 1 — Islam: Blueprint for Life* must remain in their existing navigation order. The user's local configuration can include chapters from Updates 28–35 that the public remote has not yet registered; preserve all of them.

After merging the new Markdown files, add this **one new top-level section** under the existing `nav:` key, at the same two-space indentation as other top-level sections. It is intentionally a fragment, not a full YAML replacement:

```yaml
  - "Native C23 change impact and professional build recovery":
      - "Major Update 36 learning path": lessons/05-engineering/update-36-learning-path.md
      - "Git and build recovery quick reference": lessons/05-engineering/git-build-recovery-quick-reference-update36.md
      - "252. Change impact as repository engineering": lessons/05-engineering/252-change-impact-as-repository-engineering.md
      - "253. Reuse Framework VCS observations": lessons/05-engineering/253-read-framework-vcs-observations.md
      - "254. Dependency graphs and public ABI": lessons/05-engineering/254-understand-dependency-graphs-and-abi.md
      - "255. Bounded change-impact planning in C23": lessons/05-engineering/255-implement-bounded-impact-planning-in-c23.md
      - "256. Map modules to verification gates": lessons/05-engineering/256-map-changes-to-verification-gates.md
      - "257. Bind evidence to the correct source": lessons/05-engineering/257-bind-revision-to-complete-build-evidence.md
      - "258. Find the first failing build stage": lessons/05-engineering/258-find-the-first-failing-build-stage.md
      - "259. Investigate crashes and Not Run tests": lessons/05-engineering/259-investigate-crashes-and-tests-not-run.md
      - "260. Recover Framework and OS submodules": lessons/05-engineering/260-recover-framework-os-submodules-safely.md
      - "261. Reuse the Framework C23 SDK": lessons/05-engineering/261-use-framework-vcs-and-build-sdk.md
      - "262. Test change impact with negative cases": lessons/05-engineering/262-test-impact-planning-with-fault-injection.md
      - "263. Framework change and OS boot capstone": lessons/05-engineering/263-capstone-review-framework-change-and-os-boot.md
      - "Episode 86. Shared Framework change impact": videos/scripts/86-a-shared-framework-change-does-not-end-at-compile.md
      - "Episode 87. Native C23 verification gates": videos/scripts/87-from-dependency-graph-to-c23-verification-gates.md
      - "Episode 88. Investigate native build failures": videos/scripts/88-where-native-umicom-builds-really-fail.md
      - "Episode 89. Preserve source before publishing": videos/scripts/89-preserve-source-then-publish-framework-and-os.md
```

## Content link checks

The six new SVGs are in `content/assets/diagrams/`. Lesson links use the established `../../assets/diagrams/` relative path. Within the MkDocs website, the underlying lab source lives outside the `content` docs directory; lessons therefore cite source paths as **code text**, not as navigable website links to a missing page.

## Manual merge and strict site acceptance

1. Review the newly added files and this fragment in Beyond Compare.
2. Preserve existing MkDocs `nav` sections, all earlier lessons and the original Islam volume.
3. Copy only the new section above into your real local `mkdocs.yml`. Make sure the same label and target have not already been added.
4. Use the project's already-installed MkDocs environment if present: `& ".\.venv\Scripts\python.exe" -m mkdocs build --strict`. This invokes an existing publishing dependency; no new script is created.
5. Verify the lessons, diagrams and original volumes in the generated site. A successful SVG parse or CTest run does not establish website publication.

**No scripted YAML rewriting is delivered.** This protects unmerged local navigation work from being overwritten by an incomplete source snapshot.
