# System Administration From Zero — Stage 4: Managed Services and Recovery

**Bits to Banking · Umicom Foundation · Chapters 49–60 · UK English**

Stage 4 builds on the 48 previously published chapters. You do not need to be an expert to follow it: start with the service and identity concepts, then build confidence with scheduling, configuration and administration evidence, and finish with a C23 simulation that cannot change a real computer.

## Study route

| Chapter | Reading and practical outcome |
|---|---|
| [49. Map managed services and their dependencies](49-map-managed-services-and-their-dependencies.md) | 65–85 minutes; read-only inspection, guided exercises and Umicom Notes examples |
| [50. Inspect service identities and account boundaries](50-inspect-service-identities-and-account-boundaries.md) | 60–80 minutes; read-only inspection, guided exercises and Umicom Notes examples |
| [51. Read systemd units and understand service startup order](51-read-systemd-units-and-service-startup-order.md) | 70–90 minutes; read-only inspection, guided exercises and Umicom Notes examples |
| [52. Inspect scheduled tasks, cron and systemd timers](52-inspect-scheduled-tasks-cron-and-systemd-timers.md) | 60–80 minutes; read-only inspection, guided exercises and Umicom Notes examples |
| [53. Understand configuration, environments and secret boundaries](53-understand-configuration-environments-and-secret-boundaries.md) | 70–90 minutes; read-only inspection, guided exercises and Umicom Notes examples |
| [54. Plan software upgrades as controlled changes](54-plan-software-upgrades-as-controlled-changes.md) | 65–85 minutes; read-only inspection, guided exercises and Umicom Notes examples |
| [55. Monitor service health using baselines and sensible alerts](55-monitor-service-health-with-baselines-and-alerts.md) | 65–85 minutes; read-only inspection, guided exercises and Umicom Notes examples |
| [56. Check local listeners and understand network exposure](56-check-local-listeners-and-network-exposure.md) | 70–90 minutes; read-only inspection, guided exercises and Umicom Notes examples |
| [57. Design backup retention and recovery evidence](57-design-backup-retention-and-recovery-evidence.md) | 65–85 minutes; read-only inspection, guided exercises and Umicom Notes examples |
| [58. Rehearse restoration and document rollback](58-rehearse-restoration-and-document-rollback.md) | 70–90 minutes; read-only inspection, guided exercises and Umicom Notes examples |
| [59. Triage incidents and communicate with evidence](59-triage-incidents-and-communicate-with-evidence.md) | 70–90 minutes; read-only inspection, guided exercises and Umicom Notes examples |
| [60. Capstone: plan, review and recover a fictional Umicom Notes change](60-capstone-plan-review-and-recover-umicom-notes.md) | 95–120 minutes; read-only inspection, guided exercises and Umicom Notes examples |

## Recommended learning method

1. Read the new words and mental model before entering any command.
2. Keep the command line and result visible together. Do not type a `PS C:\>` or `$` prompt.
3. State whether the command observes, writes inside your practice folder, or would require administrator approval.
4. Record what happened on **your** machine, including unexpected results and commands that could not be run.
5. Complete the exercises and explain one situation in which the command would not be sufficient proof.
6. Use the [Stage 4 workbook](stage-4-workbook.md) and the C23 `maintenance-review` laboratory as your practical assessment.

## Safety and source rules

Windows examples are interactive PowerShell 7 commands; Linux examples use a terminal. No PowerShell or Python implementation scripts are introduced. Do not change production accounts, scheduled tasks, firewall rules, systemd units, package versions or real repositories merely to reproduce a classroom screenshot. Reusable software capability belongs in Umicom Framework and is not duplicated here.

## Source and prerequisite evidence

The previous course chapters and the originally supplied new-project beginner guide are retained in earlier updates. This batch adds files only. The maintenance-review lab links Update 40, which links Update 39, so a valid checkout must include both prerequisites.

**Next:** [Stage 4 instructor guide](stage-4-instructor-guide.md) · [Command reference](stage-4-safe-command-reference.md) · [Glossary](stage-4-glossary.md).
