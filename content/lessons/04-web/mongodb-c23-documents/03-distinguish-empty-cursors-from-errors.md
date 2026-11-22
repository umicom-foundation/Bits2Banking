<!--
Umicom Bits2Banking
File: content/lessons/04-web/mongodb-c23-documents/03-distinguish-empty-cursors-from-errors.md

PURPOSE:
Package a fixed field filter as data and track the cursor result before reporting a receipt.

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

# Distinguish an empty cursor from a failed lookup

[Course contents](index.md) · [Previous · Inspect a BSON field from the C driver boundary](02-build-and-inspect-bson-from-c.md) · [Browser edition](../../../courses/mongodb-c23-documents/lessons/03-distinguish-empty-cursors-from-errors.html)

Package a fixed field filter as data and track the cursor result before reporting a receipt.

## Rehearse the cursor lifetime

```text
Build a BSON filter with _id as a trusted field name and R-42 as the value.
Call mongoc_collection_find_with_opts on the owner-prepared training collection.
Read rows with mongoc_cursor_next and validate each document during its lifetime.
Inspect mongoc_cursor_error after iteration and report any failure.
Destroy the cursor and release owned filter storage.
```

An empty successful cursor means no receipt matched. An error means the lookup could not provide a result. An invalid document means a row arrived with data outside the expected contract. List the three observations for the learner before testing an adapter.

## Apply this to Umicom Bank

A receipt document can serve as training metadata while the core ledger remains separately configured for an authoritative balance. Keep the collection name and fields explicit, and send an unavailable state to the adaptor when a fetch or type check fails.

- [C driver retrieve data guide](https://www.mongodb.com/docs/languages/c/c-driver/current/read/retrieve/)
- [MySQL Ledger Practice in C23](../../../courses/mysql-c23-ledger/index.html)

## Continue in another course

- [Applied native courses](../../../start/applied-native-courses.md)
- [Practical Web and Data Foundations](../../../courses/practical-web-and-data-foundations/index.html)
- [Oracle Database Ledger Practice in C23](../../../courses/oracle-database-c23-ledger/index.html)

[Course contents](index.md) · [Previous · Inspect a BSON field from the C driver boundary](02-build-and-inspect-bson-from-c.md) · [Browser edition](../../../courses/mongodb-c23-documents/lessons/03-distinguish-empty-cursors-from-errors.html)
