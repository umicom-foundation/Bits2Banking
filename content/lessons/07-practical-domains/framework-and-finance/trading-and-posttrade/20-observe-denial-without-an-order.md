<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/20-observe-denial-without-an-order.md

PURPOSE:
Retain a useful denial without creating an order

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../../assets/branding/umicom-logo.svg)

# Retain a useful denial without creating an order

## A refusal can still be an observation

A user needs to know why a command was refused. The workspace can retain a denied preview while leaving its order book unchanged. These are different effects: publishing a local explanation is not accepting an order. The policy scenarios check both the returned status and the resulting owner state.

## Follow the sequence

- Create a synthetic local workspace and select a valid instrument.
- Set the draft policy to IOC or FOK without rewriting it.
- Request a preview and expect NOT_IMPLEMENTED with allowed set to false.
- Submit the same draft and expect the same unsupported result.
- Read the snapshot: the draft policy remains, but orders, executions and positions are still absent.
- Inspect risk evidence: the refusal has no fabricated valuation.

Each accepted denial observation advances the available workspace revision once. It does not allocate an order identifier or consume OMS throttle. The internal regression fixture checks those private owner details directly; the public laboratory observes the snapshot and risk-evidence contracts without reaching inside the opaque workspace.

## Handle the result deliberately

~~~c
UmiRiskDecision decision;
UmiStatus status = UmiTradingWorkspacePreviewOrderAt(workspace, 1000, &decision);
if (status == UMI_STATUS_NOT_IMPLEMENTED) {
    /* Display the retained capability explanation and keep the draft. */
}
~~~

At an exhausted owner revision, even a new explanation cannot be published safely. The command returns CAPACITY_EXCEEDED without changing owner or output. Do not read an uninitialized decision after that failure. Check which result contract produced the value you intend to display.

## Exercise and answer

Why does a disabled Submit control not replace the command check? UI state can become stale, and another client can call the service directly. The affordance describes current capability; the command remains responsible for enforcing the boundary when invoked.

## Qualification

Record the source and SDK identities alongside the named scenario results. A retained refusal demonstrates a local policy boundary. It does not prove automatic expiry, exchange matching or native keyboard and mouse behavior.

## Complete source and owner commands

[Open the laboratory guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/order-lifecycle/README.md). Offline, use labs/framework/order-lifecycle/README.md. Source and expected outcomes are supplied; installed-SDK builds, tests and native presentation await owner execution.

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [HTML edition](../../../../courses/framework-and-finance/trading-and-posttrade/lessons/20-observe-denial-without-an-order.html)
