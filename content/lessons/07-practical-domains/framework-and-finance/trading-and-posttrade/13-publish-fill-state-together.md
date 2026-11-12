<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/13-publish-fill-state-together.md

PURPOSE:
Publish the order, position and fill evidence together

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../../assets/branding/umicom-logo.svg)

# Publish the order, position and fill evidence together

## One event changes several views

A partial fill changes how much of an order remains open. It also changes the instrument position and adds evidence to the execution history. If an application updates only the displayed order, the position can disagree. Framework therefore prepares the combined change inside the workspace rather than asking each screen to perform its own arithmetic.

## Trace the actual sequence

- Validate the report and check retained execution identity.
- Admit history capacity and a workspace revision for a new event.
- Find the order through the bounded canonical order store.
- Prepare an order candidate and a position candidate without publishing them.
- Retain the report after every earlier calculation has succeeded.
- Copy the prepared values into the owner and advance its revision.

The final copies cannot fail under serialized owner access. This is why the report can be retained immediately before publication. Adding allocation or another fallible operation after that point would require redesigning the transaction. A comment saying atomic is not enough; inspect where each failure can return.

## Read, then explain

~~~c
UmiStatus status = umi_trading_workspace_record_execution(workspace, &report);
/* On success, read both the workspace snapshot and the position. */
UmiPosition position;
UmiStatus read_status = umi_trading_workspace_position_at(workspace, 0U, &position);
~~~

The complete partial scenario requests two units and supplies a one-unit fill at price ten. It expects one execution, one position and a position quantity of one. The fill does not imply that both requested units traded. Check the return codes before interpreting either output value.

## Exercise and answer

Where should a capacity failure be detected if the position book is full? Before the execution report is retained. Otherwise the history would claim an accepted event while the corresponding position is absent. The admission regression fixture injects this state into the real owner and checks that refusal preserves its value fields.

## Know the limit

This transaction coordinates in-memory state. It is not a cross-process lock or durable database commit. A production ingestion layer must define synchronization, durable evidence and recovery separately.

## Use the complete laboratory

[Read the source, owner commands and expected results](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/order-lifecycle/README.md). In an offline checkout, open labs/framework/order-lifecycle/README.md. Build and runtime qualification remains unexecuted for this authored continuation.

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [HTML edition](../../../../courses/framework-and-finance/trading-and-posttrade/lessons/13-publish-fill-state-together.html)
