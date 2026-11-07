<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/10-understand-why-a-process-id-is-not-ownership.md

PURPOSE:
  Present "Understand why a process ID is not ownership" with source-based exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Understand why a process ID is not ownership

A service supervisor starts programs, observes when they finish and sometimes stops them. This lesson explains why remembering a process number is not enough. You will connect the existing process-ownership lesson to the actual supervisor source.

Source to open: `umicomOS/boot/foundation/supervisor.c`.

## Setup recap

Use a text editor, this course and a checkout of the named source. A checkout is a folder containing a repository's files. This is a source-reading and reasoning lab; it needs no running service or account. Choose your own practice folder and keep the original example unchanged. The commands below display source rather than compile or execute it. Replace the example directory with your checkout location. The detailed terminal and editor guide explains how to obtain a checkout, open a terminal and prepare later executable exercises.

A terminal accepts commands. Set-Location (PowerShell) and cd (Bash) choose the folder in which subsequent commands work. Get-Content and sed display text. If a path is missing, locate the repository first instead of creating an empty replacement file.

### PowerShell

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
Get-Content -LiteralPath '..\umicomOS\boot\foundation\supervisor.c'
```

### Bash

```bash
cd /path/to/umicom/Umicom-Bits2Banking
sed -n '1,200p' '../umicomOS/boot/foundation/supervisor.c'
```

## Understand the idea

A process is a running program. Its process ID, or PID, is a number used by the operating system to identify it at a particular time. Numbers can be reused after processes finish. A supervisor therefore needs a lifecycle: start, retain the right to observe the child, collect its completion, and stop treating it as owned. On this POSIX path, SIGCHLD describes child-status notification and wait operations collect completion information. A process group helps manage related ordinary child processes, but it is not a containment mechanism for hostile code.

```text
not started -> owned child -> completion collected
                     |
                 wait failure
                     v
             ownership no longer established
                     |
             do not signal by stale PID
```

## Work through the lab

1. Find the existing source comments about wait ownership and SIGCHLD. Read the admission checks before launch. Record what happens when the surrounding process has configured child completion in a way the supervisor cannot safely own.
2. Draw states named not started, owned child, completion collected and ownership lost. Follow the code paths that leave the owned-child state. Do not assume that an integer PID staying nonzero means ownership remains valid.
3. Find the failed-wait handling and the decision about sending further signals. Explain in your notes why stopping after lost ownership is safer than signalling a number that may now identify another process.
4. Read tests/foundation/test_supervisor_admission.c beside the implementation. Turn one rejection condition into a learner test plan: starting environment, requested action, expected diagnostic and unchanged surrounding policy. Running the plan belongs in a dedicated test environment.

## Expected result

Your state diagram should have no path from lost ownership directly to an unconditional kill of the remembered PID. You should also explain why a supervisor should reject an incompatible surrounding signal policy rather than silently rewriting it.

## If the result differs

If the source layout differs, search for SIGCHLD, wait and ownership. A single platform error code does not prove why ownership was lost. Record the syscall result and lifecycle state separately. Do not experiment by signalling arbitrary PIDs on your workstation.

## Explain it yourself

A program exits and its old PID later belongs to another program. What does a cached PID prove about the new program?

<details>
<summary>Worked explanation</summary>

It proves nothing about ownership of the new program. The supervisor must use its lifecycle and supported operating-system mechanisms to establish whether an action still belongs to the child it started.

</details>

## Use the idea in Umicom

Umicom OS owns the supervisor's platform-specific lifecycle. Framework applications should request supported service operations through the shared contracts rather than duplicating ad hoc process-killing logic. This lesson describes a source contract, not a completed OS installer or desktop login.

[HTML edition](../../../courses/umicom-os-from-scratch/lessons/10-understand-why-a-process-id-is-not-ownership.html)

[Terminal and editor setup guide](../../learning-c/terminal-to-visual-studio.md)

[Previous lesson](09-service-process-ownership.md) · [Course contents](index.md)


[Next: Separate accepted and in-flight work](11-separate-accepted-and-in-flight-work.md)
