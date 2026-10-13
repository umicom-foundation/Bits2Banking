# Episode 87 — From a dependency graph to C23 verification gates

**Bits to Banking · Umicom Foundation · Presenter script**  
**Companion lessons:** Chapters 255–257 · **Estimated running time:** 12–15 minutes.

## Opening (0:00–1:30)

**On screen:** Show `verification-gates-update36.svg`. Read the three evidence states: failed, not run and missing. Establish the real-world question: which checks are mandatory when a shared library changes?

**Narration:** “Running tests is not enough. We must know which tests ought to run and which source they covered. Today we will build a small C23 impact model, inspect its failure-atomic contracts and refuse a release conclusion when one required observation is absent.”

## C23 records and ownership (1:30–5:00)

Open `impact.h` and `impact.c`. Show the 12-module capacity, dependency bitsets, required-gate masks and revision capacity. Explain the rules for shifting integers, why names are copied into owned storage and why `BtbImpactAddDependency` rejects cycles.

**Narration:** “A named module is an identifier, not a path. It must be validated before we copy it. A bitset gives us a compact way to teach reverse dependencies, but it becomes dangerous if we shift past its width. The twelve-node bound and index checks prevent that.”

## Compile and run (5:00–9:30)

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\change-impact" -B ".\output\learning-build\change-impact" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\change-impact" --parallel 2
ctest --test-dir ".\output\learning-build\change-impact" --output-on-failure
& ".\output\learning-build\change-impact\btb-change-impact-demo.exe"
```

**Narration:** “The first assessment is deliberately blocked because the OS boot check was not run. The second assessment becomes suitable for human review only because the fictional record now contains the missing gate. Nothing in this demonstration has booted a real operating system.”

## Negative tests and review (9:30–15:00)

Run `plan_atomic`, `assess_overlap` and `assess_stale`. Show their source assertions. Explain why success means that invalid or stale evidence was rejected, not that the unsafe state was accepted. Close by relating this to banking and TMS engineering, where unsupported claims about tested states can affect real operational decisions.

**Audience task:** Add a diagram listing three changed components and their required gates. Explain why an overlapping pass/fail mask is invalid, whereas a stale but syntactically valid source SHA is a blocking review condition.

**Production boundary:** No asynchronous execution, Git mutation, financial permission or release automation is introduced.
