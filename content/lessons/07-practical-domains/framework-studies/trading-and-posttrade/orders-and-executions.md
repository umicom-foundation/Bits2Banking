![Umicom](../../../../assets/branding/umicom-logo.svg)

# An order is a request, a fill is an event

Distinguish market data, orders, executions, positions and collateral.

Lesson 1 of 2. Read [Start here](../../../../courses/framework-and-finance/start.html) first. No banking account or live connection is needed.

An **instrument** identifies what can be traded. A symbol alone may be ambiguous: venue, currency, expiry or other contract details can matter. A **quote** reports a market observation. An **order** requests a trade under specified conditions. A **fill** reports an executed quantity.

For a fictional limit order, request 10 units with a maximum buy price of 25. A fill for 4 leaves 6 outstanding. Sending a cancellation for the remaining 6 is another request; the order is not cancelled merely because the user clicked Cancel. A fill may arrive while cancellation is being processed.

```text
submit 10 → acknowledged → fill 4 → remaining 6
                                  cancel requested
                                  ↙              ↘
                           cancelled       another fill
```

A **journal** retains events needed to explain the lifecycle. Repeated or out-of-order notifications must not create duplicate positions. Request identifiers, order identifiers and execution identifiers serve different purposes; do not replace them all with the symbol.

## Trace an order safely

1. Write the instrument identity, side, quantity and price condition.
2. Record an acknowledgement separately from a fill.
3. Apply a fill of 4 and calculate remaining quantity.
4. Request cancellation.
5. Consider both possible next events: cancellation confirmation or a further fill.

For broker-connected applications, authentication, API connection, permissions and market-data subscriptions are distinct concerns. A successful connection is not evidence that every quote is live or that orders may be submitted. Follow the configured adapter's documented authentication route; do not invent a username/password field in a socket protocol.

This is a paper lifecycle exercise. It sends no order and uses no real account. Source inspection can establish how events are represented; live functionality requires separate controlled qualification.

## Read a real Umicom source contract

In a local checkout, open `C:\umicom\Umicom-Applications\framework\src\broker_connectivity\order_journal.c`. A **contract** states what an operation accepts, returns and promises. Read its comments before its implementation.

The following excerpt comes from that source file. The surrounding declarations and comments are part of the contract too.

```text
UmiStatus umi_broker_order_journal_add(
    UmiBrokerOrderJournal *journal,
    const UmiBrokerOrderRecord *record)
{
    if (journal == NULL || record == NULL ||
        record->request.client_order_id.value[0] == '\0') {
        return UMI_STATUS_INVALID_ARGUMENT;
    }
    if (umi_broker_order_journal_find(
            journal, record->request.client_order_id.value) != NULL) {
        return UMI_STATUS_ALREADY_EXISTS;
    }
    if (journal->count >= UMI_BROKER_ORDER_JOURNAL_CAPACITY) {
        return UMI_STATUS_CAPACITY_EXCEEDED;
```

1. Locate the file in your editor. You are reading it; do not edit your working product to complete this exercise.
2. Find how order_journal.c validates or records lifecycle information. Follow one called public function to its header and identify the evidence needed to distinguish a request from an execution.
3. Write the input, expected result and a possible failure in your own words.

The source reference identifies an existing implementation or contract. It does not establish that an application has wired every operation, or that its build has passed. If your checkout differs, compare the current declarations and record the difference.

## Check your understanding

After a connection timeout, is it safe to submit the same order with a new ID?

### Worked answer

Not without checking the existing outcome. The original may have reached the broker. Reconcile known order and execution identities before deciding on another submission.

## Keep a learning checkpoint

Write one observation, one unanswered question and the result of the exercise. In Studio you may record a private checkpoint as explained in [Start here](../../../../courses/framework-and-finance/start.html#progress). Opening the page alone is not completion.

---

[Read this lesson in HTML](../../../../courses/framework-and-finance/trading-and-posttrade/lessons/orders-and-executions.html) · [Learning sequence](../../../../start/learning-sequence.md)
