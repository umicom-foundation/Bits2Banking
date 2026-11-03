# Represent money and available funds

Work with currency amounts, balances, reservations and payment states using fictional data.

Lesson 1 of 2. Read [Start here](../../../../courses/framework-and-finance/start.html) first. No banking account or live connection is needed.

A **currency** identifies the kind of money, such as GBP. An amount needs both a number and a unit. The number 100 alone could mean 100 pounds or 100 pence. A **minor unit** is a smaller accounting unit. In our GBP example, 100 pence equals one pound.

Store £12.34 as 1,234 pence for this exercise. This avoids representing that amount as an approximate binary fraction. It does not solve every monetary problem: currencies and instruments can use different scales, conversions need explicit rounding rules, and an integer can overflow if its range is exceeded.

A **ledger balance** reflects posted entries. A **reservation**, or hold, sets money aside for an action that has not yet posted. In this simplified account, available funds equal ledger balance minus active reservations.

```text
ledger balance       10,000 pence  (£100.00)
active reservation    2,500 pence   (£25.00)
available funds       7,500 pence   (£75.00)
```

## Follow a reservation

1. Start with 10,000 pence and no holds.
2. Reserve 2,500. The posted balance stays 10,000; available funds fall to 7,500.
3. Release the hold. Available funds return to 10,000.
4. Start again and capture the hold as a posted payment. Remove the reservation as the debit posts; do not subtract it twice.

Framework's reservation report distinguishes manual, card and transfer reservations. A captured report describes one revision. It may be stale after another operation. Reviewing a release against the captured revision prevents a user from acting on an unrelated newer state without noticing.

Real accounts may also include overdrafts, unsettled amounts and other rules. The arithmetic here is deliberately limited so the meaning of a reservation is visible. It is an educational simulation, not an instruction to operate a real account.

## Read a real Umicom source contract

In a local checkout, open `C:\umicom\Umicom-Applications\framework\include\umicom\bank_operations\reservations.h`. A **contract** states what an operation accepts, returns and promises. Read its comments before its implementation.

The following excerpt comes from that source file. The surrounding declarations and comments are part of the contract too.

```text
typedef enum UmiBankReservationKind {
    UMI_BANK_RESERVATION_MANUAL = 1,
    UMI_BANK_RESERVATION_CARD = 2,
    UMI_BANK_RESERVATION_TRANSFER = 3
} UmiBankReservationKind;
/** All rows are active reservations. Kind plus ID is the identity: a transfer
 * and a hold may use the same ID. Transfer state is pending or approved; the
 * field is zero for holds. Reserved money is not a posted debit. */
typedef struct UmiBankReservationRow {
    UmiBankReservationKind kind;
    UmiFinancialId id, accountId, cardId, destinationAccountId, referenceId, makerId;
    UmiMoney amount;
    UmiBankTransferState transferState;
    uint64_t createdRevision;
```

1. Locate the file in your editor. You are reading it; do not edit your working product to complete this exercise.
2. Read the reservation summary and its three category totals. Find the comment requiring those totals to explain the reserved balance.
3. Write the input, expected result and a possible failure in your own words.

The source reference identifies an existing implementation or contract. It does not establish that an application has wired every operation, or that its build has passed. If your checkout differs, compare the current declarations and record the difference.

## Check your understanding

If a £25 hold becomes a £25 posted debit, should available funds fall by another £25?

### Worked answer

Not if the same hold is removed during posting. The balance falls by £25 and the reservation disappears. Subtracting both would count the same obligation twice.

## Keep a learning checkpoint

Write one observation, one unanswered question and the result of the exercise. In Studio you may record a private checkpoint as explained in [Start here](../../../../courses/framework-and-finance/start.html#progress). Opening the page alone is not completion.

---

[Read this lesson in HTML](../../../../courses/framework-and-finance/banking-and-payments/lessons/money-and-available-balance.html) · [Learning sequence](../../../../start/learning-sequence.md)
