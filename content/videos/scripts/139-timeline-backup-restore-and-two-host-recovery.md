# Episode 139 — Timeline, Backup Restore and Two-Host Recovery

**Bits to Banking · Umicom Foundation · Update 46**  
**Suggested length:** 9–13 minutes (adjust to class pace).  
**Related chapters:** 116–120.  
**Recording policy:** Use local, authorised practice machines and fictional Umicom Notes evidence. No real passwords, account details or production logs.

## Learning objective

Two log lines one minute apart cannot establish cause if clocks differ by three minutes.

## Visual sequence and narration

### 00:00–01:30 — Define the problem

Narration: “Before touching a setting we need to know what is being reported, what the operating system actually checked and what remains unknown. A successful command is evidence only for the command's own operation.” Define unfamiliar words in plain English and draw them as separate boxes on the screen. Do not assume the audience has a GitHub account or previous administration experience.

### 01:30–05:00 — Demonstrate safely

Show offset-aware date commands, the incident timeline diagram and a safe practice-file restoration into a separate home-directory folder. Use Get-FileHash or sha256sum to compare bytes.

When opening Windows Terminal, identify the **PowerShell 7** tab and demonstrate the difference between the prompt (`PS C:\...>`) and the text to type. On Linux show the terminal emulator, then the command shell. Pause after each command and read the meaningful fields. When a tool is unavailable or denies access, explain why **Not Run** is an honest answer.

### 05:00–08:00 — Work through the Umicom case

Present a scenario with an RPO target of 15 minutes, RTO of 30 minutes, measured loss of 20 minutes and restore duration of 24 minutes. Ask which objective failed.

Do not infer business success from a green service icon. Add a table headed **Observed**, **Not observed**, **Failed**, **Next owner**. Explain the security boundary: read-only classroom queries are different from authorised administration of live machines.

### 08:00–10:00 — Guided learner pause

Ask viewers to write one paragraph explaining which fact was directly observed, which conclusion was inferred and which additional check would change their decision. Give at least 30 seconds of pause time in the recording. Demonstrate one safe way to preserve the work: a notes document under the student's own practice folder, without real personal information.

### 10:00–end — Recap and answers

End by distinguishing a recovered previous release from success of the failed proposed release. Keep source logs and the original practice file intact.

## Recording checklist

- Present original diagrams with readable labels and alt-text in the accompanying lesson.
- Commands are displayed separately for PowerShell and Linux; do not silently mix shells.
- Never show a real key, credential, private patient/customer record or unrestricted remote access.
- State when results are fictional or require a running optional lab.
- Finish with one short exercise from the corresponding chapter and direct the learner to the Stage 9 workbook.

**Next episode:** Continue the staged course; prior videos and captions remain unchanged.
