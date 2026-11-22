<!--
Umicom Bits2Banking
File: content/lessons/04-web/go-statement-tools/index.md

PURPOSE:
Teach Go Statement Tools through original worked exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

<picture>
  <source srcset="../../../assets/branding/umicom-wordmark-on-dark.svg" media="(prefers-color-scheme: dark)">
  <img src="../../../assets/branding/umicom-wordmark.svg" width="220" alt="Umicom">
</picture>

# Go Statement Tools

Read a local training statement with Go’s standard library, reject malformed data, then print deterministic account totals.

## Before you start

You know how to create a source file and use a terminal. Use a Go installation when running examples. The paper trace works without a compiler.

Use only the supplied training figures in these activities. The paper exercises work without an account.

## Lessons

1. [Read and validate CSV rows](01-read-and-validate-csv-rows.md). Parse a fixed CSV statement, convert amounts to whole cents and report the first invalid record.
2. [Print deterministic posted totals](02-print-deterministic-posted-totals.md). Group posted movements by account, retain zero entries and print account names in a stable order.

Parse every row before presenting results, then sort account names so reports are comparable.

[Open the browser course](../../../courses/go-statement-tools/index.html)

## Continue learning

- [SQL Statement Reconciliation](../../../courses/sql-statement-reconciliation/index.html)
- [Introduction to Programming](../../../courses/introduction-to-programming/index.html)

## Further reading

- [Tech Sustainify course catalogue](https://techsustainify.com/)
- [W3Schools Go tutorial](https://www.w3schools.com/go/index.php)
- [Go encoding/csv package](https://pkg.go.dev/encoding/csv)
