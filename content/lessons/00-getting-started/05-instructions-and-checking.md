# Give instructions and check what happens

Use order, a choice and repetition to describe a task, then test an expectation.

**Before you begin:** read [What the computer keeps while it works](04-memory-storage-and-information.md), or use it for a refresher.

## Order changes the result

An algorithm is a sequence of steps for solving a task. A program expresses instructions in a form a computer can carry out. We can practise algorithms on paper before learning a programming language, which is a language with rules for writing programs.

Consider these steps: put a card on the table, write A on it, then put it in a folder. Reversing the last two steps makes writing harder. A precise order matters. So do starting conditions, called preconditions: if there is no card available, the instructions need to say what to do.

## A choice is a question with consequences

A condition is a question a program evaluates to decide what to do. In a simple example it can be true or false. The rule 'if the card is blank, write A; otherwise leave it unchanged' gives two paths. Otherwise means the path used when the condition is false.

Walk through both paths. For a blank card, the condition is true and writing happens. For a card already marked B, the condition is false and B stays. The word if by itself is not enough: we need to know the question and the action that follows its answer.

## Repetition needs a stopping point

A loop repeats steps. 'For each of these three cards, write its position number' has a clear limit. 'Keep writing forever' does not finish. A useful task often needs a stopping condition, such as having processed every available card.

A variable is a named place for a value that may change during a task. Let count start at 0. After handling one card, increase count by 1. With three cards, count should finish at 3. A name helps us refer to the changing value. It does not make the value correct automatically.

## A test compares expectation with observation

A test sets up an example, performs an action and checks an expected result. For our card task, the expectation is three numbered cards and count equal to 3. Try zero cards too. That is a boundary case: an example at the edge of the allowed range. If there are no cards, the task should finish without trying to mark a card that does not exist.

A defect is a mistake in software or its design that can cause wrong behaviour. A failing test tells us an expectation was not met; it does not by itself identify the cause. Perhaps the instructions, the input, the test or our understanding is wrong. Keep the actual result so another person can investigate.

## Try it step by step

1. Write instructions for numbering a pile of cards starting at 1.
2. Trace the instructions for three cards, one card and no cards. Trace means follow each step and record its effect.
3. For each case, predict the final count before performing the steps.
4. Deliberately skip an increase of count, compare results, and explain what the mismatch tells you.

## Check your understanding

If one example works, does that prove the instructions handle every possible input?

**Explanation:** No. It proves only what that example actually checked. More carefully chosen examples can uncover problems, but we should state the limits of the checks.

## Before you continue

Continue when you can state an expected result before trying a task and describe a mismatch without guessing its cause.

[Course contents](index.md) · [Words explained](../../courses/learning-computer-architecture/glossary.html) · [Connected learning routes](../../start/systems-learning.md)

**Previous:** [What the computer keeps while it works](04-memory-storage-and-information.md).

**Next:** [Read a command before running it](06-commands-without-mystery.md).

Sammy Hegab · Umicom Foundation · MIT. Original learning material.
