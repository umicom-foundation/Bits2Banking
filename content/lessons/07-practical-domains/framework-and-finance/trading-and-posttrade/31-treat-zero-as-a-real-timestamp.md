<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/31-treat-zero-as-a-real-timestamp.md

PURPOSE:
Treat zero as a real timestamp in an attempt quota

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

# Treat zero as a real timestamp in an attempt quota

## An unused state needs its own meaning

Timestamp zero is a valid point in a local monotonic clock domain. If a throttle interprets window_start_ms equal to zero as unused on every call, repeated calls at zero keep restarting the window. The counter can fail to enforce its intended limit.


## Follow the fixed-window example

| Time in milliseconds | Expected result | Count after the call |
| --- | --- | --- |
| 0 | Admit | 1 |
| 0 | Admit | 2 |
| 0 | Refuse | 2 |
| 999 | Refuse | 2 |
| 1000 | Admit in a new window | 1 |


~~~c
UmiOrderThrottle throttle;
umi_order_throttle_init(&throttle, 2U, 1000);
int first = umi_order_throttle_accept(&throttle, 0);
int second = umi_order_throttle_accept(&throttle, 0);
int third = umi_order_throttle_accept(&throttle, 0);
/* Expected: first and second are nonzero; third is zero. */
~~~


The accepted count now identifies an unused window. A zero count starts the next accepted window at the supplied time. Negative time, a timestamp before the active window start, invalid configuration, damaged count or exhausted quota refuses without mutation. The implementation orders admitted nonnegative timestamps before subtracting them.


## State what this clock check cannot prove

The record remembers the window start rather than every call time. It therefore cannot detect every backwards movement within a window. Use one monotonic clock domain and enforce stronger sequencing in the clock owner when required. This local service is not a distributed quota shared across processes.


## An attempt is not an accepted order

The reference OMS checks its kill switch before consuming an attempt. After the throttle admits, a later request-validation, risk or storage refusal still consumes that attempt. That existing policy limits attempted submissions. Moving the quota after validation would change the policy rather than merely repair arithmetic.


## Exercise and answer

A request consumes the last attempt and is then rejected for invalid quantity. Should the client subtract one from the throttle count? No. The OMS policy already chose attempt accounting. Correct the input and follow the configured retry timing; do not mutate the service record to disguise the refusal. The quota scenario uses no real order or broker.

## Complete source and qualification commands

[Open the laboratory guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/order-lifecycle/README.md). Offline, use labs/framework/order-lifecycle/README.md and identity_lifetime.c. Compilation, installed SDK linking and execution remain separate qualification steps.

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [HTML edition](../../../../courses/framework-and-finance/trading-and-posttrade/lessons/31-treat-zero-as-a-real-timestamp.html)
