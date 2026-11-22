<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/programming-across-languages/07-plan-a-first-umicom-change.md

PURPOSE:
Write a small enhancement request with one example someone else can check.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

<picture>
  <source srcset="../../../assets/branding/umicom-wordmark-on-dark.svg" media="(prefers-color-scheme: dark)">
  <img src="../../../assets/branding/umicom-wordmark.svg" width="220" alt="Umicom">
</picture>

# Plan a first Umicom change

[Course contents](index.md) · [Previous · Give a task a name and a result](06-give-a-task-a-name-and-a-result.md) · [Browser edition](../../../courses/programming-across-languages/lessons/07-plan-a-first-umicom-change.html)

Write a small enhancement request with one example someone else can check.

## Choose a small task

Use synthetic receipts to design a line count in a local Studio project. Start with three numbered rows. Decide where the count belongs, how the learner sees it and what the result should be for an empty file.

```text
GIVEN a sample file with 3 lines of receipts
WHEN the learner asks for the number of receipt rows
THEN show 3
GIVEN an empty sample file
WHEN the learner asks for the number of receipt rows
THEN show 0
```

## Connect the next course

- Studio IDE practice: place the sample and the calculation in a small learning project and record the build command.
- Framework practice: describe the input and the expected answer for a pure helper. Keep drawing and file dialogs outside that helper.
- Automated Testing practice: compare the displayed count with the number in the fixture and record actual and expected results.
- Bank practice: use a synthetic deposit list and reconcile the count with the rows used for the summary.

## Check your plan

Ask another learner to work out both expected outputs using only the sample and the task description. If they get different answers, agree whether blank lines count before you write code.

## Continue in another course

- [Computing from the Beginning](../../../courses/computing-from-the-beginning/index.html)
- [C23 keyword reference](../../../courses/c23-keyword-reference/index.html)
- [Python keyword reference](../../../courses/python-keyword-reference/index.html)
- [Go keyword reference](../../../courses/go-keyword-reference/index.html)
- [Go statement tools](../../../courses/go-statement-tools/index.html)
- [Umicom C and C23 statement calculations](../../../courses/native-statement-calculations/index.html)

[Course contents](index.md) · [Previous · Give a task a name and a result](06-give-a-task-a-name-and-a-result.md) · [Browser edition](../../../courses/programming-across-languages/lessons/07-plan-a-first-umicom-change.html)
