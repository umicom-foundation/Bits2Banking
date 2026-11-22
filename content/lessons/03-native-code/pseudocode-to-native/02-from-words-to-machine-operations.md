![Umicom](../../../assets/branding/umicom-wordmark.svg)

# 2. Trace a rule from words to machine operations

When you run the [width example](01-one-rule-five-forms.md), the source file passes through several steps. Investigate each step by changing one line and checking where the result changes.

| Step | What happens | What you can inspect |
| --- | --- | --- |
| Read words and signs | A scanner identifies names, numbers, operators and language words such as `LET`. | Write `LET width = 6;` on paper and underline each separate part. |
| Check the structure | A parser checks the words and signs for a valid declaration, expression, branch or return. | Remove `THEN` and find the reported source position. |
| Prepare execution | Validated source is lowered into checked instructions in memory, with source spans attached. | Use `--step` to compare the reported span with the original file. |
| Execute | The shared Umicom C engine evaluates the condition, follows the reached branch and checks integer operations. | Set `width` to 5 and compare its steps with `width` set to 6. |

This profile combines C-like arithmetic with BASIC-style words and explicit blocks. D can consume native C services through `extern(C)` when both sides agree on types and calling convention. Assembly can implement a narrow native operation when its registers, memory layout and result match the C contract. The language's rules should stay the same across either boundary. [D specification on interfacing to C](https://dlang.org/spec/interfaceToC.html)

## Try errors on purpose

1. Make a copy of the example. Remove `THEN` from the copy. The parser should decline the complete program before stepping begins. Restore the word.
2. In the `RETURN` line of that copy, replace `width * scale` with `width / (scale - scale)`. The structure remains valid. The attempt to divide by zero should report an error at the operation. Restore the original line and verify the result is again 42.
3. Describe a width bound in plain words before you write it in any language. For the [graphics library](../graphics-from-scratch/index.md), a pixel coordinate is inside a row when it is at least zero and smaller than the width. For a ledger, an amount can pass its numeric check and still need a separate validity decision.

The runnable profile teaches checked integer control flow. Broader language design also needs written type rules, function boundaries, memory ownership and a test for each promised failure result. Preserve the readable rule as a test case before changing the compiler or adding an Assembly routine.

[Previous lesson: One rule in five forms](01-one-rule-five-forms.md) · [Course outline](index.md) · [Build a graphics library](../graphics-from-scratch/index.md) · [Umicom icon](../../../assets/branding/umicom-icon.svg)
