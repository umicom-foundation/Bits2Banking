<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/umicom-c-keyword-reference/04-call-the-checked-input-profile.md

PURPOSE:
Distinguish the special entry name umicom_run from a reserved word.

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

# Read the checked input entry and its limits

[Course contents](index.md) · [Previous · Repeat, skip and stop a counted loop](03-repeat-skip-and-stop.md) · [Browser edition](../../../courses/umicom-c-keyword-reference/lessons/04-call-the-checked-input-profile.html)

Distinguish the special entry name umicom_run from a reserved word.

## Read a one-input function

```c
int umicom_run(int adjustment)
{
    return 250 + adjustment;
}
```

This input-profile entry is named `umicom_run`. The spelling names the accepted entry for the input path. It arrives through the identifier path and is checked as the entry name. An argument is the value a caller supplies, here an adjustment in cents.

## Try two inputs

Save the example as `checked-input.uc`. In the same folder, run `umicom-c compile-input checked-input.uc checked-input.umcb` using a fresh output filename. Then use `umicom-c exec-input checked-input.umcb 25`. The result should be 275. Try an input of 0 and check 250.

The checked integer profile admits a bounded set of statements and expressions. Keep full C23 library calls, general functions, and floating-point examples in their own courses. Input syntax, type range, and the result range each have their own checks.

## Connect the exercise

- [Run the statement calculation on Umicom WebServer](../../../umicom/native-statement-web-lab.md)

Follow the WebServer lab only in a training workspace. Its exercise and this smaller example use different posted totals. Compare the common entry and adjustment rule on paper first.

## Continue in another course

- [Programming across languages](../../../courses/programming-across-languages/index.html)
- [C23 keyword reference](../../../courses/c23-keyword-reference/index.html)
- [Native statement calculations](../../../courses/native-statement-calculations/index.html)
- [Building a compiler in C](../../../courses/building-a-compiler-in-c/index.html)
- [Published Umicom C language guide](https://github.com/umicom-foundation/umicom-c/blob/main/docs/language.md)

[Course contents](index.md) · [Previous · Repeat, skip and stop a counted loop](03-repeat-skip-and-stop.md) · [Browser edition](../../../courses/umicom-c-keyword-reference/lessons/04-call-the-checked-input-profile.html)
