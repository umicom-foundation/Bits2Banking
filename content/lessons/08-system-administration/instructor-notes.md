# Instructor guide — System Administration From Zero

**Purpose:** Deliver a technically accurate introduction to learners who may have never used a command line. Do not dilute technical accuracy, and do not rush ahead when foundational terms are not yet understood.

## Before class

1. Prepare a Windows 10/11 machine with a standard account and a Linux machine or authorised VM. Verify the shell versions with each learner.
2. Offer a text-based version of every image and read out the command before demonstrating it.
3. Demonstrate the difference between the command and the example output. Never expect a learner to type the `PS C:\...>` prompt.
4. Agree on a private practice folder in each learner's home directory; **do not** use real Umicom repositories for experiments.
5. Ensure optional software installations are authorised. Where they are not, do the chapter as a read-only demonstration.
6. Never ask learners to share tokens, passwords, patient data, private account numbers or sensitive logs.

## A repeatable 40-minute teaching pattern

- **5 minutes:** Explain the problem the new idea solves, with one realistic example.
- **8 minutes:** Draw or inspect one simple diagram; define unfamiliar words.
- **15 minutes:** Demonstrate the commands slowly, one by one. Ask learners to check the result after each step.
- **7 minutes:** Let learners repeat the steps and explain what they observed; support different screen readers and terminal font sizes.
- **5 minutes:** Review failures, explain when a result is unverified, and connect the topic to Umicom.

## Accessibility and age inclusivity

Use plain, professional language. Explain a term before using its abbreviation. Pair images with text alternatives. Do not assume that learners own administrator credentials, a powerful laptop or a paid development tool. Allow learners to complete Windows or Linux variants as appropriate. A competent adult returning to study and a young learner both deserve precise instruction.

## Safety boundaries

Practice never requires privileged system changes, public GitHub publication, force-push, recursive deletion, mass software upgrades or live financial execution. The person teaching decides whether an installation or remote account operation is permitted. Stop when an instruction does not match the learner's platform.

## Practical differentiation

- A learner with no previous experience should work through Chapters 1–8 and practise `pwd`, `Get-Location`, `Get-Content` and file previews.
- An experienced Windows user can compare PowerShell and Linux administration commands while explaining identity and privilege.
- A software engineer can complete the optional C23 lab and describe why the educational inspector cannot replace Umicom Framework file services.

## Assessment

Use the [workbook](workbook-and-assessment.md). Ask learners to provide the command, expected result, actual result, interpretation and one precaution. Distinguish **PASS**, **NEEDS HELP** and **NOT RUN**. Do not require screenshots of personal account identifiers.
