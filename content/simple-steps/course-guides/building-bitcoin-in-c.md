<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/building-bitcoin-in-c.md

PURPOSE:
Provide practical first steps and a result to check for Building Bitcoin from Scratch Using Assembly and C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Building Bitcoin from Scratch Using Assembly and C

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Draw the lesson’s 80-byte header layout and mark the boundaries of the six fields. [Scope, bytes and compatibility](../../courses/building-bitcoin-in-c/lessons/01-scope-bytes-and-compatibility.html)
2. Use the bounded reader to trace bytes `78 56 34 12` in order. Write the decoded hexadecimal value. [A bounded little-endian reader](../../courses/building-bitcoin-in-c/lessons/02-a-bounded-little-endian-reader.html)
3. Repeat with only three bytes and set the previous result to 99 before the call. [A bounded little-endian reader](../../courses/building-bitcoin-in-c/lessons/02-a-bounded-little-endian-reader.html)

**Check your result.** Four bytes produce `0x12345678`. The short input is refused and the result remains 99.

[Continue in the full course](../../courses/building-bitcoin-in-c/index.html) · [All course guides](index.md)
