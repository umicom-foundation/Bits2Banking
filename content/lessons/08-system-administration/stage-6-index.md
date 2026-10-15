# System Administration From Zero — Stage 6
## Secure remote access, network services and support evidence

**Bits to Banking · Umicom Foundation · Chapters 73–84 · October 2026**

This stage builds on the existing 72-chapter course. It teaches **how to reason safely about remote administration** before trying to connect to another computer. It does not expect students to own a server, know Linux administration or have an SSH key. Most exercises inspect the current computer and write only in an expressly chosen private learning folder.

## Suggested progression

| Chapter | Topic | Practice outcome |
|---:|---|---|
| 73 | Remote administration boundaries | Name client, host, account, identity and authorisation. |
| 74 | TCP listeners and ports | Explain loopback and identify a local listener. |
| 75 | SSH host identity | Preview client configuration without connecting; refuse unknown host keys. |
| 76 | SSH key pairs | Create an optional disposable key in a private practice directory. |
| 77 | Least-privilege service identities | Distinguish human, service and support permissions. |
| 78 | Firewall policy | Observe profile/rules without opening ports. |
| 79 | DNS, routes and TCP | Diagnose failure by layer rather than guess. |
| 80 | TLS and HTTPS | Explain hostname matching, certificate validity and trust. |
| 81 | Controlled file transfer | Copy harmless data locally and compare SHA-256 hashes. |
| 82 | Service configuration | Draft a private, non-executable configuration review. |
| 83 | Incident evidence | Record a chronological, redacted support timeline. |
| 84 | Capstone | Produce a safe preflight report and run the offline C23 lab. |

## What the learner needs

A normal Windows PowerShell 7 terminal or an ordinary Linux shell, a text editor, and enough rights to read information about their own computer. SSH, Git, CMake and GCC are optional in the early lessons. Students who reach the C23 capstone need Updates 39–42 already merged with their preserved native labs.

**Never request or share real passwords, SSH private keys, account tokens, customer/patient files or full internal network inventories.** The examples use `notes.training.invalid`, a reserved fictional hostname. A real connection requires independently supplied permission and verified host identity.

## Practical goals

By the end, the student can differentiate transport reachability from authentication and business readiness; produce a non-sensitive evidence table; explain why an SSH host-key warning must not be ignored; and run deterministic C23 tests that deliberately reject missing observations. The lab's `REVIEWABLE` status is **not** a remote-access grant.

Continue with [Chapter 73](73-what-remote-administration-means.md) and keep the [Stage 6 workbook](stage-6-workbook.md) nearby.
