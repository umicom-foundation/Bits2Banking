<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/32-move-chart-state-with-instrument-identity.md

PURPOSE:
Move chart state with the instrument identity

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

# Move chart state with the instrument identity

## Several arrays describe one logical row

The workspace retains market records, candle histories, watchlist instruments and chart navigation in parallel arrays. Each index must refer to the same instrument across all of them. Navigation includes visible bar count, pinned timestamp, pin state and selected interval.


## Trace the removal defect

If removing the first market moves prices and candles but leaves navigation behind, the surviving instrument can inherit the removed chart view. All the numeric fields may still be valid. The error is the association between state and identity. A validator for individual navigation values cannot repair that relationship.


## Use the canonical command

~~~c
UmiChartNavigation view = {9U, 3000, 1, 900000U};
UmiStatus status = umi_trading_workspace_select_instrument(workspace, "LAB.B");
if (status == UMI_STATUS_OK)
    status = UmiTradingWorkspaceSetChartNavigation(workspace, "LAB.B", &view);
/* Check status, then remove LAB.A through the workspace service. */
~~~


The navigation scenario removes LAB.A while LAB.B is selected. It then reads LAB.B again and compares all four fields. Framework compacts navigation with the other arrays, clears the retired tail and initializes a new instrument view. Adding LAB.A again must produce default navigation rather than inherit LAB.B.


## Understand a default view

A zero navigation value follows the newest retained candle, fits the retained range and uses the provider source interval. This is a presentation rule. It does not fetch prices or guarantee that data is fresh. A selected-chart operation also checks that its captured instrument is still selected before applying an edit.


## Keep related lifecycle owners explicit

Instrument removal is not a general chart-document purge. Drawings, saved documents, undo history and provider subscriptions have separate contracts. The navigation repair makes no claim that those records are deleted or that a broker has acknowledged an unsubscribe.


## Exercise and answer

Why test removal of the last row separately? No array compaction is needed there, but stale tail state can still leak into a later addition. Test first, middle, last and sole removal, then re-add an instrument and inspect its default view. Framework regression fixtures cover these cases beyond the small installed-client demonstration.

## Complete source and qualification commands

[Open the laboratory guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/order-lifecycle/README.md). Offline, use labs/framework/order-lifecycle/README.md and identity_lifetime.c. Compilation, installed SDK linking and execution remain separate qualification steps.

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [HTML edition](../../../../courses/framework-and-finance/trading-and-posttrade/lessons/32-move-chart-state-with-instrument-identity.html)
