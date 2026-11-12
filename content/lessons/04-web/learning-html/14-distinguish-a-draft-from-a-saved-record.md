<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-html/14-distinguish-a-draft-from-a-saved-record.md

PURPOSE:
Explain draft, review and saved states

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Explain draft, review and saved states

## Before you begin
Read the request and text-rendering lessons. This exercise designs the status text around an existing form workflow; it does not add a database or claim that a mobile application is installed.

## Name the transition
A value typed into a field is a draft. A successful validation says that the draft obeys a schema. A saved acknowledgement says that a particular revision reached the storage boundary. These events can happen at different times.

~~~text
Editing revision 8
    -> review revision 8
    -> save request for revision 8
    -> user edits revision 9
    -> storage acknowledges revision 8
~~~

1. Write a status message for each step.
2. Keep revision 9 visibly unsaved after the final acknowledgement.
3. Offer a retry only after discovering whether the previous storage operation committed.
4. Keep the user's draft available when validation or storage refuses the request.

## A small presentation contract
Use an existing status region for a brief textual result. A disabled Save button during one request can reduce accidental repeats; it does not replace revision checks in the shared service.

~~~html
<p id="save-state" role="status">Draft has unsaved changes.</p>
~~~

This is a display fragment, not a functioning save handler. The host must connect it to actual request and storage results. Do not show Saved because a click handler ran or because an HTTP response had a body.

## Connect to Framework
The shared form has separate revision and saved_revision fields. umi_structured_form_mark_saved refuses an acknowledgement for a different current revision. Record persistence has its own expected record revision; the form's edit revision is not an interchangeable database version.

## Exercise and expected result
Trace the sequence above with two paper columns: current form revision and acknowledged form revision. The final values are 9 and 8. Explain why returning to revision 8 or marking revision 9 clean would lose the user's understanding of what is stored.

## Recovery
If a save response is lost, read the reviewed record state through the application's authorized recovery workflow before deciding to retry. Do not blindly issue a second create operation. If an old acknowledgement arrives late, preserve the newer draft and report the earlier saved version accurately.

Read include/umicom/application/experience/structured_form.h and include/umicom/data/structured_form_record.h for the existing native contracts. Actual browser announcements and focus behavior require UI qualification.


[Course contents](index.md) · [Previous lesson](13-display-untrusted-text-as-text.md) · [Next lesson](15-connect-field-errors-to-the-shared-contract.md)
