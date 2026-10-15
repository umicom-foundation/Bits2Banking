# Stage 6 instructor guide — from local commands to responsible remote support

**Course:** System Administration From Zero · Stage 6 · Chapters 73–84  
**Teaching duration:** Six to ten sessions of 30–60 minutes, adapted to age and prior experience.  
**Prerequisite:** Students can type commands and tell the difference between reading and changing system state.

## Teaching objectives

Learners should explain transport versus authentication versus authorisation; identify where a listener binds; distinguish SSH host and user keys; describe the risk of unverified host-key changes; recognise DNS/TCP/TLS/application failures; produce a short support timeline; and demonstrate a bounded C23 offline review with explicit failure cases.

## Lesson order and checkpoints

Sessions 1–2: Chapters 73–75, no network connections required. Ask students to identify the local host, `ssh` client and listener on their own machine. Session 3: Chapter 76, optional disposable key creation—verify the training path is outside Git and do not collect the private key. Sessions 4–5: Chapters 77–80, permissions matrix, firewall read-only inspection, DNS route ladder and HTTPS hostname verification. Session 6: Chapters 81–82, local integrity-copy exercise and a non-executable configuration proposal. Sessions 7–8: Chapters 83–84, support timeline, negative CTest cases and capstone report.

## Safety boundaries

Do not give students production remote server credentials, real patient/customer data or permission to change firewall rules. Hostnames ending in `.invalid` are illustrative and should not be used for live connection. A real instructor-provided VM, if used, must have clearly documented permission, student isolation, approved host-key fingerprint and an expiry/deprovisioning policy. No exercise requires Administrator/root by default.

The course's C23 tool merely evaluates caller-supplied fictional evidence. It never performs SSH, TLS, routing, deployment or human authorisation. **Never treat `REVIEWABLE` as “safe to log in.”**

## Assessment rubric

Use the [Stage 6 workbook](stage-6-workbook.md). Score concepts, safe command execution, honest recording of unsupported environments, and evidence-based conclusions. Penalise unsafe shortcuts even if they produce the expected output. Younger learners may draw the trust model, describe command output verbally and complete a supervised local-only exercise; older learners can submit a concise, fully redacted support incident report.

## Common misconceptions to correct

- A running process proves business readiness: false.
- A successful TCP connection proves server identity: false.
- A public SSH key provides remote permission: false; the host owner must authorise it.
- `ssh-keyscan` independently proves a host's key: false.
- `curl --insecure` is an ordinary certificate fix: false.
- An automatic green CTest count authorises a production change: false.
- A failed upgrade whose previous state was restored is a successful upgrade: false.

## Instructor evidence sheet

Record the actual teaching OS, shell, observed installed commands, number of tests run, sources used, student safety decisions and any blocked exercises. Keep private information out of public class reports. When a resource is unavailable, mark it *not run* rather than substitute an invented result.
