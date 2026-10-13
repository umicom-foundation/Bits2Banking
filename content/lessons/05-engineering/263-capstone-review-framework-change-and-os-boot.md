# Chapter 263 — Capstone: review a Framework change and an Umicom OS boot gate

**Bits to Banking · Engineering track · Umicom Foundation**  
**Prerequisites:** Chapters 252–262, the Git recovery lessons and C23 build basics.

## Objective

Prepare an evidence-driven recommendation about a **fictional change to shared Umicom Framework base services**. The candidate also affects a Studio consumer and an Umicom OS desktop profile. You must separate checked facts from missing observations, preserve source, reproduce the C23 teaching lab and explain why a passing unit suite does not prove an actual OS boots.

The objective is a traceable engineering note, **not** a green badge. A valid conclusion can be “blocked: QEMU boot not run” or “blocked: local child has unpublished changes”. No live source modifications are needed for the classroom exercise.

## Part 1 — Inspect a real checkout without mutation

```powershell
Set-Location "C:\umicom\Umicom-Applications"
git status
git branch --show-current
git rev-parse HEAD
git -C ".\framework" rev-parse HEAD
git -C ".\framework" status --short
git diff --submodule=log -- framework
```

Record the parent SHA, Framework SHA, branch status and unexpected changes. If you also have Umicom OS locally, compare its **independent** pinned reference:

```powershell
Set-Location "C:\umicom\umicomOS"
git status
git ls-files --stage -- framework
git submodule status framework
git -C ".\framework" rev-parse HEAD
```

Do not synchronise or switch branches during this step. A dirty worktree or unpublished commit requires a preservation plan first. See Chapter 260.

## Part 2 — Reproduce the self-contained C23 demonstration

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\change-impact" `
    -B ".\output\learning-build\change-impact" -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\change-impact" --parallel 2
ctest --test-dir ".\output\learning-build\change-impact" --output-on-failure
& ".\output\learning-build\change-impact\btb-change-impact-demo.exe"
```

The demo uses an explicitly **fictional** full SHA. It constructs four nodes, changes `framework.base` and computes which consumers and gates follow. Its first assessment is blocked because `BOOT` is not run. Its second assessment is eligible for *human review only* after a fictional boot result is supplied. Those printed results are not real acceptance evidence from any Framework, Studio, Bank or OS checkout.

## Part 3 — Classify the required evidence

Build a small review table with columns: affected module, reviewed source SHA, dependent target, named tests, actual outcome, missing evidence and owner. Include Framework, Studio and Umicom OS. For OS, distinguish a native host-component test from real QEMU image boot; one does not substitute for the other. For Studio, distinguish model tests from a GUI launch/installer smoke test.

Describe which Framework API owns each observation. For Git working-tree facts use `UmiVcsWorkingTreeRead`; for compiler diagnostics use Framework's build parser; for production source impact use Framework's **already-existing** `UmiBuildAutomation` service. The small bitset model is an instructional comparison only. Do not implement another production planner in Bits2Banking or a product repository.

## Part 4 — Simulate missing and failed results

Run the negative tests:

```powershell
& ".\output\learning-build\change-impact\btb-change-impact-test.exe" assess_not_run
& ".\output\learning-build\change-impact\btb-change-impact-test.exe" assess_stale
& ".\output\learning-build\change-impact\btb-change-impact-test.exe" assess_dropped
& ".\output\learning-build\change-impact\btb-change-impact-test.exe" assess_multiple
```

Each case must exit successfully **because** the unsafe conclusion is rejected. Record exactly which reason bit appears and why the result should stop release qualification.

## Part 5 — Prepare the source-preserving publication order

If a real, reviewed change is necessary, modify the authoritative Framework checkout first (`C:\umicom\Umicom-Applications\framework`), build and test it, verify branch `main`, stage only intended work, inspect the staged diff, commit and push Framework. Then update the Applications parent's Framework gitlink, verify its integration, commit and push that parent. Separately synchronise Umicom OS's clean Framework checkout, build and test OS, verify the parent pointer and finally commit and push the OS parent. **Never copy the Framework source into each parent**, force an update over dirty files or commit a failed qualification as if it passed.

For the learning-repository delivery itself, only `Umicom-Bits2Banking` should be committed, after its actual local tests and navigation review. The exact standard commands are in `UPDATE_36_BUILD_TEST_AND_GIT.md`.

## Required assessment artefact

Write a two-page engineering note containing: problem definition; authoritative repositories; complete observed SHAs; branch/detached state; local tracked/untracked changes and preservation status; source-to-consumer graph; affected-module and gate masks; exact compiler/configuration; CTest totals including not-run; GUI/boot acceptance; any dropped diagnostics; pending checks; minimum safe change; recovery and rollback plan; and reviewer decision. Mark unknowns as unknowns rather than guessing.

## Instructor rubric

A complete submission should demonstrate: correct Git identity and gitlink interpretation; no destructive commands; validated C23 build; correct explanation of all observed gate categories; accurate treatment of missing, stale and dropped evidence; safe Framework-first publication order; and honest separation of the educational simulation from live Umicom product readiness. Answers that merely report “tests passed” without identifying the source and required consumers are incomplete.

**Next major update:** advance the native engineering curriculum into target-level build graphs, incremental regression selection, structured test observations and controlled delivery, reusing Umicom Framework whenever real product functionality is required.
