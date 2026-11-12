<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/ui-values-aliased-text.md

PURPOSE:
Stage aliased text before replacing a display value

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../assets/branding/umicom-logo.svg)

# Stage aliased text before replacing a display value

## Recognize an input that belongs to the destination

An alias is another pointer to the same storage. In C, a function can receive a destination value and a text pointer that points inside that value. This is common when removing a path prefix or reusing part of an edited label. If the implementation clears the destination before reading the input, it destroys the source it was supposed to copy.


~~~c
UmiUiValue label;
UmiStatus status = umi_ui_value_set_string(&label, "prefix/Umicom");
if (status != UMI_STATUS_OK) return status;
status = umi_ui_value_set_string(&label, label.string_value + 7U);
if (status != UMI_STATUS_OK) return status;
~~~


The suffix begins after seven bytes. The successful result is the owned string Umicom. Framework stages the text in a temporary complete value, finds a terminator within the supported limit, and only then replaces label. The application does not need a second private string implementation or a temporary widget to make this operation safe.


## Treat capacity as part of admission

The field holds 512 bytes including the terminator. A maximum-length accepted string therefore has 511 nonzero bytes. This is not a count of user-visible characters: one encoded character may occupy several bytes. The value service copies bytes and does not make an encoding promise beyond the caller's own policy.


The refused-title scenario first stores integer 42, then tries to replace it with oversized text. CAPACITY_EXCEEDED must preserve the whole previous value, including its INTEGER kind. A failure that leaves a truncated STRING is a partial publication. It changes what observers see even though the caller was told the update was not accepted.


## Read the concrete laboratory observation

~~~powershell
.\build\btb-framework-ui-values.exe alias
.\build\btb-framework-ui-values.exe refused-title
~~~


These commands are supplied for owner execution. The first should print Title: Umicom. The second should report CAPACITY_EXCEEDED and Previous integer: 42. Exit zero describes the laboratory's successful observation of those expected outcomes; it does not mean oversized text was accepted.


## Extend the reasoning before extending the program

Draw the destination, the pointer into its string field and the temporary candidate. Mark the moment at which publication becomes safe. Then predict the result of passing label.string_value itself, a pointer to its terminating zero and a separate 511-byte string. Explain which cases succeed and why all failed cases leave the owner intact.


The caller must provide readable input through a terminator or the supported capacity. A bound does not make an arbitrary pointer readable. Do not demonstrate the rule by pointing beyond an allocation and hoping a zero appears. Use complete arrays and valid suffixes, then retain source, expected output and actual owner-run evidence separately.

## Source and practice

<!-- Previous source-tree links are retained for review; public repository routes
     below remain usable after the lesson is published.
[UI value laboratory and owner commands](../../../labs/native/framework-ui-values/README.md) · [HTML edition](../../courses/umicom-development/lessons/ui-values-aliased-text.html)
-->
[UI value laboratory and owner commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-ui-values/README.md) · [HTML edition](../../courses/umicom-development/lessons/ui-values-aliased-text.html)

[Previous lesson](ui-values-active-payload.md) · [Next lesson](ui-values-property-publication.md) · [Course index](index.md)
