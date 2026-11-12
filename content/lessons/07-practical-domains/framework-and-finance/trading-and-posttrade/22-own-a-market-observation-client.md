<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/22-own-a-market-observation-client.md

PURPOSE:
Build a market-observation client around one Framework owner

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../../assets/branding/umicom-logo.svg)

# Build a market-observation client around one Framework owner

## Start with the state you need

A market monitor needs instrument metadata, quotes, public prints, depth and alerts. An account execution changes an order or position; a public print only describes activity reported by a market-data provider. Keeping those concepts separate prevents a display feed from accidentally becoming an account ledger. The new market_observation.c laboratory demonstrates the distinction with synthetic values.



## Create the owner, then add an instrument

~~~c
UmiTradingWorkspace *workspace = NULL;
UmiStatus status = umi_trading_workspace_create(&config, &workspace);
/* After checking status, add the complete synthetic instrument. */
~~~



The workspace pointer is opaque. The client calls public operations and reads copied snapshots; it does not copy private structures or maintain another alert or trade-tape engine. SyntheticInstrument fills fixed lesson identifiers, currency and multiplier. Those literal string copies are bounded by known constants and are not a recipe for accepting arbitrary user input.



## Trace the lifetime

- Create one workspace and check the result.
- Register the instrument before publishing observations.
- Validate temporary input, call the owner and inspect its status.
- Read a fresh snapshot after an accepted change.
- Destroy the workspace once through the common cleanup path.



The example keeps its checks active in optimized builds. An assertion disabled by a release compiler would otherwise remove required setup or hide a failed operation. Every failed check leads to the same cleanup path, which releases the owner only when creation succeeded.



## Exercise and answer

Does a successful public-print update prove that an account traded? No. Run the tape scenario after building the matching SDK client. Its expected observations include two retained public prints and zero executions and positions. That is a local state check, not evidence about an external account or venue.



## Qualification boundary

The source and expected results are supplied. Build and run the installed-SDK example separately from native Trader qualification. Neither an authored lesson nor a resolved header reference proves that the executable links or that a screen refreshes correctly.



## Complete source and owner commands

[Open the laboratory guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/order-lifecycle/README.md). Offline, use labs/framework/order-lifecycle/README.md. Installed-SDK builds, scenario checks and native presentation require owner execution.

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [HTML edition](../../../../courses/framework-and-finance/trading-and-posttrade/lessons/22-own-a-market-observation-client.html)
