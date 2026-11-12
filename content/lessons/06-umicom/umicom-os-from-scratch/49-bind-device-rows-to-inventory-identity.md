<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/49-bind-device-rows-to-inventory-identity.md

PURPOSE:
Teach bind device rows to inventory identity through the shared native media adapter.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Bind device rows to inventory identity

![Umicom](../../../assets/branding/umicom-wordmark-on-dark.svg)

## Prepare a source review

A media-writing interface must identify the device the user actually selected. Open adapters/win32/boot_media.c in Umicom Framework and locate PopulateDevices, SelectedDevice and Start. This is the existing Windows Boot Media Centre; the exercise does not create a new screen layout or grant permission to write a disk.

Read the shared boot-media guide first. The native --check-selection mode constructs hidden controls and synthetic observations. It is an owner-run acceptance check, not an executed result in this lesson. Keep physical-device writing disabled while studying presentation behavior.

## Watch an index become misleading

Imagine an inventory containing devices A, B and C. A has a label that cannot be converted to Unicode, so the dropdown shows B and C as rows zero and one. Using selected row zero directly as the inventory index would retrieve A, even though the user selected B.

The old code made exactly that assumption. It remains in an explained disabled block. The replacement attaches an explicit key to each successfully added row. A row can move or an earlier row can disappear without changing that association.

## Attach a key only after insertion succeeds

CB_ADDSTRING returns the row that was added, or an error. Bind data to that returned row rather than assuming insertion succeeded. The adapter stores index plus one, keeping zero available to mean unbound.

~~~c
LRESULT row = SendMessageW(list, CB_ADDSTRING, 0, (LPARAM)wide);
if (row < 0) continue;
if (SendMessageW(list, CB_SETITEMDATA, (WPARAM)row,
        (LPARAM)(i + 1U)) == CB_ERR) {
    SendMessageW(list, CB_DELETESTRING, (WPARAM)row, 0);
    continue;
}
~~~

This excerpt belongs inside PopulateDevices, where the inventory is bounded and the complete label has already been converted. The row is removed if the binding cannot be established. A displayed but unbound row must not become a usable review target.

## Resolve the selection through its owner

1. Retrieve the selected row and refuse no-selection or control errors.
2. Read its item data and require a key from one through the current inventory count.
3. Convert the admitted key back to an inventory index and copy that observation into the owned worker job.
4. Enable Review only when a bound selection exists. A refreshed inventory clears the selection and requires a new review.

## Keep presentation and device authority separate

Correct row binding fixes which observation is reviewed. It does not prove that the observation is still true. The shared service re-observes identity and geometry, binds the image and destination into a plan, and checks the required confirmation before an enabled transfer.

The synthetic regression removes the first visible row, selects the remaining row and checks that its original inventory identity survives. It also rejects zero, negative and out-of-range keys and an excessive inventory count. No device discovery or transfer is called.

## Exercise and answer

A list is sorted alphabetically after insertion. Is the visible row number now a safe inventory key? Answer: no. Sorting is another reason visual order and source identity can differ. Item data travels with the row; use the bound identity and still validate it against the current owner.

Read Microsoft's CB_ADDSTRING and CB_SETITEMDATA documentation alongside the source. Passing these synthetic checks would verify control behavior on the tested Windows environment; it would not qualify USB discovery, unplug/replug handling or a destructive write.

[Read the complete native adapter](https://github.com/umicom-foundation/umicom-framework/blob/main/adapters/win32/boot_media.c) · [Media guide](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/development/boot-media.md)

[Microsoft: CB_ADDSTRING](https://learn.microsoft.com/en-us/windows/win32/controls/cb-addstring) · [Microsoft: CB_SETITEMDATA](https://learn.microsoft.com/en-us/windows/win32/controls/cb-setitemdata) · [Microsoft: MultiByteToWideChar](https://learn.microsoft.com/en-us/windows/win32/api/stringapiset/nf-stringapiset-multibytetowidechar)

[Course contents](index.md) · [Previous lesson](48-qualify-produced-images-in-stages.md) · [Next lesson](50-format-device-labels-without-splitting-utf8.md)
