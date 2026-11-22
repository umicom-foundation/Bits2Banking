<!--
Umicom Bits2Banking
File: content/lessons/04-web/oracle-database-c23-ledger/01-read-an-oracle-number.md

PURPOSE:
A signed integer amount and an optional adjustment use different database rules.

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

# Read an exact numeric projection in Oracle

[Course contents](index.md) · [Next · Follow a named OCI bind and a result indicator](02-follow-a-named-bind-and-indicator.md) · [Browser edition](../../../courses/oracle-database-c23-ledger/lessons/01-read-an-oracle-number.html)

A signed integer amount and an optional adjustment use different database rules.

## Trace an optional adjustment

```sql
CREATE TABLE training_adjustment (
    entry_id NUMBER(19,0) PRIMARY KEY,
    cents NUMBER(19,0),
    CONSTRAINT training_cents_range CHECK (
        cents >= -9223372036854775808 AND cents <= 9223372036854775807
    )
);
INSERT INTO training_adjustment (entry_id, cents) VALUES (42, 0);
INSERT INTO training_adjustment (entry_id, cents) VALUES (43, NULL);
SELECT entry_id, cents FROM training_adjustment ORDER BY entry_id;
```

A NUMBER(19,0) stores a whole decimal number up to the declared precision. Its allowed declared numeric range can be wider than a signed 64-bit C value, so the exercise uses a separate range check. This check allows the optional amount to remain NULL. Row 42 says zero. Row 43 has no amount. A lookup for row 44 yields no row.

## Walk the native representation

```c
struct OptionalAmount {
    bool present;
    int64_t cents;
};
```

For row 42, present is true and cents is zero. For row 43, present is false and the cents storage is unused. Add a fetched row with −850 to see how a deliberate signed adjustment differs from absence.

- [Oracle Call Interface bindings and definitions](https://docs.oracle.com/en/database/oracle/oracle-database/26/lnoci/binding-and-defining-in-oci.html)

## Continue in another course

- [Applied native courses](../../../start/applied-native-courses.md)
- [MySQL Ledger Practice in C23](../../../courses/mysql-c23-ledger/index.html)
- [Bookkeeping from Your First Entry](../../../courses/bookkeeping-from-first-entry/index.html)

[Course contents](index.md) · [Next · Follow a named OCI bind and a result indicator](02-follow-a-named-bind-and-indicator.md) · [Browser edition](../../../courses/oracle-database-c23-ledger/lessons/01-read-an-oracle-number.html)
