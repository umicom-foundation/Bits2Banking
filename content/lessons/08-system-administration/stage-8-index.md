# Stage 8 — Operational resilience and safe recurring administration

**Bits to Banking · System Administration From Zero · Chapters 97–108**  
**Umicom Foundation · Sammy Hegab · UK English**

Stage 8 follows the first 96 chapters without assuming the reader already works as an administrator. We introduce the language of routine checks, alert ownership, capacity planning, backup objectives and recovery. Windows PowerShell 7 and Linux terminal instructions are shown separately. The purpose is to produce **explainable evidence**, not to teach people to change production systems without permission.

## Learning order

| Chapter | Topic | Practice result |
|---|---|---|
| [97](97-recurring-maintenance-and-check-cadence.md) | Daily, weekly and monthly maintenance | Three-row schedule with owners and evidence |
| [98](98-windows-task-scheduler-observation.md) | Windows scheduled-task observation | Read-only task inventory |
| [99](99-linux-cron-and-systemd-timers.md) | Linux cron/systemd timer observation | Compare timer vs actual service outcome |
| [100](100-from-metrics-to-alerts.md) | Metrics, thresholds and alerts | An actionable fictional alert |
| [101](101-capacity-planning-with-trends.md) | Capacity and trends | Evidence table with assumptions |
| [102](102-alerts-oncall-and-incident-communication.md) | Ownership and incidents | Six-line handover |
| [103](103-backup-rotation-rpo-and-rto.md) | Backup generations, RPO and RTO | Checksum and worked recovery arithmetic |
| [104](104-disaster-recovery-runbooks-and-drills.md) | Isolated recovery drill | Practice restore without overwriting originals |
| [105](105-maintenance-windows-timing-and-approvals.md) | Change windows and rollback | Fictional go/no-go review |
| [106](106-multi-machine-inventory-and-time-consistency.md) | Host inventories and clock skew | Three-host dependency diagram |
| [107](107-least-privilege-for-recurring-operations.md) | Task identity and least privilege | Training permissions matrix |
| [108](108-capstone-seven-day-operations-plan.md) | Complete seven-day operating plan | Reviewable dossier and optional C23 tests |

## For absolute beginners

A **command** is a text instruction. A **shell** is the program that reads commands. **Windows Terminal** is an application that can contain PowerShell tabs. **PowerShell 7**, started with `pwsh`, is the shell taught in Windows examples. **Windows PowerShell** is an older shell, commonly version 5.1. A Linux terminal normally starts a shell such as Bash. The text before your cursor (for example `PS C:\>` or `$`) is the **prompt**; never type the prompt as part of a command.

When an exercise uses a practice directory, keep it inside your own home directory. Do not turn off a firewall, create scheduled jobs, change service accounts, edit `/etc` or `C:\Windows`, or remove data. Every command is chosen to be read-only unless the exercise explicitly creates a harmless **learner-owned** practice file.

## One consistent teaching method

1. **Understand the goal:** describe what observation will answer the question.
2. **Understand the command:** identify the program, arguments and any output formatting.
3. **Run safely:** check the shell and directory, then type one line at a time.
4. **Read the result:** numbers and names vary by computer; do not invent expected host values.
5. **Explain limitations:** a running process is not necessarily a working service.
6. **Keep evidence:** time, host role, source, observation, next owner and permission to proceed.

## Additional resources

- [Stage 8 glossary](stage-8-glossary.md)
- [Practical workbook and suggested answers](stage-8-workbook.md)
- [Instructor guide](stage-8-instructor-guide.md)
- [Safe PowerShell and Linux reference](stage-8-safe-command-reference.md)
- [Blank administration runbook template](stage-8-operational-runbook-template.md)
- [Previous Stage 7 security material](stage-7-index.md)
- [Native C23 operations laboratory](../../labs/index.md) (also see `labs/native/operational-resilience/README.md` in the repository)

**Source-preservation rule:** This stage adds lessons and small educational examples. It does not replace earlier chapters, original books, the *Umicom New Project Beginner Guide*, or Umicom Framework implementations. Reusable runtime functionality belongs in Framework; no Python or PowerShell implementation scripts are delivered.
