# A trade creates future obligations

Trace a fictional foreign-exchange obligation through dates, valuation, cash and settlement.

Lesson 1 of 2. Read [Start here](../../../../courses/framework-and-finance/start.html) first. No banking account or live connection is needed.

**Treasury** manages an organisation's cash, funding and financial exposures. A treasury management system, or TMS, records agreements and helps people control what must happen next. It does more than display a price.

A **foreign-exchange forward** is an agreement to exchange currencies on a future date at an agreed rate. In our fictional example, a company will pay GBP 1,000 and receive USD 1,250 in one month. The two currency amounts are separate obligations. They cannot be added together as though pounds and dollars were the same unit.

```text
agreement → validation → confirmation → due obligations
                                          ↓
                              settlement evidence → reconciliation
```

**Confirmation** compares the parties' understanding of the agreement. **Settlement** is the fulfilment of the due obligations. **Reconciliation** compares internal expectations with independent records. A trade can be validly captured while settlement is still incomplete.

## Trace the example

1. Record both parties, the two currencies, amounts, rate and agreed date.
2. Separate trade date, when the agreement was made, from settlement date.
3. Write one outgoing and one incoming cash obligation.
4. Mark a received confirmation without marking either cash movement settled.
5. At maturity, compare expected amounts with observed settlement records. Keep any unmatched item visible.

Framework's settlement-obligation type is a small existing contract with cash, security quantity and state. It illustrates that settlement has its own identity and lifecycle. It is not a complete FX-forward trade model and does not itself send money or securities.

For every state change, ask who may request it, which evidence is required, and what the next operator should see if it fails. That question connects financial understanding to application design.

## Read a real Umicom source contract

In a local checkout, open `C:\umicom\Umicom-Applications\framework\include\umicom\finance\treasury\settlement_obligation.h`. A **contract** states what an operation accepts, returns and promises. Read its comments before its implementation.

The following excerpt comes from that source file. The surrounding declarations and comments are part of the contract too.

```text
typedef struct UmiTreasurySettlementObligation {
    char id[UMI_TREASURY_ID_CAPACITY];
    int64_t cash_minor;
    int64_t security_quantity;
    UmiTreasurySettlementState state;
} UmiTreasurySettlementObligation;
/**
 * Initialise treasury settlement obligation from caller-provided values so later
 * operations receive a known state.
 */
UmiStatus umi_treasury_settlement_obligation_init(UmiTreasurySettlementObligation *value,
    const char *id,
    int64_t cash_minor,
    int64_t security_quantity,
```

1. Locate the file in your editor. You are reading it; do not edit your working product to complete this exercise.
2. Read UmiTreasurySettlementObligation. Identify the fields it has and list at least three FX-forward details it does not contain. Do not assume an isolated value type is a complete TMS.
3. Write the input, expected result and a possible failure in your own words.

The source reference identifies an existing implementation or contract. It does not establish that an application has wired every operation, or that its build has passed. If your checkout differs, compare the current declarations and record the difference.

## Check your understanding

Why is a captured trade not the same as a settled trade?

### Worked answer

Capture records the agreement. Settlement fulfils its obligations later. Dates, approvals, external systems and failures can intervene between those facts.

## Keep a learning checkpoint

Write one observation, one unanswered question and the result of the exercise. In Studio you may record a private checkpoint as explained in [Start here](../../../../courses/framework-and-finance/start.html#progress). Opening the page alone is not completion.

---

[Read this lesson in HTML](../../../../courses/framework-and-finance/treasury-operations/lessons/trade-to-settlement.html) · [Learning sequence](../../../../start/learning-sequence.md)
