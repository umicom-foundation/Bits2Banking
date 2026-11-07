<!--
Umicom Bits2Banking
File: content/lessons/13-ai-research/experiment-observation-lab.md

PURPOSE:
  Present "Lab: turn a performance claim into an experiment" with source-based exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Lab: turn a performance claim into an experiment

A faster-looking demonstration is a starting observation, not a finished research result. This lesson uses a real Umicom inference test to show how to write a small research question, choose evidence and separate correctness from performance.

Source to open: `Umicom-Applications/framework/tests/ai_training/test_training_inference_checkpoint.c`.

## Setup recap

Use a text editor, this course and a checkout of the named source. A checkout is a folder containing a repository's files. This is a source-reading and reasoning lab; it needs no running service or account. Choose your own practice folder and keep the original example unchanged. The commands below display source rather than compile or execute it. Replace the example directory with your checkout location. The detailed terminal and editor guide explains how to obtain a checkout, open a terminal and prepare later executable exercises.

A terminal accepts commands. Set-Location (PowerShell) and cd (Bash) choose the folder in which subsequent commands work. Get-Content and sed display text. If a path is missing, locate the repository first instead of creating an empty replacement file.

### PowerShell

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
Get-Content -LiteralPath '..\Umicom-Applications\framework\tests\ai_training\test_training_inference_checkpoint.c'
```

### Bash

```bash
cd /path/to/umicom/Umicom-Bits2Banking
sed -n '1,200p' '../Umicom-Applications/framework/tests/ai_training/test_training_inference_checkpoint.c'
```

## Understand the idea

A research question states what you want to find out. A hypothesis is a proposed answer you can test. A controlled comparison changes one intended factor while recording other factors that might influence the result. For inference, the model, input tokens, configuration, compiler, hardware and background work can matter. Correctness asks whether the results meet the contract. Performance asks how much time or other resource the work consumes. The source deliberately compares deterministic counts and state while leaving CPU-time values as measurements rather than equality assertions.

```text
Question -> fixed workload -> correctness checks -> repeated observations
                                                       |
                                    report variation and limitations
```

## Work through the lab

1. Write the question: does this profiling operation preserve the checkpoint while reporting the same structural work after restoration? Identify which assertions in the existing test answer it.
2. Write a separate speed question about a reference path and an optimised path. Define the workload first: same checkpoint, input sequence, output requirements and machine. A smaller workload must not be presented as an algorithm improvement.
3. Design an observation sheet with source revision, compiler options, machine, workload, warm-up policy, individual timings and correctness result. Retain every planned run rather than selecting only the fastest outcome.
4. Explain how you would investigate an unusual slow run. Record it and its environment; repeat under the same declared procedure. An exclusion requires a reason recorded before reporting an aggregate, not merely an inconvenient result.

## Expected result

You should finish with two clearly separated claims: one about preserved behaviour and one about measured performance. A successful equality assertion cannot establish a speed improvement; a fast timing cannot establish correct output.

## If the result differs

If the comparison changes several things at once, describe it as a whole-system comparison instead of attributing the difference to one cause. If a test fails, retain that failure beside timing evidence and investigate it before calling the implementation equivalent.

## Explain it yourself

One implementation is faster because it processes half the tokens. Does that answer a question about faster processing of the same workload?

<details>
<summary>Worked explanation</summary>

No. The workload changed. Either restore equal work or explicitly ask a different question about the reduced workload and its quality trade-off. A useful result states exactly what was compared.

</details>

## Use the idea in Umicom

Record inputs, expected outputs and refusal cases before extending the example. Reusable production behaviour belongs in Umicom Framework; applications translate user actions and show the service result. A traced example explains a contract. It does not establish that every application using a similar idea has been integrated or tested.

[HTML edition](../../courses/ai-research/lessons/experiment-observation-lab.html)

[Terminal and editor setup guide](../learning-c/terminal-to-visual-studio.md)

[Previous lesson](056-measure-governance-value-before-introducing-tokens.md) · [Course contents](index.md)
