# Trace a controlled payment from request to report

Translate data without losing meaning and trace one controlled lifecycle across services.

Lesson 2 of 2. Read [Start here](../../../../courses/framework-and-finance/start.html) first. No banking account or live connection is needed.

This capstone joins the earlier lessons. A **capstone** is a final exercise combining several skills. You will trace one fictional payment through shared services and explain the evidence at each boundary. No bank connection or real money is involved.

Use account A with 10,000 GBP minor units. Prepare a payment of 1,250 to fictional party B. Give the request a stable identity P42 and a distinct idempotency key. Record the initial account state and the intended date before changing anything.

```text
request → permission → validation → approval → execution
                                               ↓
                            ledger → reconciliation → report
                                               ↓
                                      linked evidence
```

## Build the evidence folder

1. Create a folder you choose for this exercise.
2. Write the original request and the units of every amount.
3. Record maker and checker decisions using fictional identities.
4. Calculate the expected remaining balance: 8,750, before any explicitly modelled fees.
5. Create a balanced journal for the teaching event and explain its account mapping.
6. Simulate a lost response and retry with the original identity. Record why it must not create a second debit.
7. Compare an independent statement with the expected movement.
8. Write a short report listing unresolved differences instead of hiding them.

Add one failure: change the currency in a retry while retaining the same idempotency key. The correct outcome is a conflict requiring review, not a fresh payment and not silent reuse of an unrelated result.

Keep **expected** and **observed** results separate. The arithmetic you calculated is expected evidence. A real program's recorded result becomes observed evidence only after execution. A screenshot of a success label alone is weaker than a complete trace of the service result and persisted state.

When following this exercise in Studio, record a private learning checkpoint with a reference to your own evidence folder. Reading the lesson does not automatically complete the exercise or authorise application commands.

## Read a real Umicom source contract

In a local checkout, open `C:\umicom\Umicom-Applications\framework\include\umicom\finance\payments\payment_instruction.h`. A **contract** states what an operation accepts, returns and promises. Read its comments before its implementation.

The following excerpt comes from that source file. The surrounding declarations and comments are part of the contract too.

```text
typedef struct UmiPaymentsPaymentInstruction {
    UmiFinancialId id;
    UmiFinancialId debtor_party_id;
    UmiFinancialId creditor_party_id;
    UmiCurrency currency;
    int64_t amount_minor;
    UmiFinancialDate requested_date;
    UmiPaymentsStatus status;
    char idempotency_key[UMI_PAYMENTS_ID_CAPACITY];
} UmiPaymentsPaymentInstruction;
/**
 * Initialise payments payment instruction from caller-provided values so later operations
 * receive a known state.
 */
```

1. Locate the file in your editor. You are reading it; do not edit your working product to complete this exercise.
2. Return to payment_instruction.h, bank_operations/operations.h and accounting/journal_entry.h. Mark which part of the trace each contract owns and which external evidence remains outside those contracts.
3. Write the input, expected result and a possible failure in your own words.

The source reference identifies an existing implementation or contract. It does not establish that an application has wired every operation, or that its build has passed. If your checkout differs, compare the current declarations and record the difference.

## Check your understanding

What would make this capstone incomplete even if the ending balance is correct?

### Worked answer

Missing identities, approval evidence, duplicate handling, currency rules or reconciliation can hide errors that happen to cancel numerically. Completion requires an explainable lifecycle, not only one matching number.

## Keep a learning checkpoint

Write one observation, one unanswered question and the result of the exercise. In Studio you may record a private checkpoint as explained in [Start here](../../../../courses/framework-and-finance/start.html#progress). Opening the page alone is not completion.

---

[Read this lesson in HTML](../../../../courses/framework-and-finance/financial-integration/lessons/lifecycle-capstone.html) · [Learning sequence](../../../../start/learning-sequence.md)
