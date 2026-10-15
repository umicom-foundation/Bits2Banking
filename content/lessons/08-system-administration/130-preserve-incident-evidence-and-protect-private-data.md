# Chapter 130 — Keep useful incident evidence without exposing private information

*System Administration From Zero · Stage 10 · Umicom Foundation*

When something breaks, people understandably want it fixed quickly. But clearing logs, reinstalling an application or restarting every service can remove the very information needed to understand the cause.

A **support incident** is an unexpected event that affects a service or user. **Incident evidence** is the information collected so people can reconstruct what happened. Good evidence is specific, dated and handled responsibly.

## What should an incident record contain?

A useful report begins with a plain description, not with a guess. For example:

> “At 10:15 local time, a user tried to save a fictional Umicom Notes document. The application displayed ‘Unable to save’. Other users have not yet been tested.”

This tells us the action, the time, the observed error and what is still unknown. It is better than “the server is broken”.

Then note the application version, computer name, relevant log entries, steps to reproduce and any recent approved changes. If there is a trace or correlation ID, preserve it because it may link a user action to a service request.

## Privacy matters even during an outage

A log can contain usernames, account numbers, file paths, customer names or other private data. Some diagnostic outputs may include access tokens or passwords if logging has been misconfigured. Do not post raw support bundles into a public repository, group chat or issue tracker.

Use authorised storage and access controls. Redact personal and secret information when sharing outside the approved team, while preserving the original evidence securely when required by policy. A redacted report should say what was removed and why.

## Create a safe practice incident record

Open PowerShell and create a file in your own practice area:

```powershell
New-Item -ItemType Directory -Force -Path "$HOME\UmicomLearning\Incident" | Out-Null
Set-Location "$HOME\UmicomLearning\Incident"
notepad .\incident-notes.txt
```

In Notepad, record a **fictional** issue with a date, symptom, exact error message, and what you checked. Save the document. To check its file identity later, type:

```powershell
Get-FileHash .\incident-notes.txt -Algorithm SHA256
```

The hash helps detect a byte-level change to the file. It is not proof that the statements inside the file are accurate; good evidence still depends on careful observation.

## What not to do

Do not share screenshots containing credentials, private messages or patient data. Do not alter a production system solely to reproduce a dangerous failure. Do not write conclusions such as “the database is faulty” unless evidence actually supports them.

**Exercise:** Rewrite “The bank application was slow because the server was bad” into two sentences: one fact and one hypothesis.

**Example answer:** “At 09:40, a test query took 12 seconds on the approved environment. The cause is not yet confirmed; the next check is the service and database timing evidence.”
