# Template — one-page fictional Umicom service runbook

Copy this Markdown template into **your own learning notes**. Do not place real names, login secrets, internal host addresses, customer details or patient information in public course material.

| Field | Example for fictional Notes service | Your practice entry |
|---|---|---|
| Service and environment | `NotesTraining` in an isolated teaching VM | |
| Release/source revision | 40-hex-character fictional Git SHA | |
| User-facing purpose | Open, edit and safely save practice notes | |
| Primary owner | Named training mentor (fictional) | |
| Backup owner | Another training mentor | |
| Daily check | Confirm disk and fresh save evidence | |
| Weekly check | Examine backup success evidence | |
| Monthly check | Independent restore rehearsal | |
| Maximum heartbeat age | 3 minutes in this *example policy* | |
| Capacity alert | Queue more than 5 work items | |
| RPO | 15 minutes (fictional requirement) | |
| RTO | 2 hours (fictional requirement) | |
| Change window | Saturday, fixed date and UTC time | |
| Approval and rollback | Ticket, checker, prior artifact available | |
| Data-handling rule | No secrets or personal data in course outputs | |

## During an incident

**Observed facts:** date/time + time zone, machine role, exact service revision, user impact, source of evidence and log correlation identifier.  
**Unknowns:** what has not been checked or cannot be accessed.  
**Next action:** who will investigate and by when.  
**Safety decision:** whether changes are permitted, or the incident must be escalated.  
**Closure:** a business-facing check and independent confirmation, not only a process restart.

## Review gate

Circle one for each requirement: **Verified / Missing / Failed / Not applicable (reason required)**. Missing evidence is not a pass. If a proposed release fails and the previous version is restored, explicitly report the proposed release **Failed**, with the service **Restored to previous state** only after independent verification.
