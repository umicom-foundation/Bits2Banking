# Major Update 35 — Technical overview

**Framework VCS Integration, Build Diagnostics and Owned C23 Evidence**  
Sammy Hegab · Umicom Foundation · 13 October 2026

## 1. Scope and architectural ownership

The batch introduces Chapters **240–251**, Episodes **82–85**, five original SVG diagrams, a native C23 `build-evidence` laboratory, a Git/build quick reference and an instructor guide. All files are new. Existing Framework, Studio, Trader, Bank, Kernel, OS, Bits2Banking manuscripts and site configuration are not replaced.

The **production** owners are already in Umicom Framework. `UmiVcsWorkingTreeRead` and `Describe` provide read-only Git observations. `UmiCompilerDiagnosticParseText`, `umi_build_parse_diagnostic_line` and `umi_build_parse_output` provide canonical compiler/build diagnostics. `umi_repository_submodule_lock` and the `umicom repo verify/lock` command manage parent gitlink staging under review. **This batch does not implement any of those capabilities again.**

The **educational** owner, Bits2Banking, receives copied, normalised facts and demonstrates safe interpretation: who owns a snapshot, whether evidence is complete, what changed across two builds, and what a release reviewer should refuse to assert.

## 2. Native library API

The standalone public header is `labs/native/build-evidence/evidence.h`. All names use existing C23 coding conventions, with UpperCamelCase functions (`BtbEvidenceRunInit`), camelCase fields and UPPER_SNAKE constants.

| Function | Purpose | Failure contract |
|---|---|---|
| `BtbEvidenceRunInit` | Validate a complete revision/profile/toolchain identity | Invalid input preserves caller output |
| `BtbEvidenceAddProblem` | Deep-copy one already parsed diagnostic | Invalid, locked or full leaves snapshot unchanged |
| `BtbEvidenceRecordBuild` | Record process exit and dropped diagnostics | Record exactly once; no later problem additions |
| `BtbEvidenceRecordTests` | Record passed/failed/skipped/not-run counts | Requires build; guards `size_t` overflow and repeat writes |
| `BtbEvidenceSeal` | Finish the immutable observation | Does not mean success; requires build outcome |
| `BtbEvidenceRunValid` | Inspect bounds, text fields and invariants | Read-only; no mutation |
| `BtbEvidenceAssess` | Explain blocked/incomplete/stale review evidence | Returns a copied report only on valid input |
| `BtbEvidenceCompare` | Exact multiset comparison of two sealed snapshots | Refuses incompatible profile/toolchain and invalid inputs |

### Source-identity limitations

- Accepts 40-hex SHA-1 or 64-hex SHA-256 strings. Does not implement Git object hashing or ref resolution.
- The SHA represents a commit, not a dirty worktree. The caller remains responsible for worktree provenance.
- An observation sequence is caller-supplied, not a trusted clock or signing proof.
- Umicom OS publication needs its **own** parent SHA and the exact child Framework gitlink; one SHA alone is not a multi-repository release manifest.

### Bounded storage

- Maximum 24 diagnostic *occurrences* per snapshot.
- SHA storage: 65 bytes. Profile/toolchain: 80 bytes each.
- File path: 256 bytes, diagnostic code: 64 bytes, message: 256 bytes, including the terminating NUL.
- No heap, global mutable runtime, mutex, background thread, socket, shell invocation or filesystem modification in the standalone model.
- Oversized or malformed text is rejected rather than silently cropped; `droppedDiagnostics` represents input limitations reported by the owner.

### Exact comparison algorithm

For each current record, search for a previous **unmatched** record with equal stage, severity, source path, position, code and message. Count a match as persisting. Otherwise count it as introduced. Any previous occurrences left unmatched are resolved. Duplicate messages are treated as occurrences, not collapsed into a set. Complexity is O(n²), with n at most 24. Different toolchains or profiles return `INCOMPARABLE` without touching the output report.

A moved line number may produce one introduced and one resolved record; this lab does not implement AST-based diagnostic identity. `earliestErrorStage` is the earliest reported error phase, **not** an automatically determined root cause.

## 3. Real Framework SDK adapter (optional)

`framework_bridge.h` and `framework_bridge.c` include supported public headers, copy `UmiVcsWorkingTreeSummary` into the teaching identity and project `UmiBuildDiagnosticList` records. The adapter never parses Git status output or compiler text. It links `Umicom::vcs` and `Umicom::build` when the installed CMake package is enabled via `BTB_ENABLE_FRAMEWORK_SDK=ON`. The companion `framework_demo.c` uses the real read-only Framework VCS reader (optional `--repo`) and canonical compiler-line parser.

The default C23 build excludes these sources. The optional SDK target was **not built or tested** in the authoring environment; it requires a matching installed Framework. Its compile/link/runtime qualification is an open acceptance gate, not a claimed achievement.

## 4. Source-preservation decisions

No pre-existing code is modified or deleted. The update does not touch `mkdocs.yml` because prior local merges may have added chapters not yet registered in the public repository. The navigation document provides reviewable additive entries instead. The original *Islam: Blueprint for Life* volume and all historic lesson/video paths remain unmodified.

The only delivered new executable source uses C23. PowerShell appears solely as interactive build/Git instructions. The existing MkDocs virtual environment is invoked as an existing documentation tool, not implemented or replaced by a new Python script.

## 5. Tests and acceptance

The standalone CMake configuration registers **56 named CTest cases**, including a runnable demo. Tests cover SHA/identity bounds, deep-copy and data ownership, malformed and unterminated text rejection, capacity, failure-atomic mutation, sealed-state rules, compiler/build/test review flags, dropped diagnostics, skipped/not-run tests, exact duplicate matching, changed source locations, incompatible toolchains and a reproducible 50,000-operation property scenario.

Validation under GCC 14.2.0 C23 and Clang 17 ASan/UBSan is recorded in `UPDATE_35_VALIDATION_REPORT.md`. The Windows UCRT64 toolchain, full website build, standalone Windows runtime packaging, full Framework tests and optional installed SDK integration are **not run** here.

## 6. Next engineering direction

The next learning batch can develop source-to-test change impact and crash-evidence workflows that reuse Framework test platforms and diagnostics; it should not implement yet another Git client or compiler parser. Before enabling production repository operations, complete real SDK-linked tests and Windows/OS integration acceptance with explicit user approval.
