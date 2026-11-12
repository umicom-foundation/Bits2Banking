<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/50-format-device-labels-without-splitting-utf8.md

PURPOSE:
Teach format device labels without splitting utf-8 through the shared native media adapter.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Format device labels without splitting UTF-8

![Umicom](../../../assets/branding/umicom-wordmark-on-dark.svg)

## Prepare the label boundary exercise

A device path is text encoded as bytes. UTF-8 uses one to four bytes for a Unicode character. A byte count that happens to fall inside a character cannot safely be used as a display truncation boundary. Open MediaDeviceLabel in the Framework Windows boot-media adapter and compare its preserved predecessor in Finish.

The --check-labels mode supplies synthetic strings to the real native conversion path. It does not open those paths. The check is authored and requires owner execution before any runtime result can be claimed.

## Why a bounded printf can still lose a row

The former label used %.127s for the path. That prevents reading an unlimited string into the formatted label, but precision counts bytes, not Unicode characters. If a three-byte euro sign begins at byte 126, the projection includes only its first byte. Strict UTF-8 conversion then rejects the whole label.

Relaxing Unicode validation would hide the damaged data instead of fixing its cause. The replacement first proves that each fixed array contains a terminator, formats every complete field into a sufficiently large temporary buffer and converts the complete result with MB_ERR_INVALID_CHARS.

## Separate the two capacity contracts

The temporary label capacity covers the full path, model, serial and reason plus separators and the largest displayed decimal byte count. snprintf reports whether the byte buffer was sufficient. MultiByteToWideChar separately receives the destination's capacity in wchar_t elements.

~~~c
int length = snprintf(label, sizeof label,
    "%s | %s | %s | %llu bytes | %s",
    device->path, device->model, device->serial,
    (unsigned long long)device->bytes, device->reason);
if (length < 0 || (size_t)length >= sizeof label) return 0;
return MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS,
    label, -1, wide, capacity) > 0;
~~~

This excerpt follows bounded terminator checks for all four source arrays. The negative return check occurs before converting length to size_t. The explicit unsigned long long cast matches %llu. A nonzero result means conversion succeeded; it does not establish that the path names a device.

## Exercise boundary cases, not only ordinary names

1. Place a three-byte euro sign across the old 127-byte precision boundary and require the complete character and .img suffix to survive.
2. Offer one UTF-16 element for a longer label and require refusal.
3. Supply invalid UTF-8 and require refusal rather than substitution.
4. Fill each source array without a zero terminator in turn and require refusal before formatting.
5. Fill every field to its documented maximum and use UINT64_MAX for the byte count; the complete label should still fit its designed buffer.

## Exercise and answer

Would replacing %.127s with %s alone solve the problem? Answer: only if the input arrays are known to terminate and the destination is large enough with checked formatting. Without those prerequisites, the new code could read outside an array or silently truncate a different part of the label.

If a product later needs visual shortening, perform it at a character boundary and retain an accessible complete value for review. The current adapter chooses complete bounded fields. Selection identity remains separately bound to inventory item data, so a conversion refusal cannot shift a later row onto the wrong device.

[Read the complete native adapter](https://github.com/umicom-foundation/umicom-framework/blob/main/adapters/win32/boot_media.c) · [Media guide](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/development/boot-media.md)

[Microsoft: CB_ADDSTRING](https://learn.microsoft.com/en-us/windows/win32/controls/cb-addstring) · [Microsoft: CB_SETITEMDATA](https://learn.microsoft.com/en-us/windows/win32/controls/cb-setitemdata) · [Microsoft: MultiByteToWideChar](https://learn.microsoft.com/en-us/windows/win32/api/stringapiset/nf-stringapiset-multibytetowidechar)

[Course contents](index.md) · [Previous lesson](49-bind-device-rows-to-inventory-identity.md)


[Continue: Connect an owned image read port](51-connect-an-owned-image-read-port.md)
