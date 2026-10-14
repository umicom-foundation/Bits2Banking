# Episode 109 — Why Running Does Not Mean Ready

**Bits2Banking · Umicom Foundation · Instructor-ready script**  
**Target running time:** 09:30.  
**Audience:** absolute beginners, returning learners and supervised younger students.  
**Recording rule:** Show only your own authorised practice computer or anonymised fictional output. No real bank, healthcare or production records.

## Learning objectives

- Introduce each concept in ordinary language before showing commands.
- Execute commands interactively in PowerShell 7 or Linux, never as newly introduced `.ps1` or `.py` implementation scripts.
- Explain what a correct observation proves and what remains unknown.
- Finish with a concrete exercise and a safe stopping point.

## On-screen preparation

Use the Stage 3 course lesson, its original SVG illustration and an ordinary PowerShell 7 terminal. Enlarge text for accessibility, avoid flashing or rapid transitions, caption the spoken commands and show any error message without cutting off the explanation. The instructor should prepare fictional sample output for environments in which commands are restricted.

## 00:00–01:20 — Define the precise question

**Narration / teaching notes:**

A process is running when the OS still manages its execution. A service is useful when it actually completes its purpose. A Notes window may be visible while file storage is inaccessible. Liveness and readiness describe different evidence.

**Visual direction:** Keep the terminal output large. Highlight one important field or path at a time. If the next operation would require administrator access or a real setting change, demonstrate the *plan* rather than executing it.

## 01:20–03:15 — Read service state safely

**Narration / teaching notes:**

Display a small sample of Get-Service and explain why a Stopped entry is not necessarily broken. Read one service configuration from Win32_Service and discuss service identity and dependencies. No restarts occur.

**Visual direction:** Keep the terminal output large. Highlight one important field or path at a time. If the next operation would require administrator access or a real setting change, demonstrate the *plan* rather than executing it.

## 03:15–05:15 — Connect a dependency chain

**Narration / teaching notes:**

Draw Notes document storage, application service and user request. A failed storage requirement must block a dependent Notes request even when the Notes process is present.

**Visual direction:** Keep the terminal output large. Highlight one important field or path at a time. If the next operation would require administrator access or a real setting change, demonstrate the *plan* rather than executing it.

## 05:15–07:20 — Run the C23 model

**Narration / teaching notes:**

Show the existing Update 39 observation library and the new Update 40 service-readiness demonstration. Run its native executable and explain that two READY services are fictional supplied data, not actual host findings.

**Visual direction:** Keep the terminal output large. Highlight one important field or path at a time. If the next operation would require administrator access or a real setting change, demonstrate the *plan* rather than executing it.

## 07:20–09:30 — Test failure honestly

**Narration / teaching notes:**

Run the inherited-block and stale named CTest cases. Both tests should PASS because the code correctly reports BLOCKED for unhealthy supplied evidence. Ask viewers to explain the difference between a passing test case and a ready business service.

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
