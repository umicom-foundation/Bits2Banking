# Chapter 282 — Select native tests and record what actually ran

**Bits to Banking · Optional Advanced Unit · Build and test engineering**  
**Time:** 30–45 minutes · **Requirements:** configured `contributor-notes` CMake build.

## Not every test is relevant to every source change

A contributor who edits a Markdown learning page needs content and link checks. Someone who changes `notes.c` must rebuild and run Notes tests. A change in a shared Framework header may require dependent application tests and packaging checks. Umicom Framework already provides the production **build-automation planning** service. CTest is one of the tools that actually *executes* registered tests.

We first learn how to run a targeted set of tests without confusing “selected” with “passed”.

## Step 1 — Confirm configuration

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
```

If the `contributor-notes` build directory is not configured, follow Chapter 277 before continuing.

## Step 2 — List the registered tests without executing them

```powershell
ctest --test-dir ".\output\learning-build\contributor-notes" -N
```

The result should list **eight** tests for the default standalone build. The `-N` option does **not** run these programmes, so do not write “8 passed” beside this output. It only proves the test registrations were visible to CTest.

## Step 3 — Run one named test

```powershell
ctest --test-dir ".\output\learning-build\contributor-notes" `
    -R "contributor_notes.capacity" --output-on-failure
```

`-R` chooses tests whose **test name** matches a regular expression. `capacity` checks what happens when our bounded note array has no free slot. It must reject the ninth note while preserving the eight existing notes. A regular-expression selection that matches zero tests must not be described as a successful regression.

## Step 4 — Run the full group

```powershell
ctest --test-dir ".\output\learning-build\contributor-notes" `
    --no-tests=error --output-on-failure
```

`--no-tests=error` turns a zero-selected-tests situation into an error, protecting us from accidentally claiming green results when nothing ran. `--output-on-failure` shows details for failed test programmes. Read the final test summary and compare the number of tests *registered* with the number *executed*.

## Step 5 — Record the evidence

A useful test record contains: source commit or reviewed working-tree state, operating system, compiler, CMake preset/build directory, actual command, selected tests, passed, failed, skipped and **not run** counts. A test that could not launch is “Not Run”; it is not “Passed”. If an optional Framework SDK integration was disabled, label it *not exercised* rather than adding it to the passing total.

## Regression selection and safety

A quick focused test is a helpful feedback step, not always the complete acceptance gate. For example, a change to Umicom Framework's stable C ABI can affect Studio, Trader, OS user-space and installers even if the Notes tests pass. Do not mark a complete platform build green solely because the smallest example passes.

**Practice:** List the eight tests without executing them. Run the `capacity` case, then run all eight. Write a one-paragraph evidence summary identifying which result came from a real execution and which was just discovery.

**Next:** [Publish a verified learning update safely](283-capstone-verified-learning-delivery.md).
