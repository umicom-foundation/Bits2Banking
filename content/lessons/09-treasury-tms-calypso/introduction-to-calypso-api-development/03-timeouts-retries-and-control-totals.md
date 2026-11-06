# Timeouts, retries and control totals

[Course contents](index.md) · [Previous: A Java port and a fake repository](02-a-java-port-and-a-fake-repository.md)

## A missing reply is an unknown outcome

Suppose an integration submits a request and waits. The server may accept it, but the reply may be lost. A timeout tells the caller that no reply arrived before the deadline; it does not prove that the operation was rejected.

Reliable treasury integrations need bounded queries, retry limits and a way to stop interrupted work. We apply those concepts to an original exercise. No vendor write method is assumed here.

```text
request sent -> server may commit -> reply lost
      client sees timeout
      client must establish outcome before repeating a write
```

## Design a read-only investigation

1. Restrict the query by an authorised book, product and date range.
2. Choose a page size and stable ordering supported by the service.
3. Record query criteria, snapshot identity when available, page count and received record count.
4. Detect repeated or missing pages. Do not declare success solely because one page arrived.
5. Report partial results separately from a complete result set.

For a write, use the system's supported idempotency or correlation mechanism if available. Idempotency means repeating the same request does not repeat its business effect. If the API provides no such guarantee, query the known outcome or escalate for reconciliation rather than blindly retrying.

## Exercise

A paged query returns 100, 100 and 17 records. The service reports a total of 217 for the same stable snapshot. What control can you record? What if the third page times out?

## Explained answer

The count reconciles: 100 + 100 + 17 = 217. This count alone does not prove every field is correct, so retain identifiers and snapshot criteria too. With the third page missing, report 200 received and incomplete. Do not turn the partial collection into an authoritative portfolio or settlement report.

## Connect to Framework

Put reusable pagination, status, mapping and evidence rules behind Framework contracts. Keep the vendor-specific adapter narrow. Public lesson examples contain fictional identifiers; operational logs must avoid passwords, tokens and unnecessary customer details. The next course module will map a read operation to a documented licensed environment, which cannot be inferred from these teaching classes.

## Continue learning

[Course contents](index.md) · [Previous: A Java port and a fake repository](02-a-java-port-and-a-fake-repository.md)

[Browser edition](../../../courses/introduction-to-calypso-api-development/lessons/03-timeouts-retries-and-control-totals.html)

## Read the related Umicom source

[Source and context](../sources-and-licensing.md). Follow the source and licensing notes before using vendor APIs.
