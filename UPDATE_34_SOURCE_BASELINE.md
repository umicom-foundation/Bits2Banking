# Update 34 — Source and compatibility baseline

**Author:** Sammy Hegab · **Organisation:** Umicom Foundation  
**Inspection date:** 13 October 2026 (GitHub main, during batch authoring).

## Canonical upstreams observed

| Repository | Observed main revision | Purpose in this update |
|---|---|---|
| `umicom-foundation/Bits2Banking` | `99c6739295fff57d42aabc07723229caccdb6aff` | Source directory, education conventions, Updates 28–33, current MkDocs layout and existing native labs. |
| `umicom-foundation/umicom-framework` | `0d40b2d9222d0a0a0eaf912b8594e0e29fbb2796` | Existing public VCS/Git provider and submodule locking interfaces; **read-only reference**. |

The revisions above describe the **inspected authoring baseline**, not a Git lock, release guarantee or assertion that your local working tree matches it. Before merging the ZIP, compare its new files against your current local project and inspect any newer remote commits. No pull, commit or push is performed by the ZIP.

## Actual source reviewed

The existing Bits2Banking repository already contains:

- `NATIVE_SOURCE_POLICY.md` defining C23/Assembly preference and preserving legacy scripts without introducing new runtime implementations in them.
- `content/lessons/05-engineering/16-git.md` and `17-first-pull-request.md` explaining basic Git, contributor forks and collaborative workflows.
- The Update 29 bounded work-handoff lab, Update 31 Git history lab, Update 32 release-evidence lab and Update 33 Git review-timeline lab.
- Original `mkdocs.yml`, original Islam volume navigation and other published lessons.

The Framework repository contains the inspected public headers:

- `include/umicom/vcs/working_tree.h`
- `include/umicom/vcs/git_cli.h`
- `include/umicom/repository/gitlink.h`
- `include/umicom/repository/submodule_lock.h`
- `docs/SHARED_FRAMEWORK_SUBMODULE_UPDATE_POLICY.md`

The exact API names in Chapter 235 are based on those headers. The C23 lab in this update **does not need Framework to compile**, does not include Framework source and does not claim a linked Framework integration test.

## Folder compatibility

The update archive preserves the single top-level `Umicom-Bits2Banking` folder and adds files under established `content/lessons/05-engineering`, `content/videos/scripts`, `content/assets/diagrams`, and `labs/native`. Root-level `UPDATE_34_*.md` documents provide release, build, review and validation information. No prior file is replaced by design.

**Special caveat:** The live remote `mkdocs.yml` did not conclusively establish that all Update 28–33 navigation entries were already installed locally. The update therefore delivers a manual additive navigation group rather than a full replacement configuration.
