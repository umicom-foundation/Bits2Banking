# Episode 97 — Inspect a computer without changing it

**Series:** Bits2Banking · System Administration From Zero  
**Duration:** approximately 8–14 minutes, depending on learner pauses  
**Audience:** absolute beginners and returning users  
**Course chapters:** 9, 10, 11, 12, 13, 14  
**Implementation policy:** interactive commands are demonstrations; no scripting-language application implementations.

## Teaching objective

Explain identity, processes, services, logs, hardware, storage and a verified copy using actual Umicom teaching situations. The demonstration must show the expected result and at least one plausible failure, rather than presenting commands without context.

## Preparation

- Open an ordinary Windows PowerShell 7 session; when covering Linux, use an authorised Linux terminal.
- Prepare a personal `$HOME\UmicomLearning` folder; do not edit real Umicom checkouts during the demonstration.
- Hide personal account names, tokens, machine serials, patient information and private IP addresses.
- Make the cursor and terminal font large enough for viewers of different ages and sight needs.

## Narration: opening (0:00–1:30)

> Today we are learning how to approach a computer problem so that we understand each command before typing it. You do not need previous programming knowledge. We will explain the terms, run one command at a time, and compare the output with the expected result. If an exercise cannot run on your computer, record it as not run rather than guessing.

## Demonstration sequence (1:30–7:30)

Show the progression: **`whoami` → `Get-Process` → `Get-Service` → `Get-WinEvent` → `Get-FileHash`**. For each transition explain which program owns the operation and whether it changes anything. A beginner should be able to answer: “Where am I, what will this do, and what should I see?”

Narration cue: **Observation is the default: record what you know before asking for permission to change anything.** Pause after each result so that learners can read it and compare it with the written chapter. Show one deliberate safe mistake such as running a command in the wrong practice directory, then recover using `Get-Location` or `pwd`. Do not create a production incident for demonstration.

## Guided exercise (7:30–10:30)

1. Ask the learner to explain the next command without looking at the notes.
2. Ask them to identify whether it is read-only or may alter files, accounts or network settings.
3. Demonstrate the command in a disposable practice environment.
4. Compare the observation with the expected output; record discrepancies.
5. Connect the lesson to the relevant Umicom Framework capability or contributor practice.

## Troubleshooting example (10:30–12:30)

A command returns an error because an expected tool or directory is missing. Do not bypass the error with force flags. First check the prompt and working directory, then look up the command with `Get-Command` or its documented equivalent. Review prerequisites and retry only the necessary safe step.

## Recap and learner questions

- What problem did the command solve?
- Which action in this lesson could modify files or publish data?
- What specific output would prove the operation worked?
- What would you report if the tool were unavailable?
- Which Umicom component should own reusable native functionality?

**Close:** Continue with the next course chapter and record the actual evidence in the practice workbook. No live Umicom repository, bank account or operating-system security setting needs to be changed for the lesson.
