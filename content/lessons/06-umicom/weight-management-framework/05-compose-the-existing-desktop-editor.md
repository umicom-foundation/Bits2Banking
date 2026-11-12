<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/weight-management-framework/05-compose-the-existing-desktop-editor.md

PURPOSE:
Reuse the native desktop form editor

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Reuse the native desktop form editor

## Before you begin
Read the form and persistence lessons. Use an existing qualified GTK4 application host and a Framework SDK with Umicom::structured_form_gtk4. This chapter studies the established editor; it does not introduce a new product layout.

## Keep the screen thin
The existing GTK4 editor consumes the same immutable schema as the C client. It owns its widget state, while the host decides where the editor appears and how a save operation is authorized.

~~~c
GtkWidget *editor = UmiStructuredFormGtk4New(umi_weight_log_schema(), initial);
if (editor == NULL) {
    /* Report creation refusal; do not attach an invalid widget. */
}
~~~

The returned widget follows the documented floating-reference contract. A real host must arrange its parent/reference ownership and keep the schema valid. The schema returned by the weight module is process-lifetime data.

1. Read include/umicom/ui/gtk4/structured_form.h.
2. Find the operations that apply the entire draft, copy a snapshot and acknowledge a saved revision.
3. Separate those operations from database persistence.
4. Keep the product's approved existing branding and form layout.

## Submit and close
UmiStructuredFormGtk4Apply(editor, 1) checks required fields before accepting a complete draft. UmiStructuredFormGtk4Snapshot then copies accepted state into caller-owned storage. The initial generated field uses canonical grams; it does not automatically become a kilogram control merely because the domain parser exists.

UmiStructuredFormGtk4CanClose also considers visible unapplied text. Destroying a widget is not a save operation. The host must obtain an explicit discard decision or finish an appropriate save workflow.

## Exercise and expected result
Trace a user typing an invalid date, pressing Save, then closing the window. The accepted model should stay intact after refusal, and the unsaved visible text should still affect close handling. Write down which call observes each state.

## Recovery
Retired or detached editors cannot be revived by calling Apply again. Stop pending callbacks before releasing host data, recreate a new editor from an explicitly selected snapshot, and never silently substitute a newer record.

A desktop qualification should check focus, keyboard access, visible errors, logo/icon resources and actual font fallback. Passing the headless C example establishes none of those UI properties.


[Course contents](index.md) · [Previous lesson](04-save-revisions-with-the-existing-record-service.md) · [Next lesson](06-connect-an-authorized-web-host.md)
