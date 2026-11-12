<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/ui-values-archive-admission.md

PURPOSE:
Validate every encoded field without confusing data with authority

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Validate every encoded field without confusing data with authority

## Follow the same contract into a record envelope

A reactive command parameter contains a UI value plus metadata. Change events contain both a before and an after value. Expression results also carry values. These envelopes should not maintain separate lists of recognized kinds. They reuse Framework's shared value admission before accepting or encoding an embedded payload.


The archive scenario initializes a command parameter, supplies a deliberately unsupported kind and tries to encode it. The expected result is INVALID_ARGUMENT before either the output bytes or reported size changes. The lab then replaces the malformed payload with integer 7 and asks the encoder to measure the required size.


~~~c
UmiUiReactiveCommandParameter parameter;
umi_ui_reactive_command_parameter_init(&parameter);
UmiStatus status = umi_ui_value_set_integer(&parameter.value, 7);
if (status != UMI_STATUS_OK) return status;
size_t required = 0U;
status = umi_ui_reactive_command_parameter_archive_encode(
    &parameter, NULL, 0U, &required);
~~~


## Distinguish measurement from publication

Passing a null byte buffer and zero capacity asks for the required encoded size. It does not save a file or execute the command represented by the data. A caller can allocate storage after measuring, then encode through the same public API. Check each status and keep output ownership explicit.


Generic value validation examines only the active payload. Archive validation can be stricter because the format may serialize inactive fields too. A scalar value with unterminated unused text may be acceptable as a current UI value but unacceptable as an archived envelope. Retaining the archive's terminator checks prevents a serializer from reading beyond that fixed field.


## Keep admission separate from domain execution

A recognized converter source kind does not prove a converter implementation is installed. A valid command parameter does not grant permission to execute a command. A saved expression result does not prove the expression ran against current dependencies. The archive transfers data; the responsible live service decides whether and how to adopt it.


| Check | Establishes | Does not establish |
| --- | --- | --- |
| Kind admission | Declared representation | Business meaning |
| Payload admission | Readable active data | Command permission |
| Archive validation | All encoded fields satisfy the format | Current live-service authority |
| Owner adoption | Service accepts a reviewed state change | Every later workflow succeeds |


## Practice a preservation assertion

Read the two sentinel arrays and size variable in ShowArchive. Explain why the lab compares all output bytes after refusal instead of checking only the error status. Then propose a malformed after-value for a change event. State which owner API should refuse it and which output must remain unchanged; do not write a replacement serializer in the application.


If an older installed SDK accepts the malformed record, preserve that observation with its source and installation identity. Update the matching Framework package through the owner workflow. Do not weaken the checker or label a later successful size measurement as proof that the earlier malformed input was correctly refused.

## Source and practice

<!-- Previous source-tree links are retained for review; public repository routes
     below remain usable after the lesson is published.
[UI value laboratory and owner commands](../../../labs/native/framework-ui-values/README.md) · [HTML edition](../../courses/umicom-development/lessons/ui-values-archive-admission.html)
-->
[UI value laboratory and owner commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-ui-values/README.md) · [HTML edition](../../courses/umicom-development/lessons/ui-values-archive-admission.html)

[Previous lesson](ui-values-reactive-revisions.md) · [Next lesson](ui-values-installed-qualification.md) · [Course index](index.md)
