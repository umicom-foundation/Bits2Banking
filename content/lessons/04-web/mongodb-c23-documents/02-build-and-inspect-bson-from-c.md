<!--
Umicom Bits2Banking
File: content/lessons/04-web/mongodb-c23-documents/02-build-and-inspect-bson-from-c.md

PURPOSE:
Append a typed amount to a local BSON object and ask the iterator for the exact type.

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

# Inspect a BSON field from the C driver boundary

[Course contents](index.md) · [Previous · Read a receipt document and its required fields](01-read-required-document-fields.md) · [Next · Distinguish an empty cursor from a failed lookup](03-distinguish-empty-cursors-from-errors.md) · [Browser edition](../../../courses/mongodb-c23-documents/lessons/02-build-and-inspect-bson-from-c.html)

Append a typed amount to a local BSON object and ask the iterator for the exact type.

## Create and inspect a local document

```c
bson_t doc;
bson_iter_t value;
bson_init(&doc);
bool ready = BSON_APPEND_UTF8(&doc, "_id", "R-42") &&
             BSON_APPEND_INT64(&doc, "cents", INT64_C(0));
if (ready && bson_iter_init_find(&value, &doc, "cents") &&
    BSON_ITER_HOLDS_INT64(&value)) {
    int64_t cents = bson_iter_int64(&value);
    /* Supply this checked value to the native result adapter. */
    (void)cents;
}
bson_destroy(&doc);
```

This excerpt requires the libbson header and standard integer types. The BSON object owns the stored data. Read through the iterator while the object is valid, then destroy it. If append fails, release the initialized document and refuse the incomplete object.

For the trace, remove BSON_APPEND_INT64 and imagine inserting a string instead. The iterator can find the field, and its type check then refuses it. When there is no field at all, the find result already fails.

## Optional native practice

From the Bits2Banking checkout, open a Windows UCRT64 toolchain session. In PowerShell with the C23 compiler already on your path, compile the supplied files. Expect exit code 0 and the line shown below when you run the resulting training program. If the compiler is missing, use the paper trace first.

```powershell
Set-Location labs/native/service-practice/mongodb-receipts
gcc -std=c23 -Wall -Wextra -Werror main.c -o mongodb-document-rules.exe
.\mongodb-document-rules.exe
```

```text
document field checks ready
```

- [Read the complete native lab source](../../../labs/native/service-practice/mongodb-receipts/main.c)
- [MongoDB C driver](https://www.mongodb.com/docs/languages/c/c-driver/current/)

## Continue in another course

- [Applied native courses](../../../start/applied-native-courses.md)
- [Practical Web and Data Foundations](../../../courses/practical-web-and-data-foundations/index.html)
- [Oracle Database Ledger Practice in C23](../../../courses/oracle-database-c23-ledger/index.html)

[Course contents](index.md) · [Previous · Read a receipt document and its required fields](01-read-required-document-fields.md) · [Next · Distinguish an empty cursor from a failed lookup](03-distinguish-empty-cursors-from-errors.md) · [Browser edition](../../../courses/mongodb-c23-documents/lessons/02-build-and-inspect-bson-from-c.html)
