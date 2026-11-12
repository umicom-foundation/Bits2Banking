<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/23-validate-depth-before-lookup.md

PURPOSE:
Validate depth before looking up its instrument

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../../assets/branding/umicom-logo.svg)

# Validate depth before looking up its instrument

## Treat a snapshot as structured input

A depth value contains fixed-size identity fields, array counts and numeric levels. Checking only the counts leaves important questions unanswered: does each identity field terminate inside its storage, is the contract multiplier usable, and are the active prices and sizes finite? Framework answers these questions in the shared depth validator before the workspace performs identity lookup.



## Call the canonical validator

~~~c
if (!umi_market_depth_valid(&depth)) {
    /* Reject malformed evidence before publication. */
}
UmiStatus status = umi_trading_workspace_update_depth(workspace, &depth);
~~~



In an application, return or take an error branch after a failed validation; the snippet shows the two relevant entry points. The complete example checks every result. Its invalid-depth scenario supplies a NaN size and expects INVALID_ARGUMENT with the earlier workspace revision and depth state retained.



## Separate structure from feed policy

| Shared check | Adapter responsibility |
| --- | --- |
| Bounded canonical instrument | Provider identity mapping |
| Counts inside array capacity | Level ordering |
| Finite active prices | Crossed-book policy |
| Finite nonnegative sizes | Freshness and timestamp interpretation |



Finite negative prices, zero sizes and empty sides are supported structural values. Inactive array tails are ignored. Do not invent a positive-price rule for every market merely because one risk model uses positive prices. Conversely, structural acceptance does not certify that a provider sorted its levels or supplied current data.



## Compare complete contract metadata

The metadata scenario changes the multiplier while retaining the identifier. Standalone depth validation still succeeds, but the workspace rejects the mismatch against its registered instrument. A stable identifier cannot silently replace the economic meaning of a contract.



## Exercise and answer

The best-bid accessor returns zero. Is the bid absent? The value alone cannot answer: zero is also a supported price. Inspect validation and bid_count first. The accessor reads the first active level and relies on the adapter to establish its ordering contract.



## Complete source and owner commands

[Open the laboratory guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/order-lifecycle/README.md). Offline, use labs/framework/order-lifecycle/README.md. Installed-SDK builds, scenario checks and native presentation require owner execution.

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [HTML edition](../../../../courses/framework-and-finance/trading-and-posttrade/lessons/23-validate-depth-before-lookup.html)
