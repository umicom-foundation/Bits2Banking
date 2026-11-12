<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-qt/19-utf8-ownership-and-zero-characters.md

PURPOSE:
Keep text ownership and byte boundaries explicit

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Keep text ownership and byte boundaries explicit

## Follow the lifetime

appendButton receives QString references and creates local QByteArray values with toUtf8. The C setters copy bytes into the temporary component specification before those byte arrays leave scope. The registry later copies the admitted specification. No pointer into a temporary Qt string is stored in the model. The rolesAndCopiedOwnership case changes the original Qt strings after insertion and checks that the model still returns the original values.

## Prevent hidden suffixes

~~~cpp
QString input = QStringLiteral("save");
input.append(QChar(0));
input.append(QStringLiteral("hidden"));
const UmiStatus status = model.appendButton(input, "Save");
// Expected: UMI_STATUS_INVALID_ARGUMENT; no new row.
~~~

A Qt string can contain a zero character inside its length. A terminated C string ends at that character. Without the explicit adapter check, the C function could see save while the caller supplied a longer value. This check translates between string representations; it does not replace the component validity policy.

## Count bytes, including the terminator

The component text field has 256 bytes. Its largest terminated value uses 255 data bytes. The test builds 127 copies of U+00E9, which need 254 UTF-8 bytes, then adds one ASCII character. That value fits. Adding one more ASCII character does not. The character count and byte count answer different questions. Framework setters enforce the destination capacity.

## Exercise and recovery

Change the boundary test to use a three-byte character and calculate the largest fitting combination before running it. On refusal, inspect the status and UTF-8 byte length rather than truncating the label silently. An application needing larger text should use an appropriate shared contract; changing only the Qt control limit does not enlarge the C record.

## Read the source

[labs/framework/qt-component-model/component_model.cpp](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/qt-component-model/component_model.cpp). Use the matching local revision when offline.

## Continue learning

[Course contents](../../../courses/learning-qt/index.html) · [Previous: Map registry records to rows and roles](18-map-registry-records-to-qt-roles.md) · [Next: Prepare an edit before publishing a Qt row](20-prepare-a-model-edit-before-notification.md)
