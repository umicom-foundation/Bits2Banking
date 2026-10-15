# Stage 7 — Instructor and mentor guide

**Bits2Banking · Umicom Foundation · UK English**  
**Audience:** mixed ability, from first-time computer users to returning engineers. Use professional terminology, define it first, and never embarrass someone for a missing command or unfamiliar interface.

## Teaching philosophy

A good beginner course is not a list of commands to memorise. Introduce the *problem*, show a small *mental model*, demonstrate a safe *observation*, explain the *output*, give the learner a realistic *task*, and then challenge the learner to identify *what remains unverified*. Reuse the same Umicom Notes training scenario across chapters so new concepts attach to something familiar.

Keep software implementation examples in native C23 or Assembly when appropriate. PowerShell and Linux commands are interactive learning/administration instructions, **not new program implementation scripts**. All class source files retain comments, licences, authorship and existing functionality.

## Schedule suggestion

| Session | Chapters | Classroom objective | Time |
| --- | --- | --- | --- |
| 1 | 85–87 | Security goals; accounts and permissions | 75 min |
| 2 | 88–89 | Safe practice-file configuration and SHA-256 drift | 75 min |
| 3 | 90–91 | Patch plans and interpreting endpoint/firewall evidence | 65 min |
| 4 | 92–93 | Credential rotation planning and certificates | 65 min |
| 5 | 94–95 | Redacted incident timelines and independent restore checks | 75 min |
| 6 | 96 and 308–311 | Review capstone and optional C23 tests | 90 min |

Shorter sessions may be appropriate for younger students. The review worksheet works without CMake and can be completed before any source-code exercise.

## Demonstration rules

**Always show the difference between the prompt and the command.** On PowerShell, `PS C:\>` is part of the prompt and should not be typed. Explain that a pipeline `|` passes information between commands. Commands like `Select-Object -First 5` intentionally reduce output. On Linux, `head` also limits displayed lines; neither alters account records.

**Use personal training files only.** For Chapters 88, 89 and 95, prepare a folder below the learner's home directory and label files `notes-training.*`. Never ask a child or unsupervised novice to edit `/etc`, `C:\Windows`, production servers or family devices belonging to another person. Even harmless filesystem observations can expose identity information, so have learners use redacted values in shared worksheets.

**Demonstrate failure without bypassing controls.** If a tool is absent or access is denied, show how to record Not verified. Explain why disabling a firewall or turning off certificate validation is not a solution. Never request private passwords, secret keys, MFA codes or customer data from learners.

## Review the C23 laboratory

The Update 44 laboratory composes the previous five labs using their existing public APIs. Its tests are deterministic fictional cases, not real security compliance checks. Explain `BTB_SECURITY_REVIEWABLE`, `BLOCKED`, `PENDING`, and `RESTORED_ONLY`, and require learners to identify at least one missing-evidence bit. A pass in CTest means the model behaved as expected; it does not grant permission to administer a host.

If earlier update sources are absent, stop at the CMake prerequisite error and merge the correct package, rather than rebuilding a previous library from shortened sample code. Present actual toolchain and test results accurately. Windows acceptance is separate from Linux acceptance.

## Marking and correction

Use the Stage 7 workbook rubric. Reward precise uncertainty: a student who writes “I have not checked the restore procedure” demonstrates better engineering judgement than one who invents an affirmative result. Ask learners to revise overconfident statements to distinguish observation, decision, authority and uncertainty.

For a second attempt, let the student demonstrate each missing element independently. Avoid requiring administrator permissions or public GitHub publication to complete the course.

## Course boundaries

The existing *Creating a New Umicom Application* guide remains included in earlier batches. This Stage 7 course adds an operational perspective without modifying its source or inventing an implemented automatic-module-discovery tool. Umicom Framework is the authority for reusable security/observability/configuration functions; Bits2Banking only supplies education and offline simulations.
