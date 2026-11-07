# Records and a journal

A journal is an ordered collection of entries. This small program checks one relationship between two totals. It does not operate a bank account or move money.

## 1. Locate the demonstration

Open [LedgerDemo.java](../../../labs/java-ledger/LedgerDemo.java). Java source is compiled into class files that a Java runtime can execute. The source uses records, so optional execution needs a Java version supporting records as a standard feature, such as Java 17 or later. Reading this lesson needs no installation.

## 2. Name the parts of a record

```text
record Posting(String account, BigDecimal debit, BigDecimal credit) {}
```

`Posting` is the type name. Each posting has an account label, a debit value and a credit value. A record supplies a concise way to hold these components and retrieve them. `String` represents text. `BigDecimal` represents a decimal number. A record does not automatically validate that an account exists or that an amount follows accounting policy.

In this lab, debit and credit name the two sides being totaled. Do not substitute “money out” and “money in” for them in every situation: the interpretation depends on the account and transaction. The coding exercise only compares totals.

 <svg viewbox="0 0 700 110" role="img" aria-label="The program checks numerical balance, not the business validity of a transaction." style="width:100%;max-width:700px"><title>The program checks numerical balance, not the business validity of a transaction.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">posting records</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">sum each side</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">compare totals</text></svg>

The program checks numerical balance, not the business validity of a transaction.

## 3. Follow the list

```text
List<Posting> journal = List.of(
    new Posting("Cash", new BigDecimal("25.10"), BigDecimal.ZERO),
    new Posting("Donation income", BigDecimal.ZERO, new BigDecimal("25.10"))
);
```

The angle brackets say that the list contains Posting values. `List.of` creates an unmodifiable list: the caller cannot add or remove elements through it. `new` constructs an object. Each pair of parentheses supplies that object's inputs. The commas separate inputs or entries. The quoted account names are invented teaching labels.

## 4. Trace the function

`IsBalanced` starts both totals at zero. The enhanced for loop takes each posting from the list. `posting.debit()` reads its debit component; `posting.credit()` reads its credit component. After the first posting the totals are 25.10 and 0. After the second they are 25.10 and 25.10. The printed message is expected to say `Journal balanced: true` for this source.

## 5. Connect to Umicom

Compare the C23 financial services under `Umicom-Applications/framework/include/umicom/finance`. The Framework represents amounts, currencies and errors explicitly. The Java lab is a teaching comparison, not an alternative implementation of the shared financial engine.

Exercise: change only the second amount on paper to 24.10. Which total changes and what result should the function give? Answer: credit becomes 24.10, so the comparison is false. Adding an invented account label would not be detected by this particular check; account validation is a separate requirement.

---

[Read this lesson in HTML](../../../courses/learning-java/lessons/01-records-and-a-journal.html) · [Learning sequence](../../../start/learning-sequence.md)

[Next: Decimal values and checks](02-decimal-values-and-checks.md)
