<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/11-own-a-workspace-execution-session.md

PURPOSE:
Own a workspace for a local execution session

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../../assets/branding/umicom-logo.svg)

# Own a workspace for a local execution session

## Start with one owner

The earlier laboratory used a simulated broker table to retain and cancel requests. A fill needs more context: an order, a position and execution history must agree. The Framework trading workspace owns that combined local state. The application receives an opaque pointer, which means it uses public functions instead of editing the private structure.

Open labs/framework/order-lifecycle/execution.c. The program creates one workspace, adds a synthetic instrument and prepares a limit order. The health flags select local availability for this demonstration; setting them does not connect an account or make a real broker ready. The default workspace environment is simulation.

## Make lifetime visible

~~~c
UmiTradingWorkspace *workspace = NULL;
UmiTradingWorkspaceConfig config = umi_trading_workspace_config_default();
UmiStatus status = umi_trading_workspace_create(&config, &workspace);
/* Check status before using workspace. */
umi_trading_workspace_destroy(workspace);
~~~

The complete example checks every operation and uses one finish label to destroy the workspace after either success or failure. Its REQUIRE_EXECUTION macro remains active in release builds. Ordinary assert statements can disappear when NDEBUG is defined; placing required service calls only inside assert would change what the example actually does.

## Keep the client small

- Construct input values and select the local scenario.
- Call Framework for validation, submission, execution and cancellation.
- Read snapshots and positions to explain the result.
- Release the owner after its last use.

## Exercise and answer

Why does execution.c not copy the workspace structure into the course repository? A copied layout would drift from Framework and invite a second implementation. The public pointer and exported trading target keep ownership in the shared service. The regression fixtures may include the real implementation for fault injection, but this installed-SDK client deliberately uses only public APIs.

## Expected boundary

A successful local run demonstrates that the installed workspace API satisfies these synthetic checks. It does not establish a GUI workflow, market connectivity, persistence or settlement. Record the SDK and executable identities when the owner runs the example.

## Use the complete laboratory

[Read the source, owner commands and expected results](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/order-lifecycle/README.md). In an offline checkout, open labs/framework/order-lifecycle/README.md. Build and runtime qualification remains unexecuted for this authored continuation.

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [HTML edition](../../../../courses/framework-and-finance/trading-and-posttrade/lessons/11-own-a-workspace-execution-session.html)
