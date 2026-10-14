# Episode 107 — A Backup Is Not Proven Until It Restores

**Bits2Banking · Umicom Foundation · Instructor-ready script**  
**Target running time:** 10:00.  
**Audience:** absolute beginners, returning learners and supervised younger students.  
**Recording rule:** Show only your own authorised practice computer or anonymised fictional output. No real bank, healthcare or production records.

## Learning objectives

- Introduce each concept in ordinary language before showing commands.
- Execute commands interactively in PowerShell 7 or Linux, never as newly introduced `.ps1` or `.py` implementation scripts.
- Explain what a correct observation proves and what remains unknown.
- Finish with a concrete exercise and a safe stopping point.

## On-screen preparation

Use the Stage 3 course lesson, its original SVG illustration and an ordinary PowerShell 7 terminal. Enlarge text for accessibility, avoid flashing or rapid transitions, caption the spoken commands and show any error message without cutting off the explanation. The instructor should prepare fictional sample output for environments in which commands are restricted.

## 00:00–01:15 — Why this matters

**Narration / teaching notes:**

A learner may believe that pressing Copy has created a backup. It has created a second file, but recovery has not been verified. Real backups must also account for separate storage, retention and access restrictions. Today we practise with a harmless fictional Notes document and never use private or production files.

**Visual direction:** Keep the terminal output large. Highlight one important field or path at a time. If the next operation would require administrator access or a real setting change, demonstrate the *plan* rather than executing it.

## 01:15–03:20 — Create one practice document

**Narration / teaching notes:**

Open PowerShell 7 as an ordinary user. Make a folder inside UmicomLearning/BackupLab/source; explain what $HOME means and why Set-Content replaces a file. Show the exact source file and warn viewers not to run it on an existing document with meaningful contents.

**Visual direction:** Keep the terminal output large. Highlight one important field or path at a time. If the next operation would require administrator access or a real setting change, demonstrate the *plan* rather than executing it.

## 03:20–05:20 — Copy, then compare

**Narration / teaching notes:**

Create a backup folder, copy the practice notes.txt into it and run Get-FileHash with SHA256 for both paths. Show the two outputs and explain that an equal digest is evidence for byte equality, not for accuracy of the note or future restore success.

**Visual direction:** Keep the terminal output large. Highlight one important field or path at a time. If the next operation would require administrator access or a real setting change, demonstrate the *plan* rather than executing it.

## 05:20–07:30 — Restore separately

**Narration / teaching notes:**

Create a restored folder and copy the backup into it. Open the restored document and compare its hash with the backup. Explain why copying back over the original too early can lose the last working evidence.

**Visual direction:** Keep the terminal output large. Highlight one important field or path at a time. If the next operation would require administrator access or a real setting change, demonstrate the *plan* rather than executing it.

## 07:30–10:00 — Understand the limits

**Narration / teaching notes:**

Draw the difference between local copies, independent backups and disaster recovery. Review RPO and RTO using the fictional Notes application. End with an exercise in which the learner records three paths, a matching hash and one risk that remains.

**Visual direction:** Keep the terminal output large. Highlight one important field or path at a time. If the next operation would require administrator access or a real setting change, demonstrate the *plan* rather than executing it.

## Practical viewer activity

Pause the video. Write down one command and explain it in plain English. Run it only if your own device permits the operation. Record a real result, an expected result and one limitation. A missing or blocked check is a valid observation, not a failure of the learner.

## Instructor checks

- Did the learner identify the active shell and current location before touching files?
- Did they distinguish an observation from a diagnosis?
- Did they avoid elevated commands and unapproved system changes?
- Did they explain how they would verify the result independently?

## Production boundary

The C23 example is educational and offline. All reusable real system services belong in existing Umicom Framework capabilities or an approved native Framework extension, not PowerShell, Python or duplicated application modules.

**Rights and credits:** Original educational narration for Umicom Foundation. Author/project lead: Sammy Hegab.
