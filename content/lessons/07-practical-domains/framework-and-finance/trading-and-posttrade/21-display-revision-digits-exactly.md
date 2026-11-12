<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/21-display-revision-digits-exactly.md

PURPOSE:
Display revision digits without signed casts or rounding

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../../assets/branding/umicom-logo.svg)

# Display revision digits without signed casts or rounding

## The display type has a range too

An owner revision can use all 64 unsigned bits. A signed 64-bit UI integer cannot represent the upper half of that range. Casting does not extend the destination type, and using a floating-point value can lose individual integer digits. An identity must remain exact even when it is shown rather than calculated.

## Reuse the Framework value owner

~~~c
UmiUiValue value;
UmiStatus status = UmiUiValueSetUnsigned(&value, UINT64_MAX);
/* The result is STRING: "18446744073709551615". */
~~~

UmiUiValueSetUnsigned stores values through INT64_MAX as the existing INTEGER kind. Larger values become canonical decimal STRING values. It changes neither the value layout nor its enum kinds. Consumers of a property using this contract must accept both forms and should not perform owner mutations from a display value.

## Read the complete client

The revision_value.c example in the existing laboratory demonstrates small, boundary and maximum observations. It calls Framework to construct the value, checks its kind and exact content, and prints the result. It does not copy the conversion algorithm, change a workspace revision or open a native window.

## Compare the boundaries

| Input | Expected kind | Expected display |
| --- | --- | --- |
| 42 | INTEGER | 42 |
| 9223372036854775808 | STRING | 9223372036854775808 |
| 18446744073709551615 | STRING | 18446744073709551615 |

The generic native property renderer already has integer and string display branches. That source path explains why the shared value fits the existing rendering model. A real native-window qualification is still required before claiming that a particular screen shows the result correctly.

## Exercise and answer

Is a decimal string suitable as a global revision identity by itself? No. The revision still belongs to one owner and its lifetime. Exact formatting preserves digits; it does not add owner identity, ordering across services or authority to replay a command.

## Run and interpret

After building the laboratory against a matching SDK, run btb-revision-value maximum and the learning.trading.revision-value tests. The output above is expected, not captured evidence. A missing symbol indicates that headers and libraries may come from different SDK revisions; install the complete matching SDK.

## Complete source and owner commands

[Open the laboratory guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/order-lifecycle/README.md). Offline, use labs/framework/order-lifecycle/README.md. Source and expected outcomes are supplied; installed-SDK builds, tests and native presentation await owner execution.

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [HTML edition](../../../../courses/framework-and-finance/trading-and-posttrade/lessons/21-display-revision-digits-exactly.html)

[Next: Build a market-observation client around one Framework owner](22-own-a-market-observation-client.md)
