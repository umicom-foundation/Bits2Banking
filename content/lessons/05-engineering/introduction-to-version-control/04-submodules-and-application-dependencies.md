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

---

[Read this lesson in HTML](../../../courses/introduction-to-version-control/lessons/04-submodules-and-application-dependencies.html) · [Learning sequence](../../../start/learning-sequence.md)

[Next: Read a parent pin and a child checkout](05-read-a-parent-pin-and-a-child-checkout.md)
