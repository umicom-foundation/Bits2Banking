<!--
Umicom Bits2Banking
File: content/lessons/04-web/oracle-database-c23-ledger/03-keep-optional-values-in-a-report.md

PURPOSE:
Make zero, absence and refusal observable across a native and a D caller.

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

# Keep optional values distinct in a financial report

[Course contents](index.md) · [Previous · Follow a named OCI bind and a result indicator](02-follow-a-named-bind-and-indicator.md) · [Browser edition](../../../courses/oracle-database-c23-ledger/lessons/03-keep-optional-values-in-a-report.html)

Make zero, absence and refusal observable across a native and a D caller.

## Rehearse a narrow typed boundary

```d
struct OptionalAmount {
    bool present;
    long cents;
}
auto zero = OptionalAmount(true, 0);
auto absent = OptionalAmount(false, 0);
```

D long is a signed 64-bit type. The second field is meaningful only when present is true. The two constructors model the native states. For a real D-to-C call, use a separately qualified C ABI mapping for layout and boolean values.

The previous lab sets an amount to −850 then encounters a rejected indicator. It preserves the valid amount and reports a refused decode. A UI can attach an error status to the last complete figure instead of presenting a replacement.

## Apply this to Umicom TMS

One screen can show zero as 0.00, missing as an em dash with an accessible label, and a rejected fetch as an error with the prior evidence. Qualify each case through Umicom Automated Testing without needing real ledger data.

- [Read the complete native lab source](../../../labs/native/service-practice/oracle-ledger/main.c)
- [Compare typed documents](../../../courses/mongodb-c23-documents/index.html)

## Continue in another course

- [Applied native courses](../../../start/applied-native-courses.md)
- [MySQL Ledger Practice in C23](../../../courses/mysql-c23-ledger/index.html)
- [Bookkeeping from Your First Entry](../../../courses/bookkeeping-from-first-entry/index.html)

[Course contents](index.md) · [Previous · Follow a named OCI bind and a result indicator](02-follow-a-named-bind-and-indicator.md) · [Browser edition](../../../courses/oracle-database-c23-ledger/lessons/03-keep-optional-values-in-a-report.html)
