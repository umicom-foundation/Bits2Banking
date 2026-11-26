<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/learning-x86-assembly.md

PURPOSE:
Provide practical first steps and a result to check for Learning x86 Assembly.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Learning x86 Assembly

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Open `add_x86_64.S`. Write two rows for the Windows and System V argument registers. [A function called from C](../../courses/learning-x86-assembly/lessons/02-a-function-called-from-c.html)
2. Place 10 and 2 in the two argument registers for each platform. Trace `movl` and `addl` into `EAX`. [A function called from C](../../courses/learning-x86-assembly/lessons/02-a-function-called-from-c.html)
3. Find the function declaration in the example. Write a C-side check for the result using the declared argument types. [A function called from C](../../courses/learning-x86-assembly/lessons/02-a-function-called-from-c.html)

**Check your result.** Both platform traces end with 12 in `EAX`, using their own calling conventions.

[Continue in the full course](../../courses/learning-x86-assembly/index.html) · [All course guides](index.md)
