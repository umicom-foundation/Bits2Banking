# Explain where a report's numbers came from

Understand balanced entries, reconciliation and traceable reports using small worked examples.

Lesson 2 of 2. Read [Start here](../../../../courses/framework-and-finance/start.html) first. No banking account or live connection is needed.

**Reconciliation** compares independent records of the same business activity. Matching two copies of the same mistaken source is not independent confirmation. A bank statement, internal ledger and trade record may provide different views that need careful mapping.

Imagine an internal cash ledger of 1,000 units and an external statement of 970. The difference is 30. Do not immediately force one number to equal the other. A fee, timing difference, missing transaction or duplicate could explain it. Preserve both observations while investigating.

```text
source records → selection rules → transformations → report total
     ↑                  ↑                 ↑               ↑
 identity/date      included rows      rule version     evidence
```

**Lineage** records how a value was derived. A **cut-off** defines which events belong in a report. A report produced today may describe yesterday's business date. Re-running it later with newly arrived data can change the result unless its population and inputs were fixed.

## Make a tiny reconciliation

1. List internal entries +600 and +400.
2. List statement entries +600, +400 and a fee of −30.
3. Match the two shared entries by identity and amount.
4. Leave the fee as an explained difference until the correct internal accounting action is reviewed.
5. Record source, business date and explanation alongside the totals.

A **control total** is a simple check such as record count or sum. It helps detect missing or changed data, but equal totals can hide different rows. Keep identities and detail available for investigation.

Framework's ledger-balance contract distinguishes debit and credit totals and the account's normal side. It is an arithmetic building block. A full report also needs population rules, source evidence and appropriate review. These lessons teach controls, not jurisdiction-specific reporting obligations.

## Read a real Umicom source contract

In a local checkout, open `C:\umicom\Umicom-Applications\framework\include\umicom\finance\accounting\ledger_balance.h`. A **contract** states what an operation accepts, returns and promises. Read its comments before its implementation.

The following excerpt comes from that source file. The surrounding declarations and comments are part of the contract too.

```text
typedef struct UmiAccountingLedgerBalance {
    UmiFinancialId id;
    UmiFinancialId account_id;
    UmiAccountingNormalSide normal_side;
    int64_t debit_minor;
    int64_t credit_minor;
} UmiAccountingLedgerBalance;
/**
 * Initialise accounting ledger balance from caller-provided values so later operations
 * receive a known state.
 */
UmiStatus umi_accounting_ledger_balance_init(UmiAccountingLedgerBalance *value,
    const char *id,
    const char *account_id,
```

1. Locate the file in your editor. You are reading it; do not edit your working product to complete this exercise.
2. Find the checked net-balance function and its invalid-input rules. Write down which reporting facts are outside this value type and must be supplied by a report service.
3. Write the input, expected result and a possible failure in your own words.

The source reference identifies an existing implementation or contract. It does not establish that an application has wired every operation, or that its build has passed. If your checkout differs, compare the current declarations and record the difference.

## Check your understanding

Two reports have the same total. Must they contain the same transactions?

### Worked answer

No. Different rows can cancel to the same sum. Compare counts, identities, amounts, currencies and dates as well as the total.

## Keep a learning checkpoint

Write one observation, one unanswered question and the result of the exercise. In Studio you may record a private checkpoint as explained in [Start here](../../../../courses/framework-and-finance/start.html#progress). Opening the page alone is not completion.

---

[Read this lesson in HTML](../../../../courses/framework-and-finance/accounting-and-control/lessons/reconciliation-and-lineage.html) · [Learning sequence](../../../../start/learning-sequence.md)
