<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/61-check-native-release-without-retrying-handles.md

PURPOSE:
Teach check native release without retrying handles through the installed Framework media client.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-logo.svg)

# Check native release without retrying handles

## Finish the ownership protocol

Closing a native handle is an operation with a result. Ignoring that result can turn an incomplete operation into a misleading success report. Framework now uses the private BmCloseResult boundary when completing inspection, transfer and comparison. Application code still calls the public media service; it must not adopt this private transport helper as an installed API.


~~~c
UmiStatus targetClose = BmCloseResult(target);
UmiStatus sourceClose = BmCloseResult(source);
if (s == UMI_STATUS_OK) s = targetClose;
if (s == UMI_STATUS_OK) s = sourceClose;
~~~


## Preserve the first failure

Both owned wrappers receive a close attempt even if the first attempt fails. An earlier write or read error remains the primary result. If all earlier work succeeded, destination close failure takes precedence over source close failure. The report cannot mark verified when one of these required release operations fails. This preserves useful diagnosis without pretending cleanup can undo previous writes.


## Do not reuse consumed ownership

The helper consumes its wrapper on every result. On Linux it attempts close once because a descriptor may already have been released and reused when an error is reported. Retrying the numeric descriptor could affect another file. Windows held-volume handles are each attempted even after an earlier failure. A failed attempt does not prove the native resource was released; the consumed wrapper must nevertheless never be dereferenced again.


## Trace the regression boundary

- Read test_close_observation.c: synthetic handles never reach an operating-system close.
- Read test_read_close.c and find the case where source release failure prevents comparison-target acquisition.
- Explain why an injected error test is useful but does not prove behaviour of your real filesystem or removable device.


## References and limits

Consult the Linux close manual and Microsoft CloseHandle documentation linked from the Framework boot-media guide. Successful close is not a substitute for flush, readback or a boot test. The lab consumes the resulting public status; native-platform qualification remains a separate owner-run exercise.

[Complete application](../../../../labs/native/framework-boot-media/main.c) · [Lab setup and recovery](../../../../labs/native/framework-boot-media/README.md)

[Course contents](index.md) · [Previous lesson](60-interpret-cancellation-after-payload-writing.md) · [Next lesson](62-retain-failed-media-artifacts-for-recovery.md)
