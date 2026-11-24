<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/automated-testing-with-umicom/11-keep-startup-evidence-with-its-test-attempt.md

PURPOSE:
Keep startup evidence with its test attempt

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Keep startup evidence with its test attempt

Two people can start the same automated check at nearly the same time. If both checks write into one folder, a later reader needs to know which attempt owns the result. This exercise uses the hosted Umicom OS startup check to follow one folder, two attempts and four evidence files on paper.

## 1. Reserve the shared folder before writing

A **writer** is the process changing the files. A **lock** reserves a shared location for one cooperating writer at a time. In the startup check, the writer takes a lock before clearing earlier evidence or starting the console. It holds the lock while it writes this attempt’s evidence.

The four files describe different parts of the same attempt.

| File | What it holds |
| --- | --- |
| `stdout.txt` | Ordinary console output |
| `stderr.txt` | The diagnostic stream |
| `exit.txt` | The process result, or `not-started` while the process is still unrun |
| `inputs.umi` | The state of the input identity receipt |

The check starts these files as empty output, `not-started`, and `state=incomplete`. That tells a reviewer that a fresh attempt began and has more work to do. When the console returns, the check saves both streams and the process result before judging them. The final input record says `state=matched-observations` only after the output passes and both the selected executable and version header have the same fingerprints in the before-and-after observations.

## 2. Trace the second attempt

Draw a folder in the centre of a page. Place four cards inside it to stand for the existing files. Label the two check attempts A and B.

1. Give A the folder lock. Give the four file cards the label “A”.
2. Let B ask for the same folder. The check allows B up to five seconds to obtain the lock. In this exercise A holds it past that wait.
3. B reports `Cannot reserve Umicom OS startup evidence`. B never starts its console and leaves all four cards untouched.
4. Read B’s own test result to learn why B stopped. The folder contents still belong to A. Once the active attempt has finished, a later retry can acquire the folder and record its own attempt.

~~~text
REQUEST the shared startup evidence lock
IF the lock is unavailable within the wait
    REPORT contention and end this attempt
WRITE the new attempt's initial evidence
OBSERVE the input identities, run the check and record its output
PUBLISH matching input observations after the required checks
~~~

## 3. Check the evidence for the exact claim

The saved test uses a mocked console and made-up files. The test holds the lock, tries a second attempt and checks both that the mocked console was never called and that all four earlier files still match their saved bytes. An older implementation changed the four files in the matching comparison case. Running the four existing control cases separately checks that a valid attempt can finish, changed inputs receive a refusal, and a process error keeps its own captured result.

Try one more paper case. A completes successfully and `exit.txt` says 0. B fails to take the lock. Write two rows in your notes, one for A’s saved exit and one for B’s reservation failure. This distinction lets an automated testing dashboard show the correct attempt even when the same folder still contains an earlier successful result.

The fixture checks hosted startup evidence with a mock process. A boot or guest outcome comes from its own run and record.

[Course contents](index.md) · [Previous lesson · Keep the outer test total](10-keep-the-outer-test-total.md) · [Related lesson · Read a workflow summary](08-read-a-workflow-summary.md) · [Related lesson · Follow the first blocked boot service](../../06-umicom/umicom-os-from-scratch/69-follow-the-first-blocked-boot-service.md) · [Related lesson · Plan startup before executing it](../../06-umicom/umicom-os-from-scratch/03-service-dependencies.md) · [HTML edition](../../../courses/automated-testing-with-umicom/lessons/11-keep-startup-evidence-with-its-test-attempt.html)
