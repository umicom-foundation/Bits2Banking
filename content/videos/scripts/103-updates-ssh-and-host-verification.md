# Episode 103 — Plan an update and recognise an SSH host key

**Bits to Banking · Umicom Foundation · System Administration: From Zero**  
**Audience:** absolute beginners through returning professionals.  
**Suggested duration:** 9–15 minutes.  
**Lessons:** Chapters 29–30.  
**Executable project source:** C23 only; PowerShell and terminal lines are interactive teaching commands.

## Learning promise

Safe administration has a change window and two independent SSH trust decisions.

## Scene 1 — First question (0:00–1:30)

**On screen:** A clean learning environment, a terminal, and a clearly labelled example. No private names or real credentials are shown.

**Narrator:** “A professional administrator does not guess a solution from the first error message. First establish which computer, account, task and time are involved. We are going to learn the meaning of a few commands and then test our understanding with a harmless example.”

**Instructor note:** Do not rush through command prompts. Explain where to click, which program is open, and why the learner must not type the visual prompt prefix. Invite younger learners to pause and predict each result before entering a command.

## Scene 2 — Explain the mental model (1:30–4:00)

**On screen:** A vector illustration from the accompanying System Administration course. Follow the arrows one at a time, first describing the components in everyday language and then naming the proper engineering terms.

**Narrator:** “The important distinction is between what we can observe and what we can safely change. A service can be running while an application fails. A backup can exist without being restorable. A version-control repository can be clean without passing tests. We must be able to say which of these claims we have actually checked.”

## Scene 3 — Safe worked demonstration (4:00–9:00)

**Teaching plan:** Inspect `winget list --upgrade-available` without installing changes, then show `ssh -V` and an illustrative server fingerprint verification process. Never show or paste private keys.

The presenter reads and interprets each output, explicitly marks any unavailable command as “not verified”, and never switches to Administrator or root merely to eliminate a warning. For a filesystem example, use only `$HOME\UmicomLearning` or `$HOME/UmicomLearning`, never confidential source or patient files.

### Expected result

The learner can explain the purpose of the commands, the relevant operating-system differences and the information that remains unproven. An unsuccessful probe may still be a successful lesson if the outcome is recorded accurately.

## Scene 4 — Failure investigation (9:00–11:00)

**Narrator:** “A failed command contains information. Record the exact error and the step at which it occurred. It is not evidence that the whole system has failed, and it is never a reason to run a destructive cleanup command automatically.”

**Demonstration:** Show one benign missing-file or inaccessible-service example. Point to its cause, explain which facts can be confirmed without system modification, and pause before considering any change.

## Scene 5 — Reuse, safety and next steps (11:00–13:00)

**Learner challenge:** Describe why a changed host key is not safely repaired by deleting `known_hosts` blindly.

**Narrator:** “Our goal is a trustworthy explanation. The Umicom Framework owns reusable production functionality. We teach safe observations with native C23 experiments where code is needed. You can become an effective contributor by understanding and documenting a problem before attempting to change it.”

## Presenter checklist

- Demonstrate only authorised, non-sensitive environments.
- Show a real expected output and at least one possible failure outcome.
- Label Windows PowerShell, PowerShell 7 and Linux Bash correctly.
- Do not create `.ps1` or `.py` files; any executable educational code is C23.
- Do not silently edit or remove earlier lessons, comments or features.
- End by asking learners to explain the evidence in their own words.
