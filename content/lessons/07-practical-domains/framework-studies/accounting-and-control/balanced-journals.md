# Read a balanced journal

Understand balanced entries, reconciliation and traceable reports using small worked examples.

Lesson 1 of 2. Read [Start here](../../../../courses/framework-and-finance/start.html) first. No banking account or live connection is needed.

A **ledger** is an organised record of accounting entries. A **journal entry** groups related lines for one accounting event. **Debit** and **credit** name the two sides of accounting. They do not universally mean “bad” and “good”, or “money out” and “money in”. Their effect depends on the kind of account.

Use a fictional business buying equipment for 500 units of cash. A simple entry debits equipment by 500 and credits cash by 500. Both accounts are assets: equipment increases and cash decreases. Total debits equal total credits.

```text
account       debit   credit
Equipment       500        0
Cash              0      500
Totals          500      500
```

Balance is necessary but not sufficient. An entry for 5,000 instead of 500 can still balance. So can an entry posted to the wrong accounts or date. Controls must check the business event, account mapping, units, approval and period as well as arithmetic.

## Review the entry

1. Add the debit lines and credit lines separately.
2. Compare the totals.
3. Compare the amount with the original fictional purchase record.
4. Check that the accounts represent the intended economic event.
5. Confirm the accounting date and whether the period is open.

Framework has a bounded journal entry with lines, status and accounting date. The checked totals API reports failure separately from a valid zero total. Its contract leaves outputs unchanged on invalid data or overflow. A caller must check the returned status before displaying the output as a current answer.

No currency conversion occurs automatically in that totals operation. Before adding amounts, establish compatible currency and scale. A sum of 500 GBP minor units and 500 JPY units is not a meaningful single-currency total.

## Read a real Umicom source contract

In a local checkout, open `C:\umicom\Umicom-Applications\framework\include\umicom\finance\accounting\journal_entry.h`. A **contract** states what an operation accepts, returns and promises. Read its comments before its implementation.

The following excerpt comes from that source file. The surrounding declarations and comments are part of the contract too.

```text
typedef struct UmiAccountingJournalEntry { UmiFinancialId id; UmiFinancialDate accounting_date; UmiAccountingJournalStatus status; UmiAccountingJournalLine lines[UMI_ACCOUNTING_MAX_LINES]; size_t line_count; } UmiAccountingJournalEntry;
/**
 * Initialise accounting journal entry from caller-provided values so later operations
 * receive a known state.
 */
UmiStatus umi_accounting_journal_entry_init(UmiAccountingJournalEntry *value,const char *id,UmiFinancialDate accounting_date);
/**
 * Provide the accounting journal entry add line operation used by this module and its
 * client applications.
 */
UmiStatus umi_accounting_journal_entry_add_line(UmiAccountingJournalEntry *value,const UmiAccountingJournalLine *line);
/**
 * Check that accounting journal entry satisfies its contract before another service relies
 * on it.
```

1. Locate the file in your editor. You are reading it; do not edit your working product to complete this exercise.
2. Find umi_accounting_journal_entry_totals. Contrast its status-plus-output contract with the legacy scalar accessors. Explain why a failure must not be interpreted as a zero balance.
3. Write the input, expected result and a possible failure in your own words.

The source reference identifies an existing implementation or contract. It does not establish that an application has wired every operation, or that its build has passed. If your checkout differs, compare the current declarations and record the difference.

## Check your understanding

If both totals are 500, has the entry been proven correct?

### Worked answer

Only the balance check has succeeded. The amount, accounts, currency, date, event identity and approval can still be wrong. Each needs its own evidence.

## Keep a learning checkpoint

Write one observation, one unanswered question and the result of the exercise. In Studio you may record a private checkpoint as explained in [Start here](../../../../courses/framework-and-finance/start.html#progress). Opening the page alone is not completion.

---

[Read this lesson in HTML](../../../../courses/framework-and-finance/accounting-and-control/lessons/balanced-journals.html) · [Learning sequence](../../../../start/learning-sequence.md)
