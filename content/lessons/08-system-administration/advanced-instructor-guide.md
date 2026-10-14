# Stage 3 Instructor Guide — Practical Infrastructure

**Audience:** volunteer tutors, school technology clubs, adult learning groups and Umicom contributor mentors. **Recommended approach:** discussion first, safe command second, evidence and reflection last.

## Safe teaching environment

1. Use a normal, non-elevated Windows PowerShell 7 shell or an authorised Linux account. If access to a command is restricted, teach the meaning of that refusal.
2. Do not request student accounts, passwords, personal machine serial numbers, full IP configurations, domain names or raw system logs in a shared classroom channel.
3. Practice files belong under `$HOME\UmicomLearning` on Windows or `$HOME/UmicomLearning` on Linux. Do not enter corporate, financial, school administration or healthcare data.
4. Screenshots should show only relevant fields. Redact usernames, hostname and network information before sharing outside the device.
5. A supervised younger learner may inspect a shared device only with its owner's explicit permission. **No system settings should be changed in this course.**

## Two-route delivery

**Beginner route:** Chapters 37–42, 45, 48. Use lab folders, Windows baseline, copy/hash/restore and discussion of services. Use teacher-supplied printed outputs for commands unavailable on a managed machine.

**Expanded route:** Chapters 37–48. Add Linux comparative exercises, IP/DNS/port explanation, firewall observation, update planning and incident timeline analysis.

## Assessment: learner demonstrates sound judgement

The objective is not memorisation. A satisfactory learner can explain what a command reads, show one verified observation, distinguish missing evidence from a pass, preserve a sample file, and ask for approval before making a system change. Encourage short notes with **command → observation → interpretation → uncertainty**.

## A staged 90-minute workshop

| Time | Activity | Evidence |
|---|---|---|
| 0–10 min | Identify shell and working directory | A redacted shell/location note |
| 10–25 min | Baseline operating system and storage | Three factual fields + timestamp |
| 25–45 min | Complete practice-file copy/hash/restore | Equal hashes and separate destination |
| 45–60 min | Distinguish process status and service readiness | A drawn dependency chain |
| 60–80 min | Work fictional Notes outage capstone | Timeline + READY/REVIEW/BLOCKED explanation |
| 80–90 min | Peer review and next step | One supported conclusion and one remaining question |

## Answer integrity

A learner who writes “NOT RUN — Windows cmdlet unavailable here” has met the reporting requirement when they explain why. Do not award invented green checks. Exercises are not operational authorisations and do not qualify actual Umicom production systems.

## Guide provenance

This stage reuses the established Bits2Banking curriculum and points to the existing *Creating a New Umicom Application* beginner guide delivered with Update 38. That original document should remain unchanged; its planned automatic-discovery design must not be presented as implemented code.
