<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/learning-aarch64-assembly.md

PURPOSE:
Provide practical first steps and a result to check for Learning AArch64 Assembly.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Learning AArch64 Assembly

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Write `0x12345678_ffffffff` in an X0 box. Split the drawing into high and low 32-bit halves. [Trace a write to W0](../../lessons/03-native-code/learning-aarch64-assembly/01-trace-a-register-write.md)
2. Trace the example that adds one to W0. Keep the low 32 bits of the sum and apply the W0 write rule to the high half. [Trace a write to W0](../../lessons/03-native-code/learning-aarch64-assembly/01-trace-a-register-write.md)
3. Compare `0xffffffff` with 1 once as signed values and once as unsigned values. Record the result in two columns. [Compare the same bits as signed and unsigned](../../lessons/03-native-code/learning-aarch64-assembly/03-compare-signed-and-unsigned.md)

**Check your result.** X0 becomes zero after the W0 write. The same bit pattern is less than 1 in the signed comparison and greater than 1 in the unsigned comparison.

[Continue in the full course](../../courses/learning-aarch64-assembly/index.html) · [All course guides](index.md)
