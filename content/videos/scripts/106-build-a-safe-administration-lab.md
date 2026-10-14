# Episode 106 — Build a Safe Administration Laboratory

**Bits2Banking · Umicom Foundation · Instructor-ready script**  
**Target running time:** 08:30.  
**Audience:** absolute beginners, returning learners and supervised younger students.  
**Recording rule:** Show only your own authorised practice computer or anonymised fictional output. No real bank, healthcare or production records.

## Learning objectives

- Introduce each concept in ordinary language before showing commands.
- Execute commands interactively in PowerShell 7 or Linux, never as newly introduced `.ps1` or `.py` implementation scripts.
- Explain what a correct observation proves and what remains unknown.
- Finish with a concrete exercise and a safe stopping point.

## On-screen preparation

Use the Stage 3 course lesson, its original SVG illustration and an ordinary PowerShell 7 terminal. Enlarge text for accessibility, avoid flashing or rapid transitions, caption the spoken commands and show any error message without cutting off the explanation. The instructor should prepare fictional sample output for environments in which commands are restricted.

## 00:00–01:10 — What counts as a safe experiment

**Narration / teaching notes:**

A system administrator is responsible for other people’s work as well as technical performance. We therefore begin by deciding what belongs inside our learning exercise. The host is the actual laptop; a guest is a virtual machine if one is available. We can learn useful principles without installing a VM. The safe practice folder under the current account is enough for this first lesson.

**Visual direction:** Keep the terminal output large. Highlight one important field or path at a time. If the next operation would require administrator access or a real setting change, demonstrate the *plan* rather than executing it.

## 01:10–02:50 — Open and recognise the correct shell

**Narration / teaching notes:**

Show the Start search results and explain Windows Terminal as a tabbed host, Windows PowerShell 5.1 as the older installed shell, and PowerShell 7 as pwsh. Use the ordinary shell without Run as Administrator. Type Get-Location and read the path; discuss what a directory is. On Linux compare a terminal window and the command pwd.

**Visual direction:** Keep the terminal output large. Highlight one important field or path at a time. If the next operation would require administrator access or a real setting change, demonstrate the *plan* rather than executing it.

## 02:50–04:45 — Use a private practice location

**Narration / teaching notes:**

Type Test-Path for the UmicomLearning folder and only then create the SysadminLab directory under the current account. Explain why we do not create a new project at the drive root or modify another user’s folder. Show a successful folder result and a deliberately printed not-found example, both labelled truthfully.

**Visual direction:** Keep the terminal output large. Highlight one important field or path at a time. If the next operation would require administrator access or a real setting change, demonstrate the *plan* rather than executing it.

## 04:45–06:25 — Make a baseline before change

**Narration / teaching notes:**

Run the simple OS and PowerShell version commands. Record a timestamp and note that some values may be private. Discuss why a before/after comparison is meaningful only if the same fields are checked under similar conditions.

**Visual direction:** Keep the terminal output large. Highlight one important field or path at a time. If the next operation would require administrator access or a real setting change, demonstrate the *plan* rather than executing it.

## 06:25–08:30 — Prove understanding

**Narration / teaching notes:**

Ask the viewer to name the host, guest, shell, working directory and rollback plan. Show the completed worksheet with observations separated from guesses, then invite them to continue to storage and backup exercises.

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
