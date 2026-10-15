# System Administration From Zero — Stage 5
## Virtual machines, reproducible builds and safe service deployment

**Umicom Foundation · Update 42 · Chapters 61–72**

This stage assumes only the basic vocabulary introduced in Chapters 1–60. Absolute beginners can enter here after the introductory stages. Each chapter provides a clear problem, definitions, a real-world Umicom scenario, separate interactive Windows PowerShell 7 and Linux terminal commands, expected results, troubleshooting, exercises and answers.

| Chapter | Main question | Practice boundary |
|---|---|---|
| 61 | What is a VM and why do we use it? | Observe architecture and tools only |
| 62 | How do we prepare a disposable guest? | Own directory and verified downloads |
| 63 | What does QEMU actually prove? | Read machine help, no guest start |
| 64 | Which architecture and OS am I using? | Read-only platform inspection |
| 65 | How does a disk image differ from a real disk? | Read-only image metadata |
| 66 | Which identity should run administration tools? | Read-only account/permission checks |
| 67 | How do I select the correct C23 toolchain? | Version and preset inspection |
| 68 | How do I stage a private copy of a program? | Practice-prefix CMake install |
| 69 | Why does an executable fail after relocation? | Observe declared runtime dependencies |
| 70 | Why is a running process not always ready? | Read-only service observation |
| 71 | How do I investigate a failed launch? | Diagnostics, no forced recovery |
| 72 | Can I complete an end-to-end release rehearsal? | Private copy and fictional evidence |

**Suggested schedule:** Twelve guided sessions of 60–90 minutes, with optional deeper exercises for experienced learners. The dedicated practice workbook supplies assignments and marking criteria. The child/young-learner path uses only read-only observations and private directory exercises with adult supervision; deeper service and VM configuration is reserved for approved training machines.

### Teaching conventions

- **Type:** the literal command only, not the PowerShell prompt shown to the left of it.
- **Check:** what should appear and what it actually means.
- **Record:** any error without hiding it, avoiding passwords, account secrets and private data.
- **Stop:** if a step names a file that does not exist, asks for elevated privileges or could overwrite unrelated work.
- **Distinguish:** Windows uses `C:\` style paths and PowerShell; Linux uses `/` style paths and its terminal shell.

This stage does **not** add a new production deployment subsystem. The new `labs/native/deployment-rehearsal` exercise composes the prior C23 administration, readiness and maintenance models, and the course calls existing Umicom Framework development facilities where appropriate.
