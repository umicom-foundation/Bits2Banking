<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-hdl-vhdl.md

PURPOSE:
Give learners an additional practical case for Learning HDL and VHDL.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep a carry outside four bits

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice four-bit unsigned adder receives 1111 and 0001. Its demonstration prints a result of 0000.

1. Write the exact binary sum on paper. Compare the required result width with the signal declared in the adder lesson.
2. In a practice simulation or a trace, extend both operands to five bits before adding and compare the two displayed outputs.

**Check your result.** The four-bit value is 0000. The five-bit sum is 10000, including a carry of 1.

[Step-by-step course guide](../course-guides/learning-hdl-vhdl.md) · [Full course](../../courses/learning-hdl-vhdl/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-hdl-vhdl.md)
