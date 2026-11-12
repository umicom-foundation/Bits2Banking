<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/27-handle-refusal-without-resetting-owners.md

PURPOSE:
Handle refusal without resetting the owner in place

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../../assets/branding/umicom-logo.svg)

# Handle refusal without resetting the owner in place

## An error result describes a boundary

A client should distinguish malformed input, unsupported local behavior and exhausted observation capacity. These results call for different responses. Silently replacing an invalid value, changing a requested policy or resetting a revision counter can make a screen appear successful while changing the meaning of the command.



## Use a temporary proposal

- Keep the proposed input separate from the last accepted snapshot.
- Call the canonical Framework command.
- On success, refresh the view from the owner.
- On refusal, retain accepted state and show the specific returned status.
- Retire an exhausted owner through a deliberate lifecycle workflow.



The draft scenario illustrates evidence invalidation after an accepted edit. It previews a synthetic ticket, confirms that evidence exists, then changes quantity. The earlier risk evidence becomes unavailable because it described the previous ticket. Submission still performs its own evaluation; an old preview is not a transferable approval token.



## Read the changed evidence

~~~c
UmiStatus edit = umi_trading_workspace_set_draft_quantity(workspace, 2.0);
/* After an accepted edit, the previous preview is no longer current. */
UmiStatus evidence = UmiTradingWorkspaceRiskEvidence(workspace, &copy);
~~~



The expected evidence result in this sequence is NOT_FOUND. At revision capacity, by contrast, a refused draft edit leaves the previous ticket and evidence intact. The public example does not manufacture capacity by accessing private workspace storage. Framework regression fixtures inject that boundary separately.



## Build the complete client

The laboratory uses the exported trading, ui and trading_ui components. Reconfigure against one matching SDK after integrating the new shared APIs, build btb-market-observation and run its eight named scenarios. A missing symbol requires checking SDK header/library identity, not copying an isolated header or weakening a check.



## Exercise and answer

Does a fresh workspace continue the retired one automatically? No. It has a new lifetime. Preserve needed records, reconcile provider sequence and account state deliberately, and qualify restoration separately. The current example is synthetic and does not implement durable restart or external reconciliation.



## Record actual evidence

Keep source identity, command, expected result and observed result together. Until the owner executes the build and tests, the example remains authored source with expected outcomes. Native views require their own presentation and lifecycle checks.



## Complete source and owner commands

[Open the laboratory guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/order-lifecycle/README.md). Offline, use labs/framework/order-lifecycle/README.md. Installed-SDK builds, scenario checks and native presentation require owner execution.

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [HTML edition](../../../../courses/framework-and-finance/trading-and-posttrade/lessons/27-handle-refusal-without-resetting-owners.html)

Continue with [Distinguish an instrument identity from its array position](28-distinguish-identity-from-array-position.md).
