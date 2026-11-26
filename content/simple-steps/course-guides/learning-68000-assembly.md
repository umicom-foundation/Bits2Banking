<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/learning-68000-assembly.md

PURPOSE:
Provide practical first steps and a result to check for Learning Motorola 68000 Assembly.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Learning Motorola 68000 Assembly

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Draw boxes for data registers D0 and D1. Fill them with 5 and 2 using the sample `move.l` instructions. [Registers and a first calculation](../../lessons/03-native-code/learning-68000-assembly/01-registers-and-a-calculation.md)
2. Trace `sub.l %d1, %d0`. Record which box changes and its new value. [Registers and a first calculation](../../lessons/03-native-code/learning-68000-assembly/01-registers-and-a-calculation.md)
3. Open the bounded-loop example. On paper, record D0 once for each pass until the loop stops. [Comparisons and a bounded loop](../../lessons/03-native-code/learning-68000-assembly/03-comparisons-and-loops.md)

**Check your result.** After subtraction D0 holds 3 and D1 still holds 2. The separate loop reaches 3 and stops.

[Continue in the full course](../../courses/learning-68000-assembly/index.html) · [All course guides](index.md)
