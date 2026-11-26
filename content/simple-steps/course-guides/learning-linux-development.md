<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/learning-linux-development.md

PURPOSE:
Provide practical first steps and a result to check for Learning Linux Development.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Learning Linux Development

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Save the lesson's Linux `hello.c` in your own practice folder. Compile it, then run `./hello`. [Your first user-space build](../../courses/learning-linux-development/lessons/01-your-first-user-space-build.html)
2. Run `./hello > output.txt 2> errors.txt`, then immediately save `$?` as shown in the lesson. [Processes, output and exit status](../../courses/learning-linux-development/lessons/02-processes-output-and-exit-status.html)
3. Change the practice source from `return 0;` to `return 3;`. Rebuild and repeat the capture. [Processes, output and exit status](../../courses/learning-linux-development/lessons/02-processes-output-and-exit-status.html)

**Check your result.** The message in `output.txt` stays the same. The reported status changes from 0 to 3.

[Continue in the full course](../../courses/learning-linux-development/index.html) · [All course guides](index.md)
