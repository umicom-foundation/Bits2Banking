# Major Update 35 — Source baseline and preservation record

**Source inspection date:** 13 October 2026  
**Canonical public Bits2Banking repository:** `umicom-foundation/Bits2Banking`  
**Repository root on the user's Windows machine:** `C:\umicom\Umicom-Bits2Banking`

## Observed remote checkpoints

At source inspection, the public Bits2Banking `main` reference was `0df1af46e98b8a471acc92762b08287487cb15cf`. The Umicom Framework `main` reference was `0d40b2d9222d0a0a0eaf912b8594e0e29fbb2796`. These are **inspection references**, not verified local checkout SHAs or a claim that every developer has fetched the current remote. This package is an additive ZIP based on the visible folder conventions, the previous Update 34 archive and the Framework public headers; it is not a full replacement of either repository.

The existing Bits2Banking educational tree contains `content/lessons/05-engineering`, `content/videos/scripts`, `content/assets/diagrams` and `labs/native`. Update 34 ended at Chapter 239 and Episode 81. This update begins at Chapter **240** and Episode **82**.

The relevant Framework public APIs inspected for this update include:

- `include/umicom/vcs/working_tree.h`
- `include/umicom/vcs/git_cli.h`
- `include/umicom/build/parser.h`
- `include/umicom/build/diagnostic.h`
- `include/umicom/diagnostics/compiler_parser.h`
- `include/umicom/repository/gitlink.h`
- `include/umicom/repository/submodule_lock.h`
- `docs/SHARED_FRAMEWORK_SUBMODULE_UPDATE_POLICY.md`
- `examples/build_diagnostics/CMakeLists.txt` (installed target `Umicom::build`)

The imported target `Umicom::vcs` was also found in the Framework build definitions. These public interfaces are the authority for optional integration. The package does **not** embed copies of Framework source or headers.

## Review requirements

1. Compare additions using Beyond Compare; do not mirror-delete the repository.
2. Verify that any local material from Updates 28–34 was preserved, whether or not the remote navigation currently lists it.
3. Merge new MkDocs entries only into the **current, complete** `mkdocs.yml`, preserving all Islamic content and book references.
4. Build and test the independent C23 laboratory on Windows UCRT64 before committing.
5. Treat SDK-linked Framework acceptance as a separate test, not presumed from the Linux standalone result.
6. Check the staged diff after `git add -A` and before committing to `main`.

**Source preservation:** zero existing files replaced, zero existing files deleted; no Framework/OS/Kernel/Application repository changes.
