# Major Update 37 — Additive MkDocs navigation and review instructions

**Do not replace the original `mkdocs.yml`** with a newly generated configuration. Preserve all existing navigation entries, previous updates, video scripts, historical books and especially *Volume 1 — Islam: Blueprint for Life*.

After merging the package content, add the following as **one new top-level entry** under the existing `nav:` key in `mkdocs.yml`, at the same indentation as other top-level navigation entries. This is a fragment intended for **manual reviewed insertion** using Beyond Compare:

```yaml
  - "Absolute beginner: PowerShell, system administration, Git and C23":
      - "Start here — complete course": lessons/05-engineering/absolute-beginners-admin-git-course-update37.md
      - "First-day command sheet": lessons/05-engineering/beginner-command-sheet-update37.md
      - "264. Open Windows Terminal and PowerShell": lessons/05-engineering/264-open-terminal-and-choose-powershell.md
      - "265. Install PowerShell, Git, GitHub CLI and editor": lessons/05-engineering/265-install-powershell-git-github-cli-and-editor.md
      - "266. Find, create and inspect files": lessons/05-engineering/266-navigate-create-and-inspect-files.md
      - "267. Inspect Windows hardware and storage": lessons/05-engineering/267-check-system-hardware-and-storage.md
      - "268. Users, permissions and safe administration": lessons/05-engineering/268-users-permissions-and-safe-administration.md
      - "269. Processes, services and event logs": lessons/05-engineering/269-processes-services-and-event-logs.md
      - "270. Networking, DNS and connection checks": lessons/05-engineering/270-network-and-dns-first-steps.md
      - "271. Linux terminal for beginners": lessons/05-engineering/271-linux-terminal-for-first-time-users.md
      - "272. Configure Git and sign in to GitHub": lessons/05-engineering/272-configure-git-and-sign-in-to-github.md
      - "273. Create and commit a local Git repository": lessons/05-engineering/273-create-and-commit-first-local-git-repository.md
      - "274. Publish repository with GitHub CLI": lessons/05-engineering/274-publish-the-repository-with-github-cli.md
      - "275. Clone and contribute to Umicom": lessons/05-engineering/275-clone-and-contribute-to-umicom.md
      - "276. Install C23 GCC, CMake and Ninja": lessons/05-engineering/276-install-msys2-ucrt64-cmake-and-ninja.md
      - "277. Build and test C23 Umicom Notes": lessons/05-engineering/277-build-and-test-first-c23-notes-program.md
      - "278. Diagnose errors without deleting work": lessons/05-engineering/278-diagnose-first-errors-without-deleting.md
      - "279. Complete the beginner capstone": lessons/05-engineering/279-capstone-first-umicom-contributor.md
      - "280. Use Framework repository verification": lessons/05-engineering/280-use-framework-repository-verify.md
      - "281. Call Framework build planner from C23": lessons/05-engineering/281-call-existing-framework-build-planner.md
      - "282. Select CTest regressions and record results": lessons/05-engineering/282-select-native-tests-and-record-results.md
      - "283. Capstone verified learning delivery": lessons/05-engineering/283-capstone-verified-learning-delivery.md
      - "Episode 90. Open the correct PowerShell": videos/scripts/90-open-the-correct-powershell.md
      - "Episode 91. Read computer information safely": videos/scripts/91-read-computer-information-safely.md
      - "Episode 92. Create and publish your first Git repository": videos/scripts/92-create-and-publish-first-git-repository.md
      - "Episode 93. Build the Umicom Notes programme": videos/scripts/93-build-your-first-umicom-notes-program.md
      - "Episode 94. Review Framework builds and gitlinks": videos/scripts/94-review-framework-build-and-gitlinks.md
```

## Preserve earlier entries

The public baseline may not list Chapters 167–263 even when their files exist, because earlier batches deliberately avoided overwriting the complete YAML. If the user's local `mkdocs.yml` already contains those entries, retain them. If not, review their previous additive fragments separately. Do not use a script to rewrite or sort the full navigation.

## Source and link checks

The new lessons use relative image references under `../../assets/diagrams/` and `../../assets/screenshots/`; video references in the course landing page use `../../videos/scripts/`. The source laboratory is outside `docs_dir: content` and is described by *code path text*, not a broken website link. All new destination paths in the fragment should exist after merging the ZIP.

## Strict website verification

From the Bits2Banking root, after merging and reviewing navigation, run your established MkDocs installation through the existing `.venv` if available:

```powershell
& ".\.venv\Scripts\python.exe" -m mkdocs build --strict
```

This executes a **pre-existing external MkDocs publishing dependency**, not a new Python implementation delivered by Update 37. If the environment lacks MkDocs, record this gate as **not run**, not as passed. Check the generated website's course landing page, screenshots, diagrams, absolute beginner chapter sequence, videos and historic Islam volume.
