# Stage 5 instructor guide — Virtual machines, reproducibility and private staging

**Umicom Foundation · Course owner: Bits2Banking · Update 42**

## Audience and preparation

This course teaches the same foundational system concepts to teenagers, adults and experienced engineers returning for a refresher. Do not assume learners know the difference between a shell window, an operating system, an executable or a file path. Students can perform read-only exercises without special privileges. A younger learner should use a supervised account and never install a guest OS on shared hardware without adult/owner approval.

Before the session, verify whether each machine has PowerShell 7, Git, CMake, Ninja and an approved C23 toolchain. The **absence of QEMU is acceptable** for the initial conceptual lessons. Do not ask participants to download guest images from a random site or run unverified firmware/installer commands during class.

## Recommended session structure

- **10 minutes:** Define the problem and introduce four new terms with a diagram.
- **15 minutes:** Instructor demonstration of only the read-only commands; point out the prompt and explain that the prompt itself is not typed.
- **20 minutes:** Learners repeat on their own workspaces; the instructor checks actual outputs instead of collecting personal machine identifiers.
- **15 minutes:** Troubleshooting: what happens when the tool is absent, path differs or an OS behaves differently?
- **15 minutes:** Practical independent exercise and a short evidence log.
- **5 minutes:** Questions and recap; name the next dependency.

## Learning-specific teaching notes

**Chapters 61–63:** Draw host, guest, emulator, firmware and kernel as separate boxes. A running QEMU process is not evidence of successful guest boot. Treat guest snapshots and backups as different tools.

**Chapters 64–66:** Demonstrate identity, architecture and permissions using commands that do not modify system state. Always state why privilege escalation is not needed for observation.

**Chapters 67–69:** Walk through configure, build, test and stage as separate gates. Have learners inspect an executable in a private prefix; do not stage into Program Files or `/usr/local`.

**Chapters 70–72:** Teach Running versus Ready, incident stages and recovery. Use the supplied fictional Umicom Notes evidence, not an actual production service.

## Common misconceptions

- “I saw a command prompt, therefore I am running PowerShell 7.” — Run `$PSVersionTable.PSVersion` to identify the shell.
- “The emulator opened, therefore the kernel booted.” — Review guest serial/boot evidence separately.
- “The file is 1 GB, therefore its guest disk cannot grow.” — Sparse virtual sizes can be larger.
- “Green CMake output means all tests passed.” — Configure, compile, test and staging must be checked independently.
- “The review says QUALIFIED, therefore we installed successfully.” — It is an offline educational model with supplied fictional evidence.
- “A rollback restored the old version, therefore the upgrade succeeded.” — A recovered baseline is **RESTORED_ONLY**.

## Assessment and safeguarding

Record only a learner's commands, reasoning and pass/fail outcomes. Do not demand screenshots containing private user names, tokens, hardware serials or customer information. Correctly identifying “not verified” should be rewarded. Do not ask students to run destructive Git, package, disk, firewall, permission or service commands merely to reproduce a failure.

The complete C23 implementation is in `labs/native/deployment-rehearsal`. It requires previous Updates 39–41. Prefer a shared classroom starter repository with those prior labs already present. Run the included native CTest suite on the class toolchain, and distinguish its actual results from the reference Linux validation report.
