<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/ui-values-active-payload.md

PURPOSE:
Read a UI value as a kind and an owned payload

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Read a UI value as a kind and an owned payload

## Begin with the existing owner

A toolkit-neutral UI value is a record an application can copy without depending on GTK widgets. Its kind tells the reader which payload has meaning. This is useful when the same model feeds a console example, a property inspector and a native window. Framework owns the representation and copying rules; the application decides what a title or quantity means in its domain.


Before starting, be comfortable with C structs, enums, pointers and the terminating zero byte in a string. Open the laboratory main.c and the installed umicom/ui/value.h header. Find UmiUiValue, its five declared kinds and the fixed string field. The record has several fields, but only the one selected by kind is active. Avoid reading every scalar as though all fields describe the same value.


| Kind | Active meaning | Additional policy |
| --- | --- | --- |
| NONE | No active payload | Decide how absence appears |
| BOOLEAN | Stored boolean integer | Use the setter for normalized 0 or 1 |
| INTEGER | Signed 64-bit integer | Check business bounds separately |
| REAL | Floating-point observation | Decide whether NaN or infinity is permitted |
| STRING | Bounded copied bytes | Apply text encoding rules separately |


## Construct rather than guess

~~~c
UmiUiValue quantity;
UmiStatus status = umi_ui_value_set_integer(&quantity, 42);
if (status != UMI_STATUS_OK) return status;
if (!umi_ui_value_valid(&quantity)) return UMI_STATUS_INVALID_STATE;
~~~


The setter establishes deterministic inactive fields as well as the active payload. Validation recognizes the declared kind and checks a bounded terminator when STRING is active. It does not validate a trade, decode UTF-8 or grant a command permission. Keeping those responsibilities separate allows the same Framework value service to serve different products without absorbing their business rules.


## Distinguish kind validity from value validity

A converter descriptor names a source and target kind without storing either payload. It can use umi_ui_value_kind_valid. A complete value instead needs umi_ui_value_valid because a recognized STRING kind can still contain unterminated bytes. Constructing an empty dummy string merely to check a kind obscures that distinction.


## Practice and explain the result

Run the publish scenario only after building the installed client through the laboratory instructions. Identify the source record, the stored copy and the later observation. Then write a short explanation of why changing source.kind directly to 99 is a malformed fixture rather than a new application type. Do not extend the enum locally in a client header; that would invent a contract the shared library and other applications do not recognize.


For a second exercise, decide whether an unavailable temperature should be NONE or a REAL NaN in a proposed application. State the display and validation rules you would need. There is no universal choice supplied by this generic container. The important requirement is that the producer and consumer agree, and that your evidence distinguishes a valid payload from a valid domain observation.

## Source and practice

[UI value laboratory and owner commands](../../../labs/native/framework-ui-values/README.md) · [HTML edition](../../courses/umicom-development/lessons/ui-values-active-payload.html)

[Previous lesson](build-history-layered-qualification.md) · [Next lesson](ui-values-aliased-text.md) · [Course index](index.md)
