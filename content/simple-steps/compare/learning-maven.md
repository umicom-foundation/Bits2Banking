<!--
Umicom Bits2Banking
File: content/simple-steps/compare/learning-maven.md

PURPOSE:
Give learners an additional practical case for Learning Maven.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Separate direct dependencies from transitive dependencies

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A fictional POM explicitly declares report-parser. The fixture metadata for report-parser lists text-reader as a compile dependency.

1. Draw each coordinate as a node and trace both arrows used by the dependencies lesson.
2. Read only the POM declaration first, then read the full dependency graph. Record which file names the added library.

**Check your result.** report-parser is directly declared by the project. text-reader appears as a transitive node supplied by report-parser.

[Step-by-step course guide](../course-guides/learning-maven.md) · [Full course](../../courses/learning-maven/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/learning-maven.md)
