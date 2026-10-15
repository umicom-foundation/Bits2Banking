# Update 43 — MkDocs navigation and preservation checklist

**Rule:** Do not replace your `mkdocs.yml` with a historical copy. Use the accompanying snippet as **new entries only**. Your current site may already contain later versions, original manuscripts, navigation and the historical *Islam: Blueprint for Life* book. All must remain.

1. Open your current `mkdocs.yml` and `UPDATE_43_MKDOCS_NAV_SNIPPET.yml` side by side in Beyond Compare.
2. Under the existing **System Administration From Zero** course group, append the Stage 6 Chapters **73–84** and the five Stage 6 reference files. Create a course group under the existing `nav:` key only if absent; never add a second `nav:` key.
3. Under your existing software engineering group, append Chapters **304–307**, which concern C23 access-review and Framework ownership.
4. Under Videos, add Episodes **121–125**. All five are Markdown narration scripts, not executable scripts.
5. Verify the resulting paths relative to `docs_dir: content`. Add the seven SVG illustrations under their existing `assets/diagrams/` path.
6. Run `mkdocs build --strict` using the existing publishing environment. If unavailable, document **not run**. A snippet syntax check is not equivalent to a full strict build.
7. View the standalone offline `UPDATE_43_SYSTEM_ADMINISTRATION_COMPLETE_COURSE.html` to review **84 continuous chapters**. Earlier 72 chapter bodies are preserved byte-for-byte; this is an additive edition.

### Required quality gates

- [ ] All previous chapter and video links retained.
- [ ] The original Umicom New Project Beginner Guide remains present and attributed from the earlier update.
- [ ] Every added `.md` referenced in the merged navigation resolves under `content/`.
- [ ] PowerShell commands are **instructions only**, not generated `.ps1` files.
- [ ] Real SSH, TLS, firewall, key or Git operations are **not** implemented by the new C23 lab.
- [ ] Git staged changes include only the intended additions and reviewed navigation edit.

The ZIP is **additive** and does not ship a replacement `mkdocs.yml`, `index.md` or existing lab file. Only one top-level folder exists: `Umicom-Bits2Banking/`.
