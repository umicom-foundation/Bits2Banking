<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/29-bound-queries-and-protect-output.md

PURPOSE:
Bound a query and protect the caller output

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
<!-- The approved offline logo alias remains for compatibility review:
![Umicom](../../../../assets/branding/umicom-logo.svg)
New website manuscripts use the preferred supplied wordmark. -->
![Umicom](../../../../assets/branding/umicom-wordmark.svg)

# Bound a query and protect the caller output

## A C string needs a terminator

A fixed array of characters is not automatically a C string. The terminating zero byte must occur inside readable storage. A direct string comparison can continue looking for that byte beyond the intended field. The watchlist query contract limits inspection to the financial identifier capacity.


## Construct a deliberate refusal

~~~c
char query[UMI_FINANCE_ID_CAPACITY];
memset(query, 'q', sizeof(query));
size_t index = SIZE_MAX;
UmiStatus status = umi_watchlist_find(&list, query, &index);
/* Expect CAPACITY_EXCEEDED and index still equal to SIZE_MAX. */
~~~


This fixture deliberately allocates the entire readable query span. The capacity rule does not make an invalid pointer readable. An ordinary short string needs storage through its first zero byte. The service captures admitted query bytes before publishing an output.


## Refusal is an output contract

The new watchlist lookup leaves the output index unchanged on every refusal. That makes a sentinel useful in a test, but applications should branch on status rather than mistake an old output for a new match. The order-store lookup has a different established contract: for admitted separate output storage it writes a null pointer on lookup failure. Read each API contract instead of assuming all functions behave alike.


## Keep outputs outside their owner

~~~c
UmiStatus status = umi_watchlist_find(&list, "LAB.A", &list.count);
/* Refused: publishing an index here would overwrite owner metadata. */
~~~


The output pointer in this example is correctly aligned and writable, yet belongs to the owner. The shared overlap check refuses it. Query and output may share a separate allocation because the query is captured before output publication. This distinction is about ownership, not merely pointer equality.


## Exercise and answer

Why not shorten an oversized identifier automatically? Truncation can change identity and accidentally select another record. Refuse the input, report the byte limit and let the caller provide a complete intended identifier. Run the query scenario after building the matching SDK client; its printed outcome remains expected until you execute it.

## Complete source and qualification commands

[Open the laboratory guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/order-lifecycle/README.md). Offline, use labs/framework/order-lifecycle/README.md and identity_lifetime.c. Compilation, installed SDK linking and execution remain separate qualification steps.

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [HTML edition](../../../../courses/framework-and-finance/trading-and-posttrade/lessons/29-bound-queries-and-protect-output.html)
