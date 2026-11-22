<!--
Umicom Bits2Banking
File: content/lessons/04-web/mongodb-c23-documents/01-read-required-document-fields.md

PURPOSE:
One document groups labelled values such as a receipt identifier and the exact amount.

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

# Read a receipt document and its required fields

[Course contents](index.md) · [Next · Inspect a BSON field from the C driver boundary](02-build-and-inspect-bson-from-c.md) · [Browser edition](../../../courses/mongodb-c23-documents/lessons/01-read-required-document-fields.html)

One document groups labelled values such as a receipt identifier and the exact amount.

## Compare three data shapes

```json
[
  {"_id":"R-42","cents":{"$numberLong":"0"}},
  {"_id":"R-43"},
  {"_id":"R-44","cents":"2600"}
]
```

The array lays out three separate examples. In Canonical Extended JSON, the $numberLong wrapper preserves a BSON signed 64-bit integer. BSON is the database representation that distinguishes an integer field from a string. The actual zero and the text 2600 are different types. The middle example has no cents field at all.

The native rule accepts only a nonempty receipt ID and a BSON 64-bit amount. The first example is accepted. The second and third are returned to the adapter as refused. Try adding an explicit BSON int32 with $numberInt. It remains outside this exercise’s int64 contract even when it contains the same mathematical value.

## Check the branch in FreeBASIC

```basic
Dim hasInt64Field As Integer = 1
Dim cents As LongInt = 0
If hasInt64Field <> 0 Then
    Print "Amount present"; cents
End If
```

Switch the flag to zero and trace why no amount is printed. In this simplified independent check, the flag represents the already verified type.

- [MongoDB C driver](https://www.mongodb.com/docs/languages/c/c-driver/current/)
- [Read the complete native lab source](../../../labs/native/service-practice/mongodb-receipts/main.c)

## Continue in another course

- [Applied native courses](../../../start/applied-native-courses.md)
- [Practical Web and Data Foundations](../../../courses/practical-web-and-data-foundations/index.html)
- [Oracle Database Ledger Practice in C23](../../../courses/oracle-database-c23-ledger/index.html)

[Course contents](index.md) · [Next · Inspect a BSON field from the C driver boundary](02-build-and-inspect-bson-from-c.md) · [Browser edition](../../../courses/mongodb-c23-documents/lessons/01-read-required-document-fields.html)
