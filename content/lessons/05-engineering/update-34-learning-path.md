# Update 34 guided learning path — from Git conflict to reviewed Umicom main

**Audience:** Contributors who know basic Git commands and C23 syntax but need to handle complex Umicom repository incidents safely. **Programme:** 6–9 hours plus assessments.

## Learning progression

| Session | Material | Demonstrable outcome |
|---|---|---|
| 1 — Git internals | 228–229; Video 78 introduction | Explain commit/tree/blob identity, local/remote refs and common ancestry. |
| 2 — Conflicts | 230–231; Video 78 | Read actual index stages 1/2/3 in a disposable practice repo and articulate both requirements. |
| 3 — C23 ownership | 232–233; Video 79 | Build the bounded reconciliation model, inspect conflict classification and distinguish absence from empty values. |
| 4 — Validation | 234; Video 79 | Run 36 focused CTest cases, inspect atomic failure and explain why a model is not the Git engine. |
| 5 — Framework authority | 235–237; Video 80 | Trace existing Framework VCS contracts, identify OS parent/child SHAs and preserve unpublished work. |
| 6 — Release evidence | 238–239; Video 81 | Produce a reviewed commit/pin/publication plan and execute the Bits2Banking main-only workflow only after gates pass. |

## Evidence students must submit

A complete submission contains (1) output of the disposable conflict's `git ls-files --unmerged`, (2) a written interpretation of stages 1/2/3, (3) the C23 demo output, (4) CTest pass/fail details, (5) parent-child SHA table for an inspected checkout, (6) an explanation of the Framework source owner, and (7) the reviewed staged diff for any repository they are authorised to commit.

An accepted answer may state **BLOCKED** or **NOT RUN** for a missing integration test. The assessment rewards accurate evidence, not optimistic completion percentages.

## Suggested discussion questions

Why can `git push origin main` reject when `git status` is clean? Why can two independent changes require a third combined implementation? Why must the Framework source be committed first while OS pins it later? Which C23 API ensures an unresolved conflict cannot publish a half-written result? Compare the stored SHA identity with the independent evidence of compilation and runtime behaviour.

## Safety and scope

Use the disposable practice repositories in Chapter 230 for mutating Git exercises. Do not run training merge commands against canonical Umicom Framework, Applications, Kernel or OS repositories. The delivered native code is purely educational and resides under `labs/native/git-three-way`. No Python or PowerShell implementation scripts are added. Markdown, SVG and CMake are document/build formats.
