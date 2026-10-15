# Episode 136 — Two Computers, One Umicom Notes Service

**Bits to Banking · Umicom Foundation · Update 46**  
**Suggested length:** 9–13 minutes (adjust to class pace).  
**Related chapters:** 109–110.  
**Recording policy:** Use local, authorised practice machines and fictional Umicom Notes evidence. No real passwords, account details or production logs.

## Learning objective

A Windows laptop and two fictional Notes service hosts are not the same environment.

## Visual sequence and narration

### 00:00–01:30 — Define the problem

Narration: “Before touching a setting we need to know what is being reported, what the operating system actually checked and what remains unknown. A successful command is evidence only for the command's own operation.” Define unfamiliar words in plain English and draw them as separate boxes on the screen. Do not assume the audience has a GitHub account or previous administration experience.

### 01:30–05:00 — Demonstrate safely

Show Windows Terminal and a Linux terminal side-by-side. Use hostname and explicit date formats; then display a three-row inventory with source and verification columns.

When opening Windows Terminal, identify the **PowerShell 7** tab and demonstrate the difference between the prompt (`PS C:\...>`) and the text to type. On Linux show the terminal emulator, then the command shell. Pause after each command and read the meaningful fields. When a tool is unavailable or denies access, explain why **Not Run** is an honest answer.

### 05:00–08:00 — Work through the Umicom case

Ask viewers to identify which properties were observed on their own computer and which two service hosts remain fictional and unverified. Explain why a developer Git checkout cannot establish a remote installed release.

Do not infer business success from a green service icon. Add a table headed **Observed**, **Not observed**, **Failed**, **Next owner**. Explain the security boundary: read-only classroom queries are different from authorised administration of live machines.

### 08:00–10:00 — Guided learner pause

Ask viewers to write one paragraph explaining which fact was directly observed, which conclusion was inferred and which additional check would change their decision. Give at least 30 seconds of pause time in the recording. Demonstrate one safe way to preserve the work: a notes document under the student's own practice folder, without real personal information.

### 10:00–end — Recap and answers

The closing answer is an inventory with verified host identity only where evidence exists. Never ask the audience to probe an unauthorised host.

## Recording checklist

- Present original diagrams with readable labels and alt-text in the accompanying lesson.
- Commands are displayed separately for PowerShell and Linux; do not silently mix shells.
- Never show a real key, credential, private patient/customer record or unrestricted remote access.
- State when results are fictional or require a running optional lab.
- Finish with one short exercise from the corresponding chapter and direct the learner to the Stage 9 workbook.

**Next episode:** Continue the staged course; prior videos and captions remain unchanged.
