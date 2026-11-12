<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/19-separate-validity-from-capability.md

PURPOSE:
Separate a valid request from a supported capability

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../../assets/branding/umicom-logo.svg)

# Separate a valid request from a supported capability

## Validation answers a narrower question

A time-in-force enum can be valid even when a particular service cannot implement its behavior. Framework declares DAY, GTC, IOC and FOK because requests and external providers need that vocabulary. The local retained-order service has no immediate matching transaction. Accepting an IOC or FOK request as an ordinary resting order would silently change its meaning.

## Read the shared boundary

~~~c
UmiStatus status = UmiTimeInForceCheckLocalRetention(request.tif);
/* IOC and FOK return UMI_STATUS_NOT_IMPLEMENTED for this local model. */
~~~

The new helper checks a local capability rather than changing umi_time_in_force_valid. This preserves the generic request contract for other providers. The local broker and workspace call the same helper before retaining a new order. An external adapter must report and enforce its own supported policies; this helper is not a registry of venue capabilities.

## Keep the remaining behavior explicit

| Request | Local model |
| --- | --- |
| DAY | Can retain a resting request; caller owns session-end cancellation |
| GTC | Can retain a resting request until caller cancellation or session destruction |
| IOC | Refused because immediate fill and remainder handling are absent |
| FOK | Refused because immediate all-or-none matching is absent |

DAY acceptance does not mean that a calendar timer has been installed. The local model does not supply automatic expiry, durable restart behavior or a broker acknowledgement. Keeping these limits visible is more useful than presenting an enum choice as a completed feature.

## Exercise and answer

Should the client replace FOK with DAY after receiving NOT_IMPLEMENTED? No. That changes the requested behavior. Preserve the draft and explain the unsupported local capability. The user can deliberately choose a supported policy or an appropriate provider; the application must not silently reinterpret the request.

## Run the owned example

The existing execution laboratory now has policy-ioc and policy-fok scenarios. They prepare a synthetic draft and inspect a denied preview and submission result before any fill is constructed. The scenarios are authored checks awaiting an owner build and run.

## Complete source and owner commands

[Open the laboratory guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/order-lifecycle/README.md). Offline, use labs/framework/order-lifecycle/README.md. Source and expected outcomes are supplied; installed-SDK builds, tests and native presentation await owner execution.

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [HTML edition](../../../../courses/framework-and-finance/trading-and-posttrade/lessons/19-separate-validity-from-capability.html)
