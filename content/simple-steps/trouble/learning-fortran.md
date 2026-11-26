<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-fortran.md

PURPOSE:
Give learners an additional practical case for Learning Fortran.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Match a scalar argument to C

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice binding declares the input of a C function as a Fortran reference. The C declaration takes a plain int value.

1. Place the C declaration and the Fortran interface beside each other. Underline the scalar input and mark pointer outputs separately.
2. Change the scalar input in your practice interface to integer(c_int), value. Leave the output declarations as required by the C contract.

**Check your result.** The revised interface passes the sample input 4 as a C integer value. The original interface describes an address for that position.

[Step-by-step course guide](../course-guides/learning-fortran.md) · [Full course](../../courses/learning-fortran/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-fortran.md)
