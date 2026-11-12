<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/24-observe-public-prints-without-fills.md

PURPOSE:
Pause public prints without inventing account fills

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../../assets/branding/umicom-logo.svg)

# Pause public prints without inventing account fills

## Give each sequence a clear meaning

The public trade tape orders records by a provider-supplied sequence. This sequence is different from an execution identifier and from the workspace revision. A sequence gap records missing provider evidence; it does not create a synthetic account fill to compensate. The tape scenario publishes sequence 1 followed by sequence 3 so the distinction is visible.



## Retain while the view is paused

~~~c
umi_trading_workspace_set_trade_tape_paused(workspace, 1);
/* Check the result, then publish the next validated public print. */
umi_trading_workspace_snapshot(workspace, &snapshot);
~~~



The complete client checks both calls. Pausing freezes the visible sequence boundary, while ingestion may continue. After the second print, the expected retained count is two and the missing-sequence count is one. The paused selection still exposes sequence 1. Resuming makes sequence 3 the newest visible print without requesting a resend.



## Read the observations separately

| Observation | What it establishes |
| --- | --- |
| retained_count | Rows still stored in the bounded tape |
| selected_trade_count | Rows visible for the selected instrument |
| missing_sequence_count | Observed gaps in accepted provider sequence |
| execution_count | Account execution records, separate from public prints |



A full retained window and a full revision counter are different conditions. Normal row capacity discards the oldest row under the tape contract. Revision exhaustion refuses a new data edit before changing rows or diagnostic counters. Provider availability can still be observed while its revision saturates; a maximum revision is therefore unsuitable as the sole readiness cache key.



## Exercise and answer

Should resuming a paused view replay prints through the account execution API? No. It changes presentation of already retained public data. The expected execution and position counts remain zero throughout this scenario.



## Run the scenario

After an owner build, run btb-market-observation tape. The program checks retained and visible counts as well as account isolation. These are expected outcomes, not captured runtime evidence.



## Complete source and owner commands

[Open the laboratory guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/order-lifecycle/README.md). Offline, use labs/framework/order-lifecycle/README.md. Installed-SDK builds, scenario checks and native presentation require owner execution.

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [HTML edition](../../../../courses/framework-and-finance/trading-and-posttrade/lessons/24-observe-public-prints-without-fills.html)
