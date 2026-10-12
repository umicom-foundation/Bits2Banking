# Chapter 201 — GitHub reviews, permissions and contributor collaboration

**Bits to Banking · Open-source collaboration · Umicom Foundation**
**Prerequisites:** [First contribution and pull request](17-first-pull-request.md), Chapters 196 and 200.

## Direct-to-main development and external contribution are different roles

Umicom's maintainer workflow deliberately commits approved changes to `main` without creating internal feature branches. That is a workflow policy, not an argument against code review. Every direct commit still needs a clear change scope, tests, full-file inspection, correct licence and evidence that the remote history has not advanced unexpectedly. External contributors may fork a public repository and submit a pull request for maintainer review; their fork/branch workflow does not require changing the maintainer's internal direct-to-main rule.

A pull request is a proposal to integrate changes. It provides a conversation, diff, checks and review history. A green automated build is useful but not evidence that a new financial workflow is authorised or that native memory ownership is correct. Reviewers must connect implementation to its documented contract and check what has been retained or superseded.

## A practical Umicom source review

For a C23 Framework change, inspect the public header first: input validation, error codes, caller-owned buffers, pointer lifetimes, cancellation semantics, ABI stability and possible reuse by multiple products. Next inspect the implementation for failure atomicity and bounds. Then inspect tests: nominal, invalid, boundary, repeat operation, cancellation and resource cleanup. Finally, check documentation and build CMake registration. An untested new `.c` file lying in a repository may not be compiled by any target.

For a Bits2Banking curriculum change, review the learner's path in the correct order, verify every linked source filename and run the actual displayed commands. A professional tutorial should identify **what a successful result proves**, what it cannot prove, and how to recover from a rejected command. Do not delete earlier authored lessons to make a table of contents shorter.

## Read-only GitHub CLI checks

In an authenticated clone, the following commands inspect rather than edit the remote repository:

```powershell
gh auth status
gh repo view umicom-foundation/Bits2Banking
gh pr list --repo umicom-foundation/Bits2Banking
gh issue list --repo umicom-foundation/Bits2Banking
```

Authentication and permissions vary per contributor. `gh auth login` can connect a developer's account, but must never require placing a token in a tracked project file. Do not copy other people's personal access tokens into documentation. A maintainer decides whether to merge a reviewed contribution; maintainers may require additional checks for Framework, trading risk, banking or kernel code.

## Approval questions

1. Does the change belong in Umicom Framework or in a thin application?
2. Does it preserve public interfaces, headers and previous functionality?
3. Can we reproduce the build and relevant tests on the target platform?
4. Is the developer authorised to publish the change to the remote repository?
5. Are all external dependencies and untested assumptions recorded explicitly?

**Next:** [The native C23 graph model](202-model-git-ancestry-in-c23.md).
