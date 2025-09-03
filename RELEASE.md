# Release Guide — Bits to Banking

This guide explains how to cut a release and publish the latest book artifacts.

---

## Versioning
- Use **calendar tags** for early drafts, then semantic once stable.
  - Examples: `v2025.09.02`, `v0.1.0`, `v0.2.0`
- Keep **CHANGELOG.md** up to date.

---

## Pre‑release Checklist
1. CI is green (Build, Lint, Docs).
2. `README.md` links work (About, Roadmap, Support, etc.).
3. `CHANGELOG.md` has an entry for this release.
4. Volume builds succeed locally.
5. Donation details in `SUPPORT.md` still valid.

---

## Step‑by‑Step (Git / GitHub)

### 1) Update CHANGELOG
Add a new block at the top for the date/version.

```markdown
## [2025-09-02]
### Added — 2025-09-02
- ...
### Fixed — 2025-09-02
- ...
```

Commit the changes:
```powershell
git add CHANGELOG.md
git commit -m "docs(changelog): update for <version>"
git push
```

### 2) Create a Tag
Pick a version (example here uses a calendar tag):

```powershell
$version = "v2025.09.02"
git tag -a $version -m "Release $version"
git push origin $version
```

> You can also use semantic versioning: `v0.1.0`, `v0.2.0`, etc.

### 3) Build Artifacts Locally (optional but recommended)
```powershell
python scripts\make_volume0_from_md.py
# Output: volumes\Volume_00_Source_Control.docx
```

### 4) Draft a GitHub Release
Go to **GitHub → Releases → Draft a new release**:
- **Tag**: select the tag you just pushed
- **Title**: `Release <version>`
- **Notes**: copy highlights from CHANGELOG
- **Attach files**: upload `volumes/Volume_00_Source_Control.docx` (and PDFs if available)
- Click **Publish release**

### 5) Verify Pages Site (Docs)
- Ensure **Settings → Pages → Source = GitHub Actions**
- Check the site updates after the latest build: <https://umicom-foundation.github.io/Bits2Banking>

---

## Optional: GitHub CLI (gh)

If you have the GitHub CLI installed and authenticated (`gh auth login`), you can automate some steps:

```powershell
# Create a release with notes from CHANGELOG and attach DOCX
$version = "v2025.09.02"
gh release create $version -t "Release $version" -n "See CHANGELOG for details."
gh release upload $version .\volumes\Volume_00_Source_Control.docx
```

---

## Post‑release
- Announce in Discussions.
- Share links to the **Release** and **Docs**.
- Thank new contributors in ACKNOWLEDGEMENTS (if applicable).

---

## Troubleshooting
- **Pages 404 during deploy**: ensure repo **Settings → Pages → Source = GitHub Actions** and workflow permissions include `pages: write`, `id-token: write`.
- **Missing artifact**: build locally and attach, or ensure CI uploads the DOCX in the build job.
