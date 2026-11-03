# Follow a payment from instruction to evidence

Work with currency amounts, balances, reservations and payment states using fictional data.

Lesson 2 of 2. Read [Start here](../../../../courses/framework-and-finance/start.html) first. No banking account or live connection is needed.

A **payment instruction** requests movement of money. The **debtor** is the party expected to pay; the **creditor** is expected to receive. A party is a person or organisation represented by an identifier. Names alone are unreliable identifiers because different parties may share a name.

Use a fictional payment P42: debtor D1 pays creditor C1 1,250 GBP minor units on an agreed date. The instruction needs a currency, amount, requested date and identity. A requested date expresses intent; it is not proof that the money moved on that date.

```text
prepared → validated → approved → submitted → acknowledged
                                               ↓
                                    settlement evidence or exception
```

This diagram is a teaching lifecycle, not the exact enumeration of any network. Acknowledgement can mean only that a message was received. A rejection can arrive later. Keep the original instruction and later events so an operator can explain what is known and what remains uncertain.

## Prepare a safe request

1. Write P42, D1, C1, GBP, 1,250 and the requested date.
2. Check the amount is in the intended units and the parties differ as required by the business case.
3. Add an idempotency key representing this logical request.
4. Imagine the reply is lost after submission. Query by that key instead of inventing a second payment.
5. Record a network rejection without rewriting the original request into a different amount.

Framework's payment instruction API validates a value and can encode or decode an archive. An **archive** is a stored representation. Successful decoding means the representation satisfied that contract. It does not authorise payment, contact a bank, or prove settlement.

A bank connector translates between the canonical instruction and a particular external format. Keep that translation at the boundary so the same validation can serve Bank, TMS and other applications.

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
2. Find the instruction's idempotency key and requested date. Compare _valid, _final and archive decode declarations; describe their distinct responsibilities.
3. Write the input, expected result and a possible failure in your own words.

The source reference identifies an existing implementation or contract. It does not establish that an application has wired every operation, or that its build has passed. If your checkout differs, compare the current declarations and record the difference.

## Check your understanding

The archive decoder returned success. May the UI display “money delivered”?

### Worked answer

No. Decoding validates stored data. Delivery requires independently recorded business evidence from the relevant payment process.

## Keep a learning checkpoint

Write one observation, one unanswered question and the result of the exercise. In Studio you may record a private checkpoint as explained in [Start here](../../../../courses/framework-and-finance/start.html#progress). Opening the page alone is not completion.

---

[Read this lesson in HTML](../../../../courses/framework-and-finance/banking-and-payments/lessons/payment-states.html) · [Learning sequence](../../../../start/learning-sequence.md)
