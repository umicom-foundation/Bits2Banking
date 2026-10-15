# Stage 5 learner workbook — Virtualisation and deployment evidence

**Umicom Foundation · Update 42 · Suitable for supervised beginners and adult learners**

## Section A — Foundation checks (20 marks)

1. (2) Draw host and guest. Identify which contains your own files by default.
2. (2) Explain why an ISO is not the same as a mutable guest disk.
3. (2) State why `qemu-system-riscv64 -machine help` is a safer first command than an unreviewed `-kernel` command.
4. (3) Write Windows and Linux commands to read processor architecture and OS release.
5. (3) Explain virtual disk size versus physical host disk usage.
6. (3) Name three conditions under which VM isolation may be weakened.
7. (5) Describe the difference between a guest snapshot, a copied file and a verified backup restore.

## Section B — Safe system observation (20 marks)

1. (5) Record a sanitised, read-only platform baseline: OS family, release, architecture, shell version and compiler version. Provide the commands you used.
2. (5) Read permissions of a folder you own. Explain why an application usually should not run as administrator.
3. (5) Compare one process observation and one service observation. Why are neither sufficient to prove readiness?
4. (5) Given “application launches from terminal, but not from icon”, propose a read-only investigation plan with at least three steps.

## Section C — Native training laboratory (30 marks)

1. (5) Configure Update 42 with the chosen C23 compiler and a separate build directory.
2. (5) Run the full CTest suite; write the actual number of passed, failed and not-run cases.
3. (5) Check that `C:\umicom\learning-stage-update42` or `$HOME/umicom-learning-stage` is an appropriate private destination before staging.
4. (5) Run the staged demonstration; report exactly what it prints and what it **does not** prove.
5. (5) Run `missing-runtime`, `stale-verification`, `rollback` and `restored`. Describe the difference between the four outcomes.
6. (5) Locate the imported existing maintenance model in the source and explain how duplicate implementation was avoided.

## Section D — Incident and recovery case study (30 marks)

A fictional Umicom Notes update is built and staged. After startup it can no longer read the document store. An independent recovery check confirms the previous version works again.

1. (5) Which layer failed: build, stage, loader or service dependency? Explain your evidence.
2. (5) Why does a green `git status` not close the incident?
3. (5) What must be recorded before trying another candidate release?
4. (5) Should the newer release be labelled QUALIFIED, BLOCKED, ROLLBACK_REQUIRED or RESTORED_ONLY after independent restoration? Explain.
5. (5) Which Umicom components own real package integrity, build, process supervision and release controls?
6. (5) Prepare a clear five-line status report for the instructor, distinguishing observed evidence from assumptions.

## Suggested answers (instructor use)

**Section A:** The host contains the actual user environment; the guest has separately presented virtual hardware. ISO and guest disks have different roles; help commands enumerate options without booting. Windows: `Get-ComputerInfo ...`; Linux: `uname -m` and `/etc/os-release`. VM sharing, USB passthrough and permissive networking weaken isolation. Snapshots do not replace off-VM tested backups.

**Section B:** Use commands demonstrated in Chapters 64, 66 and 70. Read-only observations do not change accounts or services. A service can be running without its data store. Desktop startup may differ from a terminal's PATH or working directory.

**Section C:** Cite your **actual** CTest count. On a fully merged Updates 39–42 lab, the reference Linux build registered 79 tests. Do not copy that number if your host reports something different. The demonstration uses fictional values; it does not hash real files or install an OS service.

**Section D:** The dependency/readiness stage failed, not necessarily compilation. A clean Git working tree proves no pending local changes, not operational success. Record revision, package, diagnosis, evidence and the approved next step. After independent restoration the status is **RESTORED_ONLY**, not successful deployment. Production reuse belongs to Umicom Framework's existing VCS, build, packaging, security, logging and lifecycle facilities.

**Assessment standard:** A learner earns full credit for honest “not installed”, “not run” or “cannot verify” statements when supported by observation. Fabricated evidence and dangerous operations invalidate the affected practical task.
