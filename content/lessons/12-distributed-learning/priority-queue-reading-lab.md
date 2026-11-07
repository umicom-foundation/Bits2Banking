<!--
Umicom Bits2Banking
File: content/lessons/12-distributed-learning/priority-queue-reading-lab.md

PURPOSE:
  Present "Lab: trace a stable job queue" with source-based exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Lab: trace a stable job queue

Distributed work begins with deciding which task is considered next. This lesson traces a small existing Framework queue used for financial jobs, then identifies what additional contracts a learning-work scheduler would need.

Source to open: `Umicom-Applications/framework/src/finance/enterprise/distributed_job_queue.c`.

## Setup recap

Use a text editor, this course and a checkout of the named source. A checkout is a folder containing a repository's files. This is a source-reading and reasoning lab; it needs no running service or account. Choose your own practice folder and keep the original example unchanged. The commands below display source rather than compile or execute it. Replace the example directory with your checkout location. The detailed terminal and editor guide explains how to obtain a checkout, open a terminal and prepare later executable exercises.

A terminal accepts commands. Set-Location (PowerShell) and cd (Bash) choose the folder in which subsequent commands work. Get-Content and sed display text. If a path is missing, locate the repository first instead of creating an empty replacement file.

### PowerShell

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
Get-Content -LiteralPath '..\Umicom-Applications\framework\src\finance\enterprise\distributed_job_queue.c'
```

### Bash

```bash
cd /path/to/umicom/Umicom-Bits2Banking
sed -n '1,200p' '../Umicom-Applications/framework/src/finance/enterprise/distributed_job_queue.c'
```

## Understand the idea

A queue stores work until a consumer asks for an item. A priority queue chooses by a priority value instead of simply taking the oldest entry. Stable ordering means that items with equal priority retain their relative insertion order. This implementation stores both the job and an insertion number. Pop scans for the highest priority and uses the earlier insertion number for a tie, then shifts the remaining entries. It is a bounded in-memory helper. Its source does not establish a durable network scheduler, worker trust or validation of learning results.

```text
Insertion: A(priority 2, #1), B(priority 5, #2), C(priority 5, #3)
Pop order: B -> C -> A -> NOT_FOUND
Tie rule: equal priority chooses the earlier insertion number.
```

## Work through the lab

1. Read init and note the empty count and first insertion number. Create three paper jobs: A with priority 2, B with priority 5, C with priority 5. Push them in that order and record their insertion numbers.
2. Follow pop's best variable through the comparison loop. First B outranks A. C has the same priority as B, so compare insertion numbers. Record which job is returned and which entries shift.
3. Repeat until the queue is empty. Then follow one more pop and record UMI_STATUS_NOT_FOUND. For push at capacity, locate the check before the copy and count increment.
4. Write a separate design list for distributing learning work: task identity, required memory, worker capability, lease expiry, retry policy, result verification and durable records. Mark every item as a proposed scheduler requirement unless a separately inspected implementation provides it.

## Expected result

Your trace returns B, C and A. It demonstrates priority and tie handling for this bounded example. It does not establish fairness under an endless stream of higher-priority jobs, behaviour after insertion-counter exhaustion, or correctness of results received from another machine.

## If the result differs

If C is selected before B in your trace, reread the less-than comparison on insertion numbers. If your design equates priority with trust, separate scheduling urgency from independent verification of a result. A job selected first is not automatically a valid result.

## Explain it yourself

What could happen to A if new priority-5 jobs keep arriving before each pop?

<details>
<summary>Worked explanation</summary>

A may wait indefinitely. Stable ordering only orders equal-priority jobs; it does not guarantee service for a lower-priority class. A production scheduler needs an explicit fairness policy if that guarantee is required.

</details>

## Use the idea in Umicom

The inspected queue is a shared Framework component, not a new learning-network implementation. Reuse it only after checking capacity, concurrency and lifetime requirements. Worker admission and result validation need their own reviewed contracts.

[HTML edition](../../courses/distributed-learning/lessons/priority-queue-reading-lab.html)

[Terminal and editor setup guide](../learning-c/terminal-to-visual-studio.md)

[Previous lesson](084-design-a-reproducible-three-worker-experiment.md) · [Course contents](index.md)
