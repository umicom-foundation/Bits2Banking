<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/26-preserve-protective-actions-and-status.md

PURPOSE:
Keep protective actions available and report their status

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../../assets/branding/umicom-logo.svg)

# Keep protective actions available and report their status

## A display counter must not block protection

Most edits need a new observation number before changing state. A kill switch and live disarming have a different responsibility: they must still take effect when the counter cannot advance. Framework retains those protective effects and saturates the revision at its maximum. Resetting the switch or arming live mode releases a gate and therefore requires representable capacity.



## Use the shared controller

~~~c
UmiStatus status = umi_trading_ui_controller_reset_kill_switch(&controller);
/* Inspect status and controller.state.last_status before showing success. */
~~~



The protect scenario initializes the toolkit-neutral action controller, engages the switch, reads its effect and performs a checked reset. It opens no native window and contacts no broker. A local kill switch is not an acknowledgement that external orders were cancelled. Applications must keep external reconciliation separate.



## Distinguish a callback from success

The controller records its status and message before notifying the view. Rejections notify too, because an operator needs to see a refused command. An observer that treats every callback as a successful reset can display the opposite of the actual protective state. Read the returned status and fresh snapshot instead.



## Know the compatibility boundary

| Interface | How to interpret it |
| --- | --- |
| Checked workspace reset | Inspect its returned status |
| Shared UI controller | Inspect last_status and the snapshot |
| Legacy void reset | Do not infer success from return; read resulting state |



At the maximum revision, protective fields may change while the number remains fixed. Refresh them directly. A session-report current check conservatively returns false there, although the historical report remains readable. Exact revision formatting does not remove this lifetime and freshness limitation.



## Exercise and answer

Should an application convert a refused reset into a direct write to the switch field? No. That bypasses the owner contract. Leave protection engaged, explain the refusal and use the application session-retirement workflow. The ordinary protect scenario and the separate Framework capacity tests qualify different boundaries.



## Complete source and owner commands

[Open the laboratory guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/order-lifecycle/README.md). Offline, use labs/framework/order-lifecycle/README.md. Installed-SDK builds, scenario checks and native presentation require owner execution.

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [HTML edition](../../../../courses/framework-and-finance/trading-and-posttrade/lessons/26-preserve-protective-actions-and-status.html)
