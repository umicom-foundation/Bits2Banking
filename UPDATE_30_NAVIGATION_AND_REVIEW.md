# Major Update 30 — MkDocs navigation registration and preservation check

## Why this is a reviewed edit rather than a script

The current Bits2Banking `mkdocs.yml` contains extensive existing navigation, including the original *Islam: Blueprint for Life* chapters and prior books. A full-file replacement based on an earlier ZIP could overwrite new material. **Do not replace the complete YAML file with a generated copy.** After merging Updates 28–30, open the **current** `mkdocs.yml` in Umicom Studio or your preferred editor and make the following additive insertion with Beyond Compare review. No Python or PowerShell script is needed.

The latest visible navigation ends the new HTTP sections with **“HTTP caching, conditional requests and bounded admission”** (Chapters 162–166 and Videos 56–57), then continues to **“Framework integration examples”**. Insert the **four** groups below **before** the latter group, at the same YAML indentation as neighbouring top-level navigation groups.

## YAML insertion (copy exactly; maintain two-space indentation)

```yaml
  - "Nonblocking C23 networking and graceful shutdown":
      - "167. Why nonblocking I/O matters": lessons/05-engineering/167-why-nonblocking-io-matters.md
      - "168. Build a C23 select reactor": lessons/05-engineering/168-build-a-c23-select-reactor.md
      - "169. Monotonic timeouts and graceful shutdown": lessons/05-engineering/169-monotonic-timeouts-and-graceful-shutdown.md
      - "170. Test and diagnose the nonblocking server": lessons/05-engineering/170-test-and-diagnose-the-nonblocking-server.md
      - "171. Connect reactors to Umicom service ownership": lessons/05-engineering/171-connect-reactors-to-umicom-service-ownership.md
      - "Video 58. Two clients and one nonblocking reactor": videos/scripts/58-two-clients-one-nonblocking-reactor.md
      - "Video 59. Deadlines and graceful shutdown": videos/scripts/59-deadlines-and-graceful-http-shutdown.md

  - "C23 work handoff, cancellation and deterministic ownership":
      - "172. Why request handoff needs ownership": lessons/05-engineering/172-why-request-handoff-needs-ownership.md
      - "173. Bounded FIFO work and backpressure": lessons/05-engineering/173-bounded-fifo-work-and-backpressure.md
      - "174. Cancellation, generations and late completions": lessons/05-engineering/174-cancellation-generations-and-late-completions.md
      - "175. Quiescence and deterministic tests": lessons/05-engineering/175-quiescence-and-deterministic-tests.md
      - "176. From teaching queue to Umicom Framework": lessons/05-engineering/176-from-teaching-queue-to-umicom-framework.md
      - "Video 60. Who owns a request after handoff": videos/scripts/60-who-owns-a-request-after-handoff.md
      - "Video 61. Cancellation and late completions": videos/scripts/61-cancellation-late-completions-and-shutdown.md

  - "C23 dispatch, completion delivery and service contracts":
      - "Learning path": lessons/05-engineering/update-30-learning-path.md
      - "177. From handoff to completion delivery": lessons/05-engineering/177-from-work-handoff-to-completion-delivery.md
      - "178. Compose existing C23 libraries": lessons/05-engineering/178-compose-existing-c23-libraries.md
      - "179. Downstream capacity and fair scheduling": lessons/05-engineering/179-downstream-capacity-and-fair-scheduling.md
      - "180. Cancellation, identity and graceful drain": lessons/05-engineering/180-cancellation-identity-and-graceful-drain.md
      - "181. Verification and Framework integration": lessons/05-engineering/181-verify-and-integrate-umicom-services.md
      - "Video 62. From handoff to an owned completion": videos/scripts/62-from-handoff-to-owned-completion.md
      - "Video 63. When the completion queue is full": videos/scripts/63-when-the-completion-queue-is-full.md

  - "Professional Git and Umicom version control":
      - "182. Git working tree, index and history": lessons/05-engineering/182-git-working-tree-index-and-history.md
      - "183. Daily Umicom Git workflow": lessons/05-engineering/183-daily-umicom-git-workflow.md
      - "184. Remotes, fetch, pull and push": lessons/05-engineering/184-git-remotes-fetch-pull-and-non-fast-forward.md
      - "185. Git submodules and detached HEAD": lessons/05-engineering/185-umicom-git-submodules-and-detached-head.md
      - "186. Stash and preserve local work": lessons/05-engineering/186-stash-preserve-and-recover-work.md
      - "187. GitHub CLI and new repositories": lessons/05-engineering/187-github-cli-setup-and-repository-creation.md
      - "188. Read history, diffs and provenance": lessons/05-engineering/188-read-history-diffs-and-provenance.md
      - "189. Review, recover and revert safely": lessons/05-engineering/189-review-recover-and-revert-safely.md
      - "190. Git capstone and multi-repository release": lessons/05-engineering/190-umicom-git-capstone-and-cheat-sheet.md
      - "Git command quick reference": lessons/05-engineering/git-safe-commands-quick-reference.md
      - "Video 64. Git from working files to main": videos/scripts/64-git-from-working-files-to-main.md
      - "Video 65. Rescue a blocked Framework submodule": videos/scripts/65-rescue-a-blocked-framework-submodule.md
```

This block adds **24 chapters** across Updates 28–30, **eight video scripts**, **one new landing page** and **one Git command reference**. It leaves previously registered material untouched.

## Verify source files before accepting links

- Chapters 167–171 and Videos 58–59 require **Update 28**.
- Chapters 172–176 and Videos 60–61 require **Update 29**.
- Chapters 177–190, Videos 62–65, and the reference/landing page require **Update 30**.

If previous updates are missing, **merge them first**. Avoid adding nav entries pointing to files that do not exist. Verify old entries for *Islam: Blueprint for Life* and other historical books remain in their original sequence.

## Optional update of existing course index

The existing `content/lessons/05-engineering/index.md` is preserved and not overwritten. At the end of that file, a reviewed paragraph can link to the new landing page:

```markdown
## Native dispatch and professional Git workshops

[Continue with Major Update 30: C23 work dispatch and professional Git](update-30-learning-path.md).

For a compact everyday reference, see [safe Git commands for Umicom](git-safe-commands-quick-reference.md).
```

This is not required for the navigation group to function, but makes the material discoverable from the section overview.

## Final validation (PowerShell commands, not a script)

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\.venv\Scripts\mkdocs.exe" build --strict
git diff --check
git diff -- mkdocs.yml
```

Review the actual diff for unexpected removals. The strict documentation build needs the existing publishing environment. A successful XML check of new diagrams does not prove the full MkDocs site builds. Leave the update marked publication-pending until the strict build passes in the user's complete repository.
