<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/weight-management-framework/04-save-revisions-with-the-existing-record-service.md

PURPOSE:
Save a reviewed revision without losing a newer draft

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Save a reviewed revision without losing a newer draft

## Before you begin
Read the native client lesson and the existing Framework record-service guide. This chapter is a persistence integration exercise. The console example does not open a Data Server, authenticate a user or save records.

## Keep two revisions distinct
A form revision tracks editing. A record revision tracks storage history. An observation can have several draft edits before its first database revision exists.

~~~c
status = umi_structured_form_record_save(
    server, &metadata, umi_weight_log_schema(), form,
    expected_record_revision, &saved_record);
~~~

This integration fragment assumes a live authorized Data Server, reviewed metadata, a stable form and declared output. The existing service saves form content with its record metadata; do not create a parallel private file format inside each frontend.

1. Load or create the host's authorized record identity.
2. Capture the form revision being saved.
3. Use zero as the expected record revision only for a genuinely new entity.
4. After storage succeeds, acknowledge that captured form revision only if it still matches the current form.

## Worked race
Suppose the form is at edit revision 8 and storage head is 3. The host saves edit 8 with expected record revision 3. While it waits, the user creates edit 9. Storage may now return record revision 4. That does not make edit 9 saved.

umi_structured_form_mark_saved protects the current form against a mismatched acknowledgement. The host must keep edit 9 dirty and present the successful earlier save accurately.

## Exercise and expected result
Draw two columns for the sequence above. The storage column ends at 4; the current edit column ends at 9. State which values can be safely shown as saved. Then repeat with a competing writer who changes storage revision 3 before this request. The stale expected revision must be refused.

## Recovery
A lost response does not prove that a transaction failed. Reconcile the authorized record state before retrying a create. Retain the user's draft, the captured revision and the operation outcome separately. Do not log request bodies or notes to make recovery easier.

The existing record primitive does not encrypt data or authenticate an actor label. Those are real host requirements, not properties established by successful serialization. Personal-data deployment and cross-device synchronization remain separate work.


[Course contents](index.md) · [Previous lesson](03-edit-and-read-a-native-form.md) · [Next lesson](05-compose-the-existing-desktop-editor.md)
