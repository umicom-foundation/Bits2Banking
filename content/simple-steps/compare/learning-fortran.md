<!--
Umicom Bits2Banking
File: content/simple-steps/compare/learning-fortran.md

PURPOSE:
Give learners an additional practical case for Learning Fortran.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare a default integer and a C interoperability kind

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice project uses a default integer for local totals and declares a C-bound argument with integer(c_int). Both hold the number 8.

1. Label the local arithmetic variable and the imported C argument in the interface lesson. Identify the role expressed by each declaration.
2. Compare a copied declaration that uses the local default kind at the boundary with the explicit c_int declaration.

**Check your result.** Both represent the value 8 in the scratch example. Only the explicit c_int declaration identifies the C int contract directly.

[Step-by-step course guide](../course-guides/learning-fortran.md) · [Full course](../../courses/learning-fortran/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/learning-fortran.md)
