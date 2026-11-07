# Decimal values and checks

Numbers with a decimal point need a clear representation. Begin with the exact values in the lab, then separate a numerical check from a complete financial workflow.

## 1. Why construct from text?

In [the existing source](../../../labs/java-ledger/LedgerDemo.java), `new BigDecimal("25.10")` reads a decimal text value directly. The quotes matter. A binary floating-point value has already been rounded to that representation before a constructor receives it. Parsing the intended decimal text avoids that particular intermediate conversion.

A decimal value includes an unscaled integer and a scale. For 25.10, one representation has integer 2510 and scale 2: move the decimal point two places. This is about representation, not an exchange rate or a currency's required precision.

## 2. Addition returns a new value

```text
totalDebit = totalDebit.add(posting.debit());
```

BigDecimal is immutable: its arithmetic does not change the existing object. `add` returns the result, and assignment keeps it under `totalDebit`. Calling add and ignoring the returned value would leave the name referring to the old total. Draw two boxes labelled 0 and 25.10, then move the totalDebit arrow to the result.

## 3. Compare the intended property

```text
return totalDebit.compareTo(totalCredit) == 0;
```

`compareTo` returns a negative value, zero or a positive value for less than, numerically equal or greater than. The double equals compares that result with zero. Decimal 25.1 and 25.10 compare numerically equal even though their scales differ. `equals` also considers BigDecimal's scale, so it answers a different question.

## 4. Test boundaries in thought

1. Empty journal: both totals stay zero, so this function returns true.
2. One debit of 5 and no credit: false.
3. One debit of 5 and one credit of 5.00: true.
4. Equal negative totals: the function can still return true.

These results follow from the source, not from a rule that every example is a valid journal. A production workflow would need account and currency checks, permitted signs, balancing policy, authorization, durable recording and duplicate handling. Those are deliberately outside this tiny lab.

## 5. Read a related C boundary

Open `Umicom-Applications/framework/include/umicom/finance/decimal.h` and `money.h` in your checkout. Identify a type, an operation and its result status. A fixed-width C representation also needs overflow checks. A Java decimal object can use more memory as its size grows; it still needs input and resource limits. Different languages do not remove the need to state those limits.

Exercise: write pseudocode that first rejects an empty journal and then performs the existing balance check. Answer: `IF count is zero: reject; ELSE: compare the two totals`. Do not edit the original lab merely to make it satisfy a policy that has not been chosen.

---

[Read this lesson in HTML](../../../courses/learning-java/lessons/02-decimal-values-and-checks.html) · [Learning sequence](../../../start/learning-sequence.md)


## Continue learning

[Continue: Values, methods and checks](03-values-methods-and-checks.md)

[Previous: Records and a journal](01-records-and-a-journal.md)
