<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/140-read-a-declared-hardware-timebase.md

PURPOSE:
Read a declared hardware timebase

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Read a declared hardware timebase

Imagine a form that asks for the speed of a clock. An empty answer tells you nobody supplied a value. A written zero is an answer you can inspect. Umicom Kernel keeps those observations separate when it reads a hardware timebase.

## 1. Give the setting a unit

A **timebase** is a clock whose ticks can be counted. A frequency measured in **hertz** tells you how many ticks occur in one second. For this exercise the test's clock value is ten million ticks per second, or 10 MHz.

The Kernel's flattened device-tree reader obtains `timebase-frequency` from the `/cpus` node when the setting is present. The hardware catalogue is the Kernel's collected description of the platform. It uses a stored zero to represent an absent observation.

| Synthetic input | Catalogue interpretation |
| --- | --- |
| `/cpus` exists and the property is absent | Keep the absent observation. |
| Four bytes `00 98 96 80` | Record 10,000,000 ticks per second. |
| Four bytes `00 00 00 00` | Refuse the declared zero. |

The bytes in the table are written in big-endian order. The most significant byte comes first. A four-byte field is a fixed-width encoding. A field with the wrong width also needs an error result.

## 2. Keep presence with the value

Ask two questions about a zero first. Was the property present? Did the numeric reader accept its width? The shared numeric reader already handles width. The catalogue checks presence when the returned value could mean either absence or an explicitly declared zero.

~~~text
READ the numeric property using the existing width check
IF the numeric read fails, report that error
IF the result is zero and the property was present, refuse the value
OTHERWISE keep the accepted value or the absent observation
~~~

An error protects the caller from mistaking a refused update for a fresh catalogue. The host regression supplies a previously successful result, changes the synthetic property to zero, and checks that the stale ready catalogue was cleared.

## 3. Compare three host cases

Use the same configured `tests/hardware_catalogue` build from the previous lesson.

~~~powershell
ctest --test-dir $hardwareBuild --output-on-failure -R '^hardware[.](zero_timebase|malformed_timebase|missing_timebase)$'
~~~

The mirror's selected host run passed all three controls. Do the same exercise on paper for an optional sampling frequency in an Umicom application. Decide how your interface would display absence, a valid number and a value the reader refused. Record the observed frequency separately when you later test real firmware.

[Course contents](index.md) · [Previous lesson · Find a short device-tree path after a long branch](139-find-a-short-device-tree-path-after-a-long-branch.md) · [Next lesson · Order page permission changes](141-order-page-permission-changes.md) · [HTML edition](../../../courses/umicom-kernel-from-scratch/lessons/140-read-a-declared-hardware-timebase.html)
