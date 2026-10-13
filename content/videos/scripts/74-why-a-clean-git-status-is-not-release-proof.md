# Episode 74 — Why a clean Git status is not release proof

**Bits to Banking · Umicom Foundation · Author: Sammy Hegab**  
**Format:** 8–11-minute narrated terminal demonstration.  
**Reading:** Chapters 216–217 and the Framework `working_tree.h` public contract.

## Learning objective

By the end, viewers can identify the different responsibilities of HEAD, the index, a remote-tracking reference and a parent repository's submodule gitlink. They understand why a clean working tree does not imply that the build, remote ancestry or OS integration was validated.

## Opening (0:00–1:15)

**Visual:** A terminal shows `git status` saying “nothing to commit, working tree clean”. Alongside it, a second pane shows Umicom OS still recording a different Framework SHA.

**Narration:** “A clean checkout is valuable evidence, but it answers only one question. Today we will identify what Git checked, what Git did not check, and why release engineering needs the answers kept separate.”

**On-screen prompt:** *Repository clean ≠ Remote current ≠ Tests passed ≠ Parent gitlink verified.*

## Demonstration (1:15–4:30)

Show PowerShell in a local Umicom OS checkout. Run `git status`, `git rev-parse HEAD`, `git ls-files --stage framework`, `git submodule status framework` and `git -C framework rev-parse HEAD`. Pause after each command; label the repository that owns the displayed SHA. Do not assume the submodule's working tree is safe to change.

Explain that `160000` represents a gitlink. A framework directory tracked by a parent is not stored as ordinary source files within the parent's commit. The parent points to one child commit. Updating the checkout and publishing a new parent pointer are different operations.

## Inspect the Framework API (4:30–7:30)

Open `include/umicom/vcs/working_tree.h`. Highlight `UmiVcsWorkingTreeRead`, `UmiVcsWorkingTreeDescribe` and `UmiVcsWorkingTreeDestroy`. Trace ownership: a read creates an owned observation, describe copies its summary, destroy releases it. Explain why applications should consume this provider rather than parsing localized, human-oriented Git output themselves.

Show `git status --porcelain=v2 --branch` as a diagnostic. Explain that the byte-safe `-z` form exists and should be consumed by a bounded native parser, already a Framework responsibility.

## Learner challenge (7:30–10:00)

Ask which command proves remote publication. The correct answer is: no displayed command alone proves that the tested child commit is published and pinned; further remote and release evidence is required. Have viewers write a five-column checklist: repository, current SHA, remote comparison, changes, build/test proof.

## Closing

“Version control is not only about commands. It is about being able to say exactly what changed, who owns it, and which evidence shows that the next operation is safe.” Link to Chapter 218 and Episode 75. The episode performs no Git writes.
