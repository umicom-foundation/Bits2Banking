# Submodules and application dependencies

Umicom Applications uses separate repositories for shared Framework and application modules. The parent records which child commits belong together.

## Read the real registration

Open `Umicom-Applications/.gitmodules`. The Framework entry includes:

```text
[submodule "framework"]
    path = framework
    url = https://github.com/umicom-foundation/umicom-framework.git
    branch = main
```

The path is relative to the parent repository. The URL says where the child history comes from. The branch setting is a preference for branch-aware operations; it does not automatically keep every checkout on main or at the latest commit.

A **gitlink** is the parent tree entry that records a child commit identifier. The child has its own files, staging area and commits. Recording the parent does not record uncommitted child edits.

 <svg viewbox="0 0 700 110" role="img" aria-label="Publish shared source once; then each parent records the checked-out child commit it uses." style="width:100%;max-width:700px"><title>Publish shared source once; then each parent records the checked-out child commit it uses.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">Publish Framework</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">Update clean copies</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">Record parent pin</text></svg>

Publish shared source once; then each parent records the checked-out child commit it uses.

## Inspect the relationship

```text
Set-Location "C:\umicom\Umicom-Applications"
git ls-tree HEAD framework
git -C framework status --short --branch
git -C framework rev-parse HEAD
git diff --submodule=log
```

The first command shows the published-in-that-parent pin. The third shows the child currently checked out. Different identifiers need explanation: the child may be intentionally newer, older, or independently edited. A parent status can also report modified child content without a changed child commit.

## Follow the Framework implementation

Read `umicom-framework/src/repository/control/lock_plan.c`. `umi_repository_lock_plan_build` receives an inventory, observed child heads and policy, then produces proposed steps. Its action names include `no-change`, `stage-gitlink` and `missing-head`. This separates deciding what to record from actually changing the parent index.

```text
for each registered child:
    read its checked-out commit
    if the commit is missing:
        report the missing input
    otherwise:
        compare it with the parent's recorded commit
        propose no change or a gitlink update
```

This is explanatory pseudocode, not an executable script. Locking records checked-out revisions; it does not download new source or prove that every child commit is published.

## A safe publication order

1. Review and publish the edited Framework repository once.
2. Fast-forward other clean main-branch Framework copies to the published revision. Preserve unique edits separately.
3. Review the parent gitlinks and its own changes.
4. Record and publish the parent after its children. A parent push using `--recurse-submodules=check` checks referenced submodule commits are available on a remote.

That availability check is not proof that every remote is the intended one or that tests passed. Do not update third-party dependency pins merely because another dependency changed.

## Exercise

Framework contains an uncommitted edit, while its HEAD identifier still equals the parent pin. Will committing the parent include that edit?

<details>

<summary>Answer</summary>

No. The edit belongs to the child working tree. First review and record the child, publish it, then record the new child identifier in the parent.

</details>

## Choose one editing copy explicitly

A remote repository can appear in several local directories. That does not make those directories interchangeable. An operating-system checkout may contain Framework for dependency builds, while the Applications checkout contains the copy where shared source is authored.

For an existing Umicom workspace, this command previews the explicit ownership policy. It fetches metadata but does not stage or publish:

```text
umicom repo publish-all "C:\umicom" --primary-directory Umicom-Applications
```

The path after `--primary-directory` is relative to the workspace argument. The service groups checkouts by remote identity, selects the unique matching copy in that directory, then orders the groups by their child relationships. It includes application modules such as Healthcare when they are registered under that Applications checkout. A repository elsewhere, such as Kernel, retains ordinary selection if no copy is inside the chosen directory.

Read [the primary-selection source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/repository/operations/publication_primary.c). Notice that it does not copy files. An edited outside copy or a different unpublished history stops publication. A misspelled primary directory is also an error; silent fallback could publish from the wrong place.

### Work through two copies

Suppose `Umicom-Applications/framework` is clean at commit A, and `umicomOS/framework` contains an uncommitted fix based on A. Which copy should the explicit policy publish?

<details><summary>Worked answer</summary>

Neither is ready. The fix exists outside the designated authoring directory. Preserve it, compare it with the primary source, and deliberately reconcile it there. The service must not silently promote the dependency copy or erase its edits. After publishing the intended Framework change once, clean copies can fast-forward and parents can record their checked-out revisions. The `framework.repository.publication.primary.edited-copy` regression covers this refusal; it is separate from proving an actual remote push succeeded.

</details>

## Observe recursive revisions through the native CLI

Prepare an existing local checkout with its registered children. This command observes them without fetching, initializing or changing their revisions:

```text
umicom repo submodules "C:\umicom\Umicom-Applications"
```

1. Read the commit identifiers and leading markers. A space means initialized at the indexed revision, minus means uninitialized, plus means a checked-out revision differs, and U means an unresolved submodule merge conflict.
2. Inspect changed working files separately with `umicom repo review --root PATH` inside each initialized child. The recursive listing does not prove those files are clean.
3. Retain the listing with the parent HEAD record and the exact qualification command. Neither record proves remote freshness.

The direct alternative is `git submodule status --recursive` from the parent. A successful native observation exits with zero even if it reports mismatches: success means the observation completed. A failed process, ten-second timeout, capture exceeding 4 MiB or malformed record exits with one and publishes no counts. Argument errors exit with two. Review partial diagnostic output before retrying; do not interpret it as an empty repository.

### Diagnose an unexpected status line

The shared implementation lives in [submodule_probe.c](https://github.com/umicom-foundation/umicom-framework/blob/main/src/repository/inspection/submodule_probe.c). The reader retains bounded bytes, checks every complete record, then assigns the summary. A diagnostic such as “warning: …” must not become an initialized-child count. The parser accepts 40- or 64-digit hexadecimal commit IDs and preserves the human-readable tail without pretending to extract an exact pathname. Escaped display text is not a command argument.

**Exercise:** the listing contains two valid records followed by an unexpected diagnostic. Should the CLI publish a count of two?

<details><summary>Worked answer</summary>

No. That would make partial evidence look complete. The parser refuses the whole summary and leaves the caller's existing output unchanged. The CLI displays the failed observation and its captured text. The `framework.repository_inspection.submodules.warning` case places the diagnostic after a valid record to check this boundary. A separate oversized-line case ensures a long record is validated rather than silently skipped. These are source-level regression contracts; executing them and testing real Git output are separate qualification steps.

</details>

Read the [Git submodule reference](https://git-scm.com/docs/git-submodule) for the status convention. No command in this observation exercise changes a parent pin.

---

[Read this lesson in HTML](../../../courses/introduction-to-version-control/lessons/04-submodules-and-application-dependencies.html) · [Learning sequence](../../../start/learning-sequence.md)

[Next: Read a parent pin and a child checkout](05-read-a-parent-pin-and-a-child-checkout.md)
