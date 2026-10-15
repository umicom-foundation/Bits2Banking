# Episode 140 — C23 Fleet Review: Pending, Blocked and Restored Only

**Bits to Banking · Umicom Foundation · Update 46**  
**Suggested length:** 9–13 minutes (adjust to class pace).  
**Related chapters:** 316–319.  
**Recording policy:** Use local, authorised practice machines and fictional Umicom Notes evidence. No real passwords, account details or production logs.

## Learning objective

Turn earlier independent C23 evidence reviews into one bounded two-host classroom decision.

## Visual sequence and narration

### 00:00–01:30 — Define the problem

Narration: “Before touching a setting we need to know what is being reported, what the operating system actually checked and what remains unknown. A successful command is evidence only for the command's own operation.” Define unfamiliar words in plain English and draw them as separate boxes on the screen. Do not assume the audience has a GitHub account or previous administration experience.

### 01:30–05:00 — Demonstrate safely

Open fleet_readiness.h, identify the four-host capacity and copied BtbOpsReview. Show CMake configure, build and CTest, then run btb-fleet-readiness-demo.

When opening Windows Terminal, identify the **PowerShell 7** tab and demonstrate the difference between the prompt (`PS C:\...>`) and the text to type. On Linux show the terminal emulator, then the command shell. Pause after each command and read the meaningful fields. When a tool is unavailable or denies access, explain why **Not Run** is an honest answer.

### 05:00–08:00 — Work through the Umicom case

Pause after each state: missing host yields PENDING; two complete fictional observations yield REVIEWABLE; failed Notes save yields BLOCKED; restored old release yields RESTORED_ONLY. Review the atomic-evaluate test.

Do not infer business success from a green service icon. Add a table headed **Observed**, **Not observed**, **Failed**, **Next owner**. Explain the security boundary: read-only classroom queries are different from authorised administration of live machines.

### 08:00–10:00 — Guided learner pause

Ask viewers to write one paragraph explaining which fact was directly observed, which conclusion was inferred and which additional check would change their decision. Give at least 30 seconds of pause time in the recording. Demonstrate one safe way to preserve the work: a notes document under the student's own practice folder, without real personal information.

### 10:00–end — Recap and answers

The demo is an offline policy exercise. It does not discover hosts, check live services, authorise access, stage releases or certify Umicom OS.

## Recording checklist

- Present original diagrams with readable labels and alt-text in the accompanying lesson.
- Commands are displayed separately for PowerShell and Linux; do not silently mix shells.
- Never show a real key, credential, private patient/customer record or unrestricted remote access.
- State when results are fictional or require a running optional lab.
- Finish with one short exercise from the corresponding chapter and direct the learner to the Stage 9 workbook.

**Next episode:** Continue the staged course; prior videos and captions remain unchanged.
