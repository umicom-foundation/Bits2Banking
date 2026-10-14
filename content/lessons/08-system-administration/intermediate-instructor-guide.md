# Instructor Notes — System Administration Part II

The intended learners range from younger students to professional returners. Do not use childish examples: every exercise is based on a realistic training workstation, notes application, website, support incident or Umicom development environment. Explain unfamiliar vocabulary before using it in tasks. Invite learners to predict a command's effect before running it.

## Teaching sequence

Each session should contain: (1) a five-minute concept explanation, (2) a demonstration on **throwaway training data**, (3) individually executed commands with output reviewed after each line, (4) one troubleshooting example, (5) a no-risk written assessment. The aim is comprehension, not speed.

## Safeguards

- Never require an actual Administrator or root login to pass a lesson.
- Do not publish screenshots exposing personal information, hostnames, tokens, SSH keys, patient data or customer records.
- Never ask learners to disable the firewall, grant broad ACL rights, format disks, or force-push history.
- For minors, remote access and software installs must be supervised; substitute instructor-provided screenshots when unavailable.
- If a Windows-only or systemd-only command does not exist, mark **not applicable**. Do not install a service manager simply to satisfy an exercise.
- Highlight the distinction between a script file and an interactive command: learners execute PowerShell lines, while the *delivered executable Umicom code* uses C23 or Assembly.

## Suggested timetable

- Week 5: Chapters 25–27: identity, ACLs and Windows services.
- Week 6: Chapters 28–30: Linux services, updates and SSH trust.
- Week 7: Chapters 31–33: networking, storage and recovery drills.
- Week 8: Chapters 34–36: security, incident investigation and handover.

For accessibility, use high-contrast slides, display commands in a monospace font, and avoid relying solely on colour to indicate failure. Allow text-only submissions where screenshots may reveal private information.
