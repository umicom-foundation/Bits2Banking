# Major Update 32 — Source baseline and integration caveats

**Prepared:** 13 October 2026 (UTC date)  
**Bits2Banking GitHub repository:** `umicom-foundation/Bits2Banking`  
**Observed `main` commit during authoring:** `88efcf4a50c65c8a9a85744ee58c78bf37a8dfc2`  
**Umicom Framework GitHub repository:** `umicom-foundation/umicom-framework`  
**Observed Framework `main` during authoring:** `0d40b2d9222d0a0a0eaf912b8594e0e29fbb2796`

These are **reference observations**, not demands to reset or downgrade your existing checkout. Before merging, compare your local repository with the delivered new files. The source package does not include, rewrite or alter `mkdocs.yml`, existing CMake projects or previous lesson files.

The existing Bits2Banking `NATIVE_SOURCE_POLICY.md` requires C23-first native software, assembly when justified, preservation of older manuscripts and no new Python/PowerShell scripts. Update 32 follows that rule. The older source tree may already contain historical scripts; this ZIP neither removes nor introduces them.

The public Framework API and workflow references used in the lessons were read directly from:

- `include/umicom/vcs/working_tree.h`
- `include/umicom/vcs/git_cli.h`
- `include/umicom/repository/gitlink.h`
- `include/umicom/repository/submodule_lock.h`
- `docs/SHARED_FRAMEWORK_SUBMODULE_UPDATE_POLICY.md`

A user-provided Framework checkout could be at a different revision. Check the *actual local public header* before compiling a production integration; this update intentionally does not install one.

**Integration status:** All project paths added by Update 32 are new. MkDocs navigation merge, complete website build, Windows UCRT64 tests and any live GitHub publishing remain local follow-up steps. See the validation report for executed and not-run checks.
