<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/learning-6800-assembly.md

PURPOSE:
Provide practical first steps and a result to check for Learning Motorola 6800 Assembly.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Learning Motorola 6800 Assembly

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Draw a box labelled accumulator A. Trace `LDAA #5` followed by `ADDA #3` and write A’s value after each line. [An eight-bit accumulator](../../lessons/03-native-code/learning-6800-assembly/01-an-eight-bit-accumulator.md)
2. Draw byte locations `$0100` and `$0101`. Write 6 in the first location and 0 in the second. [Addresses and stored values](../../lessons/03-native-code/learning-6800-assembly/02-addresses-and-stored-values.md)
3. Trace `LDAA $0100`, `ADDA #2` and `STAA $0101` on the drawing. [Addresses and stored values](../../lessons/03-native-code/learning-6800-assembly/02-addresses-and-stored-values.md)

**Check your result.** The first trace ends with A at 8. In the second trace `$0100` still holds 6 and `$0101` now holds 8.

[Continue in the full course](../../courses/learning-6800-assembly/index.html) · [All course guides](index.md)
