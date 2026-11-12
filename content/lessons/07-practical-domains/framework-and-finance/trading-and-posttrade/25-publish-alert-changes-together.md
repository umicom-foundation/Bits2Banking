<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/25-publish-alert-changes-together.md

PURPOSE:
Observe crossings and remove dependent alerts together

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../../assets/branding/umicom-logo.svg)

# Observe crossings and remove dependent alerts together

## Seed a rule before observing a crossing

An alert compares successive observations against a threshold. Creating a rule should not invent a crossing from an unknown starting value. The workspace seeds a new rule from its current quote midpoint. The alerts scenario begins at midpoint 100, creates an above-101 rule, then publishes midpoint 102 at a later event time.



## Inspect the activation

~~~c
UmiStatus status = umi_trading_workspace_add_price_alert(
    workspace, "price-crossing", instrument.instrument_id.value,
    UMI_TRADING_PRICE_ALERT_CROSSES_ABOVE, 101, 1000);
~~~



After checking the result and publishing the later quote, the client expects one active, unacknowledged alert. Acknowledgement clears the active notification while retaining the rule and its history. It does not delete the instrument or create an order. Disabled rules continue following observations under the shared contract so resuming them does not invent a stale crossing.



## Reserve the child revision

The alert book owns a revision independently of the workspace. Evaluation first identifies eligible rules, then reserves capacity before updating any row. A stale or nonmatching observation is a no-op. If a required child change is refused, the workspace must not replace its quote while pretending dependent evaluation succeeded.



## Remove dependent state deliberately

The remove scenario adds a public print and then removes the instrument. Framework prepares a private alert-book copy, applies one canonical removal batch, asks the tape to remove matching records and only then publishes the prepared book and compacts the market arrays. Allocation or child-capacity failure leaves the earlier owners intact.



## Exercise and answer

Why not loop over alert IDs in the application and ignore individual failures? The UI would own a second transaction policy, and a partial loop could leave alerts for an instrument already removed from view. Reuse the workspace command and report its returned status.



## Qualification boundary

Run the alerts and remove scenarios against the matching SDK. The example demonstrates ordinary behavior; Framework boundary fixtures separately inject allocation failure, malformed retained rules and exhausted child revisions. Both layers still require execution.



## Complete source and owner commands

[Open the laboratory guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/order-lifecycle/README.md). Offline, use labs/framework/order-lifecycle/README.md. Installed-SDK builds, scenario checks and native presentation require owner execution.

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [HTML edition](../../../../courses/framework-and-finance/trading-and-posttrade/lessons/25-publish-alert-changes-together.html)
