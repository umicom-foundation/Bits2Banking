# Update 34 — Instructor guide and assessment rubric

**Bits to Banking · Professional Git engineering · Umicom Foundation**  
**Author:** Sammy Hegab · **Audience:** experienced beginners to intermediate contributors.

## Teaching philosophy

Treat the Git incident as a software engineering exercise, not a list of magical commands. Ask students to explain **why** Git rejected an operation and **which object or reference** a command manipulates. Use the current Umicom projects to make the exercise relevant: the Framework checkout under Applications is authoritative for reusable code, while an OS `framework` gitlink records a tested consumer revision. Students must never be encouraged to delete source merely to make `git status` clean.

The three-way lab is a deliberately bounded C23 record model. It is **not** Git's actual text merge, a production source merge, a banking transaction engine, a security boundary, or a replacement for existing Framework VCS. This distinction should be restated at the beginning and end of the laboratory.

## Suggested schedule (6–9 hours)

- **Workshop A (60 min):** Objects, refs, HEAD/local main/origin main, merge base and ahead/behind. Use Chapters 228–229 and inspect `git cat-file` output.
- **Workshop B (75 min):** Create a disposable two-clone conflict on `main` following Chapter 230; read three index stages, list requirements, resolve without deleting behaviour.
- **Workshop C (90 min):** Walk `merge.h` and `merge.c` function by function. Model unilateral, identical and conflicting decisions including absence/deletion; run demo.
- **Workshop D (60 min):** Run the 36 CTest cases. Step through one capacity rejection and one unresolved-output refusal in the debugger.
- **Workshop E (60 min):** Inspect Framework VCS contracts and the real source-owner/OS-consumer Git policy. Present a no-destructive-command recovery plan.
- **Workshop F (60 min):** Review a hypothetical tested release and execute the Bits2Banking `git add -A`, `git commit`, `git push origin main` sequence only in an authorised repository.

## Marking rubric (100 points)

| Criterion | Points | Acceptable evidence |
|---|---:|---|
| Ref and ancestry literacy | 15 | Correct distinction between HEAD, local main, origin/main, merge base and parent gitlink. |
| Index stage interpretation | 15 | Correct stage 1/2/3 evidence and an explanation for absent stages. |
| Source preservation | 15 | Both functional requirements identified; avoids silent deletion, hard reset, forced push and blind side selection. |
| C23 API understanding | 15 | Can explain caller-owned buffers, copied plan, no partial output, bounded inputs and conflict states. |
| Executable testing | 15 | Actual CTest transcript with observed pass/fail total and analysis of one failed/error path. |
| Framework integration boundaries | 10 | Uses canonical Framework contracts; understands OS/Applications consumer pins. |
| Release and Git discipline | 10 | Reviews staged diff, uses direct main workflow correctly and distinguishes local commit from remote publication. |
| Evidence honesty | 5 | Labels NOT RUN or BLOCKED rather than fabricating acceptance. |

## Instructor answer key

**What is a merge base?** A common ancestor of two histories, used to establish the starting content for three-way comparison. It does not tell us which descendant implementation is business-correct.

**What are index stages 1/2/3?** Base, checked-out side, incoming side in a merge. Their presence depends on conflict type; stage 1 can be absent in add/add and one descendant can be absent in delete/modify.

**Can an implementation be deleted because the merge was mechanically clean?** No. The Umicom source-preservation rule requires review of existing behaviour, comments, headers and features. A mechanically clean merge can still introduce semantic regression.

**Why does `git push origin main` fail from detached HEAD?** The command pushes the local `main` ref, not necessarily the detached checked-out commit. If local main is behind remote, a non-fast-forward rejection protects remote history.

**What does `umicom repo lock .` do?** It stages a parent repository's gitlink(s) using currently checked-out submodule HEADs. It does not update the child from GitHub, run tests, commit or push.

**When does `BtbMergeMaterialise` write to its output?** Only after it validates the plan and confirms every conflicting record is resolved. Its local candidate is then copied into caller-owned output as one step.

**Why no Python or PowerShell scripts?** New executable project logic is C23; PowerShell is used only as an interactive command interface. CMake describes the native build, not application logic.

## Instructor caution

Do not ask students to reproduce destructive conflict scenarios in the real Umicom Framework, Applications or OS checkouts. The practice commands in Chapter 230 create **disposable local repositories**. Verify student terminal location before any write. A learner who safely stops because evidence is missing may be more competent than someone who forces an apparently successful push.
