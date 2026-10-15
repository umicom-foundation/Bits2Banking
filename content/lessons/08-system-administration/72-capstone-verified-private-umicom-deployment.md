# Chapter 72 — Capstone: rehearse a verified private Umicom Notes deployment

**Bits to Banking · System Administration From Zero · Stage 5 · Umicom Foundation**  
**Audience:** First-time computer users, older learners, new contributors and returning professionals.  
**Practical mode:** Read-only observation by default; any exercise that writes uses a clearly identified private training directory.  
**Implementation policy:** New Umicom executable functionality uses C23 or Assembly. PowerShell and Linux terminal commands here are interactive instructions, not implementation scripts.

## The problem we are solving

**Can you prepare, review and explain a software release without modifying any shared machine settings?**

This capstone combines the entire Stage 5 sequence. You will identify the host, confirm a native toolchain, build a harmless training executable, run automated tests, stage a private copy, inspect its dependencies, run it from a different working directory and produce a short evidence report. No real Umicom OS service is changed.

The update's C23 `BtbDeploymentReview` consumes the previous `BtbMaintenanceReview` model. It holds **claimed** package and configuration digests, staging observations and a source revision. It does not hash real artefacts, query Git, sign packages or operate an installer. Its value lies in teaching failure-closed review: a missing dependency, stale capture or incomplete maintenance state prevents the fictional deployment from being labelled QUALIFIED.

The most important professional habit is separating three statements: **I built it**, **I tested it**, and **I deployed it successfully**. These are different claims. Include the command, environment, source revision and evidence for each; report “not verified” if the observation was not performed.

![Course illustration: Capstone: rehearse a verified private Umicom Notes deployment](../../assets/diagrams/sysadmin-rollback-gates-update42.svg)

## Words you need before you continue

- **Release evidence** — Records showing how a particular version was built and checked.
- **Change approval** — Authorisation to carry out a change under a defined policy.
- **Drift** — An unapproved difference between expected and actual state.
- **Qualification gate** — A stated condition that must be satisfied before declaring a result acceptable.

## Worked Umicom example

A learner completes the build and test but forgets to inspect runtime dependencies. The educational release gate reports BLOCKED rather than passing. The learner then records the missing check, performs a harmless inspection and explains why a new capture must be fresher than the old observation. This is the correct mindset for enterprise software.

## Before touching your computer

Read each command all the way through. Check the directory or filename first. A **command** is something you type in the terminal; the command output is the evidence you interpret. If a step requires a file or application that is not installed, record **not available** and continue with the conceptual part. Do not invent a result and do not try a more powerful command merely to make the exercise appear to pass.

> **Safety boundary:** Perform this only in your own training checkout. If the intended stage directory already contains valuable files, choose a different empty prefix. Do not create production Git commits, change network permissions or deploy Umicom OS from this capstone.

## Windows — PowerShell 7, step by step

Start Windows Terminal and select **PowerShell**, or use **PowerShell 7** directly. Confirm with `$PSVersionTable.PSVersion`. The prompt ending in `>` is where you enter the command; **do not type the prompt itself**. Commands are shown exactly, except for placeholders such as `YOUR_APPROVED_LINUX.iso`, which must be replaced with a real filename before execution.

### 1. Run the complete native learning test suite

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\deployment-rehearsal" -B ".\output\learning-build\deployment-rehearsal" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\deployment-rehearsal" --parallel 2
ctest --test-dir ".\output\learning-build\deployment-rehearsal" --no-tests=error --output-on-failure
```

**Expected result and interpretation:** Record the actual CTest summary. Do not write “all passed” if any test failed or did not run.

### 2. Stage and launch the exercise binary

```powershell
cmake --install ".\output\learning-build\deployment-rehearsal" --prefix "C:\umicom\learning-stage-update42"
& "C:\umicom\learning-stage-update42\bin\btb-deployment-review-demo.exe"
git status --short
```

**Expected result and interpretation:** The stage contains the training executable, its demonstration prints fictional decisions, and Git shows any uncommitted repository changes.


## Linux — terminal, step by step

Open the distribution's Terminal application. The examples assume an ordinary, non-root account. Linux paths use `/` and case-sensitive names on most filesystems; a Windows path beginning `C:\` must not be pasted unchanged into Linux commands.

### 1. Configure, test and stage only in your own directory

```bash
cmake -S labs/native/deployment-rehearsal -B output/learning-build/deployment-rehearsal -G Ninja -DBUILD_TESTING=ON
cmake --build output/learning-build/deployment-rehearsal --parallel 2
ctest --test-dir output/learning-build/deployment-rehearsal --no-tests=error --output-on-failure
cmake --install output/learning-build/deployment-rehearsal --prefix "$HOME/umicom-learning-stage"
```

**Expected result and interpretation:** Do not use sudo. Record the exact test count from your environment.

### 2. Run the staged demonstration and inspect Git

```bash
"$HOME/umicom-learning-stage/bin/btb-deployment-review-demo"
git status --short
```

**Expected result and interpretation:** The demonstration is separate from any actual service deployment.


## Guided practice laboratory

1. Write a preflight table with OS/architecture, source revision, toolchain versions and intended private stage directory.
2. Run the C23 configure/build/test commands in order and record their actual results.
3. Stage only under an approved private prefix and confirm the staged executable launches.
4. Run the negative CTest cases `missing-runtime`, `stale-verification`, `rollback` and `restored`, explaining their different outcomes.
5. Prepare a support note: what was proven, what remained unverified, and whether anyone authorised a real deployment (answer: no).

**Keep evidence:** Note the date, selected environment, commands entered, expected outcomes and actual outcomes. Omit passwords, tokens, private patient/customer details and unnecessary machine identifiers. A missing or failed step belongs in your report; it is not a reason to hide the error.

## Common problems and how to investigate

| Symptom | Safe investigation |
|---|---|
| Test suite reports failure | Do not proceed to staging. Save the first failing test and the associated source revision. |
| Private prefix contains unrelated files | Do not overwrite them. Choose a fresh practice directory and state that choice in the evidence report. |

Never substitute `git reset --hard`, `git clean -fd`, broad permission changes, service shutdown or force-push for diagnosis. Those operations can discard unrelated work.

## Review questions with suggested answers

1. **What does QUALIFIED mean in the C23 lab?**

   *Answer:* Only that fictional supplied evidence passed the teaching policy; it is not production certification.

2. **Why is RESTORED_ONLY distinct from QUALIFIED?**

   *Answer:* The old state may have been recovered after a failed change; the new release did not succeed.

3. **What are the three separate claims?**

   *Answer:* Built, tested and deployed successfully, each with its own evidence.


## How this fits into Umicom

We keep the responsibilities clear. **Umicom Kernel** owns privileged boot and hardware behaviour. **Umicom OS** composes the operating-system environment. **Umicom Framework** owns reusable C23/Assembly services, build, VCS, security and application lifecycle contracts. **Bits2Banking** owns the teaching material and isolated laboratories. A lesson should not be mistaken for proof that a production system is ready.

**Next:** Engineering Chapter 300 — Reproducible C23 staging and installation.
